#ifndef GAME_H
#define GAME_H
#include "GameObject.h"
#include "Player.h"
#include "keyPressReader.h"
#include <iostream>
#include <string> 
#include <thread>
#include <chrono>
#include "Bullet.h"
#include <vector>
#include <algorithm>
class Game{
public:
    Game();
    ~Game();

    void run();
    void runManualInput();
    void update();
    void clearBullets();
    void moveBullets();
    void shootPlayerBullet();
    void movePlayerLeft();
    void movePlayerRight();

    friend std::ostream & operator<<(std::ostream & out, const Game & g);
    std::ostream & render(std::ostream & out)const;

    private:
        const int DEFAULT_ROWS = 27;
        const int DEFAULT_COLS = 36;
        Player * player;
        GameObject *** field; //matrix of pointers to GameObject
        std::vector<Bullet> bullets;
        bool gameOver;
        int tikSpeed;
        int reloadTime;

};
#endif