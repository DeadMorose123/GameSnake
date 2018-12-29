#include "Game.h"

Game::Game()
{
    txCreateWindow(_windowSize, _windowSize);

    txBegin();

    _background = txLoadImage("Images\\background.bmp");

    if (!_background)
    {
        txMessageBox("Не могу загрузить фон из sample.bmp", "Нет, я не скопировал это из примера");
    };
    
    Vector snakePosition = {100, 100};
     _snake = new aSnake (snakePosition);
    Vector foodPosition = {rand() % _windowSize, rand() % _windowSize};
     _food = new aSharik (foodPosition, RGB (255, 255, 255), RGB (255, 255, 255));    

}

void Game::Run()
{

    while (!GetAsyncKeyState(VK_ESCAPE) && _snake -> snakeLength < LengthToWin)
    {

        txBitBlt(0, 0, _background);
        _food  -> Draw();
        //_snake -> Draw();  
     
        /*snake.shariki[0].KeyBoardControl(Player);

        snake.shariki[0].Physic();

        food.Draw();

        EatingFood(&snake.shariki[0], &snake.len, &food);

        snake.Draw();

        cout << snake.len;

        Vector vectorMouse = {txMouseX () - 100, txMouseY () - 100};

         Draw (vectorMouse, {100, 100}); */     

        txSleep(50);
    } 

}

void Game::Finish()
{
    txSelectFont("Comic Sans MS", 150);
    txDrawText(100, 100, 900, 900, "You win !!!");
    txSleep(1000);
    txDeleteDC(_background);    
}
