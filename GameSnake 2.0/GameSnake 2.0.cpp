
#include "TXLib.h"
const int w = 1000;
const int h = 1000;
const int SizeSnake = 20;
const COLORREF ColorWalls = RGB (0, 0, 0);
const int RSnake = 10;
const int Head = 'H';
const int Tail = 'T';
const int Turn1 = '1';
const int Turn2 = '2';
const int Turn3 = '3';
const int Turn4 = '4';
const int Body = 'B';

struct resource
    {
    HDC background, mapOfTheWalls, cherry, wall, menu, head, tail, body1, body2;

    };

struct aKeyBoardControl
    {
    int left, up, right, down, space;
    };

struct aSharik
    {
    int x, y, xv, yv;
    int maxV;
    COLORREF colorIn, colorOut;
    int type;

    void Draw (resource pictures);
    void Physic ();
    void KeyBoardControl (const aKeyBoardControl theControl);
    };

struct aSnake // изменить
    {
    int len;
    aSharik shariki [SizeSnake+1];

    void Physic ();
    void PrintSnake ();
    void Draw (resource pictures);
    void GiveTypes ();
    };

void Clamp (int* val, int maxVal, int minVal);
void EatingFood (aSharik* head, int* len, aSharik* food, HDC mapOfTheWalls);
double CountDistance (aSharik ball1, aSharik ball2);
void Game (resource pictures);
void Menu (resource pictures);
void DeleteDC (resource pictures);
resource LoadDC ();
void Score (int score);


int main()
    {

    txCreateWindow (w, h);

    txBegin ();

    resource pictures = LoadDC ();

    txDisableAutoPause();

    Menu(pictures);

    DeleteDC (pictures);

    return 0;
    }
//=============================================================
void Score (int score)
        {
        score = (score - 1) * 10;

        char outPut[50] = "";

        sprintf (outPut, "Score = %i \n", score);

        txSelectFont("Segoe Script Bold", 100);
        txSetColor (RGB(21, 99, 0));
        txTextOut (18, 918, outPut);

        txSetColor (RGB(255, 0, 0));
        txTextOut (15, 915, outPut);


        }
//=============================================================
resource LoadDC ()
    {
    HDC background  = txLoadImage ("Images\\background.bmp");
    HDC mapOfTheWalls  = txLoadImage ("Images\\MapOfTheWalls.bmp");
    HDC cherry = txLoadImage ("Images\\cherry.bmp");
    HDC wall = txLoadImage ("Images\\wall.bmp");
    HDC menu = txLoadImage ("Images\\menu.bmp");
    HDC head = txLoadImage ("Images\\Head.bmp");
    HDC tail = txLoadImage ("Images\\Tail.bmp");
    HDC body1 = txLoadImage ("Images\\Body1.bmp");
    HDC body2 = txLoadImage ("Images\\Body2.bmp");

    if (!background) txMessageBox ("Не могу загрузить фон из background");
    if (!mapOfTheWalls) txMessageBox ("Не могу загрузить фон из mapsOfTheWalls");
    if (!cherry) txMessageBox ("Не могу загрузить фон из cherry");
    if (!wall) txMessageBox ("Не могу загрузить фон из wall");
    if (!head) txMessageBox ("Не могу загрузить фон из head");
    if (!tail) txMessageBox ("Не могу загрузить фон из tail");
    if (!body1) txMessageBox ("Не могу загрузить фон из body1");
    if (!body2) txMessageBox ("Не могу загрузить фон из body2");

    resource pictures = {background, mapOfTheWalls, cherry, wall, menu, head, tail, body1, body2};

    return pictures;
    }
//=============================================================
void DeleteDC (resource pictures)
    {
    txDeleteDC (pictures.mapOfTheWalls);
    txDeleteDC (pictures.background);
    txDeleteDC (pictures.cherry);
    txDeleteDC (pictures.wall);
    txDeleteDC (pictures.menu);


    txDeleteDC (pictures.head);
    txDeleteDC (pictures.tail);
    txDeleteDC (pictures.body1);
    txDeleteDC (pictures.body2);
    }
//=============================================================
void Menu (resource pictures)
    {
    while (true)
        {

        //printf ("Координаты мыши по x и y: %i %i \n", txMouseX(), txMouseY());

        txBitBlt (0, 0, pictures.menu);

        if (410 < txMouseX() && 610 < txMouseY() && 584 > txMouseX() && 670 > txMouseY() && txMouseButtons() == 1)
            {
            Game (pictures);
            }

        if (430 < txMouseX() && 810 < txMouseY() && 568 > txMouseX() && 870 > txMouseY() && txMouseButtons() == 1)
            {
            break;
            }

        }
    }
