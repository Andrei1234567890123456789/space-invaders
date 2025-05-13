#include "Bullet.h"

Bullet::Bullet():GameObject(0, 0), direction(1){
    setName(BULLET_NAME);
}
Bullet::Bullet(int x, int y, int direction): GameObject(x, y), direction(direction){
    setName(BULLET_NAME);
}
Bullet::Bullet(const Bullet & b): GameObject(b.getX(), b.getY()), direction(b.getDirection()){
    setName(BULLET_NAME);
}
Bullet & Bullet::operator=(const Bullet & b){
    if(this != &b){
        setName(BULLET_NAME);
        setPossition(b.getX(), b.getY());
        direction = b.getDirection();
    }
    return *this;
}
Bullet::~Bullet(){}

void Bullet::update(){
    if(direction == 1 && getY() > 0){//up
        setPossition(getX(), getY()-1);
    }else if(direction == 2 && getY() < 27){//down
        setPossition(getX(), getY()+1);
    }
}

int Bullet::getDirection()const{
    return direction;
}
void Bullet::setDirection(int d){
    direction = d;
}