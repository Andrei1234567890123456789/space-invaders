#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
    class Player : public GameObject{
        public:
            Player();
            Player(int, int);
            Player(const Player &);
            Player & operator=(const Player &);
            ~Player();

            void goLeft();
            void goRight();
            GameObject shoot();

            int getScore()const;
            int getLives()const;
            int getReload()const;

            void setLives(int l);
            void decLives();
            void setScore(int s);
            void incScore(int s);
            void setReload(int r);
            void decReload();


        private:
            const char PLAYER_NAME = '@';
            const int INITIAL_LIVES = 3;
            int lives, score;
            int reload = 0;
    };
#endif
