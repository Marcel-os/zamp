#include <iostream>
#include "Interp4Move.hh"

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
  return Interp4Move::CreateCmd();
}


/*!
 * \brief inicjalizuje wartości wejściowe.
 */
Interp4Move::Interp4Move(): _HorSpeed_ms(0), _Distance_m(0)
{}

/*!
* \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
*/
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _NameObj << " " << _HorSpeed_ms << " " << _Distance_m << endl;
}

/*!
* \brief Wyświetla nazwę polecenia
*/
const char* Interp4Move::GetCmdName() const
{
  return "Move";
}

/*!
* \brief Wykonuje polecenie oraz wizualizuje jego realizację
*/
bool Interp4Move::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
* \brief Czyta wartości parametrów danego polecenia
*/
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  Strm_CmdsList >> _NameObj >> _HorSpeed_ms >> _Distance_m;
  return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
* \brief Wyświetla składnię polecenia
*/
void Interp4Move::PrintSyntax() const
{
  cout << "   Move   object_name   hor_speed[m/s]   dist[m]" << endl;
}
