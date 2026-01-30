#include "cube3d.h"
#include "ui_cube3d.h"

cube3D::cube3D(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::cube3D)
{
    ui->setupUi(this);
    Tx = Ty = Tz = 0;
    alpha = 63.4F;
    phi = 30.0F;
    xc =254; yc =208; zc =50;

    fScaleX = fScaleY = fScaleZ = 1.0;
    angleX  = angleY = angleZ = 0.0f;
    assignCube();
}

cube3D::~cube3D()
{
    delete ui;
}

void cube3D::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    initializePort();
    projectCube();

}

void cube3D::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Right)
        Tx += 5;
    if(event->key() == Qt::Key_Left)
        Tx -= 5;
    if(event->key() == Qt::Key_Up)
        Ty += 5;
    if(event->key() == Qt::Key_Down)
        Ty -= 5;
    if(event->key() == Qt::Key_9)
        Tz += 5;
    if(event->key() == Qt::Key_0)
        Tz -= 5;

    //Escalacion
    if(event->key() == Qt::Key_R)
        fScaleX += 0;
    if(event->key() == Qt::Key_L)
        fScaleX -= 0;
    if(event->key() == Qt::Key_U)
        fScaleY += 0;
    if(event->key() == Qt::Key_D)
        fScaleY -= 0;
    if(event->key() == Qt::Key_P)
        fScaleZ += 0;
    if(event->key() == Qt::Key_E)
        fScaleZ -= 0;
    //rotacion
    if(event->key() == Qt::Key_X){
        angleX +=5.0;
        rotX = true; rotY = false; rotZ = false;
    }
    if(event->key() == Qt::Key_C){
        angleX -=5.0;
        rotX = true; rotY = false; rotZ = false;
    }


    if(event->key() == Qt::Key_Y){
        angleY +=5.0;
        rotX = false; rotY = true; rotZ = false;
    }
    if(event->key() == Qt::Key_T){
        angleY -=5.0;
        rotX = false; rotY = true; rotZ = false;
    }


    if(event->key() == Qt::Key_A){
        angleZ+=5.0;
        rotX = true; rotY = false; rotZ = true;
    }
    if(event->key() == Qt::Key_Z){
        angleZ -=5.0;
        rotX = true; rotY = false; rotZ = true;
    }

    repaint();
}

void cube3D::assignCube()
{

    Points3D cubeBase[] = {
        {37,75,0,0},{150,75,0,1},{150,112,0,1},
        {37,112,0,1},{37,75,0,1},{37,75,75,1},
        {150,75,75,1},{150,112,75,1},{150,112,0,1},
        {150,75,0,0},{150,75,75,1},{37,75,75,0},
        {37,112,75,1},{37,112,0,1},{37,112,75,0},
        {150,112,75,1},{75,112,75,0},

        {75,112,0,0},{112,112,0,1},{112,262,0,1},
        {75,262,0,1},{75,112,0,1},{75,112,75,1},
        {112,112,75,1},{112,262,75,1},{112,262,0,1},
        {112,112,0,0},{112,112,75,1},{75,112,75,0},
        {75,262,75,1},{75,262,0,1},{75,262,75,0},
        {112,262,75,1},{112,262,0,0},

        {37,262,0,0},{150,262,0,1},{150,300,0,1},
        {37,300,0,1},{37,262,0,1},{37,262,75,1},
        {150,262,75,1},{150,300,75,1},{150,300,0,1},
        {150,262,0,0},{150,262,75,1},{37,262,75,0},
        {37,300,75,1},{37,300,0,1},{37,300,75,0},
        {150,300,75,1},{75,300,75,0},

        {225,262,0,0},{337,262,0,1},{337,300,0,1},
        {225,300,0,1},{225,262,0,1},{225,262,75,1},
        {337,262,75,1},{337,300,75,1},{337,300,0,1},
        {337,262,0,0},{337,262,75,1},{225,262,75,0},
        {225,300,75,1},{225,300,0,1},{225,300,75,0},
        {337,300,75,1},{300,300,75,0},

        {262,75,0,0},{300,75,0,1},{300,262,0,1},
        {262,262,0,1},{262,75,0,1},{262,75,75,1},
        {300,75,75,1},{300,262,75,1},{300,262,0,1},
        {300,75,0,0},{300,75,75,1},{262,75,75,0},
        {262,262,75,1},{262,262,0,1},{262,262,75,0},
        {300,262,75,1},

        {412,75,0,0},{450,75,0,1},{450,300,0,1},
        {412,300,0,1},{412,75,0,1},{412,75,75,1},
        {450,75,75,1},{450,300,75,1},{450,300,0,1},
        {450,75,0,0},{450,75,75,1},{412,75,75,0},
        {412,300,75,1},{412,300,0,1},{412,300,75,0},
        {450,300,75,1},

        {450,75,0,0},{525,75,0,1},{525,112,0,1},
        {450,112,0,1},{450,75,0,1},{450,75,75,1},
        {525,75,75,1},{525,112,75,1},{525,112,0,1},
        {525,75,0,1},{525,75,75,1},{450,75,75,1},
        {450,112,75,1},{450,112,0,1},{450,112,75,1},
        {525,112,75,1},{450,525,75,0}
    };


    cube = new Points3D[117];

    for(int i = 0;i < 117; i++)
        cube[i] = cubeBase[i];

    initializePort();

    int xmin = cube[0].x, xmax = cube[0].x;
    int ymin = cube[0].y, ymax = cube[0].y;
    int zmin = cube[0].z, zmax = cube[0].z;

    for(int i = 1; i < 115; i++){
        xmin = std::min(xmin, cube[i].x);
        xmax = std::max(xmax, cube[i].x);

        ymin = std::min(ymin, cube[i].y);
        ymax = std::max(ymax, cube[i].y);

        zmin = std::min(zmin, cube[i].z);
        zmax = std::max(zmax, cube[i].z);
    }

    cX = (xmin + xmax) / 2;
    cY = (ymin + ymax) / 2;
    cZ = (zmin + zmax) / 2;

}

