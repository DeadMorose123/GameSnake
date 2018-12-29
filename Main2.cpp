//#include "Vectors.h"
//
//const int Size  = 3;
//const double Dt = 1;                   
//
//struct aKeyBoardControl
//    {
//    int left, up, right, down, space;
//    };
//
//
//
//struct aSharik
//    {
//    Vector pos;
//    Vector v;
//    COLORREF colorIn, colorOut;
//
//    void Draw ();
//    void Physic ();
//    void KeyBoardControl (const aKeyBoardControl theControl);
//    };
//
//struct aSnake
//    {
//    double length;
//    aSharik shariki [Size];
//
//    void Physic ();
//    void KeyBoardControl (const aKeyBoardControl theControl);
//    void Draw ();
//    aSharik GetHead ();
//    };
//
//
//void Clamp (double* val, double maxVal, double minVal);
////void EatingFood ( aSharik* snake, double* len, aSharik* food);
//void EatingFood ( aSnake* snake, aSharik* food); 
//double CountDistance (aSharik ball1, aSharik ball2);
//
//int main()
//    {
//
//    txCreateWindow (1000, 1000);
//
//
//    txBegin ();
//
//    HDC background  = txLoadImage ("Images\\background.bmp");
//    if (!background)
//        {
//        txMessageBox ("Не могу загрузить фон из sample.bmp", "Нет, я не скопировал это из примера");
//        }
//
//    aSharik food = {rand() % 1000, rand() % 1000,   0,  0, RGB (255, 255, 255), RGB (255, 255, 255)};
//
//    aSnake snake = {1, {{100, 100}, {0, 0},  RGB (255,   0,   0), RGB (255, 128, 128)}}; 
//
//    aKeyBoardControl Player = {'A', 'W', 'D', 'S', 'X'};
//
//    while (!GetAsyncKeyState (VK_ESCAPE) && snake.length != Size)
//        {
//
//        txBitBlt (0, 0, background);
//        
//        snake.shariki[0].KeyBoardControl (Player);
//
//        snake.shariki[0].Physic ();
//        
//        food.Draw ();                
//
//        EatingFood (&snake.shariki[0], &snake.length, &food);
//
//        snake.Draw ();
//
//        cout << snake.length;          
//        
//       /* Vector vectorMouse = {txMouseX () - 100, txMouseY () - 100}; 
//
//        Draw (vectorMouse, {100, 100});      */
//
//        txSleep (50);
//        }
//
//    txSelectFont ("Comic Sans MS", 150);
//    txDrawText (100, 100, 900, 900, "You win !!!");
//
//
//    txDeleteDC (background); 
//
//    
//
//    return 0;
//    }
////=============================================================
//aSharik aSnake :: GetHead ()
//    {
//    return shariki[0]; 
//    } 
////=============================================================
//void aSnake :: Draw()
//    {
//    for (int i = 0; i < length; i++) shariki[i].Draw ();
//
//    for (int i = length-1; i >= 0; i--) shariki[i+1] = shariki[i];
//    }     
////=============================================================
//void EatingFood (aSharik* snake, double* len, aSharik* food)  
//    {
//    if (CountDistance(*snake, *food) < 20)
//        {
//        food->pos.x = rand() % 1000;
//        food->pos.y = rand() % 1000;
//
//        *len = *len + 1;
//        if (*len > Size) *len = Size;
//
//        }
//    } 
////=============================================================
//double CountDistance (aSharik ball1, aSharik ball2)
//    {
//    return sqrt((ball1.pos.x - ball2.pos.x) * (ball1.pos.x - ball2.pos.x) +
//                (ball1.pos.y - ball2.pos.y) * (ball1.pos.y - ball2.pos.y));
//    }                  
////=============================================================
//void Clamp (double* val, double maxVal, double minVal)
//    {
//    if (*val > maxVal)
//        {
//        *val = maxVal;
//        }
//
//    if (*val < minVal)
//        {
//        *val = minVal;
//        }
//    }
////=============================================================
//
//void aSharik :: KeyBoardControl (const aKeyBoardControl theControl)
//    {
//    if (GetAsyncKeyState (theControl.right))
//        {
//        v.x += 5;
//        v.y = 0;
//        }
//
//    if (GetAsyncKeyState (theControl.left))
//        {
//        v.x -= 5;
//        v.y = 0;
//        }
//
//    if (GetAsyncKeyState (theControl.down))
//        {
//        v.y += 5;
//        v.x = 0;
//        }
//
//    if (GetAsyncKeyState (theControl.up))
//        {                  
//        v.y -= 5;
//        v.x = 0;
//        }
//
//    if (GetAsyncKeyState (theControl.space))
//        {
//        v.x = v.y = 0;
//        }
//    
//    Clamp (&v.x, 14, -14);
//    Clamp (&v.y, 14, -14);  
//
//    }
//
////=============================================================
//
//void aSharik :: Physic ()
//    {
//        if (pos.x + v.x * Dt >= 1000)
//            {
//            pos.x = 999;
//            v.x = -(v.x);
//            }
//
//        if (pos.x - v.x * Dt<= 0)
//            {
//            pos.x = 1;
//            v.x = -(v.x);
//            }
//
//        if (pos.y - v.y * Dt<= 0)
//            {
//            pos.y = 1;
//            v.y = -(v.y);
//            }
//
//        if (pos.y + v.y * Dt>= 1000)
//            {
//            pos.y = 999;
//            v.y = -(v.y);
//            }
//
//    /*pos.x += v.x * Dt;
//    pos.y += v.y * Dt;    */
//
//    //pos = operator+(pos, operator*(v, Dt));
//
//    pos = pos + v * Dt; // ВАЖНО 
//
//    }
//
////=============================================================
//void aSharik :: Draw ()
//    {
//    txSetColor (colorOut);
//    txSetFillColor (colorIn);
//    txCircle (pos.x, pos.y, 10);
//
//    }
////=============================================================
//           