#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctime>

#define width 800
#define height 600
#define arenaWidth 24
#define arenaHeight 24
#define xS 150
#define yS 79

using namespace std;

/// GRAPHICS' DECLARATIONS

sf::Sprite menuImage, menuPlayImage, menuScoreImage, menuQuitImage, menuArenaImage, menuGameOver2Image, menuGameOver1Image, playButtonImage, scoreButton1Image, scoreButton2Image, abortButton1Image, abortButton2Image, abortButton3Image, onePlayerImage, twoPlayersImage, ayeImage, nopeImage, backImage, resetImage, barImage, okImage, square[24][24];
sf::Texture menuTexture, menuPlayTexture, menuScoreTexture, menuQuitTexture, menuArenaTexture, menuGameOver2Texture, menuGameOver1Texture, playButtonTexture, scoreButton1Texture, abortButton1Texture, onePlayerTexture, twoPlayersTexture, ayeTexture, nopeTexture, backTexture, resetTexture, barTexture, okTexture;
sf::Font theFont;
sf::Event Event;
sf::RenderWindow window(sf::VideoMode(width, height), "Snake the Virus", sf::Style::Close);
sf::Text text[6], theScore, timeDouble[2], timeManga[2], textGameOver[6];
sf::Time timeSleep = sf::milliseconds(80);
string vid;
bool r=false;

struct coordonates
{
    int x, y, h, w;
};
struct coordonates playButton, scoreButton1, scoreButton2, abortButton1, abortButton2, abortButton3, onePlayerButton, twoPlayersButton, ayeButton, nopeButton, backButton, resetButton, okButton;

struct board
{
    string name;
    int points;
};
struct board B1[6], B2[6];

/// GRAPHICS' FUNCTIONS

bool pressButton(coordonates);
void putPosition(coordonates&,int,int,int,int);
void loadImages();
void loadTextures();
void loadPosition();
void loadFonts();
void loadTexts();
void displayMenu();
void displayPlay();
void displayScore();
void displayAbort();
void displaySingle();
void displayCombat();
void displayGameOver2();
void displayGameOver1();
int playMode();
int singleMode();
int combatMode();
int scoreMode();
int byeByeMode();
int gameOver2();
int gameOver1(int);

/// CODE'S DECLARATIONS

bool gameOver;
time_t startDoublePW, finishDoublePW, startMangaPW, finishMangaPW;
int score, lengthTail, upFruit, fruitDouble, doublePower, triplePower, PW;
short int T = 0;
char arena[30][30];

struct coordinates
{
    int x, y;
};
struct coordinates head, tail[580], fruit;

enum Directon
{
    STOP = 0, LEFT, RIGHT, UP, DOWN
};
enum Directon Goes;

/// CODE'S FUNCTIONS

void putObject(coordinates&);
int giveFruitAtribute();
void cutTheTail(coordinates*, int&);
void doublePoints();
void aLittleDrunk();
void gameSingle();
void setupSingle();
void drawSingle();
void logicSingle();
void resetGameSingle();
int scoreCheck(int);
void read();
void write();

/// MENU

