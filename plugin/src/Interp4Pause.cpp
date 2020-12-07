#include <iostream>
#include "Interp4Pause.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
}


/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}

/*!
 * \brief inicjalizuje wartości wejściowe.
 */
Interp4Pause::Interp4Pause(): _Pause_ms(0)
{}

/*!
* \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
*/
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Pause_ms << endl;
}

/*!
* \brief Wyświetla nazwę polecenia
*/
const char* Interp4Pause::GetCmdName() const
{
  return "Pause";
}

/*!
* \brief Wykonuje polecenie oraz wizualizuje jego realizację
*/
bool Interp4Pause::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
* \brief Czyta wartości parametrów danego polecenia
*/
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _Pause_ms;
  return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}

/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause time[ms]" << endl;
}
