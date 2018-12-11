
#include "TXLib.h"

const int Size = 3;

struct aKeyBoardControl
    {
    int left, up, right, down, space;
    };
class Vector
    {
    int x, y, xv, xy;
    };

struct aSharik
    {
    Vector v;
    COLORREF colorIn, colorOut;

    void Draw ();
    void Physic ();
    void KeyBoardControl (const aKeyBoardControl theControl);
    };

class aSnake // изменить
    {
    public:

    int len;
    aSharik shariki [Size];

    void Physic ();
    void KeyBoardControl (const aKeyBoardControl theControl);
    void Draw ();
    };
void Clamp (int val, int maxVal, int minVal);
void EatingFood ( aSharik* snake, int* len, aSharik* food); 
double CountDistance (aSharik ball1, aSharik ball2);

int main()
    {

    txCreateWindow (1000, 1000);

    txBegin ();

    HDC background  = txLoadImage ("Images\\background.bmp");
    if (!background)
        {
        txMessageBox ("Не могу загрузить фон из sample.bmp", "Нет, я не скопировал это из примера");
        }

    txBitBlt (0, 0, background);

    aSharik food = {rand() % 1000, rand() % 1000,   0,  0, RGB (255, 255, 255), RGB (255, 255, 255)};

    aSnake snake = {1, {{100, 100,   0,  0,  RGB (255,   0,   0), RGB (255, 128, 128)}}}; 



    aKeyBoardControl Player = {'A', 'W', 'D', 'S', 'X'};

   

    while (!GetAsyncKeyState (VK_ESCAPE) && snake.len != Size)
        {

        txBitBlt (0, 0, background);
        
        snake.shariki[0].KeyBoardControl (Player);

        snake.shariki[0].Physic ();
        
        food.Draw ();                

        EatingFood (&snake.shariki[0], &snake.len, &food);

        snake.Draw();

        cout << snake.len;

        txSleep (50);
        }

    txSelectFont ("Comic Sans MS", 150);
    txDrawText (100, 100, 900, 900, "You win !!!");


    txDeleteDC (background);
    return 0;
    }
//=============================================================
void aSnake :: Draw()
    {
    for (int i = 0; i < len; i++) shariki[i].Draw ();

    for (int i = len-1; i >= 0; i--) shariki[i+1] = shariki[i];
    }     
//=============================================================
void EatingFood (aSharik* snake, int* len, aSharik* food)  
    {
    if (CountDistance(*snake, *food) < 20)
        {
        food->x = rand() % 1000;
        food->y = rand() % 1000;

        *len = *len + 1;
        if (*len > Size) *len = Size;

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

void aSharik :: KeyBoardControl (const aKeyBoardControl theControl)
    {
    if (GetAsyncKeyState (theControl.right))
        {
        xv += 5;
        yv = 0;
        }

    if (GetAsyncKeyState (theControl.left))
        {
        xv -= 5;
        yv = 0;
        }

    if (GetAsyncKeyState (theControl.down))
        {
        yv += 5;
        xv = 0;
        }

    if (GetAsyncKeyState (theControl.up))
        {                  
        yv -= 5;
        xv = 0;
        }

    if (GetAsyncKeyState (theControl.space))
        {
        xv = yv = 0;
        }
    
    Clamp (&xv, 14, -14);
    Clamp (&yv, 14, -14);  

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
