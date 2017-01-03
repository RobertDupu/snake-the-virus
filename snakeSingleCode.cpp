//by Dupu Robert
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
time_t startDoublePW,finishDoublePW,startMangaPW,finishMangaPW;
const int width=24;
const int height=24;
int score;
int lengthTail;
struct coordinates{
int x;
int y;
};
int UPfruit,fruitDouble,DoublePower,PW;
coordinates head,tail[580],fruit;
enum Directon { STOP = 0, LEFT, RIGHT, UP, DOWN};
Directon Goes;
void PutObject(coordinates &object)
{

        object.x=rand()%(width-1)+1;
	    object.y=rand()%(height-1)+1;
	    if (head.x==object.x&&head.y==object.y)
           PutObject(object);

        else
      for (int i=0;i<=lengthTail;i++)
    if (tail[i].x==object.x&&tail[i].y==object.y)
       PutObject(object);

}
int GivefruitAtribut()
{
    	int Dice;
		Dice=rand()%6;
		if(Dice!=0)

		  { fruitDouble++;
		      return 0;}

		else

        return rand()%3+1;

}
void CutTheTail(coordinates v[],int&l)
{
    for(int i=l/2;i<=l;i++)
        v[i].x=v[i].y=0;
    l=l/2;
}
void DoublePoints()
{

  time(&startDoublePW);
  finishDoublePW=startDoublePW;
  DoublePower=2;

}
void Manga()
{

  time(&startDoublePW);
  finishMangaPW=startMangaPW;
  DoublePower=3;
PW=1;
}
void Setup()
{
	gameOver=false;

	Goes=STOP;
	head.x=width/2;
	head.y=height/2;
	PutObject(fruit);
    score=0;
    UPfruit=0;
    DoublePower=1;
    startDoublePW=0;
    finishDoublePW=0;
    startMangaPW=0;

 PW=0;
                finishMangaPW=0;
}
char Arena[100][100];
void Draw()
{
	system("cls");
for(int i=0;i<=width;i++)
    for(int j=0;j<=height;j++)
    if(i==0||j==0||i==width||j==height)
        Arena[i][j]='#';
        else
        Arena[i][j]=' ';

	Arena[head.y][head.x]='O';
	if(UPfruit==0)
	Arena[fruit.y][fruit.x]='f';
	else
	if(UPfruit==1)
	Arena[fruit.y][fruit.x]='m';
	else
	if(UPfruit==2)
	Arena[fruit.y][fruit.x]='l';
	else
	if(UPfruit==3)
	Arena[fruit.y][fruit.x]='n';
	else
    Arena[fruit.y][fruit.x]='F';

	for(int i=1;i<=lengthTail;i++)
        Arena[tail[i].y][tail[i].x]='o';

	for(int i=0;i<width+1;i++)
    {for(int j=0;j<height+1;j++)
       cout<<Arena[i][j];
       cout<<endl;
    }
	cout<<endl;
	cout<<"Score:"<<score<<endl;
	if(startDoublePW!=0)
        cout<<"powertime!"<<20-(finishDoublePW-startDoublePW)<<endl;
    if(startMangaPW!=0)
        cout<<"powertime!"<<20-(finishMangaPW-startMangaPW)<<endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
		    if(Goes!=RIGHT)
			Goes=LEFT;
			break;
		case 'd':
		    if(Goes!=LEFT)
			Goes=RIGHT;
			break;
		case 'w':
		    if(Goes!=DOWN)
			Goes=UP;
			break;
		case 's':
		    if(Goes!=UP)
			Goes=DOWN;
			break;
		case 'k':
			gameOver=true;
			break;
		}
	}

}
void Logic()
{
    coordinates prev;
	prev.x=tail[0].x;
	prev.y=tail[0].y;
	coordinates prev2;
	tail[0].x=head.x;
	tail[0].y=head.y;
	for (int i=0;i<=lengthTail;i++)
	{
		prev2.x=tail[i].x;
		prev2.y=tail[i].y;
		tail[i].x=prev.x;
		tail[i].y=prev.y;
		prev.x=prev2.x;
		prev.y=prev2.y;
	}
if(PW==0)
	switch (Goes)
	{
	case LEFT:
		head.x--;
		break;
	case RIGHT:
		head.x++;
		break;
	case UP:
		head.y--;
		break;
	case DOWN:
		head.y++;
		break;
	default:
		break;
	}
	else
switch (Goes)
	{
	case UP:
		head.x--;
		break;
	case  DOWN:
		head.x++;
		break;
	case RIGHT:
		head.y--;
		break;
	case LEFT:
		head.y++;
		break;
	default:
		break;
	}

	if (head.x>=width)
        head.x=1;
    else
       if (head.x<=0)
         head.x=width-1;
	if (head.y>=height)
	     head.y=1;
           else
    if (head.y<=0)
     head.y=height - 1;

	for (int i=0;i<=lengthTail;i++)
		if (tail[i].x==head.x&&tail[i].y==head.y)
			gameOver=true;

			if(startDoublePW!=0)
                {if(finishDoublePW-startDoublePW>=20)
            {
                startDoublePW=0;
                finishDoublePW=0;
                PW=0;
                DoublePower=1;
            }
            else
                time(&finishDoublePW);}

            if(startMangaPW!=0)
                {if(finishMangaPW-startMangaPW>=20)
            {
                startMangaPW=0;
                finishMangaPW=0;
                DoublePower=1;
            }
            else
                time(&finishDoublePW);}

	if (head.x==fruit.x && head.y==fruit.y)
	{
        if(UPfruit==0)
		{score+=10*DoublePower;lengthTail++;}
		else
        if(UPfruit==4)
        {score+=20*DoublePower;lengthTail++;}
        else
       if(UPfruit==1)
        CutTheTail(tail,lengthTail);
        else
        if(UPfruit==2)
        DoublePoints();
        else
        Manga();

		PutObject(fruit);
	   UPfruit=GivefruitAtribut();
	   if(UPfruit==0&&fruitDouble%5==0)
        UPfruit=4;

	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(30);
	}
	return 0;
}
