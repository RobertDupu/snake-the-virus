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

sf::Sprite menuImage, menuPlayImage, menuScoreImage, menuQuitImage, menuArenaImage, menuGameOver2Image, menuGameOver1Image, retryImage, menuNoviceImage[6], menuHardImage[6], menuImpossibleImage[3], menuSasserImage, menuStuxnetImage, menuILOVEYOUImage, loserImage, winnerImage, noviceImage, hardImage, impossibleImage, p60Image, p120Image, p180Image, startImage, startInsertImage, legendsOnlyImage,playButtonImage, scoreButton1Image, scoreButton2Image, abortButton1Image, abortButton2Image, abortButton3Image, onePlayerImage, twoPlayersImage, ayeImage, nopeImage, backImage, resetImage, barImage, okImage, square[24][24];
sf::Texture menuTexture, menuPlayTexture, menuScoreTexture, menuQuitTexture, menuArenaTexture, menuGameOver2Texture, menuGameOver1Texture, retryTexture, menuNoviceTexture[6], menuHardTexture[6], menuImpossibleTexture[3], menuSasserTexture, menuStuxnetTexture, menuILOVEYOUTexture, loserTexture, winnerTexture, noviceTexture, hardTexture, impossibleTexture, p60Texture, p120Texture, p180Texture, startTexture, startInsertTexture, legendsOnlyTexture, playButtonTexture, scoreButton1Texture, abortButton1Texture, onePlayerTexture, twoPlayersTexture, ayeTexture, nopeTexture, backTexture, resetTexture, barTexture, okTexture;
sf::Font theFont;
sf::Event Event;
sf::RenderWindow window(sf::VideoMode(width, height), "Snake the Virus", sf::Style::Close);
sf::Text text[7], theScore, timeDouble[2], timeManga[2], textGameOver[7], textStart, textScorePlayer, textScoreAI, timeCombat;
sf::Time timeSleepSingle = sf::milliseconds(90), timeSleepCombat = sf::milliseconds(115), sleepCombat = sf ::milliseconds(3000);
string vid;
bool r = false;

struct coordonates
{
    int x, y, h, w;
};
struct coordonates playButton, scoreButton1, scoreButton2, abortButton1, abortButton2, abortButton3, onePlayerButton, twoPlayersButton, ayeButton, nopeButton, backButton, resetButton, okButton, noviceButton, hardButton, impossibleButton, startButton, p60Button, p120Button, p180Button;

struct board
{
    string name;
    int points;
    bool noviceWin, hardWin, impossibleWin;
};
struct board B1[7], B2[7];

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
void displayCombat(int,int);
void displayGameOver2();
void displayGameOver1();
void displayRetry();
void displayStart(bool,int,int);
void displayNovice(int);
void displayHard(int);
void displayImpossible(int);
void displayFail();
void displayWonWon();
int playMode();
int singleMode();
int combatMode();
int scoreMode();
int byeByeMode();
void startMode(int,int);
int noviceMode(int,int);
int hardMode(int,int);
int impossibleMode(int,int);
int gameOver2();
int gameOver1(int);
int retry();
int fail();
int wonWon();

/// CODE'S DECLARATIONS

bool gameOver, lose;
time_t startDoublePW, finishDoublePW, startMangaPW, finishMangaPW, TimeUp, TimeStart;
int score, lengthTail, upFruit, fruitDouble, doublePower, triplePower, PW, playerScore, AIscore, AIlengthTail;
short int T = 0;
char arena[30][30];
bool battlefield[30][30];

struct coordinates
{
    int x, y;
};
struct coordinates head, tail[580], fruit, AIhead, AItail[580];

enum Directon
{
    STOP = 0, LEFT, RIGHT, UP, DOWN
};
enum Directon Goes;

/// CODE'S FUNCTIONS

///SINGLE

void putObjectSingle(coordinates&);
int giveFruitAtribute();
void cutTheTail(coordinates*, int&);
void doublePoints();
void aLittleDrunk();
void gameSingle();
void setupSingle();
void drawSingle();
void logicSingle();
void resetGameSingle();

/// COMBAT
void gameNovice(int);
void gameHard(int);
void gameImpossible(int);
void timeOn();
void putObject(coordinates&);
void setupCombat();
void drawCombat(int);
void input();
void teleport(coordinates&);
void movementTail(coordinates&,coordinates*,int);
void movementPlayer();
void AIeyes();
void movementAINovice(coordinates&);
void movementAIHard(coordinates&);
void addTail(int&,coordinates,int&);
void endGameCondition(int);
void logicCombat(int,int);
void startGame();
void Play();
void resetGameCombat();
void favorableCase(bool&,int,int,int,int);
void worstCase(int,int,int,int);

