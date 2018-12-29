#include "Sharik.h"

void aSharik::Draw()
{
 
txCircle (200, 200, 10);

}

aSharik::aSharik(Vector position, COLORREF fillColor, COLORREF lineColor)
{
_position = position;
_fillColor = fillColor;
_lineColor = lineColor;
}
