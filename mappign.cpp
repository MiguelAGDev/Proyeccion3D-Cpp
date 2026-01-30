#include "mappign.h"



//Mappign::Mappign() {}



/// Seteamos cada uno de los puntos de los extremos
/// en sus minimos y maximos que se tienen en el mundo real
void Mapping::setWindow(float Xw1, float Yw1, float Xw2, float Yw2)
{

    XwMin = Xw1;
    YwMin = Yw1;
    XwMax = Xw2;
    YwMax = Yw2;

}


/// Seteamos cada uno de los puntos de los extremos
/// en sus minimos y maximos que tenemos en el puerto
/// de vision
void Mapping::setViewPort(int Xvp1, int Yvp1, int Xvp2, int Yvp2)
{

    XvpMin = Xvp1;
    YvpMin = Yvp1;
    XvpMax = Xvp2;
    YvpMax = Yvp2;

}

/// Aplicamos el mapeo
void Mapping::applyMap(float Xw, float Yw, int &Xvp, int &Yvp, int L, int M)
{
    float Sx, Sy;

    /// Escalacion en X
    Sx = (XvpMax - XvpMin) / (XwMax - XwMin);
    cout<<"Escalacion en X: "<<Sx<<endl;
    /// Escalacion en Y
    Sy = (YvpMax - YvpMin) / (YwMax - YwMin);
    cout<<"Escalacion en Y: "<<Sy<<endl;

    /// LA POSICION CERO ES DESDE DONDE SURGE LA IMAGEN EN ESTE CASO
    /// XWcero = 0          XVPcero = 0
    /// YWcero = 0          YVPcero = alto del puerto de vision
    /// Posicion cero + (Escalacion * (PuntoW Actual -  Punto Minimo en W) + Punto minimo en VP)
    Xvp = int(round(Sx * (Xw - XwMin) + XvpMin + L));
    Yvp = int(round(Sx * (YwMin - Yw ) - YvpMin + M));


    // Xvp = int( L + round(XvpMin + Sx * (Xw - XwMin)));
    // Yvp = int( M - round(YvpMin + Sy * (Yw - YwMin)));


}