void cube3D::projectCube()
{
    canvas = new QPainter(this);
    canvas->setPen(QPen(Qt::white));
    canvas->drawLine(0, height - 1, width, height);
    canvas->drawLine(1,1,1,size().height());


    float zx1 = 0;
    float zy1 = 0;
    float zx2 = width* cos(qDegreesToRadians(phi));
    float zy2 = width* sin(qDegreesToRadians(phi));



    int x1,y1,x2,y2;
    map.applyMap(zx1, zy1, x1, y1,L,M);
    map.applyMap(zx2, zy2, x2, y2,L,M);

    canvas->drawLine(x1,y1,x2,y2);

    for(int i = 0; i < 117;i++){
        int x = cube[i].x;
        int y = cube[i].y;
        int z = cube[i].z;

        if(rotX){
            x = cube[i].x;
            y = (cube[i].y - cY)*cos(qDegreesToRadians(angleX))+(cube[i].z - cZ)*sin(qDegreesToRadians(angleX)) + cY;
            z = -(cube[i].y - cY)*sin(qDegreesToRadians(angleX))+(cube[i].z - cZ)*cos(qDegreesToRadians(angleX)) + cZ;
        }
        if(rotY){
            y = cube[i].y;
            x = cX + (cube[i].x - cX)*cos(qDegreesToRadians(angleY)) - (cube[i].z - cZ)*sin(qDegreesToRadians(angleY));
            z = cZ + (cube[i].x - cX)*sin(qDegreesToRadians(angleY)) + (cube[i].z - cZ)*cos(qDegreesToRadians(angleY));


        }
        if (rotZ){
            z = cube[i].z;
            x = cX + (cube[i].x - cX)*cos(qDegreesToRadians(angleZ)) - (cube[i].y - cY)*sin(qDegreesToRadians(angleZ));
            y = cX + (cube[i].x - cX)*sin(qDegreesToRadians(angleZ)) + (cube[i].y - cY)*cos(qDegreesToRadians(angleZ));
        }


        if(cube[i].option){
            lineTo3D(x + Tx,y +Ty,z + Tz,qDegreesToRadians(alpha),qDegreesToRadians(phi),i);
        }else{
            moveTo3D(x + Tx,y +Ty,z + Tz,qDegreesToRadians(alpha),qDegreesToRadians(phi),i);
        }
    }

    canvas->setPen(QPen(Qt::black,4));
    drawCube();
    canvas->end();

    this->setFocus();


}

void cube3D::drawCube()
{
    for(int i=0;i<116;i++)
    {
        if(cube[i+1].option){
            canvas->setPen(QPen(QColor(255, 255,255),3));
        }
        else{
            canvas->setPen(QPen(QColor(0,0,0, 0),3));
        }
        canvas->drawLine(points[i].x(),points[i].y(),points[i+1].x(),points[i+1].y());
    }
}

void cube3D::initializePort()
{
    width = this->size().width();
    height = this->size().height();

    map.setViewPort(0,0,width-200,height);
    map.setWindow(0,0,width-200,height);

    L = 0;
    M = height;

}

void cube3D::lineTo3D(int x, int y, int z, float alpha, float phi, int i)
{
    float xp, yp;
    int longitud;
    float tanalpha;
    if( (tanalpha = tan(alpha)) != 0)
        longitud = int(z/tanalpha);
    else
        longitud = 0;

    xp = x + longitud * cos(phi);
    yp = y + longitud * sin(phi);

    int x1, y1;
    map.applyMap(xp, yp, x1, y1,L,M);
    points[i].setX(x1);
    points[i].setY(y1);

    if(i==5){
        cout<<"Valores Calculados en lineTo3D "<<endl;
        cout<<"X1: "<<x1<<endl;
        cout<<"Y1: "<<y1<<endl;
    }

}

void cube3D::moveTo3D(int x, int y, int z, float alpha, float phi, int i)
{
    float xp, yp;
    int longitud;
    float tanalpha;
    if( (tanalpha = tan(alpha)) != 0)
        longitud = int(z/tanalpha);
    else
        longitud = 0;

    xp = x + longitud * cos(phi);
    yp = y + longitud * sin(phi);

    int x1, y1;
    map.applyMap(xp, yp, x1,y1,L,M);
    points[i].setX(x1);
    points[i].setY(y1);

    if(i==14){
        cout<<"Valores Calculados en MoveTo "<<endl;
        cout<<"X1: "<<x1<<endl;
        cout<<"Y1: "<<y1<<endl;
    }

}

void cube3D::scaling(int xc, int yc, int SX, int SY, int x, int y, int i)
{

    int DX = (x-xc)*SX;
    int DY = (y-yc)*SY;

    xScale = xc + DX;
    yScale = yc + DY;

    points[i].setX(xScale);
    points[i].setY(yScale);

}

void cube3D::on_alphaDial_valueChanged(int value)
{
    ui->alphaLCD->display(value);
    alpha = value;

    update();
}


void cube3D::on_phiDial_valueChanged(int value)
{
    ui->phiLCD->display(value);
    phi = value;

    update();
}

void cube3D::on_rotationAngleDial_valueChanged(int value)
{
    ui->rotationAngleLCD->display(value);

    if(ui->xRotation->isChecked())
        rotX = value;
    else if(ui->xRotation->isChecked())
        rotX = value;
    else if(ui->xRotation->isChecked())
        rotX = value;

    update();

}

