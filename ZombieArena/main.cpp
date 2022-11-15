//
//  main.cpp
//  ZombieArena
//
//  Created by Cian Farrell on 25/10/2022.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "main.hpp"
int main()
{
    enum class State {PAUSED, LEVELING_UP,GAME_OVER,PLAYING};
    
    State state = State::GAME_OVER;
    
    Vector2f resolution;
    
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;
    RenderWindow window(VideoMode(resolution.x,resolution.y),"Zombie Arena");
    View mainView(sf::FloatRect(0,0,resolution.x,resolution.y));
    
    Clock clock;
    
    Time gameTimeTotal;
    
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    
    Player player;
    IntRect arena;
    
    VertexArray background;
    Texture textureBackground;
    textureBackground.loadFromFile("../Resources/graphics/background_sheet.png");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Return && state == State::PLAYING){
                    state = State::PAUSED;
                    
                }
                else if(event.key.code == Keyboard::Return && state == State::PAUSED){
                    state = State::PLAYING;
                    clock.restart();
                }else if(event.key.code == Keyboard::Return && state == State::GAME_OVER){
                    state = State::LEVELING_UP;
                }
                if(state == State::PLAYING){
                    
                }
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }

        //Handles controls
        if(state == State::PLAYING){
            if(Keyboard::isKeyPressed(Keyboard::W)){
                player.moveUp();
            }else player.stopUp();
            
            if(Keyboard::isKeyPressed(Keyboard::S))
                player.moveDown();
            else player.stopDown();
            if(Keyboard::isKeyPressed(Keyboard::A))
                player.moveLeft();
            else player.stopLeft();
            if(Keyboard::isKeyPressed(Keyboard::D))
                player.moveRight();
            else player.stopRight();
        }
        //Handles leveling up state
        if(state == State::LEVELING_UP){
            if(event.key.code == Keyboard::Num1){
                state = State::PLAYING;}
            if(event.key.code == Keyboard::Num2){
                state = State::PLAYING;}
            if(event.key.code == Keyboard::Num3){
                state = State::PLAYING;}
            if(event.key.code == Keyboard::Num4){
                state = State::PLAYING;}
            if(event.key.code == Keyboard::Num5){
                state = State::PLAYING;}
            if(event.key.code == Keyboard::Num6){
                state = State::PLAYING;}
            
            if(state == State::PLAYING){
               //Prepare the level
                
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;
                
                int tileSize = createBackground(background,arena);
                
                player.spawn(arena, resolution, tileSize);
                
                clock.restart();
            }
        }
        //UPDATE THE FRAME
        if(state == State::PLAYING){
            Time dt = clock.restart();
            
            gameTimeTotal += dt;
            
            float dtAsSeconds = dt.asSeconds();
            
            mouseScreenPosition = Mouse::getPosition(window);
            
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(),mainView);
            
            player.update(dtAsSeconds,mouseScreenPosition);
            
            Vector2f playerPosition(player.getCenter());
            
            mainView.setCenter(playerPosition);
        }
    
        //DRAW THE SCENE
        
        if(state == State::PLAYING){
            window.clear();
            
            window.setView(mainView);
            window.draw(background, &textureBackground);
            window.draw(player.getSprite());
        }
        if(state == State::LEVELING_UP){
            
        }
        if(state == State::PAUSED){
            
        }
        if(state == State::GAME_OVER){
            
        }

        window.display();
    }

    return 0;
}
