#include <iostream>
#include "Interp4Rotate.hh"

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
  return Interp4Rotate::CreateCmd();
}

/*!
 * \brief inicjalizuje wartości wejściowe.
 */
Interp4Rotate::Interp4Rotate(): _Speed_degS(0), _DegreeZ_deg(0)
{}

/*!
* \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
*/
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _NameObj << " " << _Speed_degS  << " " <<  _DegreeZ_deg << endl;
}

/*!
* \brief Wyświetla nazwę polecenia
*/
const char* Interp4Rotate::GetCmdName() const
{
  return "Rotate";
}

/*!
* \brief Wykonuje polecenie oraz wizualizuje jego realizację
*/
bool Interp4Rotate::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
* \brief Czyta wartości parametrów danego polecenia
*/
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _NameObj >> _Speed_degS >> _DegreeZ_deg;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate   object_name   rotation_speed[deg/s]   rotation_angleZ[deg]" << endl;
}
