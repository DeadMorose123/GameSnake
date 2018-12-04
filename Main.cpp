
#include "TXLib.h"

const int Size = 100;

struct aSharik
    {
    int x, y, xv, yv;
    COLORREF colorIn, colorOut;

    void Draw ();
    void Physic ();
    };

struct aKeyBoardControl
    {
    int left, up, right, down, space;
    };

void Clamp (int* val, int maxVal, int minVal);
void KeyBoardControl (aSharik* theBall, const aKeyBoardControl theControl); //

void EatingFood ( aSharik* snake, int* len, aSharik* food); 
double CountDistance (aSharik ball1, aSharik ball2);
void DrawSnake (aSharik snake [], int len);

int main(){txCreateWindow (1000, 1000);}

int mmain()
    {

    txCreateWindow (1000, 1000);

    txBegin ();

    HDC background  = txLoadImage ("Images\\background.bmp");
    if (!background)
        {
        txMessageBox ("Не могу загрузить фон из sample.bmp", "Нет, я не скопировал это из примера");
        }

    txBitBlt (0, 0, background);

    aSharik snake[Size] = {{100, 100,   0,  0, RGB (255,   0,   0), RGB (255, 128, 128)}};

    int len = 1;

    aSharik food = {rand() % 1000, rand() % 1000,   0,  0, RGB (255, 255, 255), RGB (255, 255, 255)};

    aKeyBoardControl Player = {'A', 'W', 'D', 'S', 'X'};

   

    while (!GetAsyncKeyState (VK_ESCAPE))
        {

        txBitBlt (0, 0, background);
        for (int i = 0; i < len; i++) snake[i].Draw ();
        food.Draw ();

        for (int i = len-1; i >= 0; i--) snake[i+1] = snake[i];
        
        DrawSnake (snake, len);

        EatingFood (&snake[0], &len, &food);

        KeyBoardControl (&snake[0], Player);

        snake[0].Physic ();

        txSleep (50);
        }

    txDeleteDC (background);

    return 0;
    }
//=============================================================
void DrawSnake (aSharik snake [], int len)
    {
    for (int i = 0; i < len; i++) snake[i].Draw ();

    for (int i = len-1; i >= 0; i--) snake[i+1] = snake[i];
    }     
//=============================================================
void EatingFood (aSharik* snake, int* len, aSharik* food)  
    {
    if (CountDistance(*snake, *food) < 50)
        {
        food->x = rand() % 1000;
        food->y = rand() % 1000;

        *len = *len + 1;
        if (*len > Size - 1) *len = Size - 1;

        }
    } 
//=============================================================
double CountDistance (aSharik ball1, aSharik ball2)
    {
    return sqrt((ball1.x - ball2.x) * (ball1.x - ball2.x) +
                (ball1.y - ball2.y) * (ball1.y - ball2.y));
    }                  
//=============================================================
void Clamp (int* val, int maxVal, int minVal)
    {
    if (*val > maxVal)
        {
        *val = maxVal;
        }

    if (*val < minVal)
        {
        *val = minVal;
        }
    }
//=============================================================

void KeyBoardControl (aSharik* theBall, const aKeyBoardControl theControl) //!
    {
    if (GetAsyncKeyState (theControl.right))
        {
        theBall->xv += 5;
        theBall->yv = 0;
        }

    if (GetAsyncKeyState (theControl.left))
        {
        (*theBall).xv -= 5;
        (*theBall).yv = 0;
        }

    if (GetAsyncKeyState (theControl.down))
        {
        theBall->yv += 5;
        theBall->xv = 0;
        }

    if (GetAsyncKeyState (theControl.up))
        {                  
        theBall->yv -= 5;
        theBall->xv = 0;
        }

    if (GetAsyncKeyState (theControl.space))
        {
        theBall->xv = theBall->yv = 0;
        }
    
    Clamp (&theBall->xv, 14, -14);
    Clamp (&theBall->yv, 14, -14);

    }

//=============================================================

void aSharik :: Physic ()
    {
        if (x + xv >= 1000)
            {
            x = 999;
            xv = -(xv);
            }

        if (x - xv <= 0)
            {
            x = 1;
            xv = -(xv);
            }

        if (y - yv <= 0)
            {
            y = 1;
            yv = -(yv);
            }

        if (y + yv >= 1000)
            {
            y = 999;
            yv = -(yv);
            }

    x += xv;
    y += yv;
    }

//=============================================================

void aSharik :: Draw ()
    {
    txSetColor (colorOut);
    txSetFillColor (colorIn);
    txCircle (x, y, 10);

    }
