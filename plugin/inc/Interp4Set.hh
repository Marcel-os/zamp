#ifndef  COMMAND4SET_HH
#define  COMMAND4SET_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które ustawia obiekt w określonej pozycji.
 *
 *  Klasa modeluje polecenie dla robota mobilnego, które ustawia obiekt w określonej pozycji zadanej współrzędnymi oraz kątem obrotu względem osi Z.
 */
class Interp4Set: public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */

  /*!
   * \brief Nazwa obiektu
   * string zawiera nazwę obiektu
   */
  std::string _NameObj;
  /*!
   * \brief Współrzędna X
   * zmienna zawiera informację o współrzędnej X, jednostka: metr.
   */
  double  _X;
  /*!
   * \brief Współrzędna Y
   * zmienna zawiera informację o współrzędnej Y, jednostka: metr.
   */
  double  _Y;
  /*!
   * \brief kąt obrotu względem osi Z
   * zmienna zawiera informację o kącie obrotu względem osi Z, jednostka: stopień.
   */
  double  _DegreeZ_deg;
 public:
  /*!
   * \brief
   */
  Interp4Set();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd( DronPose  *pRobPose,   Visualization *pVis) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
