#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"

class Bullet : public GameObject{
    public:
        Bullet();
        Bullet(int x, int y, int direction);
        Bullet(const Bullet & b);
        Bullet & operator=(const Bullet & b);
        ~Bullet();

        void update();

        int getDirection()const;
        void setDirection(int d);

    private:
        const char BULLET_NAME = '*';
        int direction;
};

#endif