#include "TXLib.h"

void DrawBall (double x, double y, COLORREF inColor, COLORREF outColor);
void Phisics (double* x, double* y, double* vx, double* vy);

int main ()
    {
    txCreateWindow (1000, 1000);

    txBegin ();

    double x = 100;
    double y = 100;
    double vx = 10;
    double vy = 5;



    while ( !(GetAsyncKeyState (VK_ESCAPE)))
        {
        txSetFillColor (TX_WHITE);
        txClear();

        DrawBall (x, y, TX_GREEN, TX_RED);
        Phisics (&x, &y, &vx, &vy);
        //printf ("���������� %lf %lf �������� %lf %lf \n", x, y, vx, vy);

        txSleep (50);
        }

    return 0;
    }

void DrawBall (double x, double y, COLORREF inColor, COLORREF outColor)
    {
    txSetFillColor (inColor);
    txSetColor (outColor);
    txCircle (x, y, 10);
    }

void Phisics (double* x, double* y, double* vx, double* vy)
    {
    *x += *vx;
    *y += *vy;

    if (*x >= 1000)
        {
        *x = 990;
        *vx = -*vx;
        }

    if (*y >= 1000)
        {
        *y = 990;
        *vy = -*vy;
        }

    if (*x <= 0)
        {
        *x = 10;
        *vx = -*vx;
        }

    if (*y <= 0)
        {
        *y = 10;
        *vy = -*vy;
        }

    }