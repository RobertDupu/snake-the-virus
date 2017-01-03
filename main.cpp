#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <stdlib.h>
#define width 800
#define height 600

using namespace std;

sf::Sprite menuImage, menuPlayImage, menuScoreImage, menuQuitImage, menuArenaImage, playButtonImage, scoreButton1Image, scoreButton2Image, abortButton1Image, abortButton2Image, abortButton3Image, onePlayerImage, twoPlayersImage, ayeImage, nopeImage, backImage;
sf::Texture menuTexture, menuPlayTexture, menuScoreTexture, menuQuitTexture, menuArenaTexture, playButtonTexture, scoreButton1Texture, abortButton1Texture, onePlayerTexture, twoPlayersTexture, ayeTexture, nopeTexture, backTexture;
sf::Font font1;
sf::Event Event;
sf::RenderWindow window(sf::VideoMode(width, height), "Snake the Virus", sf::Style::Close);
sf::Text text[6];

struct coordonates
{
    int x, y, h, w;
};
coordonates menu, menuPlay, menuScore, menuQuit, menuArena, playButton, scoreButton1, scoreButton2, abortButton1, abortButton2, abortButton3, onePlayer, twoPlayers, aye, nope, backk;

struct board
{
    string nume, points;
};
board B[6];

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
int playMode();
int singleMode();
int combatMode();
int scoreMode();
int byeByeMode();

