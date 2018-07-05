#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;

struct vertex
{
    float x;
    float y;
    float z;
};

int n;
vertex poly[20];
int edgemat[20][20];        //edge matrix
vertex temp[20];

draw_3dpoly(vertex temp[], int n, int edgemat[][20], int xc, int yc)
{
    for (int i=1; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (edgemat[i][j]==0)
                continue;
            line(temp[i].x+xc, temp[i].y+yc, temp[j].x+xc, temp[j].y+yc);
        }
    }
}

void sideview(int xc, int yc)
{
    //yz plane
    for (int i=0; i<n; i++)
    {
        temp[i].x = poly[i].z;
        temp[i].y = poly[i].y;
    }
    draw_3dpoly(temp, n, edgemat, xc, yc);
}

void frontview(int xc, int yc)
{
    //xy plane
    for (int i=0; i<n; i++)
    {
        temp[i].x = poly[i].x;
        temp[i].y = poly[i].y;
    }
    draw_3dpoly(temp, n, edgemat, xc, yc);
}

void topview(int xc, int yc)
{
    //xz plane
    for (int i=0; i<n; i++)
    {
        temp[i].x = poly[i].x;
        temp[i].y = -poly[i].z;
    }
    draw_3dpoly(temp, n, edgemat, xc, yc);
}

void isometricview(int xc, int yc)
{
    for (int i=0; i<n; i++)
    {
        temp[i].x = 0.707*poly[i].x - 0.707*poly[i].z;
        temp[i].y = -0.707*0.577*poly[i].x + 0.816*poly[i].y -0.577*0.707*poly[i].z;
    }
    draw_3dpoly(temp, n, edgemat, xc, yc);
}

void dimetricview(int xc, int yc)
{
    //for 1:1:k
    float k=0.5;
    float costh1= sqrt(2-k*k)/sqrt(2);;
    float sinth1= k/sqrt(2);
    float costh2= sqrt(2)/sqrt(2+k*k);
    float sinth2= k/sqrt(2+k*k);;
    for (int i=0; i<n; i++)
    {
        temp[i].x = costh1*poly[i].x - sinth1*poly[i].z;
        temp[i].y = -sinth1*sinth2*poly[i].x + costh2*poly[i].y -sinth2*costh1*poly[i].z;
    }
    draw_3dpoly(temp, n, edgemat, xc, yc);
}

void perspectiveview(int xc, int yc)
{
    //centre of projection
    vertex cop;
    cop.x = 10;
    cop.y = 10;
    cop.z = -200;
    for (int i=0; i<n; i++)
    {
        temp[i].x = (poly[i].x*(-cop.z)) / ((-cop.z) + poly[i].z);
        temp[i].y = (poly[i].y*(-cop.z)) / ((-cop.z) + poly[i].z);
    }
    draw_3dpoly(temp, n, edgemat, xc, yc);
}

void view()
{
    line(0,230,640,230);        //for 640 X 460 display
    line(212,0,212,460);
    line(424,0,424,460);

    sideview(106,115);
    frontview(318,115);
    topview(530, 115);
    isometricview(106,345);
    dimetricview(318,345);
    perspectiveview(530,345);
}

int main()
{
    int gd=DETECT, gm=0;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    cout<<"Enter no. of vertices of shape"<<endl;
    cin>>n;
    cout<<"Enter vertices (x,y,z) in order"<<endl;
    for (int i=0; i<n; i++)
        cin>>poly[i].x>>poly[i].y>>poly[i].z;

    cout<<"Enter edges"<<endl;
    for (int i=0; i<n; i++)
    {
        cout<<"For vertex no. "<<i<<":"<<endl;
        for (int j=0; j<i; j++)              //lower triangular matrix
        {
            cout<<"If vertex "<<i<<" is connected to vertex "<<j<<", enter 1, else enter 0:"<<endl;
            cin>>edgemat[i][j];
        }
    }

    view();

    char ch;
    cout<<"Enter any key to start rotation"<<endl;
    cin>>ch;
    //rotate
    float thrad = 3.14/180;          //rotate by 1 degree anticlockwise each time
    while(true)
    {
        cleardevice();
        //rotating around y axis
        for (int i=0; i<n; i++)
        {
            float x = poly[i].x;
            float y = poly[i].y;
            float z = poly[i].z;
            poly[i].x = cos(thrad)*x + sin(thrad)*z;
            poly[i].y = y;
            poly[i].z = -sin(thrad)*x + cos(thrad)*z;
        }
        view();
        delay(100);
    }

    getch();
    closegraph();
    return 0;
}