int scoreCheck(int);
bool isLegend(string,int&);
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
                    write();
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
    retryTexture.loadFromFile("graphics/gameover/retry.png");
    menuNoviceTexture[0].loadFromFile("graphics/menu/play/combat/pc11.png");
    menuNoviceTexture[1].loadFromFile("graphics/menu/play/combat/pc12.png");
    menuNoviceTexture[2].loadFromFile("graphics/menu/play/combat/pc13.png");
    menuNoviceTexture[3].loadFromFile("graphics/menu/play/combat/nov1.png");
    menuNoviceTexture[4].loadFromFile("graphics/menu/play/combat/nov2.png");
    menuNoviceTexture[5].loadFromFile("graphics/menu/play/combat/nov3.png");
    menuHardTexture[0].loadFromFile("graphics/menu/play/combat/pc21.png");
    menuHardTexture[1].loadFromFile("graphics/menu/play/combat/pc22.png");
    menuHardTexture[2].loadFromFile("graphics/menu/play/combat/pc23.png");
    menuHardTexture[3].loadFromFile("graphics/menu/play/combat/med1.png");
    menuHardTexture[4].loadFromFile("graphics/menu/play/combat/med2.png");
    menuHardTexture[5].loadFromFile("graphics/menu/play/combat/med3.png");
    menuImpossibleTexture[0].loadFromFile("graphics/menu/play/combat/pc31.png");
    menuImpossibleTexture[1].loadFromFile("graphics/menu/play/combat/pc32.png");
    menuImpossibleTexture[2].loadFromFile("graphics/menu/play/combat/pc33.png");
    startInsertTexture.loadFromFile("graphics/menu/play/combat/insertclean.png");
    legendsOnlyTexture.loadFromFile("graphics/menu/play/combat/legendsonly.png");
    menuSasserTexture.loadFromFile("graphics/menu/play/combat/Sasser.png");
    menuStuxnetTexture.loadFromFile("graphics/menu/play/combat/Stuxnet.png");
    menuILOVEYOUTexture.loadFromFile("graphics/menu/play/combat/ILOVEYOU.png");
    loserTexture.loadFromFile("graphics/menu/play/combat/loser.png");
    winnerTexture.loadFromFile("graphics/menu/play/combat/winner.png");

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

    noviceTexture.loadFromFile("graphics/menu/play/combat/novice.png");
    hardTexture.loadFromFile("graphics/menu/play/combat/hard.png");
    impossibleTexture.loadFromFile("graphics/menu/play/combat/impossible.png");

    p60Texture.loadFromFile("graphics/menu/play/combat/60.png");
    p120Texture.loadFromFile("graphics/menu/play/combat/120.png");
    p180Texture.loadFromFile("graphics/menu/play/combat/180.png");
    startTexture.loadFromFile("graphics/menu/play/combat/start.png");
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
    retryImage.setTexture(retryTexture);
    for (int i = 0; i < 6; ++i)
    {
        menuNoviceImage[i].setTexture(menuNoviceTexture[i]);
        menuHardImage[i].setTexture(menuHardTexture[i]);
    }
    for (int i = 0; i < 3; ++i) menuImpossibleImage[i].setTexture(menuImpossibleTexture[i]);
    startInsertImage.setTexture(startInsertTexture);
    legendsOnlyImage.setTexture(legendsOnlyTexture);
    menuSasserImage.setTexture(menuSasserTexture);
    menuStuxnetImage.setTexture(menuStuxnetTexture);
    menuILOVEYOUImage.setTexture(menuILOVEYOUTexture);
    loserImage.setTexture(loserTexture);
    winnerImage.setTexture(winnerTexture);

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

    noviceImage.setTexture(noviceTexture);
    hardImage.setTexture(hardTexture);
    impossibleImage.setTexture(impossibleTexture);

    p60Image.setTexture(p60Texture);
    p120Image.setTexture(p120Texture);
    p180Image.setTexture(p180Texture);
    startImage.setTexture(startTexture);
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
    retryImage.setPosition(0,0);
    for (int i = 0; i < 6; ++i)
    {
        menuNoviceImage[i].setPosition(0,0);
        menuHardImage[i].setPosition(0,0);
    }
    for (int i = 0; i < 3; ++i) menuImpossibleImage[i].setPosition(0,0);
    startInsertImage.setPosition(0,0);
    legendsOnlyImage.setPosition(0,0);
    menuSasserImage.setPosition(0,0);
    menuStuxnetImage.setPosition(0,0);
    menuILOVEYOUImage.setPosition(0,0);
    loserImage.setPosition(0,0);
    winnerImage.setPosition(0,0);

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

    noviceImage.setPosition(340,180);
    putPosition(noviceButton,340,180,35,120);
    hardImage.setPosition(360,262);
    putPosition(hardButton,360,262,35,80);
    impossibleImage.setPosition(299,344);
    putPosition(impossibleButton,299,344,35,200);

    p60Image.setPosition(205,490);
    putPosition(p60Button,205,490,35,70);
    p120Image.setPosition(355,490);
    putPosition(p120Button,355,490,35,70);
    p180Image.setPosition(515,490);
    putPosition(p180Button,515,490,35,70);
    startImage.setPosition(339,565);
    putPosition(startButton,339,565,34,120);
}
void loadFonts()
{
    theFont.loadFromFile("fonts/RussoOne.ttf");
}
void loadTexts()
{
    text[1].setPosition(290,242);
    text[1].setFont(theFont);
    text[1].setCharacterSize(33);
    text[1].setColor(sf::Color(0, 255, 255));

    text[2].setPosition(290,282);
    text[2].setFont(theFont);
    text[2].setCharacterSize(33);
    text[2].setColor(sf::Color(0, 255, 255));

    text[3].setPosition(290,322);
    text[3].setFont(theFont);
    text[3].setCharacterSize(33);
    text[3].setColor(sf::Color(0, 255, 255));

    text[4].setPosition(290,362);
    text[4].setFont(theFont);
    text[4].setCharacterSize(33);
    text[4].setColor(sf::Color(0, 255, 255));

    text[5].setPosition(290,402);
    text[5].setFont(theFont);
    text[5].setCharacterSize(33);
    text[5].setColor(sf::Color(0, 255, 255));

    textGameOver[1].setPosition(225,360);
    textGameOver[1].setFont(theFont);
    textGameOver[1].setCharacterSize(33);
    textGameOver[1].setColor(sf::Color(0, 255, 255));

    textGameOver[2].setPosition(225,400);
    textGameOver[2].setFont(theFont);
    textGameOver[2].setCharacterSize(33);
    textGameOver[2].setColor(sf::Color(0, 255, 255));

    textGameOver[3].setPosition(225,440);
    textGameOver[3].setFont(theFont);
    textGameOver[3].setCharacterSize(33);
    textGameOver[3].setColor(sf::Color(0, 255, 255));

    textGameOver[4].setPosition(225,480);
    textGameOver[4].setFont(theFont);
    textGameOver[4].setCharacterSize(33);
    textGameOver[4].setColor(sf::Color(0, 255, 255));

    textGameOver[5].setPosition(225,520);
    textGameOver[5].setFont(theFont);
    textGameOver[5].setCharacterSize(33);
    textGameOver[5].setColor(sf::Color(0, 255, 255));

    for (int i = 1; i < 6; ++i)
        if (!B1[i].points) text[i].setString("404 not found");
        else
        {
            std::stringstream aux;
            aux << B1[i].points;
            string a = B1[i].name + ' ' + aux.str().c_str();
            text[i].setString(a);
        }
    for (int i = 1; i < 6; ++i)
        if (!B2[i].points) textGameOver[i].setString("404 not found");
        else
        {
            std::stringstream aux;
            aux << B2[i].points;
            string a = B2[i].name + ' ' + aux.str().c_str();
            textGameOver[i].setString(a);
        }

    theScore.setPosition(654,30);
    theScore.setFont(theFont);
    theScore.setCharacterSize(24);
    theScore.setColor(sf::Color(0,255,255));

    textStart.setPosition(300,100);
    textStart.setFont(theFont);
    textStart.setCharacterSize(33);
    textStart.setColor(sf::Color(0,255,255));

    textScorePlayer.setPosition(50,235);
    textScorePlayer.setFont(theFont);
    textScorePlayer.setCharacterSize(24);
    textScorePlayer.setColor(sf::Color(0,255,255));

    textScoreAI.setPosition(50,295);
    textScoreAI.setFont(theFont);
    textScoreAI.setCharacterSize(24);
    textScoreAI.setColor(sf::Color(0,255,255));

    timeCombat.setPosition(50,120);
    timeCombat.setFont(theFont);
    timeCombat.setCharacterSize(40);
    timeCombat.setColor(sf::Color(0,255,255));

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
void loadCombatImage(const char* path, int y, int x)
{
    sf::Texture auxT;
    auxT.loadFromFile(path);
    square[y][x].setTexture(auxT);
    square[y][x].setPosition(xS + y*20,yS + x*20);
    window.draw(square[y][x]);
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
    for (int i = 1; i < 6; ++i)
    {
        fin >> B1[i].name;
        fin >> B1[i].points >> B1[i].noviceWin >> B1[i].hardWin >> B1[i].impossibleWin;
        fin.get();
    }
    fin.close();
    r = true;
}
void write()
{
    ofstream fout;
    fout.open("scoreboard.in");
    for (int i = 1; i < 6; ++i)
        if (B1[i].points) fout << B1[i].name << ' ' << B1[i].points << ' ' << B1[i].noviceWin << ' ' << B1[i].hardWin << ' ' << B1[i].impossibleWin << '\n';
    fout.close();
    r = false;
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
                    write();
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
                    write();
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
    for (int i = 1; i < 6; ++i) window.draw(text[i]);
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
                    write();
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
                            write();
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
    window.setFramerateLimit(12);
    while (window.isOpen())
    {
        while (!gameOver)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {if (Goes != DOWN) Goes = UP; start = true;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {if (Goes != LEFT) Goes = RIGHT;start = true;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {if (Goes != UP) Goes = DOWN; start = true;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {if (Goes != RIGHT) Goes = LEFT;start = true;}
            while (window.pollEvent(Event))
            {
                switch (Event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        resetGameSingle();
                        write();
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
}
void setupSingle()
{
	gameOver = false;
	Goes = STOP;
	head.x = arenaWidth / 2;
	head.y = arenaHeight / 2;
	putObjectSingle(fruit);
    score = upFruit = startDoublePW = finishDoublePW = startMangaPW = PW = finishMangaPW = 0;
    doublePower = 1;
    triplePower = 1;
}
void putObjectSingle(coordinates &object)
{
    object.x = rand() % (arenaWidth - 1) + 1;
    object.y = rand() % (arenaHeight - 1) + 1;
    if (head.x == object.x && head.y == object.y) putObjectSingle(object);
    else
        for (int i = 0 ; i <= lengthTail; i++)
            if (tail[i].x == object.x && tail[i].y == object.y) putObjectSingle(object);
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
            if (arena[i][j] == 'O' || arena[i][j] == 'o')
            {
                if (!PW) loadArenaImage("graphics/Snake/snake.png",i,j);
                else loadArenaImage("graphics/Snake/drunk.png",i,j);
            }
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
            startDoublePW = finishDoublePW = 0;
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

        putObjectSingle(fruit);
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
    int l, s;
    l = s = 0;
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    write();
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
                        if (pressButton(noviceButton))
                        {
                            l = s = 0;
                            break;
                        }
                        if (pressButton(hardButton))
                        {
                            l = 1;
                            s = 0;
                            break;
                        }
                        if (pressButton(impossibleButton))
                        {
                            l = 2;
                            s = 0;
                            break;
                        }
                        if (pressButton(p60Button))
                        {
                            s = 0;
                            break;
                        }
                        if (pressButton(p120Button))
                        {
                            s = 1;
                            break;
                        }
                        if (pressButton(p180Button))
                        {
                            s = 2;
                            break;
                        }
                        if (pressButton(startButton))
                        {
                            startMode(l,s);
                            break;
                        }
                    }
                }
            }
        }
        displayCombat(l,s);
    }
}
void startMode(int l, int s)
{
    int a = 0, b = 0;
    if (!r) read();
    loadTexts();
    textStart.setString("<new name>");
    textStart.setStyle(sf::Text::Italic);
    string nameEntered = vid;
    short int letters = 0;
    int i;
    bool notGood = false;
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    write();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(backButton))
                        {
                            return;
                            break;
                        }
                        if (pressButton(okButton))
                        {
                            if (nameEntered.size())
                            {
                                for (i = 1; i < 6 ; ++i) B2[i] = B1[i];
                                i = 5;
                                if (!isLegend(nameEntered,i))
                                {
                                    notGood = true;
                                    break;
                                }
                                if (!l)
                                {
                                    if (!noviceMode(s,i)) return;
                                    else break;
                                }
                                if ((l == 1 && !B2[i].noviceWin) || (l == 2 && !B2[i].noviceWin && !B2[i].hardWin))
                                {
                                    a = 1;
                                    b = 3;
                                    notGood = true;
                                    break;
                                }
                                else if (l == 1 && B2[i].noviceWin)
                                    {
                                        if (!hardMode(s,i)) return;
                                        else break;
                                    }
                                if (l == 2 && !B2[i].hardWin)
                                {
                                    a = 2;
                                    b = 3;
                                    notGood = true;
                                    break;
                                }
                                else if (l == 2 && B2[i].hardWin)
                                    {
                                        if (!impossibleMode(s,i)) return;
                                        else break;
                                    }
                            }
                        }
                        if (pressButton(p60Button))
                        {
                            if (a) b = 3;
                            break;
                        }
                        if (pressButton(p120Button))
                        {
                            if (a) b = 4;
                            break;
                        }
                        if (pressButton(p180Button))
                        {
                            if (a) b = 5;
                            break;
                        }
                        if (pressButton(startButton))
                        {
                            if (a == 1)
                                if (!noviceMode(b,i)) return;
                                else break;
                            if (a == 2)
                                if (!hardMode(b,i)) return;
                                else break;
                        }
                    }
                case sf::Event::TextEntered:
                    if (letters < 10)
                    {
                        if ((Event.text.unicode > 64 && Event.text.unicode < 91) || (Event.text.unicode > 96 && Event.text.unicode < 123) || (Event.text.unicode > 47 && Event.text.unicode <58 ))
                        {
                            nameEntered += (char)Event.text.unicode;
                            ++letters;
                            textStart.setString(nameEntered);
                            textStart.setStyle(sf::Text::Italic);
                            break;
                        }
                    }
                    if (Event.text.unicode == 8)
                    {
                        if (!nameEntered.size())
                        {
                            textStart.setString(nameEntered);
                            break;
                        }
                        nameEntered.erase(nameEntered.size()-1,nameEntered.size());
                        --letters;
                        textStart.setString(nameEntered);
                        textStart.setStyle(sf::Text::Italic);
                        break;
                    }
            }
        }
        displayStart(notGood,a,b);
    }
}
void displayStart(bool x, int typeLevel, int typeScore)
{
    window.clear();
    if (x && !typeLevel && !typeScore) window.draw(legendsOnlyImage);
    if (x && typeLevel == 1)
    {
        window.draw(menuNoviceImage[typeScore]);
        window.draw(p60Image);
        window.draw(p120Image);
        window.draw(p180Image);
        window.draw(startImage);
    }
    if (x && typeLevel == 2)
    {
        window.draw(menuHardImage[typeScore]);
        window.draw(p60Image);
        window.draw(p120Image);
        window.draw(p180Image);
        window.draw(startImage);
    }
    if (!x)
    {
        window.draw(startInsertImage);
        window.draw(textStart);
        window.draw(okImage);
    }
    window.draw(backImage);
    window.display();
}
void displayCombat(int typeLevel, int typeScore)
{
    window.clear();
    if (!typeLevel) window.draw(menuNoviceImage[typeScore]);
    if (typeLevel == 1) window.draw(menuHardImage[typeScore]);
    if (typeLevel == 2) window.draw(menuImpossibleImage[typeScore]);
    window.draw(backImage);
    window.draw(noviceImage);
    window.draw(hardImage);
    window.draw(impossibleImage);
    window.draw(p60Image);
    window.draw(p120Image);
    window.draw(p180Image);
    window.draw(startImage);
    window.display();
}
int noviceMode(int timer, int pos)
{
    int start = 0;
    setupCombat();
    loadTexts();
    int timeGame;
    if (!timer || timer == 3) timeGame = 60;
    if (timer == 1 || timer == 4) timeGame = 120;
    if (timer == 2 || timer == 5) timeGame = 180;
    window.setFramerateLimit(10);
    while (window.isOpen())
    {
        while (!gameOver)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {if (Goes != DOWN) Goes = UP; start++;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {if (Goes != LEFT) Goes = RIGHT; start++;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {if (Goes != UP) Goes = DOWN; start++;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {if (Goes != RIGHT) Goes = LEFT; start++;}
            if (start == 1) timeOn();
            while (window.pollEvent(Event))
            {
                switch (Event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        resetGameCombat();
                        write();
                        exit(0);
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (Event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (pressButton(backButton))
                            {
                                gameOver = true;
                                resetGameCombat();
                                return 0;
                                break;
                            }
                        }
                    default:
                        break;
                }
            }
        if (!start) displayNovice(timeGame);
        else gameNovice(timeGame);
        }
        if (gameOver)
        {
            window.clear();
            window.draw(menuSasserImage);
            window.draw(backImage);
            drawCombat(timeGame);
            window.display();
            sf::sleep(sleepCombat);
            if (lose)
                if (!fail()) return 0;
                else
                {
                    resetGameCombat();
                    setupCombat();
                    start = 0;
                }
            else
            {
                B1[pos].noviceWin = 1;
                write();
                if (!wonWon()) return 0;
                else
                {
                    resetGameCombat();
                    setupCombat();
                    start = 0;
                }
            }
        }
    }
}
void setupCombat()
{
    gameOver = false;
    Goes = STOP;
    head.x = arenaWidth / 2;
    head.y = arenaHeight / 2;
    putObject(fruit);
    playerScore = AIscore = AIlengthTail = lengthTail = 0;
    AIhead.x = arenaWidth / 2 - 5;
    AIhead.y = arenaHeight / 2;
}
void gameNovice(int timeGame)
{
    window.clear();
    window.draw(menuSasserImage);
    window.draw(backImage);
    logicCombat(timeGame,0);
    drawCombat(timeGame);
    window.display();
}
void logicCombat(int timeGame, int type)
{
    AIeyes();
    movementTail(head,tail,lengthTail);
    movementTail(AIhead,AItail,AIlengthTail);

    movementPlayer();
    if (Goes != STOP)
    {
        if (!type) movementAINovice(AIhead);
        if (type == 1) movementAIHard(AIhead);
    }
    teleport(head);
    teleport(AIhead);
    endGameCondition(timeGame);

    addTail(AIscore,AIhead,AIlengthTail);
    addTail(playerScore,head,lengthTail);
}
void AIeyes()
{
    for (int y = 0; y <= arenaHeight; y++)
        for (int x = 0; x <= arenaWidth; x++) battlefield[y][x]=1;
    battlefield[head.y][head.x] = 0;
    for (int i = 0; i <= lengthTail; i++) battlefield[tail[i].y][tail[i].x] = 0;
    for (int i = 0; i <= AIlengthTail; i++) battlefield[AItail[i].y][AItail[i].x] = 0;
    for (int j = 1; j < arenaHeight; j++) battlefield[0][j] = battlefield[arenaWidth-1][j];
    for (int j = 1; j < arenaHeight; j++) battlefield[arenaWidth][j] = battlefield[1][j];
    for (int i = 1; i < arenaWidth; i++) battlefield[i][0] = battlefield[i][arenaHeight-1];
    for (int i = 1; i < arenaWidth; i++) battlefield[i][arenaHeight] = battlefield[i][1];
}
void movementTail(coordinates &headSnake,coordinates tailSnake[],int lengthTailSnake)
{
    coordinates prev,aux;
	prev.x = tailSnake[0].x;
	prev.y = tailSnake[0].y;
	tailSnake[0].x = headSnake.x;
	tailSnake[0].y = headSnake.y;
	for (int i = 0; i <= lengthTailSnake; i++)
	{
		aux.x = tailSnake[i].x;
		aux.y = tailSnake[i].y;
		tailSnake[i].x = prev.x;
		tailSnake[i].y = prev.y;
		prev.x = aux.x;
		prev.y = aux.y;
	}
}
void movementPlayer()
{
    switch (Goes)
    {
    case LEFT:
        head.y--;
        break;
    case RIGHT:
        head.y++;
        break;
    case UP:
        head.x--;
        break;
    case DOWN:
        head.x++;
        break;
    default:
        break;
    }
}
void movementAINovice(coordinates &AIhead)
{
    int y, x;
    bool GORIGHT = battlefield[AIhead.y][AIhead.x+1];
    bool GOLEFT  = battlefield[AIhead.y][AIhead.x-1];
    bool GOUP    = battlefield[AIhead.y-1][AIhead.x];
    bool GODOWN  = battlefield[AIhead.y+1][AIhead.x];
    if(GOUP==0&&GODOWN==0&&GOLEFT==0&&GORIGHT==1)
    {
        AIhead.x++;
    }
    else
    if(GOUP==0&&GODOWN==0&&GOLEFT==1&&GORIGHT==0)
    {
        AIhead.x--;
    }
    else
    if(GOUP==0&&GODOWN==1&&GOLEFT==0&&GORIGHT==0)
    {
        AIhead.y++;
    }
    else
    if(GOUP==1&&GODOWN==0&&GOLEFT==0&&GORIGHT==0)
    {
        AIhead.y--;
    }
    else
    if(GOUP==0&&GODOWN==1&&GOLEFT==0&&GORIGHT==1)
    {
        if(fruit.x>AIhead.x)
        AIhead.x++;
        else
        AIhead.y++;
    }
    else
      if(GOUP==1&&GODOWN==0&&GOLEFT==0&&GORIGHT==1)
    {
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
                while(battlefield[y][AIhead.x]==0&&y>0)
                    y--;
                    y++;
                if(battlefield[y][AIhead.x+1]==1)
                    AIhead.x++;
                else
                   AIhead.x--;
            }
            else
             {
                while(battlefield[y][AIhead.x]==0&&y>arenaHeight)
                    y++;
                     y--;
                if(battlefield[y][AIhead.x+1]==1)
                    AIhead.x++;
                else
                   AIhead.x--;
            }
        }
    else
      if(GOUP==1&&GODOWN==0&&GOLEFT==1&&GORIGHT==0)
    {
        if(fruit.x<AIhead.x)
        AIhead.x--;
        else
        AIhead.y--;
    }
     else
      if(GOUP==0&&GODOWN==1&&GOLEFT==1&&GORIGHT==0)
    {
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
                while(battlefield[AIhead.y][x]==0&&x>0)
                    x--;
                x++;
                if(battlefield[AIhead.y+1][x]==1)
                    AIhead.y++;
                else
                   AIhead.y--;
            }
            else
             {
                while(battlefield[AIhead.y][x]==0&&x>arenaWidth)
                    x++;
                    x--;
                if(battlefield[AIhead.y+1][x]==1)
                    AIhead.y++;
                else
                   AIhead.y--;
            }
        }
    else
    if(GOUP==1&&GODOWN==1&&GOLEFT==0&&GORIGHT==1)
    {
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
void teleport(coordinates &B)
{
    if (B.x>=arenaWidth)
        B.x=1;
    else
       if (B.x<=0)
         B.x=arenaWidth-1;
	if (B.y>=arenaHeight)
	     B.y=1;
           else
    if (B.y<=0)
     B.y=arenaHeight - 1;
}
void endGameCondition(int timeGame)
{
    if(head.x==AIhead.x&&head.y==AIhead.y)
  {
      gameOver=true;
       lose=true;
  }
  else
  {
    for (int i=0;i<=lengthTail;i++)
		if(tail[i].x==head.x&&tail[i].y==head.y)
			{gameOver=true;lose=true;}
    for (int i=0;i<=AIlengthTail;i++)
		if (AItail[i].x==head.x&&AItail[i].y==head.y)
            {gameOver=true;lose=true;}
    for (int i=0;i<=lengthTail;i++)
		if (tail[i].x==AIhead.x&&tail[i].y==AIhead.y)
			{gameOver=true;lose=false;}
    for (int i=0;i<=AIlengthTail;i++)
    	if (AItail[i].x==AIhead.x&&AItail[i].y==AIhead.y)
            {gameOver=true;lose=false;}
  }
  if(TimeUp-TimeStart>=timeGame)
  {
      gameOver=true;
      if(playerScore>AIscore)
        lose=false;
      else
        lose=true;
  }
  else
    time(&TimeUp);
}
void addTail(int &score,coordinates headSnake,int &lengthTailSnake)
{
    if (headSnake.x == fruit.x && headSnake.y == fruit.y)
    {
        score += 10;
        lengthTailSnake++;
        putObject(fruit);
    }
}
void drawCombat(int timeGame)
{
    for (int y = 0; y <= arenaHeight; y++)
        for (int x = 0; x <= arenaWidth; x++)
            if (!y || !x || x == arenaWidth || y == arenaHeight) arena[y][x] = '#';
            else arena[y][x] = ' ';

    arena[head.y][head.x] = 'O';
    arena[AIhead.y][AIhead.x] = 'X';
    arena[fruit.y][fruit.x] = 'F';

    for (int i = 1; i <= lengthTail; i++) arena[tail[i].y][tail[i].x] = 'o';
    for (int i = 1; i <= AIlengthTail; i++) arena[AItail[i].y][AItail[i].x] = 'x';

    for (int y = 1; y < arenaHeight; y++)
        for (int x = 1; x < arenaWidth; x++)
        {
            if (arena[y][x] == 'O' || arena[y][x] == 'o') loadCombatImage("graphics/Snake/snake.png",y,x);
            else if (arena[y][x] == 'F') loadCombatImage("graphics/powerups/1.png",y,x);
                else if (arena[y][x] == 'X' || arena[y][x] == 'x') loadCombatImage("graphics/Snake/AI.png",y,x);
        }

    std::stringstream aux1, aux2, aux3;

    int x = timeGame - (int)(TimeUp - TimeStart);
    aux1 << x;
    timeCombat.setString(aux1.str().c_str());
    window.draw(timeCombat);

    aux2 << playerScore;
    textScorePlayer.setString(aux2.str().c_str());
    window.draw(textScorePlayer);

    aux3 << AIscore;
    textScoreAI.setString(aux3.str().c_str());
    window.draw(textScoreAI);
}
void timeOn()
{
    time(&TimeUp);
    TimeStart = TimeUp;
}
void putObject(coordinates &object)
{
    object.x = rand() % (arenaWidth - 1) + 1;
    object.y = rand() % (arenaHeight - 1) + 1;

    if (head.x == object.x && head.y == object.y) putObject(object);
    else for (int i = 0; i <= lengthTail; i++)
            if (tail[i].x == object.x && tail[i].y == object.y) putObject(object);
    if (AIhead.x == object.x && AIhead.y == object.y) putObject(object);
    else for (int i = 0; i <= AIlengthTail; i++)
            if (AItail[i].x == object.x && AItail[i].y == object.y) putObject(object);
}
int fail()
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
                    write();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(backButton))
                        {
                            resetGameCombat();
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
        displayFail();
    }
}
void displayFail()
{
    window.clear();
    window.draw(loserImage);
    window.draw(backImage);
    window.draw(resetImage);
    window.display();
}
int wonWon()
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
                    write();
                    exit(0);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (Event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (pressButton(backButton))
                        {
                            resetGameCombat();
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
        displayWonWon();
    }
}
void displayWonWon()
{
    window.clear();
    window.draw(winnerImage);
    window.draw(backImage);
    window.draw(resetImage);
    window.display();
}
void resetGameCombat()
{
    for (int i = 0; i <= lengthTail; ++i) tail[i].y = tail[i].x = 0;
    for (int i = 0; i <= AIlengthTail; ++i) AItail[i].y = AItail[i].x = 0;
    lengthTail = AIlengthTail = 0;
    for (int y = 0; y <= arenaHeight; ++y)
        for (int x = 0; x <= arenaHeight; ++x)
            arena[y][x] = ' ';
}
void displayNovice(int timeGame)
{
    window.clear();
    window.draw(menuSasserImage);
    window.draw(backImage);

    std::stringstream aux1, aux2, aux3;

    aux1 << timeGame;
    timeCombat.setString(aux1.str().c_str());
    window.draw(timeCombat);

    aux2 << playerScore;
    textScorePlayer.setString(aux2.str().c_str());
    window.draw(textScorePlayer);

    aux3 << AIscore;
    textScoreAI.setString(aux3.str().c_str());
    window.draw(textScoreAI);

    loadCombatImage("graphics/Snake/snake.png",head.y,head.x);
    loadCombatImage("graphics/Snake/AI.png",AIhead.y,AIhead.x);
    loadCombatImage("graphics/powerups/1.png",fruit.y,fruit.x);
    window.display();
}
int hardMode(int timer, int pos)
{
    int start = 0;
    setupCombat();
    loadTexts();
    int timeGame;
    if (!timer || timer == 3) timeGame = 60;
    if (timer == 1 || timer == 4) timeGame = 120;
    if (timer == 2 || timer == 5) timeGame = 180;
    window.setFramerateLimit(10);
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
                        resetGameCombat();
                        write();
                        exit(0);
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (Event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (pressButton(backButton))
                            {
                                gameOver = true;
                                resetGameCombat();
                                return 0;
                                break;
                            }
                        }
                    case sf::Event::KeyPressed:
                        start++;
                        if (start == 1) timeOn();
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {if (Goes != DOWN) Goes = UP; break;}
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {if (Goes != LEFT) Goes = RIGHT; break;}
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {if (Goes != UP) Goes = DOWN; break;}
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {if (Goes != RIGHT) Goes = LEFT; break;}
                    default:
                        break;
                }
            }
        if (!start) displayHard(timeGame);
        else gameHard(timeGame);
        }
        if (gameOver)
        {
            window.clear();
            window.draw(menuStuxnetImage);
            window.draw(backImage);
            drawCombat(timeGame);
            window.display();
            sf::sleep(sleepCombat);
            if (lose)
                if (!fail()) return 0;
                else
                {
                    resetGameCombat();
                    setupCombat();
                    start = 0;
                }
            else
            {
                B1[pos].hardWin = 1;
                write();
                if (!wonWon()) return 0;
                else
                {
                    resetGameCombat();
                    setupCombat();
                    start = 0;
                }
            }
        }
    }
}
void gameHard(int timeGame)
{
    window.clear();
    window.draw(menuStuxnetImage);
    window.draw(backImage);
    logicCombat(timeGame,1);
    drawCombat(timeGame);
    window.display();
}
void favorableCase(bool &AImove,int GOLEFT,int GORIGHT,int GOUP,int GODOWN)
{
    if(fruit.x!=AIhead.x&&AImove==false)
    {if(fruit.x>AIhead.x)
        {if((AIhead.x+width-2-fruit.x)<(fruit.x-AIhead.x))
          {if(GOLEFT==1)
          {AIhead.x--;AImove=true;}}
         else
            {if(GORIGHT==1)
              {AIhead.x++;AImove=true;}}
              if(AImove==false)
                if(AIhead.x>fruit.x)
              {
                  if(GOLEFT)
                    {AIhead.x--;AImove=true;}
              }
              else
               {
                  if(GORIGHT)
                    {AImove=true;AIhead.x++;}
              }
        }
        else
        {
           if((width-2+fruit.x-AIhead.x)<(AIhead.x-fruit.x))
             {if(GORIGHT==1)
              {AIhead.x++;AImove=true;}}
         else
            {if(GOLEFT==1)
            {AIhead.x--;AImove=true;}}

            if(AImove==false)
                   if(AIhead.x>fruit.x)
              {
                  if(GOLEFT)
                    {AIhead.x--;AImove=true;}
              }
              else
               {
                  if(GORIGHT)
                    {AIhead.x++;AImove=true;}
              }
        }
    }

      if(fruit.y!=AIhead.y&&AImove==false)
      if(fruit.y>AIhead.y)
        {if((AIhead.y+height-2-fruit.y)<(fruit.y-AIhead.y))
          {if(GOUP==1)
          {AIhead.y--;AImove=true;}}
         else
            {if(GODOWN==1)
            {AIhead.y++;AImove=true;}}

                  if(AImove==false)
                   if(AIhead.y>fruit.y)
              {
                  if(GOUP)
                    {AIhead.y--;AImove=true;}
              }
              else
               {
                  if(GODOWN)
                    {AIhead.y++;AImove=true;}
              }
        }
        else
        {
           if((height-2+fruit.y-AIhead.y)<(AIhead.y-fruit.y))
             {if(GODOWN)
             {AIhead.y++;AImove=true;}}
         else
             {if(GOUP==1)
          {AIhead.y--;AImove=true;}}

               if(AImove==false)
                   if(AIhead.y>fruit.y)
              {
                  if(GOUP)
                    {AIhead.y--;AImove=true;}
              }
              else
               {
                  if(GODOWN)
                    {AIhead.y++;AImove=true;}
              }
        }
}
void worstCase(int GOLEFT,int GORIGHT,int GOUP,int GODOWN)
{
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
void movementAIHard(coordinates &AIhead)
{
    bool AImove=false;
    bool GORIGHT = battlefield[AIhead.y][AIhead.x+1];
    bool GOLEFT  = battlefield[AIhead.y][AIhead.x-1];
    bool GOUP    = battlefield[AIhead.y-1][AIhead.x];
    bool GODOWN  = battlefield[AIhead.y+1][AIhead.x];
    int s,j;
if(GOUP==0&&GODOWN==0&&GOLEFT==1&&GORIGHT==1)
    {AImove=true;
            s=AIhead.x;
                j=AIhead.x;
                while(battlefield[AIhead.y][s]==1&&battlefield[AIhead.y][j]==1&&s>0&&j<arenaWidth)
                 {
                     s--;j++;
                 }
                   if(s==0)
                    {if(GOLEFT==1)
                    AIhead.x--;}
                 else
                 if(j==width)
                    {if(GORIGHT==1)
                    AIhead.x++;}
                    else
                 if(battlefield[AIhead.y][s]==1&&battlefield[AIhead.y][j]==0)
                 {
                     AIhead.x--;
                 }
                 else
                  if(battlefield[AIhead.y][s]==0&&battlefield[AIhead.y][j]==1)
                    {AIhead.x++;}
                      else
                  if(battlefield[AIhead.y][s]==1&&battlefield[AIhead.y][j]==1)
                    {AIhead.x++;}
                    else
                    {
                        if(AIhead.y>AItail[1].y)
                        {
                            s=AIhead.y;
                            while(battlefield[s][AIhead.x]==0&&s>0)
                                s--;
                            s++;
                            if(battlefield[s][AIhead.x+1]==1)
                                AIhead.x++;
                            else
                                AIhead.x--;
                        }
                        else
                        {
                            s=AIhead.y;
                            while(battlefield[s][AIhead.x]==0&&s<arenaHeight)
                                s++;
                            s--;
                            if(battlefield[s][AIhead.x+1]==1)
                                AIhead.x++;
                            else
                                AIhead.x--;
                        }
                    }
        }
  if(GOUP==1&&GODOWN==1&&GOLEFT==0&&GORIGHT==0)
            {
                AImove=true;
                s=AIhead.y;
                j=AIhead.y;
                while(battlefield[s][AIhead.x]==1&&battlefield[j][AIhead.x]==1&&s>0&&j>arenaHeight)
                 {
                     s--;j++;
                 }
                 if(s==0)
                    {if(GOUP==1)
                    AIhead.y--;}
                 else
                 if(j==height)
                 {if(GODOWN==1)
                    AIhead.y++;}
                    else
                 if(battlefield[s][AIhead.x]==1&&battlefield[j][AIhead.x]==0)
                 {
                     AIhead.y--;
                 }
                 else
                 if(battlefield[s][AIhead.x]==0&&battlefield[j][AIhead.x]==1)
                    {AIhead.y++;}
                 else
                  if(battlefield[s][AIhead.x]==1&&battlefield[j][AIhead.x]==1)
                    {AIhead.y--;}
                 else
                 {
                     if(AIhead.x>AItail[1].x)
                        {
                            s=AIhead.x;
                            while(battlefield[AIhead.y][s]==0&&s>0)
                                s--;
                            s++;
                            if(battlefield[AIhead.y+1][s]==1)
                                AIhead.y++;
                            else
                                AIhead.y--;
                        }
                        else
                        {
                            s=AIhead.y;
                            while(battlefield[AIhead.y][s]==0&&s<arenaWidth)
                                s++;
                            s--;
                            if(battlefield[AIhead.y+1][s]==1)
                                AIhead.y++;
                            else
                                AIhead.y--;
                        }
                 }
        }
     if (AImove == false) favorableCase(AImove,GOLEFT,GORIGHT,GOUP,GODOWN);
     if (AImove == false) worstCase(GOLEFT,GORIGHT,GOUP,GODOWN);
}
void displayHard(int timeGame)
{
    window.clear();
    window.draw(menuStuxnetImage);
    window.draw(backImage);

    std::stringstream aux1, aux2, aux3;

    aux1 << timeGame;
    timeCombat.setString(aux1.str().c_str());
    window.draw(timeCombat);

    aux2 << playerScore;
    textScorePlayer.setString(aux2.str().c_str());
    window.draw(textScorePlayer);

    aux3 << AIscore;
    textScoreAI.setString(aux3.str().c_str());
    window.draw(textScoreAI);

    loadCombatImage("graphics/Snake/snake.png",head.y,head.x);
    loadCombatImage("graphics/Snake/AI.png",AIhead.y,AIhead.x);
    loadCombatImage("graphics/powerups/1.png",fruit.y,fruit.x);
    window.display();
}
int impossibleMode(int timer, int pos)
{
    int start = 0;
    setupCombat();
    loadTexts();
    int timeGame;
    if (!timer || timer == 3) timeGame = 60;
    if (timer == 1 || timer == 4) timeGame = 120;
    if (timer == 2 || timer == 5) timeGame = 180;
    window.setFramerateLimit(10);
    while (window.isOpen())
    {
        while (!gameOver)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {if (Goes != DOWN) Goes = UP; start++;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {if (Goes != LEFT) Goes = RIGHT; start++;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {if (Goes != UP) Goes = DOWN; start++;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {if (Goes != RIGHT) Goes = LEFT; start++;}
            if (start == 1) timeOn();
            while (window.pollEvent(Event))
            {
                switch (Event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        resetGameCombat();
                        write();
                        exit(0);
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (Event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (pressButton(backButton))
                            {
                                gameOver = true;
                                resetGameCombat();
                                return 0;
                                break;
                            }
                        }
                    default:
                        break;
                }
            }
        if (!start) displayImpossible(timeGame);
        else gameImpossible(timeGame);
        }
        if (gameOver)
        {
            window.clear();
            window.draw(menuILOVEYOUImage);
            window.draw(backImage);
            drawCombat(timeGame);
            window.display();
            sf::sleep(sleepCombat);
            if (lose)
                if (!fail()) return 0;
                else
                {
                    resetGameCombat();
                    setupCombat();
                    start = 0;
                }
            else
            {
                B1[pos].impossibleWin = 1;
                write();
                if (!wonWon()) return 0;
                else
                {
                    resetGameCombat();
                    setupCombat();
                    start = 0;
                }
            }
        }
    }
}
void gameImpossible(int timeGame)
{
    window.clear();
    window.draw(menuILOVEYOUImage);
    window.draw(backImage);
    logicCombat(timeGame,1);
    drawCombat(timeGame);
    window.display();
}
void displayImpossible(int timeGame)
{
    window.clear();
    window.draw(menuILOVEYOUImage);
    window.draw(backImage);

    std::stringstream aux1, aux2, aux3;

    aux1 << timeGame;
    timeCombat.setString(aux1.str().c_str());
    window.draw(timeCombat);

    aux2 << playerScore;
    textScorePlayer.setString(aux2.str().c_str());
    window.draw(textScorePlayer);

    aux3 << AIscore;
    textScoreAI.setString(aux3.str().c_str());
    window.draw(textScoreAI);

    loadCombatImage("graphics/Snake/snake.png",head.y,head.x);
    loadCombatImage("graphics/Snake/AI.png",AIhead.y,AIhead.x);
    loadCombatImage("graphics/powerups/1.png",fruit.y,fruit.x);
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
    barImage.setPosition(170,366 + (pos - 1) * 40);
    while (window.isOpen())
    {
        while (window.pollEvent(Event))
        {
            switch (Event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    resetGameSingle();
                    write();
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
                                int i = 5;
                                if (isLegend(nameEntered,i))
                                    if (B2[i].points >= score)
                                    {
                                        if (!retry()) return 0;
                                        else break;
                                    }
                                    else
                                    {
                                        for (; i < 6; ++i) B2[i] = B2[i+1];
                                        B2[pos].name = nameEntered;
                                        B2[pos].points = score;
                                        for (int j = 1; j < 6; ++j) B1[j] = B2[j];
                                        write();
                                        break;
                                    }
                                else
                                {
                                    B2[pos].name = nameEntered;
                                    B2[pos].points = score;
                                    for (int i = 1; i < 6; ++i) B1[i] = B2[i];
                                    write();
                                    break;
                                }
                            }
                        }
                    }
                }
                case sf::Event::TextEntered:
                    if (letters < 10)
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
    for (int i = 1; i < 6; ++i) B2[i] = B1[i];
    if (score - B2[5].points <= 0) return -1;
    for (int i = 5; i > 0; --i)
        if (B2[i].points >= score)
            return i+1;
        else B2[i] = B2[i-1];
    return 1;
}
bool isLegend(string s, int &i)
{
    for (; i > 0; --i)
    {
        size_t found = B2[i].name.find(s);
        if (found != string::npos && s == B2[i].name)
            return true;
    }
    return false;
}
int retry()
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
                    write();
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
        displayRetry();
    }
}
void displayRetry()
{
    window.clear();
    window.draw(retryImage);
    window.draw(backImage);
    window.draw(resetImage);
    window.display();
}
void displayGameOver1()
{
    window.clear();
    window.draw(menuGameOver1Image);
    window.draw(backImage);
    window.draw(resetImage);
    for (int i = 1; i < 6; ++i) window.draw(textGameOver[i]);
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
                    write();
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
