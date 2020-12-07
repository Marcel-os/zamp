#ifndef WEKTOR3D_HH
#define WEKTOR3D_HH


#include <cassert>


/*!
 * \brief Symbol definiuje wymiarowi przestrzeni 3D
 *
 * Symbol odpowiada wymiarowi przestrzeni 3D.
 * Celem wprowadzenia definicji jest posiadanie w kodzie 
 * wpisu, który ma czytelną interpretację.
 */
#define WYMIAR3D    3

/*!
 * \brief Wektor z przestrzeni 3D
 */
class Wektor3D {
   double _Wsp[WYMIAR3D];

 public:  
  /*!
   * \brief Inicjalizuje współrzędne wektora wartościami 0.
   */
  Wektor3D() { for (double &Wsp : _Wsp)  Wsp = 0; }

  /*!
   * \brief Udostępnia do odczytu współrzędną o podanym indeksie.
   * 
   * Udostępnia do odczytu współrzędną o podanym indeksie.
   * Metoda nie ma kontroli wartości współrzędnej. Na potrzeby
   * debugowania jest w kodzie tylko asercja.
   *
   * \param[in]  Idx - indeks wybranej współrzędnej.
   *
   * \pre 0 <= Idx && Idx < WYMIAR3D
   */
  double operator [] (int Idx) const 
     { assert(0 <= Idx && Idx < WYMIAR3D); return _Wsp[Idx]; }
  /*!
   * \brief Udostępnia do modyfikacji współrzędną o podanym indeksie.
   * 
   * Udostępnia do modyfikacji współrzędną o podanym indeksie.
   * Metoda nie ma kontroli wartości współrzędnej. Na potrzeby
   * debugowania jest w kodzie tylko asercja.
   *
   * \param[in]  Idx - indeks wybranej współrzędnej.
   *
   * \pre 0 =< Idx && Idx < WYMIAR3D
   */
  double& operator [] (int Idx) { return _Wsp[Idx]; }

  /*!
   * \brief Udostępia do odczytu współrzędną x-ową.
   */
  double x() const { return _Wsp[0]; }
  /*!
   * \brief Udostępia do modyfikacji współrzędną x-ową
   */
  double& x() { return _Wsp[0]; }

  /*!
   * \brief Udostępia do odczytu współrzędną y-ową.
   */
  double y() const { return _Wsp[1]; }
  /*!
   * \brief Udostępia do modyfikacji współrzędną y-ową.
   */
  double& y() { return _Wsp[1]; }

  /*!
   * \brief Udostępia do odczytu współrzędną z-ową.
   */
  double z() const { return _Wsp[2]; }
  /*!
   * \brief Udostępia do modyfikacji współrzędną z-ową.
   */
  double& z() { return _Wsp[2]; }
};


#endif
