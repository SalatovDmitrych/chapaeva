#include "game.hpp"
#include "physics.hpp"

int Shashka::whitesCount = objectsCount / 2;
int Shashka::redsCount = objectsCount / 2;

Game::Game()
{
    boardTexture.loadFromFile("res/board.png");
    boardSprite.setTexture(boardTexture);
    boardSprite.setOrigin(boardTexture.getSize().x / 2, boardTexture.getSize().y / 2);
    boardSprite.setPosition(400, 400);

    window.create(sf::VideoMode(800, 800), "chapaeva");

    currentSide = WHITE;
    moveIndexer.setRadius(RADIUS);
    moveIndexer.setFillColor(sf::Color::White);
    moveIndexer.setPosition(750, 750);
    newGame(7, 0);
}

void Game::newGame(const int whiteLn, const int redLn)
{
    playerMadeMove = false;
    currentMove = 1;

    Shashka::redsCount = objectsCount / 2;
    Shashka::whitesCount = objectsCount / 2;

    whiteLine = whiteLn;
    redLine = redLn;


    for (int i = 0, s = 1; i < objectsCount; i++, s *= -1)
    {
        if (s < 0)
            objects[i].setSide(RED);
        else
            objects[i].setSide(WHITE);
    }

    for (int i = 0, x = 225; i < objectsCount; i += 2, x += 50)
    {
        objects[i].setPos(x, 225 + 50 * whiteLn);
        objects[i].putOnBoard();
        objects[i].setVelocity(0, 0);
        objects[i].update(0, objects, objectsCount, currentMove);

        objects[i + 1].setPos(x, 225 + 50 * redLn);
        objects[i + 1].putOnBoard();
        objects[i + 1].setVelocity(0, 0);
        objects[i + 1].update(0, objects, objectsCount, currentMove);
    }

    currentSh = nullptr;
}

void Game::start()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        float delta = dt.asSeconds();


        input();
        update(delta);
        draw();

        if (allChekersStop() && playerMadeMove)
        {
            changeSide();
            currentMove++;
            playerMadeMove = false;

            if (Shashka::whitesCount < 1 || Shashka::redsCount < 1)
                changeLine();
        if (currentSide == WHITE)
            moveIndexer.setFillColor(sf::Color::White);
        else
            moveIndexer.setFillColor(sf::Color::Red);
        }

    }
}

void Game::changeLine()
{
    int whiteStep = 0;
    int redStep = 0;

    if (whiteLine > redLine)
    {
        whiteStep = -1;
        redStep = 1;
    }
    else
    {
        whiteStep = 1;
        redStep = -1;
    }

    if (Shashka::redsCount < 1)
    {
        if (whiteLine + whiteStep == redLine)
        {
            if (redLine - redStep < 0 || redLine - redStep == NUM_OF_BOARD_LINES)
            {
                endGame(WHITE);
                newGame(0, 7);
                currentSide = WHITE;
            }
            else
            {
                newGame(whiteLine + whiteStep, redLine - redStep);
                currentSide = WHITE;
            }
        }
        else
        {
            newGame(whiteLine + whiteStep, redLine);
            currentSide = WHITE;
        }
    }
    else
    {
        if (redLine + redStep == whiteLine)
        {
            if (whiteLine - whiteStep < 0 || whiteLine - whiteStep == NUM_OF_BOARD_LINES)
            {
                endGame(RED);
                newGame(0, 7);
                currentSide = WHITE;
            }
            else
            {
                newGame(whiteLine - whiteStep, redLine + redStep);
                currentSide = RED;
            }
        }
        else
        {
            newGame(whiteLine, redLine + redStep);
            currentSide = RED;
        }
    }
}

void Game::endGame(const Side s)
{
    if (s == WHITE)
        endGameTexture.loadFromFile("res/whites win.png");
    else
        endGameTexture.loadFromFile("res/reds win.png");

    endGameSprite.setTexture(endGameTexture);
    endGameSprite.setOrigin(60, 15);
    endGameSprite.setPosition(400, 100);

    window.draw(endGameSprite);
    window.display();


    //Ожидаем нажатие любой клавиши
    sf::Event event;
    bool stop = false;
    while (!stop)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                stop = true;
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    stop = true;
                    window.close();
                }
                else
                    stop = true;
            }
        }
    }
}

bool Game::allChekersStop()
{
    for (int i = 0; i < objectsCount; i++)
    {
        if (objects[i].getVelocity() != sf::Vector2f(0, 0) && objects[i].onBoard())
            return false;
    }

    return true;
}

void Game::changeSide()
{
    bool chekersKnockedOut = false;

    for (int i = 0; i < objectsCount; i++)
    {
        if (objects[i].onBoard())
            continue;

        if (objects[i].whenOut() == currentMove)
        {
            chekersKnockedOut = true;

            if (objects[i].getSide() == currentSide)
            {
                currentSide = currentSide == WHITE ? RED : WHITE;
                break;
            }
        }
    }

    if (!chekersKnockedOut)
        currentSide = currentSide == WHITE ? RED : WHITE;
}

sf::Vector2f Game::mousePos(const sf::RenderWindow &w) const
{
    return w.mapPixelToCoords(sf::Mouse::getPosition(w));
}

sf::VertexArray Game::getArrowToChecker(const Shashka &s) const
{
    sf::VertexArray arrow(sf::Triangles);

    sf::Vector2f mouse = mousePos(window);

    sf::Vector2f toChecker = s.getPos() - mouse; //Вектор от мыши к центру шашки

    float distance = vecLen(toChecker);
    float halfOfBase = 15.0f; //Половина основания стрелки

    if (distance > RADIUS)
    {
        toChecker = normalize(toChecker);

        arrow.append( sf::Vertex(mouse + toChecker * (distance - RADIUS), sf::Color::Blue) );

        toChecker = sf::Vector2f(-toChecker.y, toChecker.x); //Поворачиваем вектор на 90 градусов

        arrow.append( sf::Vertex(mouse + toChecker * halfOfBase, sf::Color::Blue) );

        arrow.append( sf::Vertex(mouse + toChecker * -halfOfBase, sf::Color::Blue) );
    }

    return arrow;
}