int main()
{
    loadImages();
    loadTextures();
    loadPosition();
    loadFonts();
    srand(time(NULL));
    if (!r) read();

    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(playButton))
                        {
                            playMode();
                            break;
                        }
                        if (pressButton(scoreButton1))
                        {
                            scoreMode();
                            break;
                        }
                        if (pressButton(abortButton1))
                        {
                            byeByeMode();
                            break;
                        }
                    }
            }
        }
        displayMenu();
    }
    return 0;
}
void displayMenu()
{
    window.clear();
    window.draw(menuImage);
    window.draw(playButtonImage);
    window.draw(scoreButton1Image);
    window.draw(abortButton1Image);
    window.display();
}
void loadImages()
{
    menuTexture.loadFromFile("graphics/menu/menu1clean.png");
    menuPlayTexture.loadFromFile("graphics/menu/play/playmodeclean.png");
    menuScoreTexture.loadFromFile("graphics/menu/scoreboard/scoreboardclean.png");
    menuQuitTexture.loadFromFile("graphics/menu/quit/quitclean.png");
    menuArenaTexture.loadFromFile("graphics/Arena/arenaclean.png");
    menuGameOver2Texture.loadFromFile("graphics/gameover/gameover2.png");
    menuGameOver1Texture.loadFromFile("graphics/gameover/gameover1.png");

    playButtonTexture.loadFromFile("graphics/menu/play/playbutton.png");
    scoreButton1Texture.loadFromFile("graphics/menu/scoreboard/scoreboardbutton.png");
    abortButton1Texture.loadFromFile("graphics/menu/quit/quitbutton.png");

    onePlayerTexture.loadFromFile("graphics/menu/play/1player.png");
    twoPlayersTexture.loadFromFile("graphics/menu/play/2player.png");

    ayeTexture.loadFromFile("graphics/menu/quit/aye.png");
    nopeTexture.loadFromFile("graphics/menu/quit/nope.png");

    backTexture.loadFromFile("graphics/Arena/back.png");
    resetTexture.loadFromFile("graphics/gameover/reset.png");

    barTexture.loadFromFile("graphics/gameover/bar.png");
    okTexture.loadFromFile("graphics/gameover/ok.png");
}
void loadTextures()
{
    menuImage.setTexture(menuTexture);
    menuPlayImage.setTexture(menuPlayTexture);
    menuScoreImage.setTexture(menuScoreTexture);
    menuQuitImage.setTexture(menuQuitTexture);
    menuArenaImage.setTexture(menuArenaTexture);
    menuGameOver2Image.setTexture(menuGameOver2Texture);
    menuGameOver1Image.setTexture(menuGameOver1Texture);

    playButtonImage.setTexture(playButtonTexture);
    scoreButton1Image.setTexture(scoreButton1Texture);
    scoreButton2Image.setTexture(scoreButton1Texture);
    abortButton1Image.setTexture(abortButton1Texture);
    abortButton2Image.setTexture(abortButton1Texture);
    abortButton3Image.setTexture(abortButton1Texture);

    onePlayerImage.setTexture(onePlayerTexture);
    twoPlayersImage.setTexture(twoPlayersTexture);

    ayeImage.setTexture(ayeTexture);
    nopeImage.setTexture(nopeTexture);

    backImage.setTexture(backTexture);
    resetImage.setTexture(resetTexture);

    barImage.setTexture(barTexture);
    okImage.setTexture(okTexture);
}
void loadPosition()
{
    menuImage.setPosition(0,0);
    menuPlayImage.setPosition(0,0);
    menuScoreImage.setPosition(0,0);
    menuQuitImage.setPosition(0,0);
    menuArenaImage.setPosition(0,0);
    menuGameOver2Image.setPosition(0,0);
    menuGameOver1Image.setPosition(0,0);

    playButtonImage.setPosition(360,116);
    putPosition(playButton,360,116,35,80);
    scoreButton1Image.setPosition(285,194);
    putPosition(scoreButton1,285,194,35,230);
    abortButton1Image.setPosition(350,272);
    putPosition(abortButton1,350,272,35,100);
    scoreButton2Image.setPosition(285,355);
    putPosition(scoreButton2,285,355,35,230);
    abortButton2Image.setPosition(350,432);
    putPosition(abortButton2,350,432,35,100);
    abortButton3Image.setPosition(350,472);
    putPosition(abortButton3,350,472,35,100);

    onePlayerImage.setPosition(328,191);
    putPosition(onePlayerButton,328,191,35,140);
    twoPlayersImage.setPosition(326,270);
    putPosition(twoPlayersButton,326,270,35,140);

    ayeImage.setPosition(367,404);
    putPosition(ayeButton,367,404,35,60);
    nopeImage.setPosition(367,484);
    putPosition(nopeButton,367,484,35,60);

    backImage.setPosition(30,30);
    putPosition(backButton,30,30,35,90);

    resetImage.setPosition(670,24);
    putPosition(resetButton,670,24,115,115);

    okImage.setPosition(685,380);
    putPosition(okButton,685,380,80,80);
}
void loadFonts()
{
    theFont.loadFromFile("fonts/RussoOne.ttf");
}
void loadTexts()
{
    text[0].setPosition(290,242);
    text[0].setFont(theFont);
    text[0].setCharacterSize(33);
    text[0].setColor(sf::Color(0, 255, 255));

    text[1].setPosition(290,282);
    text[1].setFont(theFont);
    text[1].setCharacterSize(33);
    text[1].setColor(sf::Color(0, 255, 255));

    text[2].setPosition(290,322);
    text[2].setFont(theFont);
    text[2].setCharacterSize(33);
    text[2].setColor(sf::Color(0, 255, 255));

    text[3].setPosition(290,362);
    text[3].setFont(theFont);
    text[3].setCharacterSize(33);
    text[3].setColor(sf::Color(0, 255, 255));

    text[4].setPosition(290,402);
    text[4].setFont(theFont);
    text[4].setCharacterSize(33);
    text[4].setColor(sf::Color(0, 255, 255));

    textGameOver[0].setPosition(225,360);
    textGameOver[0].setFont(theFont);
    textGameOver[0].setCharacterSize(33);
    textGameOver[0].setColor(sf::Color(0, 255, 255));

    textGameOver[1].setPosition(225,400);
    textGameOver[1].setFont(theFont);
    textGameOver[1].setCharacterSize(33);
    textGameOver[1].setColor(sf::Color(0, 255, 255));

    textGameOver[2].setPosition(225,440);
    textGameOver[2].setFont(theFont);
    textGameOver[2].setCharacterSize(33);
    textGameOver[2].setColor(sf::Color(0, 255, 255));

    textGameOver[3].setPosition(225,480);
    textGameOver[3].setFont(theFont);
    textGameOver[3].setCharacterSize(33);
    textGameOver[3].setColor(sf::Color(0, 255, 255));

    textGameOver[4].setPosition(225,520);
    textGameOver[4].setFont(theFont);
    textGameOver[4].setCharacterSize(33);
    textGameOver[4].setColor(sf::Color(0, 255, 255));

    for (int i = 0; i < 5; ++i)
        if (!B1[i].points) {text[i].setString("404 not found"); textGameOver[i].setString("404 not found");}
        else
        {
            std::stringstream aux;
            aux << B1[i].points;
            string a = B1[i].name + ' ' + aux.str().c_str();
            text[i].setString(a);
            textGameOver[i].setString(a);
        }

    theScore.setPosition(654,30);
    theScore.setFont(theFont);
    theScore.setCharacterSize(24);
    theScore.setColor(sf::Color(0,255,255));

    timeDouble[0].setPosition(658,180);
    timeDouble[0].setFont(theFont);
    timeDouble[0].setCharacterSize(18);
    timeDouble[0].setColor(sf::Color(0,255,255));
    timeDouble[0].setString("Double points:");
    timeDouble[1].setPosition(710,200);
    timeDouble[1].setFont(theFont);
    timeDouble[1].setCharacterSize(24);
    timeDouble[1].setColor(sf::Color(0,255,255));

    timeManga[0].setPosition(680,270);
    timeManga[0].setFont(theFont);
    timeManga[0].setCharacterSize(18);
    timeManga[0].setColor(sf::Color(0,255,255));
    timeManga[0].setString("Beer time:");
    timeManga[1].setPosition(710,290);
    timeManga[1].setFont(theFont);
    timeManga[1].setCharacterSize(24);
    timeManga[1].setColor(sf::Color(0,255,255));
}
void loadArenaImage(const char* path, int i, int j)
{
    sf::Texture auxT;
    auxT.loadFromFile(path);
    square[i][j].setTexture(auxT);
    square[i][j].setPosition(xS + i*20,yS + j*20);
    window.draw(square[i][j]);
}
void putPosition(coordonates &button, int a, int b, int c, int d)
{
    button.x = a;
    button.y = b;
    button.h = c;
    button.w = d;
}
bool pressButton(coordonates button)
{
    int currentX, currentY;
    currentX = Event.mouseButton.x;
    currentY = Event.mouseButton.y;
    return (currentX >= button.x && currentX <= button.x + button.w && currentY >= button.y && currentY <= button.y + button.h);
}
void read()
{
    ifstream fin;
    fin.open("scoreboard.in");
    for (int i = 0; i < 5; ++i)
    {
        fin >> B1[i].name; fin.get();
        fin >> B1[i].points; fin.get();
    }
    fin.close();
    r=true;
}
void write()
{
    ofstream fout;
    fout.open("scoreboard.in");
    for (int i = 0; i < 5; ++i)
        if (B1[i].points) fout << B1[i].name << ' ' << B1[i].points << '\n';
    fout.close();
    r=false;
}
int playMode()
{
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button==sf::Mouse::Left)
                    {
                        if (pressButton(playButton))
                        {
                            return 0;
                            break;
                        }
                        if (pressButton(onePlayerButton))
                        {
                            if (!singleMode()) return 0;
                            else break;
                        }
                        if (pressButton(twoPlayersButton))
                        {
                            if (!combatMode()) return 0;
                            else break;
                        }
                        if (pressButton(scoreButton2))
                        {
                            if (!scoreMode()) return 0;
                            else break;
                        }
                        if (pressButton(abortButton2))
                        {
                            if (!byeByeMode()) return 0;
                            else break;
                        }
                    }
            }
        }
        displayPlay();
    }
}
void displayPlay()
{
    window.clear();
    window.draw(menuPlayImage);
    window.draw(playButtonImage);
    window.draw(onePlayerImage);
    window.draw(twoPlayersImage);
    window.draw(scoreButton2Image);
    window.draw(abortButton2Image);
    window.display();
}
int scoreMode()
{
    if (!r) read();
    loadTexts();
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(playButton))
                        {
                            if (!playMode()) return 0;
                            else break;
                        }
                        if (pressButton(scoreButton1))
                        {
                            return 0;
                            break;
                        }
                        if (pressButton(abortButton3))
                        {
                            if (!byeByeMode()) return 0;
                            else break;
                        }
                    }
            }
        }
        displayScore();
    }
}
void displayScore()
{
    window.clear();
    window.draw(menuScoreImage);
    for (int i = 0; i < 5; ++i) window.draw(text[i]);
    window.draw(playButtonImage);
    window.draw(scoreButton1Image);
    window.draw(abortButton3Image);
    window.display();
}
int byeByeMode()
{
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(playButton))
                        {
                            if (!playMode()) return 0;
                            else break;
                        }
                        if (pressButton(scoreButton1))
                        {
                            if (!scoreMode()) return 0;
                            else break;
                        }
                        if (pressButton(abortButton1))
                        {
                            return 0;
                            break;
                        }
                        if (pressButton(ayeButton))
                        {
                            window.close();
                            exit(0);
                            break;
                        }
                        if (pressButton(nopeButton))
                        {
                            return 0;
                            break;
                        }
                    }
            }
        }
        displayAbort();
    }
}
void displayAbort()
{
    window.clear();
    window.draw(menuQuitImage);
    window.draw(playButtonImage);
    window.draw(scoreButton1Image);
    window.draw(abortButton1Image);
    window.draw(ayeImage);
    window.draw(nopeImage);
    window.display();
}
int singleMode()
{
    bool start = false;
    setupSingle();
    loadTexts();
    while (window.isOpen())
    {
        while (!gameOver)
        {
            while (window.pollEvent(Event))
            {
                switch (Event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        resetGameSingle();
                        exit(0);
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (Event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (pressButton(backButton))
                            {
                                gameOver = true;
                                resetGameSingle();
                                return 0;
                                break;
                            }
                        }
                    case sf::Event::KeyPressed:
                        start = true;
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {if (Goes != DOWN) Goes = UP; break;}
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {if (Goes != LEFT) Goes = RIGHT; break;}
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {if (Goes != UP) Goes = DOWN; break;}
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {if (Goes != RIGHT) Goes = LEFT; break;}
                    default:
                        break;
                }
            }
        if (!start) displaySingle();
        else gameSingle();
        }
        if (gameOver)
        {
            int ok = scoreCheck(score);
            cout<<ok<<'\n';
            if (ok == -1)
            {
                if (!gameOver2()) return 0;
                else
                {
                    resetGameSingle();
                    setupSingle();
                }
            }
            else
                if (!gameOver1(ok)) return 0;
                else
                {
                    resetGameSingle();
                    setupSingle();
                }
        }
    }
}
void gameSingle()
{
    window.clear();
    window.draw(menuArenaImage);
    window.draw(backImage);
    logicSingle();
    drawSingle();
    window.display();
    sf::sleep(timeSleep);
}
void setupSingle()
{
	T = 0;
	gameOver = false;
	Goes = STOP;
	head.x = arenaWidth / 2;
	head.y = arenaHeight / 2;
	putObject(fruit);
    score = upFruit = startDoublePW = finishDoublePW = startMangaPW = PW = finishMangaPW = 0;
    doublePower = 1;
    triplePower = 1;
}
void putObject(coordinates &object)
{
    object.x = rand() % (arenaWidth - 1) + 1;
    object.y = rand() % (arenaHeight - 1) + 1;
    if (head.x == object.x && head.y == object.y) putObject(object);
    else
        for (int i=0 ; i <= lengthTail; i++)
            if (tail[i].x == object.x && tail[i].y == object.y) putObject(object);
}
void drawSingle()
{
    for (int i = 0; i <= arenaWidth; i++)
        for (int j = 0; j <= arenaHeight; j++)
            if (!i || !j || i == arenaWidth || j == arenaHeight) arena[i][j] = '#';
            else arena[i][j] = ' ';

	arena[head.x][head.y] = 'O';

	if (!upFruit) arena[fruit.x][fruit.y] = 'f';
	else if (upFruit == 1) arena[fruit.x][fruit.y] = 'm';
	else if (upFruit == 2) arena[fruit.x][fruit.y] = 'l';
        else if (upFruit == 3) arena[fruit.x][fruit.y] = 'n';
            else arena[fruit.x][fruit.y] = 'F';

	for (int i = 1; i <= lengthTail; i++) arena[tail[i].x][tail[i].y] = 'o';

	for (int i = 1; i < arenaHeight; i++)
        for (int j = 1; j < arenaWidth; j++)
        {
            if (arena[i][j] == 'O' || arena[i][j] == 'o') loadArenaImage("graphics/Snake/snake.png",i,j);
            else if (arena[i][j] == 'f') loadArenaImage("graphics/powerups/1.png",i,j);
                else if (arena[i][j] == 'F') loadArenaImage("graphics/powerups/2.png",i,j);
                    else if (arena[i][j] == 'm') loadArenaImage("graphics/powerups/half.png",i,j);
                        else if (arena[i][j] == 'l') loadArenaImage("graphics/powerups/scoreX2.png",i,j);
                            else if (arena[i][j] == 'n') loadArenaImage("graphics/powerups/plum.png",i,j);
        }

    std::stringstream aux;
    aux << score;
    theScore.setString(aux.str().c_str());
    window.draw(theScore);

	if (startDoublePW != 0)
    {
        int x = 20 - (int)(finishDoublePW - startDoublePW);
        std::stringstream aux;
        aux << x;
        timeDouble[1].setString(aux.str().c_str());
        window.draw(timeDouble[0]);
        window.draw(timeDouble[1]);
    }
    if (startMangaPW != 0)
    {
        int x = 20 - (int)(finishMangaPW - startMangaPW);
        std::stringstream aux;
        aux << x;
        timeManga[1].setString(aux.str().c_str());
        window.draw(timeManga[0]);
        window.draw(timeManga[1]);
    }
}
void logicSingle()
{
    coordinates prev, prev2;
	prev.x = tail[0].x;
	prev.y = tail[0].y;
	tail[0].x = head.x;
	tail[0].y = head.y;
	for (int i = 0; i <= lengthTail; i++)
	{
		prev2.x = tail[i].x;
		prev2.y = tail[i].y;
		tail[i].x = prev.x;
		tail[i].y = prev.y;
		prev.x = prev2.x;
		prev.y = prev2.y;
	}
    if (!PW)
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
    else switch (Goes)
	{
        case UP: /// LEFT
            head.x--;
            break;
        case DOWN:
            head.x++; /// RIGHT
            break;
        case RIGHT:
            head.y--; /// UP
            break;
        case LEFT:
            head.y++; /// DOWN
            break;
        default:
            break;
	}
	if (head.x >= arenaHeight) head.x = 1;
    else if (head.x <= 0) head.x = arenaHeight - 1;
	if (head.y >= arenaWidth) head.y = 1;
    else if (head.y <= 0) head.y = arenaWidth - 1;

	for (int i = 0; i <= lengthTail; i++)
		if (tail[i].x == head.x && tail[i].y == head.y) gameOver = true;

    if (startDoublePW != 0)
    {
        if (finishDoublePW - startDoublePW >= 20)
        {
            startDoublePW = finishDoublePW = PW = 0;
            doublePower = 1;
        }
        else time(&finishDoublePW);
    }
    if (startMangaPW != 0)
    {
        if(finishMangaPW - startMangaPW >= 20)
        {
                startMangaPW = finishMangaPW = PW = 0;
                triplePower = 1;
        }
        else time(&finishMangaPW);
    }

	if (head.x == fruit.x && head.y == fruit.y)
	{
        if (!upFruit)
		{
		    score += 10 * doublePower * triplePower;
		    lengthTail++;
        }
		else if (upFruit == 4)
        {
            score += 20 * doublePower * triplePower;
            lengthTail++;
        }
        else if (upFruit == 1) cutTheTail(tail,lengthTail);
            else if (upFruit == 2) doublePoints();
                else aLittleDrunk();

        putObject(fruit);
        upFruit = giveFruitAtribute();
        if (!upFruit && !(fruitDouble%5)) upFruit = 4;
	}
}
int giveFruitAtribute()
{
    int Dice = rand() % 6;
    if (Dice != 0)
    {
        fruitDouble++;
        return 0;
    }
    else return rand() % 3 + 1;
}
void cutTheTail(coordinates v[], int &l)
{
    for (int i = l/2; i <= l; ++i) v[i].x = v[i].y = 0;
    l = l/2;
}
void doublePoints()
{
    time(&startDoublePW);
    finishDoublePW = startDoublePW;
    doublePower = 2;
}
void aLittleDrunk()
{
    time(&startMangaPW);
    finishMangaPW = startMangaPW;
    triplePower = 3;
    PW = 1;
}
void resetGameSingle()
{
    for (int i = 0; i <= lengthTail; ++i)
        tail[i].x = tail[i].y = 0;
    lengthTail = 0;
    for (int i = 0; i <= arenaHeight; ++i)
        for (int j = 0; j <= arenaHeight; ++j)
            arena[i][j] = ' ';
}
void displaySingle()
{
    window.clear();
    window.draw(menuArenaImage);
    window.draw(backImage);

    std::stringstream aux;
    aux << score;
    theScore.setString(aux.str().c_str());
    window.draw(theScore);

    loadArenaImage("graphics/Snake/snake.png",head.x,head.y);
    loadArenaImage("graphics/powerups/1.png",fruit.x,fruit.y);
    window.display();
}
int combatMode()
{
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(backButton))
                        {
                            return 0;
                            break;
                        }
                    }
                }
            }
        }
        displayCombat();
    }
}
void displayCombat()
{
    window.clear();
    window.draw(menuArenaImage);
    window.draw(backImage);
    window.display();
}
int gameOver1(int pos)
{
    if (!r) read();
    loadTexts();
    textGameOver[pos].setString("<new name>");
    textGameOver[pos].setStyle(sf::Text::Italic);
    string nameEntered = vid;
    short int letters = 0;
    barImage.setPosition(170,366 + pos*40);
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    resetGameSingle();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    if (Event.mouseButton.button==sf::Mouse::Left)
                    {
                        if (pressButton(backButton))
                        {
                            resetGameSingle();
                            return 0;
                            break;
                        }
                        if (pressButton(resetButton))
                        {
                            return 1;
                            break;
                        }
                        if (pressButton(okButton))
                        {
                            if (nameEntered.size())
                            {
                                for (int i=4; i > pos; --i) B2[i]=B2[i-1];
                                B2[pos].name = nameEntered;
                                B2[pos].points = score;
                                for (int i=0; i < 5; ++i) B1[i]=B2[i];
                                write();
                                break;
                            }
                        }
                    }
                }
                case sf::Event::TextEntered:
                    if (letters < 8)
                    {
                        if ((Event.text.unicode > 64 && Event.text.unicode < 91) || (Event.text.unicode > 96 && Event.text.unicode < 123) || (Event.text.unicode > 47 && Event.text.unicode <58 ))
                        {
                            nameEntered += (char)Event.text.unicode;
                            std::stringstream aux1;
                            aux1 << score;
                            string aux2 = nameEntered + " : " + aux1.str().c_str();
                            ++letters;
                            textGameOver[pos].setString(aux2);
                            textGameOver[pos].setStyle(sf::Text::Italic);
                            break;
                        }
                    }
                    if (Event.text.unicode == 8)
                    {
                        if (!nameEntered.size())
                        {
                            std::stringstream aux1;
                            aux1 << score;
                            string aux2 = nameEntered + " : " + aux1.str().c_str();
                            textGameOver[pos].setString(aux2);
                            break;
                        }
                        nameEntered.erase(nameEntered.size()-1,nameEntered.size());
                        --letters;
                        std::stringstream aux1;
                        aux1 << score;
                        string aux2 = nameEntered + " : " + aux1.str().c_str();
                        textGameOver[pos].setString(aux2);
                        textGameOver[pos].setStyle(sf::Text::Italic);
                        break;
                    }
                default:
                    break;
            }
        }
        displayGameOver1();
    }
}
int scoreCheck(int score)
{
    for (int i = 0; i < 5; ++i) B2[i]=B1[i];
    if (score - B2[4].points <=0) return -1;
    for (int i = 4; i >= 0; --i)
        if (B2[i].points >= score)
            return i+1;
    return 0;
}
void displayGameOver1()
{
    window.clear();
    window.draw(menuGameOver1Image);
    window.draw(backImage);
    window.draw(resetImage);
    for (int i = 0; i < 5; ++i) window.draw(textGameOver[i]);
    window.draw(barImage);
    window.draw(okImage);
    window.display();
}
int gameOver2()
{
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    resetGameSingle();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(backButton))
                        {
                            resetGameSingle();
                            return 0;
                            break;
                        }
                        if (pressButton(resetButton))
                        {
                            return 1;
                            break;
                        }
                    }
            }
        }
        displayGameOver2();
    }
}
void displayGameOver2()
{
    window.clear();
    window.draw(menuGameOver2Image);
    window.draw(backImage);
    window.draw(resetImage);
    window.display();
}
