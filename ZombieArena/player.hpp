//
//  player.hpp
//  ZombieArena
//
//  Created by Cian Farrell on 25/10/2022.
//

#ifndef player_hpp
#define player_hpp

#include <SFML/Graphics.hpp>
#include <math.h>

using namespace sf;

class Player{
private:
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    Vector2f m_Position, m_Resolution;
    Sprite m_Sprite;
    Texture m_Texture;
    IntRect m_Arena;
    int m_TileSize, m_Health, m_MaxHealth;
    bool m_UpPressed, m_DownPressed, m_LeftPressed, m_RightPressed;
    Time m_LastHit;
    float m_Speed;
public:
    Player();
    void spawn(IntRect arena, Vector2f resolution, int tileSize);
    void resetPlayerStats();
    bool hit(Time timeHit);
    Time getLastHitTime();
    FloatRect getPosition();
    Vector2f getCenter();
    float getRotation();
    Sprite getSprite();
    int getHealth();
    void moveLeft(), moveRight(), moveUp(), moveDown();
    void stopLeft(), stopRight(), stopUp(), stopDown();
    void update(float elapsedTime, Vector2i mousePosition);
    void upgradeSpeed();
    void upgradeHealth();
    void increaseHealthLevel(int amount);
    
};

#endif /* player_hpp */


