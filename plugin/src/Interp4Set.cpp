#include <iostream>
#include "Interp4Set.hh"

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
  return Interp4Set::CreateCmd();
}

/*!
 * \brief inicjalizuje wartości wejściowe.
 */
Interp4Set::Interp4Set(): _X(0), _Y(0), _DegreeZ_deg(0)
{}

/*!
* \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
*/
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _NameObj << " " << _X << " " << _Y << " " << _DegreeZ_deg << endl;
}

/*!
* \brief Wyświetla nazwę polecenia
*/
const char* Interp4Set::GetCmdName() const
{
  return "Set";
}

/*!
* \brief Wykonuje polecenie oraz wizualizuje jego realizację
*/
bool Interp4Set::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
* \brief Czyta wartości parametrów danego polecenia
*/
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _NameObj >> _X >> _Y >> _DegreeZ_deg;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set   object_name   X[m]  Y[m]  angle Z[deg]" << endl;
}