int main()
{
    loadImages();
    loadTextures();
    loadPosition();
    loadFonts();

    ifstream fin ("scoreboard.in");
    for (int i=0; i<5; ++i)
    {
        fin>>B[i].nume;
        fin.get();
        fin>>B[i].points;
        fin.get();
    }
    fin.close();

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
                    if (Event.mouseButton.button==sf::Mouse::Left)
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
        }
        displayMenu();
    }
    return 0;
}
bool pressButton(coordonates button)
{
    int currentX, currentY;
    currentX = Event.mouseButton.x;
    currentY = Event.mouseButton.y;
    return (currentX >= button.x && currentX <= button.x + button.w && currentY >= button.y && currentY <= button.y + button.h);
}
void putPosition(coordonates &button,int a,int b,int c,int d)
{
    button.x=a;
    button.y=b;
    button.h=c;
    button.w=d;
}
void loadImages()
{
    menuTexture.loadFromFile("grafica/menu/menu1clean.png");
    menuPlayTexture.loadFromFile("grafica/menu/play/playmodeclean.png");
    menuScoreTexture.loadFromFile("grafica/menu/scoreboard/scoreboardclean.png");
    menuQuitTexture.loadFromFile("grafica/menu/quit/quitclean.png");
    menuArenaTexture.loadFromFile("grafica/Arena/arenaclean.png");

    playButtonTexture.loadFromFile("grafica/menu/play/playbutton.png");
    scoreButton1Texture.loadFromFile("grafica/menu/scoreboard/scoreboardbutton.png");
    abortButton1Texture.loadFromFile("grafica/menu/quit/quitbutton.png");

    onePlayerTexture.loadFromFile("grafica/menu/play/1player.png");
    twoPlayersTexture.loadFromFile("grafica/menu/play/2player.png");

    ayeTexture.loadFromFile("grafica/menu/quit/aye.png");
    nopeTexture.loadFromFile("grafica/menu/quit/nope.png");

    backTexture.loadFromFile("grafica/Arena/back.png");
}
void loadTextures()
{
    menuImage.setTexture(menuTexture);
    menuPlayImage.setTexture(menuPlayTexture);
    menuScoreImage.setTexture(menuScoreTexture);
    menuQuitImage.setTexture(menuQuitTexture);
    menuArenaImage.setTexture(menuArenaTexture);

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
}
void loadPosition()
{
    menuImage.setPosition(0,0);
    putPosition(menu,0,0,height,width);
    menuPlayImage.setPosition(0,0);
    putPosition(menuPlay,0,0,height,width);
    menuScoreImage.setPosition(0,0);
    putPosition(menuScore,0,0,height,width);
    menuQuitImage.setPosition(0,0);
    putPosition(menuQuit,0,0,height,width);
    menuArenaImage.setPosition(0,0);
    putPosition(menuArena,0,0,height,width);

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
    putPosition(onePlayer,328,191,35,140);
    twoPlayersImage.setPosition(326,270);
    putPosition(twoPlayers,326,270,35,140);

    ayeImage.setPosition(367,404);
    putPosition(aye,367,404,35,60);
    nopeImage.setPosition(367,484);
    putPosition(nope,367,484,35,60);

    backImage.setPosition(40,40);
    putPosition(backk,40,40,35,90);
}
void loadFonts()
{
    font1.loadFromFile("fonts/RussoOne.ttf");
}
void loadTexts()
{
    text[1].setPosition(290,242);
    text[1].setFont(font1);
    text[1].setCharacterSize(33);
    text[1].setColor(sf::Color(0, 255, 255));

    text[2].setPosition(290,282);
    text[2].setFont(font1);
    text[2].setCharacterSize(33);
    text[2].setColor(sf::Color(0, 255, 255));

    text[3].setPosition(290,322);
    text[3].setFont(font1);
    text[3].setCharacterSize(33);
    text[3].setColor(sf::Color(0, 255, 255));

    text[4].setPosition(290,362);
    text[4].setFont(font1);
    text[4].setCharacterSize(33);
    text[4].setColor(sf::Color(0, 255, 255));

    text[5].setPosition(290,402);
    text[5].setFont(font1);
    text[5].setCharacterSize(33);
    text[5].setColor(sf::Color(0, 255, 255));

    for (int i=0; i<5; ++i)
        if (!B[i].nume.length()) text[i+1].setString("404 not found");
        else
        {
            string a=B[i].nume+' '+B[i].points;
            text[i+1].setString(a);
        }
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
void displayScore()
{
    window.clear();
    window.draw(menuScoreImage);
    for (int i=1; i<6; ++i) window.draw(text[i]);
    window.draw(playButtonImage);
    window.draw(scoreButton1Image);
    window.draw(abortButton3Image);
    window.display();
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
void displaySingle()
{
    window.clear();
    window.draw(menuArenaImage);
    window.draw(backImage);
    window.display();
}
void displayCombat()
{
    window.clear();
    window.draw(menuArenaImage);
    window.draw(backImage);
    window.display();
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
                {
                    if (Event.mouseButton.button==sf::Mouse::Left)
                    {
                        if (pressButton(playButton))
                        {
                            return 0;
                            break;
                        }
                        if (pressButton(onePlayer))
                        {
                            if (!singleMode()) return 0;
                            else break;
                        }
                        if (pressButton(twoPlayers))
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
        }
        displayPlay();
    }
}
int singleMode()
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
                    if (Event.mouseButton.button==sf::Mouse::Left)
                    {
                        if (pressButton(backk))
                        {
                            return 0;
                            break;
                        }
                    }
                }
            }
        }
        displaySingle();
    }
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
                    if (Event.mouseButton.button==sf::Mouse::Left)
                    {
                        if (pressButton(backk))
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
int scoreMode()
{
    ifstream fin ("scoreboard.in");
    for (int i=0; i<5; ++i)
    {
        fin>>B[i].nume;
        fin.get();
        fin>>B[i].points;
        fin.get();
    }
    fin.close();
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
                {
                    if (Event.mouseButton.button==sf::Mouse::Left)
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
        }
        displayScore();
    }
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
                {
                    if (Event.mouseButton.button==sf::Mouse::Left)
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
                        if (pressButton(aye))
                        {
                            window.close();
                            exit(0);
                            break;
                        }
                        if (pressButton(nope))
                        {
                            return 0;
                            break;
                        }
                    }
                }
            }
        }
        displayAbort();
    }
}
