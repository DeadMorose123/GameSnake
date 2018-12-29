#include "Snake.h"

void aSnake::Draw()
{
      for (int i = 0; i < snakeLength; i++) _shariki[i] -> Draw ();
}

aSharik* aSnake::GetHead()
{
    return _shariki[0];
}

aSnake::aSnake(Vector position)
{
_shariki[0] = new aSharik(position, RGB (255,   0,   0), RGB (255, 128, 128)); 
}
