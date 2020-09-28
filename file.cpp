#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<bits/stdc++.h>
#include<sstream>

int main()
{
    /// Creating the window and setting the video mode

    sf::RenderWindow window(sf::VideoMode(800,600),"Sfml Game");

    /// setting the framerate limit to 100fps

    window.setFramerateLimit(100);

    ///Game Loop , play is the variable which keeps the gameloop running

    window.setKeyRepeatEnabled(false);
    bool play = true;

    ///creating the event
    sf::Event event;

    /// states

    bool up = false;
    bool down = false;

    ///variables

    int yVelocityPad1=0;
    int xVelocityBall=-5;
    int yVelocityBall=-5;
    int yVelocityPad2 = 0;
    int pad1Score = 0, pad2Score = 0;

    ///images and textures
    sf::Texture tex_Pad;
    sf::Texture tex_ball;
    sf::Texture tex_background;
    tex_Pad.loadFromFile("data/pad.png");
    tex_ball.loadFromFile("data/ball.png");
    tex_background.loadFromFile("data/background.png");

    ///background

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(800,600));
    background.setPosition(0,0);
    background.setTexture(&tex_background);

    ///pad1

    sf::RectangleShape pad1;
    pad1.setSize(sf::Vector2f(50,100));
    pad1.setPosition(50,200);
    pad1.setTexture(&tex_Pad);

    ///pad2

    sf::RectangleShape pad2;
    pad2.setSize(sf::Vector2f(50,100));
    pad2.setPosition(700,200);
    pad2.setTexture(&tex_Pad);

    ///ball
    sf::RectangleShape ball;
    ball.setSize(sf::Vector2f(50,50));
    ball.setPosition(400,200);
    ball.setTexture(&tex_ball);

    ///font

    sf::Font font;
    font.loadFromFile("data/crazyivanhalf.ttf");

    /// text

    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setColor(sf::Color::White);
    score.setPosition(380,10);

    ///Sounds

    sf::SoundBuffer buff_hit;
    buff_hit.loadFromFile("data/hit.wav");
    sf::Sound hit;
    hit.setBuffer(buff_hit);
    hit.setVolume(20);

    ///music

    sf::SoundBuffer bgm;
    bgm.loadFromFile("data/bgm.wav");
    sf::Sound bgmPlay;
    bgmPlay.setBuffer(bgm);
    bgmPlay.play();
    bgmPlay.setLoop(true);
    while(play == true)
    {
        ///EVENTS

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                play = false;
            }
            ///keypressed

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
            {
                up = true;
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
            {
                down = true;
            }

            ///keyreleased

            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up)
            {
                up = false;
            }
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
            {
                down = false;
            }
        }
        ///LOGIC

        ///movement Pad1

        if(up == true)
        {
            yVelocityPad1 = -5;
        }
        if(down == true)
        {
            yVelocityPad1 = 5;
        }
        if(up == true && down == true)
        {
            yVelocityPad1 = 0;
        }
        if(up == false && down == false)
        {
            yVelocityPad1 = 0;
        }
        pad1.move(0,yVelocityPad1);

        /// logic pad2

        if(ball.getPosition().y < pad2.getPosition().y)
        {
            yVelocityPad2 = -3;
        }
        if(ball.getPosition().y > pad2.getPosition().y)
        {
            yVelocityPad2 = 3;
        }
        pad2.move(0,yVelocityPad2);

        ///movement ball

        ball.move(xVelocityBall,yVelocityBall);

        ///out of bounds check

        if(pad1.getPosition().y < 0)
        {
            pad1.setPosition(50,0);
        }
        if(pad1.getPosition().y > 500)
        {
            pad1.setPosition( 50,500);
        }
        if(pad2.getPosition().y < 0)
        {
            pad1.setPosition(700,0);
        }
        if(pad2.getPosition().y > 500)
        {
            pad1.setPosition( 700,500);
        }
        if(ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) == true)
        {
            xVelocityBall = -xVelocityBall;
            hit.play();
        }
        if(ball.getGlobalBounds().intersects(pad2.getGlobalBounds()) == true)
        {
            xVelocityBall = -xVelocityBall;
            hit.play();
        }

        ///ball out of bounds

        if(ball.getPosition().y < 0)
        {
            yVelocityBall = -yVelocityBall;
        }
        if(ball.getPosition().y > 550)
        {
            yVelocityBall = -yVelocityBall;
        }
        if(ball.getPosition().x < -50)
        {
            pad2Score++;
            ball.setPosition(300,200);
        }
        if(ball.getPosition().x > 800)
        {
            pad1Score++;
            ball.setPosition(300,200);
        }

        ///RENDERING

        window.clear();
        window.draw(background);
        window.draw(pad1);
        window.draw(pad2);
        window.draw(ball);

        /// score

        std::stringstream text;
        text << pad1Score << " : " << pad2Score;
        score.setString(text.str());
        window.draw(score);
        window.display();
    }
    ///
    /// Clean up
    window.close();
    return 0;

}