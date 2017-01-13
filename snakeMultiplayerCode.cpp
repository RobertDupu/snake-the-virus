// by Mihaila Alexandra
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOverP1, gameOverP2, tie;
time_t startDoublePW1, finishDoublePW1, startMangaPW1, finishMangaPW1, startDoublePW2, finishDoublePW2, startMangaPW2, finishMangaPW2, TimeUp, TimeStart;;
const int arenaWidth = 24;
const int arenaHeight = 24;
const int timeGame = 180;
int score1, score2, lengthTail1, lengthTail2, upFruit, fruitDouble, doublePower1, triplePower1, PW1, doublePower2, triplePower2, PW2;
char arena[100][100];
struct coordinates
{
    int x, y;
};
coordinates head1, tail1[580], fruit, head2, tail2[580];

enum Directon {STOP = 0, LEFT, RIGHT, UP, DOWN};
Directon Goes1, Goes2;

void putObjectMultiplayer(coordinates&);
void doublePointsMultiplayer(time_t&,time_t&,int&);
void aLittleDrunkMultiplayer(time_t&,time_t&,int&,int&);
void setupMultiplayer();
void drawMultiplayer(int);
void endGameConditionMultiplayer(int);
void logicMultiplayer(int);

void timeOn()
{
    time(&TimeUp);
    TimeStart = TimeUp;
}
void putObjectMultiplayer(coordinates &object)
{
    object.x = rand() % (arenaWidth - 1) + 1;
    object.y = rand() % (arenaHeight - 1) + 1;
    if ((head1.x == object.x && head1.y == object.y) || (head2.x == object.x && head2.y == object.y)) putObjectMultiplayer(object);
    else
    {
        for (int i = 1; i <= lengthTail1; i++)
            if (tail1[i].x == object.x && tail1[i].y == object.y) putObjectMultiplayer(object);
        for (int i = 1; i <= lengthTail2; i++)
            if (tail2[i].x == object.x && tail2[i].y == object.y) putObjectMultiplayer(object);
    }
}
int giveFruitAtribute()
{
    int Dice;
    Dice = rand() % 6;
    if(Dice!=0)
    {
        fruitDouble++;
        return 0;
    }
    else
        return rand()%3+1;
}
void cutTheTail(coordinates v[],int&l)
{
    for(int i=l/2; i<=l; i++)
        v[i].x=v[i].y=0;
    l=l/2;
}
void doublePointsMultiplayer(time_t& a, time_t& b, int& c)
{
    time(&a);
    b = a;
    c = 2;
}
void aLittleDrunkMultiplayer(time_t& a, time_t &b, int &c, int &d)
{
    time(&a);
    b = a;
    c = 3;
    d = 1;
}
void setupMultiplayer()
{
    gameOverP1 = gameOverP2 = tie = false;
    Goes1 = Goes2 = STOP;
    head1.x=arenaWidth/2;
    head1.y=arenaHeight/2;
    head2.x=arenaWidth/2;
    head2.y=arenaHeight/2 - 5;
    putObjectMultiplayer(fruit);
    score1 = score2 = upFruit = 0;
    doublePower1 = doublePower2 = triplePower1 = triplePower2 = 1;
    startDoublePW1 = finishDoublePW1 = startMangaPW1 = finishMangaPW1 = PW1 = 0;
    startDoublePW2 = finishDoublePW2 = startMangaPW2 = finishMangaPW2 = PW2 = 0;
}
void drawMultiplayer(int timeGame)
{
    system("cls");
    for (int y = 0; y <= arenaHeight; y++)
        for (int x=0; x <= arenaWidth; x++)
            if (!y || !x || x == arenaWidth || y == arenaHeight) arena[y][x]='#';
            else arena[y][x]=' ';

    arena[head1.y][head1.x] = 'O';
    arena[head2.y][head2.x] = 'X';
    if (!upFruit) arena[fruit.y][fruit.x] = 'f';
    else if (upFruit == 1) arena[fruit.y][fruit.x] = 'm';
        else if (upFruit == 2) arena[fruit.y][fruit.x] = 'l';
            else if (upFruit == 3) arena[fruit.y][fruit.x] = 'n';
                else arena[fruit.y][fruit.x] = 'F';

    for (int i = 1; i <= lengthTail1; i++) arena[tail1[i].y][tail1[i].x] = 'o';
    for (int i = 1; i <= lengthTail2; i++) arena[tail2[i].y][tail2[i].x] = 'x';

    cout<<"time: "<<timeGame - (TimeUp - TimeStart)<<endl;
    for (int y = 0; y <= arenaHeight; y++)
    {
        for (int x = 0; x <= arenaWidth; x++)
            cout<<arena[y][x];
        cout<<endl;
    }
    cout<<endl;
    cout<<"score1: "<<score1<<endl;
    cout<<"score2: "<<score2<<endl;

    if (startDoublePW1!=0) cout<<"powertime1! "<<20 - (finishDoublePW1 - startDoublePW1)<<endl;
    if (startDoublePW2!=0) cout<<"powertime2! "<<20 - (finishDoublePW2 - startDoublePW2)<<endl;

    if (startMangaPW1!=0)cout<<"powertime1! "<<20 - (finishMangaPW1 - startMangaPW1)<<endl;
    if (startMangaPW2!=0)cout<<"powertime2! "<<20 - (finishMangaPW2 - startMangaPW2)<<endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if(Goes1!=RIGHT)
                Goes1=LEFT;
            break;
        case 'd':
            if(Goes1!=LEFT)
                Goes1=RIGHT;
            break;
        case 'w':
            if(Goes1!=DOWN)
                Goes1=UP;
            break;
        case 's':
            if(Goes1!=UP)
                Goes1=DOWN;
            break;

        case 'j':
            if(Goes2!=RIGHT)
                Goes2=LEFT;
            break;
        case 'l':
            if(Goes2!=LEFT)
                Goes2=RIGHT;
            break;
        case 'i':
            if(Goes2!=DOWN)
                Goes2=UP;
            break;
        case 'k':
            if(Goes2!=UP)
                Goes2=DOWN;
            break;

        case 'x':
            tie = true;
            break;
        }
    }

}
void endGameConditionMultiplayer(int timeGame)
{
    for (int i=1; i<=lengthTail1; i++)
        if (tail1[i].x == head1.x && tail1[i].y == head1.y)
            gameOverP1 = true;

    for (int i=1; i<=lengthTail2; i++)
        if (tail2[i].x==head2.x&&tail2[i].y==head2.y)
            gameOverP2=true;

    for (int i=1; i<=lengthTail1; ++i)
        if (tail1[i].x==head2.x && tail1[i].y==head2.y)
            gameOverP2=true;

    for (int i=1; i<=lengthTail2; ++i)
        if (tail2[i].x==head1.x && tail2[i].y==head1.y)
            gameOverP1=true;

    if (head1.x == head2.x && head1.y == head2.y && Goes1 && Goes2) tie = true;
    if (head1.x == head2.x && head1.y == head2.y && Goes1 && !Goes2) gameOverP1 = true;
    if (head1.x == head2.x && head1.y == head2.y && !Goes1 && Goes2) gameOverP2 = true;

    if(TimeUp - TimeStart >= timeGame)
    {
        if (score1 > score2) gameOverP2 = true;
        else if (score2 > score1) gameOverP1 = true;
        else tie = true;
    }
    else time(&TimeUp);
}
void logicMultiplayer(int timeGame)
{
    coordinates prev, prev2;
    prev.x=tail1[0].x;
    prev.y=tail1[0].y;
    tail1[0].x=head1.x;
    tail1[0].y=head1.y;
    for (int i=0; i<=lengthTail1; i++)
    {
        prev2.x=tail1[i].x;
        prev2.y=tail1[i].y;
        tail1[i].x=prev.x;
        tail1[i].y=prev.y;
        prev.x=prev2.x;
        prev.y=prev2.y;
    }
    prev.x=tail2[0].x;
    prev.y=tail2[0].y;
    tail2[0].x=head2.x;
    tail2[0].y=head2.y;
    for (int i=0; i<=lengthTail2; i++)
    {
        prev2.x=tail2[i].x;
        prev2.y=tail2[i].y;
        tail2[i].x=prev.x;
        tail2[i].y=prev.y;
        prev.x=prev2.x;
        prev.y=prev2.y;
    }
    if(PW1==0)
        switch (Goes1)
        {
        case LEFT:
            head1.x--;
            break;
        case RIGHT:
            head1.x++;
            break;
        case UP:
            head1.y--;
            break;
        case DOWN:
            head1.y++;
            break;
        default:
            break;
        }
    else
        switch (Goes1)
        {
        case UP:
            head1.x--;
            break;
        case  DOWN:
            head1.x++;
            break;
        case RIGHT:
            head1.y--;
            break;
        case LEFT:
            head1.y++;
            break;
        default:
            break;
        }

    if(PW2==0)
        switch (Goes2)
        {
        case LEFT:
            head2.x--;
            break;
        case RIGHT:
            head2.x++;
            break;
        case UP:
            head2.y--;
            break;
        case DOWN:
            head2.y++;
            break;
        default:
            break;
        }
    else
        switch (Goes2)
        {
        case UP:
            head2.x--;
            break;
        case  DOWN:
            head2.x++;
            break;
        case RIGHT:
            head2.y--;
            break;
        case LEFT:
            head2.y++;
            break;
        default:
            break;
        }

    if (head1.x>=arenaWidth)
        head1.x=1;
    else if (head1.x<=0)
        head1.x=arenaWidth-1;
    if (head1.y>=arenaHeight)
        head1.y=1;
    else if (head1.y<=0)
        head1.y=arenaHeight - 1;

    if (head2.x>=arenaWidth)
        head2.x=1;
    else if (head2.x<=0)
        head2.x=arenaWidth-1;
    if (head2.y>=arenaHeight)
        head2.y=1;
    else if (head2.y<=0)
        head2.y=arenaHeight - 1;

    if(startDoublePW1!=0)
    {
        if(finishDoublePW1-startDoublePW1>=20)
        {
            startDoublePW1=0;
            finishDoublePW1=0;
            doublePower1=1;
        }
        else
            time(&finishDoublePW1);
    }
    if(startDoublePW2!=0)
    {
        if(finishDoublePW2-startDoublePW2>=20)
        {
            startDoublePW2=0;
            finishDoublePW2=0;
            doublePower2=1;
        }
        else
            time(&finishDoublePW2);
    }

    if(startMangaPW1!=0)
    {
        if(finishMangaPW1-startMangaPW1>=20)
        {
            startMangaPW1=0;
            finishMangaPW1=0;
            PW1=0;
            triplePower1=1;
        }
        else
            time(&finishMangaPW1);
    }
    if(startMangaPW2!=0)
    {
        if(finishMangaPW2-startMangaPW2>=20)
        {
            startMangaPW2=0;
            finishMangaPW2=0;
            PW2=0;
            triplePower2=1;
        }
        else
            time(&finishMangaPW2);
    }

    if (head1.x==fruit.x && head1.y==fruit.y)
    {
        if(upFruit==0)
        {
            score1+=10*doublePower1*triplePower1;
            lengthTail1++;
        }
        else if(upFruit==4)
        {
            score1+=20*doublePower1*triplePower1;
            lengthTail1++;
        }
        else if(upFruit==1)
            cutTheTail(tail1,lengthTail1);
        else if(upFruit==2)
            doublePointsMultiplayer(startDoublePW1,finishDoublePW1,doublePower1);
        else
            aLittleDrunkMultiplayer(startMangaPW1,finishMangaPW1,triplePower1,PW1);
        putObjectMultiplayer(fruit);
        upFruit=giveFruitAtribute();
        if(upFruit==0&&fruitDouble%5==0)
            upFruit=4;
    }
    else if (head2.x==fruit.x && head2.y==fruit.y)
    {
        if(upFruit==0)
        {
            score2+=10*doublePower2*triplePower2;
            lengthTail2++;
        }
        else if(upFruit==4)
        {
            score2+=20*doublePower2*triplePower2;
            lengthTail2++;
        }
        else if(upFruit==1)
            cutTheTail(tail2,lengthTail2);
        else if(upFruit==2)
            doublePointsMultiplayer(startDoublePW2,finishDoublePW2,doublePower2);
        else
            aLittleDrunkMultiplayer(startMangaPW2,finishMangaPW2,triplePower2,PW2);
        putObjectMultiplayer(fruit);
        upFruit=giveFruitAtribute();
        if(upFruit==0&&fruitDouble%5==0)
            upFruit=4;
    }
}
void startGame()
{
    drawMultiplayer(timeGame);
    while(Goes1==STOP && Goes2 == STOP) Input();
    timeOn();
}
int main()
{
    setupMultiplayer();
    startGame();
    while (!gameOverP1 && !gameOverP2 && !tie)
    {
        drawMultiplayer(timeGame);
        Input();
        logicMultiplayer(timeGame);
        endGameConditionMultiplayer(timeGame);
        Sleep(70);
    }
    drawMultiplayer(timeGame);
    if (gameOverP1) cout << "player 1 lost";
    else if (gameOverP2) cout << "player 2 lost";
    else if (tie) cout << "remiza";
    return 0;
}
