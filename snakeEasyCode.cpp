//by Dupu Robert
#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;
time_t TimeUp,TimeStart;
bool gameOver,Lose;char reset;
const int width=24;
const int height=24;
const int timeGame=600;
int Pscore,AIscore,CanIgo[100][100];
int lengthTail,AIlengthTail;
struct coordinates{
int x;
int y;
};
coordinates head,tail[580],fruit,AIhead,AItail[580];
enum Directon { STOP = 0, LEFT, RIGHT, UP, DOWN};
Directon Goes;
void TimeON()
{
    time(&TimeUp);
         TimeStart=TimeUp;
}
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
       if (AIhead.x==object.x&&AIhead.y==object.y)
           PutObject(object);

        else
      for (int i=0;i<=AIlengthTail;i++)
    if (AItail[i].x==object.x&&AItail[i].y==object.y)
       PutObject(object);

}
void Setup()
{

	gameOver=false;
	tie=false;
	Goes=STOP;
	head.x=width/2;
	head.y=height/2;
	PutObject(fruit);
    Pscore=AIscore=0;
    AIlengthTail=0;
    lengthTail=0;
    AIhead.x=width/2-5;
	AIhead.y=height/2;
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
        Arena[i][j]='-';

	Arena[head.y][head.x]='O';
    Arena[AIhead.y][AIhead.x]='X';
    Arena[fruit.y][fruit.x]='F';

	for(int i=1;i<=lengthTail;i++)
        Arena[tail[i].y][tail[i].x]='o';
    for(int i=1;i<=AIlengthTail;i++)
        Arena[AItail[i].y][AItail[i].x]='x';


        cout<<"time: "<<timeGame-(TimeUp-TimeStart)<<endl;
	for(int i=0;i<width+1;i++)
    {for(int j=0;j<height+1;j++)
       cout<<Arena[i][j];
       cout<<endl;
    }
	cout<<endl;
	cout<<"Score:"<<Pscore<<endl;
	cout<<"ScoreAI:"<<AIscore<<endl;

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
void Teleport(coordinates &B)
	{if (B.x>=width)
        B.x=1;
    else
       if (B.x<=0)
         B.x=width-1;
	if (B.y>=height)
	     B.y=1;
           else
    if (B.y<=0)
     B.y=height - 1;}
void MovmentTail(coordinates &headSnake,coordinates tailSnake[],int lengthTailSnake)
{
coordinates prev,aux;
	prev.x=tailSnake[0].x;
	prev.y=tailSnake[0].y;
	tailSnake[0].x=headSnake.x;
	tailSnake[0].y=headSnake.y;
	for (int i=0;i<=lengthTailSnake;i++)
	{
		aux.x=tailSnake[i].x;
		aux.y=tailSnake[i].y;
		tailSnake[i].x=prev.x;
		tailSnake[i].y=prev.y;
		prev.x=aux.x;
		prev.y=aux.y;
	}
}
void MovmentPlayer()
{
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
}
void AIeyes()
{
   for(int i=0;i<=width;i++)
    for(int j=0;j<=height;j++)
        CanIgo[i][j]=1;


        CanIgo[head.y][head.x]=0;

        for(int i=1;i<=lengthTail;i++)
        CanIgo[tail[i].y][tail[i].x]=0;
    for(int i=1;i<=AIlengthTail;i++)
        CanIgo[AItail[i].y][AItail[i].x]=0;
}
void favorabileCase(bool &AImove)
{
    AImove=false;
     if(AIhead.x<fruit.x&&AIhead.x+1!=AItail[0].x&&CanIgo[AIhead.y][AIhead.x+1]==1)
            {AIhead.x++;AImove=true;}
            else
        if(AIhead.x>fruit.x&&AIhead.x-1!=AItail[0].x&&CanIgo[AIhead.y][AIhead.x-1]==1)
            {AIhead.x--;AImove=true;}
            else
        if(AIhead.y<fruit.y&&AIhead.y+1!=AItail[0].y&&CanIgo[AIhead.y+1][AIhead.x]==1)
            {AIhead.y++;AImove=true;}
            else
        if(AIhead.y>fruit.y&&AIhead.y-1!=AItail[0].y&&CanIgo[AIhead.y-1][AIhead.x]==1)
            {AIhead.y--;AImove=true;}


}
void NefavorabileCase()
{
    int GORIGHT = CanIgo[AIhead.y][AIhead.x+1];
    int GOLEFT  = CanIgo[AIhead.y][AIhead.x-1];
    int GOUP    = CanIgo[AIhead.y-1][AIhead.x];
    int GODOWN  = CanIgo[AIhead.y+1][AIhead.x];

    if(GORIGHT==0)
     {if(GOLEFT==0)
     {if(GODOWN==0)
      AIhead.y--;
    else
      AIhead.y++;}
      else
      AIhead.x--;}
      else
      AIhead.x++;

}
void MovementAI(coordinates &AIhead)
{
    bool AImove=false;int x,y;
    int GORIGHT = CanIgo[AIhead.y][AIhead.x+1];
    int GOLEFT  = CanIgo[AIhead.y][AIhead.x-1];
    int GOUP    = CanIgo[AIhead.y-1][AIhead.x];
    int GODOWN  = CanIgo[AIhead.y+1][AIhead.x];
    if(GOUP==0&&GODOWN==0&&GOLEFT==0&&GORIGHT==1)
    {
        AImove=true;
        AIhead.x++;
    }
    else

    if(GOUP==0&&GODOWN==0&&GOLEFT==1&&GORIGHT==0)
    {
        AImove=true;
        AIhead.x--;
    }
    else
    if(GOUP==0&&GODOWN==1&&GOLEFT==0&&GORIGHT==0)
    {
        AImove=true;
        AIhead.y++;
    }
    else
    if(GOUP==1&&GODOWN==0&&GOLEFT==0&&GORIGHT==0)
    {
        AImove=true;
        AIhead.y--;
    }
    else
    if(GOUP==0&&GODOWN==1&&GOLEFT==0&&GORIGHT==1)
    {
        AImove=true;
        if(fruit.x>AIhead.x)
        AIhead.x++;
        else
        AIhead.y++;
    }
    else
      if(GOUP==1&&GODOWN==0&&GOLEFT==0&&GORIGHT==1)
    {
        AImove=true;
        if(fruit.x>AIhead.x)
        AIhead.x++;
        else
        AIhead.y--;
    }
    else
      if(GOUP==0&&GODOWN==0&&GOLEFT==1&&GORIGHT==1)
    {
            y=AIhead.y;
            if(AItail[1].y<AIhead.y)
            {
                while(CanIgo[y][AIhead.x]==0&&y>0)
                    y--;
                    y++;
                if(CanIgo[y][AIhead.x+1]==1)
                    AIhead.x++;
                else
                   AIhead.x--;

            }
            else
             {
                while(CanIgo[y][AIhead.x]==0&&y>height)
                    y++;
                     y--;
                if(CanIgo[y][AIhead.x+1]==1)
                    AIhead.x++;
                else
                   AIhead.x--;

            }

        }
    else
      if(GOUP==1&&GODOWN==0&&GOLEFT==1&&GORIGHT==0)
    {
        AImove=true;
        if(fruit.x<AIhead.x)
        AIhead.x--;
        else
        AIhead.y--;
    }
     else
      if(GOUP==0&&GODOWN==1&&GOLEFT==1&&GORIGHT==0)
    {
        AImove=true;
        if(fruit.x<AIhead.x)
        AIhead.x--;
        else
        AIhead.y++;
    }
        else
      if(GOUP==1&&GODOWN==1&&GOLEFT==0&&GORIGHT==0)
            {
            x=AIhead.x;
            if(AItail[1].x<AIhead.x)
            {
                while(CanIgo[AIhead.y][x]==0&&x>0)
                    x--;
                x++;
                if(CanIgo[AIhead.y+1][x]==1)
                    AIhead.y++;
                else
                   AIhead.y--;

            }
            else
             {
                while(CanIgo[AIhead.y][x]==0&&x>width)
                    x++;
                    x--;
                if(CanIgo[AIhead.y+1][x]==1)
                    AIhead.y++;
                else
                   AIhead.y--;

            }

        }
    else
    if(GOUP==1&&GODOWN==1&&GOLEFT==0&&GORIGHT==1)
    {
        AImove=true;
    if(AIhead.x<fruit.x)
        AIhead.x++;
        else
        if(fruit.y<AIhead.y)
        AIhead.y--;
        else
        AIhead.y++;
    }
        else
    if(GOUP==1&&GODOWN==1&&GOLEFT==1&&GORIGHT==0)
    {
        AImove=true;
    if(AIhead.x>fruit.x)
        AIhead.x--;
        else
        if(fruit.y<AIhead.y)
        AIhead.y--;
        else
        AIhead.y++;
    }
    else

    if(GOUP==0&&GODOWN==1&&GOLEFT==1&&GORIGHT==1)
    {
        AImove=true;
    if(AIhead.y<fruit.y)
        AIhead.y++;
        else
        if(fruit.x<AIhead.x)
        AIhead.x--;
        else
        AIhead.x++;
    }
        else
    if(GOUP==1&&GODOWN==0&&GOLEFT==1&&GORIGHT==1)
    {
        AImove=true;
    if(AIhead.y>fruit.y)
        AIhead.y--;
        else
        if(fruit.x<AIhead.x)
        AIhead.x--;
        else
        AIhead.x++;
    }
    else
    {
        AImove=true;
        if(fruit.x<AIhead.x)
        AIhead.x--;
        else
        if(fruit.x>AIhead.x)
        AIhead.x++;
        else
        if(fruit.y<AIhead.y)
        AIhead.y--;
        else
        if(fruit.y>AIhead.y)
        AIhead.y++;
    }




}
addTail(int &score,coordinates headSnake,int &lengthTailSnake)
{if (headSnake.x==fruit.x && headSnake.y==fruit.y)
	{

		score+=10;
        lengthTailSnake++;
		PutObject(fruit);

	}

	}
void EndGameCondition()
{
  if(head.x==AIhead.x&&head.y==AIhead.y)
  {
      gameOver=true;
       Lose=true;
  }
  else

  {
    for (int i=0;i<=lengthTail;i++)
		if(tail[i].x==head.x&&tail[i].y==head.y)
			{gameOver=true;Lose=true;}
    for (int i=0;i<=AIlengthTail;i++)
		if (AItail[i].x==head.x&&AItail[i].y==head.y)
            {gameOver=true;Lose=true;}
    for (int i=0;i<=lengthTail;i++)
		if (tail[i].x==AIhead.x&&tail[i].y==AIhead.y)
			{gameOver=true;Lose=false;}
    for (int i=0;i<=AIlengthTail;i++)
    	if (AItail[i].x==AIhead.x&&AItail[i].y==AIhead.y)
            {gameOver=true;Lose=false;}
  }
  if(TimeUp-TimeStart>=timeGame)
  {
      gameOver=true;
      if(Pscore>AIscore)
        Lose=false;
      else
        Lose=true;
  }
  else
    time(&TimeUp);
}
void Logic()
{
    AIeyes();
    MovmentTail(head,tail,lengthTail);
     MovmentTail(AIhead,AItail,AIlengthTail);

	MovmentPlayer();
	if(Goes!=STOP)
    MovementAI(AIhead);
	Teleport(head);
	Teleport(AIhead);
    EndGameCondition();

     addTail(Pscore,head,lengthTail);
	 addTail (AIscore,AIhead,AIlengthTail);
}
void startGame()
{
    Draw();
 while(Goes==STOP)
    {
    Input();}
    TimeON();
}
void PLay()
{
    Setup();
    startGame();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
        Sleep(70);
	}
}
int main()
{
     RESET:

     PLay();
if(Lose==true)
    cout<<"lacrima";
else
    cout<<"GG"<<endl;
    cout<<endl;
    do{
    cout<<"mai vrei? d/n";
     cin>>reset;


    }while(reset!='d'&&reset!='n');
    if(reset=='d')
        goto RESET;





	return 0;
}
