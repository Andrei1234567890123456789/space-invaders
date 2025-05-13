#include "GameObject.h"

GameObject::GameObject():name(' '), x(0), y(0){}

GameObject::GameObject(int x, int y): name(' '), x(x), y(y){}
GameObject::GameObject(const GameObject & o):name(o.name), x(o.x), y(o.y){}
GameObject & GameObject::operator=(const GameObject & o){
    if(this != &o){
        name = o.name;
        x = o.x;
        y = o.y;
    }
    return *this;
}
GameObject::~GameObject(){}

char GameObject::getName()const{return name;}
int GameObject::getX()const{return x;}
int GameObject::getY()const{return y;}

void GameObject::setName(char name){this->name = name;}
void GameObject::setPossition(int x, int y){
    this->x = x;
    this->y = y;
}

std::ostream & operator<<(std::ostream & lhs, const GameObject & rhs){
    rhs.ins(lhs);
    return lhs;
}
std::ostream & GameObject::ins(std::ostream & out)const{
    out << name;
    return out;
}
