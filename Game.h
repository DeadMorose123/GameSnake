#include "Snake.h"
#include "E:\Dima\TX\TXLib-20181218.h"

const int LengthToWin = SnakeMaxLength;

class Game
    {
    private :
        aSnake* _snake;
        int _windowSize = 1000;
        aSharik* _food;
        HDC _background;


    public :
        Game ();
        void EatingFood ( aSnake* snake, aSharik* food);
        void Run ();
        void Finish ();
    };
