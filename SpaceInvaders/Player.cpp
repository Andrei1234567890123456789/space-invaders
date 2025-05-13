#include "Player.h"

Player::Player():GameObject(0, 0), score(0), lives(INITIAL_LIVES){
    this->setName(PLAYER_NAME);
}
Player::Player(int x, int y):GameObject(x, y), score(0), lives(INITIAL_LIVES){
    this->setName(PLAYER_NAME);
}
Player::Player(const Player & p):GameObject(p.getX(), p.getY()), score(p.getScore()), lives(INITIAL_LIVES){
    this->setName(PLAYER_NAME);
}
Player & Player::operator=(const Player & p){
    if(this != &p){
        this->setName(PLAYER_NAME);
        this->setPossition(p.getX(), p.getY());
        score = p.score;
        lives = p.lives;
    }
    return *this;
}
Player::~Player(){}

void Player::goLeft(){
    if(getX() > 0){
       setPossition(getX()-1, getY()); 
    }
}
void Player::goRight(){
    if(getX() < 35){
        setPossition(getX()+1, getY()); 
     }
}
GameObject Player::shoot(){
    GameObject bullet(getX(), getY()-1);
    return bullet;
}

int Player::getScore()const{return score;}
int Player::getLives()const{return lives;}
int Player::getReload()const{return reload;}


void Player::setLives(int l){lives = l;}
void Player::decLives(){lives--;}
void Player::setScore(int s){score = s;}
void Player::incScore(int s){score += s;}
void Player::setReload(int r){reload = r;}
void Player::decReload(){reload--;}