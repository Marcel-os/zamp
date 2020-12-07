#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego obrót.
 *
 *  Klasa modeluje polecenie dla robota mobilnego, które wymusza jego obrót względem osi Z o zadany kąt z zadaną prędkością.
 */
class Interp4Rotate: public Interp4Command {
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
   * \brief Prędkość kątowa
   * zmienna zawiera informację o prędkości kątowej obrotu, jednostka: stopnie na sekundę.
   */
  double  _Speed_degS;
  /*!
   * \brief Kąt obrotu
   * zmienna zawiera informację o kącie obrotu, jednostka: stopnie.
   */
  double  _DegreeZ_deg;
 public:
  /*!
   * \brief
   */
  Interp4Rotate();  
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
