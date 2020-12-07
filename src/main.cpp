#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include <cstdio>
#include <sstream>
#include <string>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <list>

#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>

#define PORT 1885

int _Socket = 0;

using std::cout;
using std::cerr;
using std::endl;

using namespace std;
using namespace xercesc;

#define LINE_SIZE 500

bool ExecPreprocesor( const char *NazwaPliku, istringstream &IStrm4Cmds );

bool ExecActions( istream &rIStrm, Interp4Command &MoveInterp, Interp4Command &SetInterp, Interp4Command &RotateInterp, Interp4Command &PauseInterp);

bool ReadFile(const char* sFileName, Configuration &rConfig);

int Send(int Sk2Server, const char *sMesg);

bool OpenConnection(int &rSocket);


int main(int argc, char **argv)
{

  //wczytanie pliku XML z konfiguraca
  Configuration Config;
  if (!ReadFile("config/config.xml",Config)) return 1;

  int Socket4Sending;  

  if (!OpenConnection(Socket4Sending)) return 1;
  Send(Socket4Sending,"Clear\n");

    for(int i = 0; i < Config.sceneConfiguration.size(); i++ ){


      char size[Config.sceneConfiguration[i].size.length() +1];
      char color[Config.sceneConfiguration[i].color.length() +1];

      strcpy(size, Config.sceneConfiguration[i].size.c_str());
      strcpy(color, Config.sceneConfiguration[i].color.c_str());

      Send(Socket4Sending,"Cube ");
      Send(Socket4Sending, size);
      Send(Socket4Sending, " 0 0 0 ");
      Send(Socket4Sending, " 0 0 0 ");
      Send(Socket4Sending, color);
      Send(Socket4Sending,"\n");
    }

  Send(Socket4Sending,"Close\n");
  close(Socket4Sending);


  //komunikat bledu argumentow
  if(argc < 2){
    cerr << "Blad parametrow wejsciowych" << endl;
    return 1;
  }

  istringstream IStrm4Cmds;
  if(! ExecPreprocesor( argv[1] , IStrm4Cmds )){
    cerr << "Blad funkcji ExecPreprocesor()" << endl;
    return 2;
  }

  cout << IStrm4Cmds.str() << endl;

  void *pLibHnd_Move = dlopen("Interp4Move.so",RTLD_LAZY);
  void *pLibHnd_Pause = dlopen("Interp4Pause.so",RTLD_LAZY);
  void *pLibHnd_Set = dlopen("Interp4Set.so",RTLD_LAZY);
  void *pLibHnd_Rotate = dlopen("Interp4Rotate.so",RTLD_LAZY);

  Interp4Command *(*pCreateCmd_Move)(void);
  Interp4Command *(*pCreateCmd_Pause)(void);
  Interp4Command *(*pCreateCmd_Set)(void);
  Interp4Command *(*pCreateCmd_Rotate)(void);

  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }

  if (!pLibHnd_Pause) {
    cerr << "!!! Brak biblioteki: Interp4Pause.so" << endl;
    return 1;
  }

  if (!pLibHnd_Set) {
    cerr << "!!! Brak biblioteki: Interp4Set.so" << endl;
    return 1;
  }

  if (!pLibHnd_Rotate) {
    cerr << "!!! Brak biblioteki: Interp4Rotate.so" << endl;
    return 1;
  }

  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  pFun = dlsym(pLibHnd_Set,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Set = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  pFun = dlsym(pLibHnd_Pause,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Pause = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  pFun = dlsym(pLibHnd_Rotate,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Rotate = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  Interp4Command *MoveInterp = pCreateCmd_Move();
  Interp4Command *SetInterp = pCreateCmd_Set();
  Interp4Command *RotateInterp = pCreateCmd_Rotate();
  Interp4Command *PauseInterp = pCreateCmd_Pause();

  while(IStrm4Cmds){
      if(! ExecActions(IStrm4Cmds, *MoveInterp, *SetInterp, *RotateInterp, *PauseInterp) ){
      cerr << "Blad funkcji ExecActions()" << endl;
      return 3;
    }
  }

  // cout << "config:"<< Config.sceneConfiguration[0].name << endl;

  // cout << endl;
  // cout << pCmd->GetCmdName() << endl;
  // cout << endl;
  // pCmd->PrintSyntax();
  // cout << endl;
  // pCmd->PrintCmd();
  // cout << endl;
  
  // delete pCmd;

   dlclose(pLibHnd_Move);
   dlclose(pLibHnd_Set);
   dlclose(pLibHnd_Rotate);
   dlclose(pLibHnd_Pause);
}

bool ExecPreprocesor( const char *NazwaPliku, istringstream &IStrm4Cmds ) 
{
  string Cmd4Preproc = "cpp -P "; 
  char Line[LINE_SIZE]; 
  //ostringstream OTmpStrm;
  ostringstream OTmpStrm;

  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

  if (!pProc) return false;

  while (fgets(Line,LINE_SIZE,pProc)) 
  {
    OTmpStrm << Line;
  }

  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0; 
}

bool ExecActions( istream &rIStrm, Interp4Command &MoveInterp, Interp4Command &SetInterp, Interp4Command &RotateInterp, Interp4Command &PauseInterp)
{
  string CmdKey;
  rIStrm >> CmdKey;

  //cout << "Polecenie: " << CmdKey << endl;
  //rInterp.PrintSyntax();

  if(CmdKey == "Move"){
        if( !MoveInterp.ReadParams(rIStrm) ) return false;
        MoveInterp.PrintSyntax();
        cout << "\tWczytane Parametry:" << endl;
        MoveInterp.PrintCmd();
        //Doing some Move...
  }

  if(CmdKey == "Pause"){
      if( !PauseInterp.ReadParams(rIStrm) ) return false;
      PauseInterp.PrintSyntax();
      cout << "\tWczytane Parametry:" << endl;
      PauseInterp.PrintCmd();
      //Doing some Pause...
  }

  if(CmdKey == "Set"){
      if( !SetInterp.ReadParams(rIStrm) ) return false;
      SetInterp.PrintSyntax();
      cout << "\tWczytane Parametry:" << endl;
      SetInterp.PrintCmd();
      //Doing some Set...
  }

  if(CmdKey == "Rotate"){
      if( !RotateInterp.ReadParams(rIStrm) ) return false;
      RotateInterp.PrintSyntax();
      cout << "\tWczytane Parametry:" << endl;
      RotateInterp.PrintCmd();
      //Doing some Rotate...
  }

  return true;
}

bool ReadFile(const char* sFileName, Configuration &rConfig)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}

int Send(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}

bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}
