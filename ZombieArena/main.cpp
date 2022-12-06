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
#include "textureHolder.hpp"
#include "bullet.hpp"

int main()
{
    enum class State {PAUSED, LEVELING_UP,GAME_OVER,PLAYING};
    TextureHolder holder;
    
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
    Texture textureBackground = TextureHolder::GetTexture("../Resources/graphics/background_sheet.png");

    int numZombies = 0;
    int numZombiesAlive = 0;
    Zombie* zombies = nullptr;
    Bullet bullets[100];
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    float fireRate = 1;
    
    Time lastPressed;
    
    window.setMouseCursorVisible(false);
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("../Resources/graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    spriteCrosshair.setOrigin(25, 25);
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
            if(state == State::PLAYING){
                if(event.key.code == Keyboard::R){
                    if(bulletsSpare >= clipSize){
                        bulletsInClip = clipSize;
                        bulletsSpare -= clipSize;
                    }
                    else if(bulletsSpare > 0){
                        bulletsInClip = bulletsSpare;
                        bulletsSpare = 0;
                    }else{
                        //More Here
                    }
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
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                if(gameTimeTotal.asMilliseconds() - lastPressed.asMilliseconds() > 1000/fireRate && bulletsInClip>0){
                    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y,
                                                 mouseWorldPosition.x, mouseWorldPosition.y - resolution.y);
                    ++currentBullet;
                    if(currentBullet > 99){
                        currentBullet = 0;
                    }
                    lastPressed = gameTimeTotal;
                    bulletsInClip--;
                    
                }
            }
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
                
                numZombies = 10;
                delete[] zombies;
                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;
            }
        }
        //UPDATE THE FRAME
        
        if(state == State::PLAYING){
            Time dt = clock.restart();
            
            gameTimeTotal += dt;
            
            float dtAsSeconds = dt.asSeconds();
            
            mouseScreenPosition = Mouse::getPosition(window);
            
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(),mainView);
            spriteCrosshair.setPosition(mouseWorldPosition.x, mouseWorldPosition.y - resolution.y);
            player.update(dtAsSeconds,mouseScreenPosition);
            
            Vector2f playerPosition(player.getCenter());
            
            mainView.setCenter(playerPosition);
            
            for(int i = 0 ; i<numZombies;++i){
                if(zombies[i].isAlive()) zombies[i].update(dt.asSeconds(), playerPosition);
            }
            
            for(int i =0; i< 100; i++){
                if(bullets[i].isInFlight()){
                    bullets[i].update(dtAsSeconds);
                }
            }
        }
    
        //DRAW THE SCENE
        
        if(state == State::PLAYING){
            window.clear();
            
            window.setView(mainView);
            window.draw(background, &textureBackground);
            for(int i = 0; i< numZombies;++i){
                window.draw(zombies[i].getSprite());
            }
            for(int i = 0; i<100; i++){
                window.draw(bullets[i].getShape());
            }
            window.draw(player.getSprite());
            window.draw(spriteCrosshair);
        }
        if(state == State::LEVELING_UP){
            
        }
        if(state == State::PAUSED){
            
        }
        if(state == State::GAME_OVER){
            
        }

        window.display();
    }
    delete[]zombies;
    return 0;
}
