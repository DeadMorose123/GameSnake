#pragma once
#include "Vectors.h"
#include "Keyboard.h"
#include "E:\Dima\TX\TXLib-20181218.h"

class aSharik
    {
    private :
        Vector _position;
        Vector _velocity;
        COLORREF _fillColor, _lineColor;
     public :
        void Draw();
        aSharik (Vector position, COLORREF fillColor, COLORREF lineColor);
    };