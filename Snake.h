#include "Vectors.h"
#include "Keyboard.h"
#include "Sharik.h"
#pragma once
#include "E:\Dima\TX\TXLib-20181218.h"

const int SnakeMaxLength = 3;

class aSnake
    {
    private:
       aSharik* _shariki[SnakeMaxLength];

    public:
       double snakeLength;
       void Draw();
        aSharik* GetHead();
        aSnake (Vector position);
    };