#include "E:\Dima\TX\TXLib-20181218.h"
#include "Game.h"

int main ()
{  
  

    /*aSharik food = { rand() % 1000, rand() % 1000,   0,  0, RGB(255, 255, 255), RGB(255, 255, 255) };

    aSnake snake = { 1, {{100, 100}, {0, 0},  RGB(255,   0,   0), RGB(255, 128, 128)} };      

    aKeyBoardControl Player = { 'A', 'W', 'D', 'S', 'X' };                        */

    Game* game = new Game ();

    game -> Run ();
    game -> Finish ();

    return 0;
}