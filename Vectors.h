#pragma once
#include "E:\Dima\TX\TXLib-20181218.h"

 struct Vector
    {
    double x, y;
    void Draw (Vector vectorA, Vector vectorBase = Vector {0, 0});
    void DrawSUPER (Vector vectorA, Vector vectorBase = Vector {0, 0}, COLORREF color = TX_BLACK, int size = 3);

    Vector operator* (double val);
    Vector operator+ (Vector vectorB);
    Vector operator- (Vector vectorB);
    };




