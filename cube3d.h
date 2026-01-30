#ifndef CUBE3D_H
#define CUBE3D_H

#include <QDialog>
#include <QWidget>
#include <QWidget>
#include <QPainter>
#include <QtGui>
#include <QKeyEvent>

#include "mappign.h"




QT_BEGIN_NAMESPACE
namespace Ui {
class cube3D;
}
QT_END_NAMESPACE



struct Points3D{


    /// POSICIONES DE LA MATRIZ
    int x,
        y,
        z;

    /// AQUIE DECLARAEMOS SI ES UN PUNTO
    /// O ES UNA LINEA
    bool option;

    /// | x1  y1  z1  opc|
    /// | x2  y2  z2  opc|
    /// | x3  y3  z3  opc|
    /// | x4  y4  z4  opc|


};


class cube3D : public QDialog
{
    Q_OBJECT

public:
    cube3D(QWidget *parent = nullptr);
    ~cube3D();

    void paintEvent(QPaintEvent *e);

    void keyPressEvent(QKeyEvent *event);

    void assignCube();

    void projectCube();

    void drawCube();

    void initializePort();

    void lineTo3D(int x, int y, int z, float alpha, float phi, int i);

    void moveTo3D(int x, int y, int z, float alpha, float phi, int i);

    void scaling(int xc, int yc, int SX, int SY, int x, int y, int i);





private slots:
    void on_alphaDial_valueChanged(int value);

    void on_phiDial_valueChanged(int value);


    void on_rotationAngleDial_valueChanged(int value);

private:
    Ui::cube3D *ui;

    QPainter *canvas;
    QPointF points[117]; // Arreglo donde se guardan los Strucs
    Points3D *cube; // Declaracion del objeto cubo para utilizar el struct
    Mapping map; // Para aplicar el mapeo
    int L, M; // L y M del puerto de vision, desde donde se generara el dibujo
    double alpha = 63.4F,// Angulo de construccion de profundidad
        phi = 30.0F; // Son los angulos de rotacion
    int width, height; // Tamano del area de dibujo
    int xc, yc, zc; // Centro del cubo

    // MOVIMIENTO
    int Tx, Ty, Tz; // Variabes de translaxcino

    // ESCALACION
    int Sx, Sy, Sz, xScale, yScale;
    int cX, cY, cZ; // ESCALACION CENTRO
    float fScaleX, fScaleY, fScaleZ; // FACTORES DE ESCALACION

    // ROTACION
    bool rotX, rotY, rotZ; // Banderas de rotacion, para saber si rota en x, y o z
    double angleX, angleY, angleZ; // Angulo de rotacion

};
#endif // CUBE3D_H
