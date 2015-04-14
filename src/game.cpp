#include "game.h"

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game() :
    mWindow(sf::VideoMode(640,480), "Readhead against rabbits", sf::Style::Close),
    mIsMovingUp(false),
    mIsMovingDown(false),
    mIsMovingRight(false),
    mIsMovingLeft(false)
{
    mWindow.setFramerateLimit(60);

    try
    {
        textures.load(Textures::Landscape, "Media/Textures/Desert.png");
        textures.load(Textures::Airplaine, "Media/Textures/Eagle.png");
    }
    catch (std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return;
    }

    mPlayer.setTexture(textures.get(Textures::Airplaine));
    mPlayer.setPosition(100.f, 100.f);

    mLandscape.setTexture(textures.get(Textures::Landscape));

    mFont.loadFromFile("Media/Sansation.ttf");
    mStatisticsText.setFont(mFont);
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10);

}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate = elapsedTime;
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::update(sf::Time elapsedTime)
{
    sf::Vector2f movement(0.f, 0.f);

    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;

    mPlayer.move(movement * elapsedTime.asSeconds());
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mLandscape);
    mWindow.draw(mPlayer);
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
    mStatisticsUpdateTime += elapsedTime;
    mStatisticsNumFrames += 1;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString(
            "Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
            "Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Z)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::Q)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}