//=============================================================
void Game (resource pictures)
        {
        aSharik food = {900, 30, 0,  0, 0, RGB (255, 255, 255), RGB (255, 255, 255)};

        aSnake snake = {10,{{20, 20,   0,  0, 50, RGB (255,   0,   0), RGB (0, 0, 0)}}};

        aKeyBoardControl Player = {'A', 'W', 'D', 'S', 'X'};



        while (true)
            {

            int xOld = snake.shariki[0].x;
            int yOld = snake.shariki[0].y;

            txBitBlt (0, 0, pictures.background);

            Score (snake.len);

            COLORREF curColorRi = txGetPixel (snake.shariki[0].x + RSnake, snake.shariki[0].y, pictures.mapOfTheWalls);
            COLORREF curColorLe = txGetPixel (snake.shariki[0].x - RSnake, snake.shariki[0].y, pictures.mapOfTheWalls);
            COLORREF curColorDo = txGetPixel (snake.shariki[0].x , snake.shariki[0].y + RSnake, pictures.mapOfTheWalls);
            COLORREF curColorUp = txGetPixel (snake.shariki[0].x , snake.shariki[0].y - RSnake, pictures.mapOfTheWalls);

            snake.shariki[0].KeyBoardControl (Player);

            snake.Physic ();

            //food.Draw ();



            EatingFood (&snake.shariki[0], &snake.len, &food, pictures.mapOfTheWalls);


            txAlphaBlend (food.x - txGetExtentX (pictures.cherry)/2, food.y - txGetExtentY (pictures.cherry)/2, pictures.cherry);

            if (curColorRi == ColorWalls || curColorLe == ColorWalls || curColorDo == ColorWalls || curColorUp == ColorWalls)
                {
                txSetColor (RGB (0, 0, 0));
                txSelectFont ("Comic Sans MS", 140);
                txDrawText (100, 100, 900, 900, "You've crashed");
                break;

                snake.shariki[0].x = xOld;
                snake.shariki[0].y = yOld;
                }

            if (snake.len == SizeSnake)
                {
                txSetColor (RGB (0, 0, 0));
                txSelectFont ("Comic Sans MS", 150);
                txDrawText (100, 100, 900, 900, "You win !!!");
                break;
                }

            snake.GiveTypes();

            snake.Draw(pictures);

            if (GetAsyncKeyState (VK_SPACE))
                {
                snake.PrintSnake ();

                while (kbhit()) getch ();

                getch();

                }

            txSleep (150);
            }

        snake.Draw(pictures);
        }
//=============================================================
void aSnake :: PrintSnake ()
    {
    for (int i = 0; i <= len; i++)
        {
        printf("[%2d], x %3d, y %3d, xv %3d, yv %3d, type %c \n", i, shariki[i].x, shariki[i].y, shariki[i].xv, shariki[i].yv, shariki[i].type);
        }
    }
//=============================================================
void aSnake :: Physic()
    {

    for (int i = len-1; i >= 0; i--) shariki[i+1] = shariki[i];

    shariki[0].Physic ();

    }
//=============================================================
void aSnake :: GiveTypes()
    {

    shariki[0].type = Head;


    for (int i = 1; i < len; i++)
        {
        int xvOld = shariki[i+1].xv;
        int yvOld = shariki[i+1].yv;

        int xvNew = shariki[i-1].xv;
        int yvNew = shariki[i-1].yv;

        if (xvNew == xvOld && yvNew == yvOld)
            {
            shariki[i].type = Body;
            }

        else
            {

            if ((xvOld <= 0 && yvOld <= 0) && (xvNew >= 0 && yvNew >= 0) && (shariki[i-1].type != Turn1))
                {
                shariki[i].type = Turn1;


                }

            else if ((xvOld >= 0 && yvOld <= 0) && (xvNew <= 0 && yvNew >= 0) && (shariki[i-1].type != Turn2))
                {
                shariki[i].type = Turn2;
                }

            else if ((xvOld >= 0 && yvOld >= 0) && (xvNew <= 0 && yvNew <= 0) && (shariki[i-1].type != Turn3))
                {
                shariki[i].type = Turn3;
                }

            else if ((xvOld <= 0 && yvOld >= 0) && (xvNew >= 0 && yvNew <= 0) && (shariki[i-1].type != Turn4))
                {
                shariki[i].type = Turn4;
                }

            else
                {
                shariki[i].type = Body;
                }
            }
        }

    shariki[len].type = Tail;

    }
