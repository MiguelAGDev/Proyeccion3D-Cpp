#ifndef MAPPING_H
#define MAPPING_H
#include <iostream>
using namespace std;

class Mapping
{
    //// Posciones X y Y que se producen en el mundo real
    /// Window <----> Ventana
    float XwMin, YwMin, XwMax, YwMax;

    /// Posiciones X y Y dentro del puerto de vision
    /// (dispositovo donde vemos la ventana)
    /// ViewPort <------> Puerto de Vision
    int XvpMin, YvpMin, XvpMax, YvpMax;

public:
    //Mapping();

    /// Funcion para redondear
    int round(float n){return n + 0.5;}

    /// Setea los valores de la ventana del mundo real, donde va desde
    /// (xw1, yw1) hasta (xw2, yw2). Este mismo se comenzando con la esquina
    /// superiro izquierda , hacia la esquina inferior derecha. Algo asi:
    ///
    ///   |
    /// ─ + ────────────────────────>
    ///   │ ┌───
    ///   │ │  ╱
    ///   │ │ ╱
    ///   │ │╱
    ///   │
    ///   │
    ///   │
    ///   │
    ///   │
    ///   │
    ///   v
    void setWindow(float Xw1, float Yw1, float Xw2, float Yw2);

    /// Setea el puerto de vision, esta es la ventana fisica (dispositovo) desde
    /// donde visualizamos la imagen. Este comienza en (Xvp1, Yvp1) hasta (Xvp2, Yvp2).
    /// Comienza desde la esquina inferior izquierda hasta la esquina superior derecha
    /// Se dibuja de la siguiente materia:
    ///
    ///   ^
    ///   │
    ///   │
    ///   │
    ///   │
    ///   │
    ///   │
    ///   │ │╲
    ///   │ │ ╲
    ///   │ │  ╲
    ///   │ └───
    /// ─ + ────────────────────────>
    ///   │
    void setViewPort(int Xvp1, int Yvp1, int Xvp2, int Yvp2);


    /// Esto aplica transformacion de la window al puerto de vision
    /// trasformando cada posicion de un punto W a un punto Vp
    void applyMap(float Xw, float Yw, int &Xvp, int &Yvp, int L, int M);
};

#endif // MAPPING_H


