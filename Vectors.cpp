#include "Vectors.h"

void Vector::Draw(Vector vectorA, Vector vectorBase)
{
DrawSUPER (vectorA, vectorBase);
Vector vectorC = vectorA * 0.3;
Vector vectorD = {-vectorC.x, vectorC.y};
DrawSUPER (vectorC, vectorBase, TX_RED, 11);
DrawSUPER (vectorD, vectorBase, TX_YELLOW, 9);
DrawSUPER (vectorC + vectorD, vectorBase, TX_BLUE, 5);
}

void Vector::DrawSUPER(Vector vectorA, Vector vectorBase, COLORREF color, int size)
{
Vector vectorB = vectorA + vectorBase;
txSetColor(color, size);
txLine (vectorBase.x, vectorBase.y, vectorB.x, vectorB.y);
txCircle (vectorB.x, vectorB.y, 3);
}

Vector Vector::operator*(double val)
{
return {this -> x * val, this -> y * val}; 
}

Vector Vector::operator+(Vector vectorB)
{
 return {this -> x + vectorB.x, this -> y + vectorB.y}; 
}

Vector Vector::operator-(Vector vectorB)
{
return {this -> x - vectorB.x, this -> y - vectorB.y}; 
}
