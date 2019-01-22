#pragma once
#include "Vectors.h"
#include "Keyboard.h"
#include "Sharik.h"
#include "E:\Dima\TX\TXLib-20181218.h"

const int SnakeMaxLength = 3;

class aSnake
    {
    private:
       aSharik* _shariki[SnakeMaxLength];

    public:
      int snakeLength;

      aSnake (Vector position);

      aSharik* GetHead(); 
      void DeleteShariks();
      void Draw();   
    };