//=============================================================
void aSnake :: Draw(resource pictures)
    {

    for (int i = 0; i <= len; i++)
        {
        shariki[i].Draw(pictures);
        }

    }
//=============================================================
void EatingFood (aSharik* head, int* len, aSharik* food, HDC mapOfTheWalls)
    {
    //printf ("Координаты головы %d %d \n", head->x, head->y);
    //printf ("Координаты еды %d %d \n", food->x, food->y);

    double distan = CountDistance(*head, *food);
    if ( distan < 20)
        {
        int oldX = food->x;
        int oldY = food->y;

        while ((oldX == food->x) && (oldY == food->y))
            {
            int x = rand() % w;
            int y = rand() % h;

            if (txGetPixel (x, y, mapOfTheWalls) != RGB(0, 0, 0))
                {
                food->x = x;
                food->y = y;
                }
            }

        *len = *len + 1;
        if (*len > SizeSnake) *len = SizeSnake;

        }
    //printf ("Расстояние до еды %lf \n", distan);
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
        xv = maxV;
        yv = 0;
        }

    if (GetAsyncKeyState (theControl.left))
        {
        xv = -(maxV);
        yv = 0;
        }

    if (GetAsyncKeyState (theControl.down))
        {
        yv = maxV;
        xv = 0;
        }

    if (GetAsyncKeyState (theControl.up))
        {
        yv = -(maxV);
        xv = 0;
        }

    /*if (GetAsyncKeyState (theControl.space))
        {
        xv = yv = 0;
        }        */

    Clamp (&xv, maxV, -(maxV));
    Clamp (&yv, maxV, -(maxV));

    }

//=============================================================

void aSharik :: Physic ()
    {
        if (x + xv >= w)
            {
            x = w-1;
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

        if (y + yv >= h)
            {
            y = h-1;
            yv = -(yv);
            }

    x += xv;
    y += yv;
    }

//=============================================================

void aSharik :: Draw (resource pictures)
    {

    txSetFillColor (RGB (255, 0, 0));
    txCircle (x, y, 10);


    if (type == Head)
        {
        int ix = 0;
        int iy = 0;

        if (yv == 0)
            {
            ix = (xv > 0);
            }

        if (xv == 0)
            {
            iy = 1;
            ix = (yv > 0);
            }

        txBitBlt (txDC (), x - txGetExtentX (pictures.head)/4, y  - txGetExtentY (pictures.head)/4, 50, 50, pictures.head, 50 * ix, 50 * iy);
        }

    if (type == Body)
        {
        if (yv == 0)
            {
            txBitBlt (txDC (), x - txGetExtentX (pictures.body2)/4, y  - txGetExtentY (pictures.body2)/2, 50, 50, pictures.body2, 0, 0);
            }
        else
            {
            txBitBlt (txDC (), x - txGetExtentX (pictures.body2)/4, y  - txGetExtentY (pictures.body2)/2, 50, 50, pictures.body2, 50, 0);
            }

        }


    if (type == Turn1)
        {
        txBitBlt (txDC (), x - txGetExtentX (pictures.body1)/4, y  - txGetExtentY (pictures.body1)/4.3, 50, 50, pictures.body1, 0, 0);
        }

    else if (type == Turn2)
        {
        txBitBlt (txDC (), x - txGetExtentX (pictures.body1)/4, y  - txGetExtentY (pictures.body1)/4.3, 50, 50, pictures.body1, 50, 0);
        }

    else if (type == Turn3)
        {
        txBitBlt (txDC (), x - txGetExtentX (pictures.body1)/4, y  - txGetExtentY (pictures.body1)/4.3, 50, 50, pictures.body1, 50, 50);
        }

    else if (type == Turn4)
        {
        txBitBlt (txDC (), x - txGetExtentX (pictures.body1)/4, y  - txGetExtentY (pictures.body1)/4.3, 50, 50, pictures.body1, 0, 50);
        }

    else if (type == Tail)
        {
        int ix = 0;
        int iy = 0;

        if (yv == 0)
            {
            ix = (xv > 0);
            }

        if (xv == 0)
            {
            iy = 1;
            ix = (yv > 0);
            }

        txBitBlt (txDC (), x - txGetExtentX (pictures.tail)/4, y  - txGetExtentY (pictures.tail)/4, 50, 50, pictures.tail, 50 * ix, 50 * iy);
        }

    }
