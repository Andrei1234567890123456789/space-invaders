#include "Game.h"

Game::Game(){
    gameOver = false;
    tikSpeed = 100;
    reloadTime = 10;
    player = new Player(DEFAULT_COLS/2, DEFAULT_ROWS-1);
    field = new GameObject**[DEFAULT_ROWS];
    for(int i = 0; i < DEFAULT_ROWS; i++){
        field[i] = new GameObject*[DEFAULT_COLS];

        for (int j = 0; j < DEFAULT_COLS; ++j) {
            field[i][j] = nullptr;
        }
    }
    field[player->getY()][player->getX()] = player;
}

Game::~Game(){
    delete player;
    if (field != nullptr) {
        for (int i = 0; i < DEFAULT_ROWS; ++i) {
            if (field[i] != nullptr) {
                for (int j = 0; j < DEFAULT_COLS; ++j) {
                    if(field[i][j] != nullptr){ 
                        delete field[i][j];
                        field[i][j] = nullptr;
                    }
                }
                delete[] field[i];
                field[i] = nullptr;
            }
        }
        delete[] field;
        field = nullptr;
    }
}

void Game::run(){
    std::cout << "\033[2J\033[H"; //clear console

    while (!isKeyPressed('S')) {
        update();
        if(isKeyPressed('A')){
            movePlayerLeft();
        }
        if(isKeyPressed('D')){
            movePlayerRight();
        }
        if(isKeyPressed('W')){
            if(player->getReload() <= 0){
                shootPlayerBullet();
                player->setReload(reloadTime);
            }
        }
        //Buttons (0-9) for speed settings testing:
        {
            if(isKeyPressed('1')){
                tikSpeed = 200;
            }
            if(isKeyPressed('2')){
                tikSpeed = 100;
            }
            if(isKeyPressed('3')){
                tikSpeed = 50;
            }
            if(isKeyPressed('4')){
                tikSpeed = 1;
            }
            if(isKeyPressed('5')){
                tikSpeed = 0;
            }
            if(isKeyPressed('6')){
                reloadTime = 10;
            }
            if(isKeyPressed('7')){
                reloadTime = 8;
            }
            if(isKeyPressed('8')){
                reloadTime = 5;
            }
            if(isKeyPressed('9')){
                reloadTime = 3;
            }
            if(isKeyPressed('0')){
                reloadTime = 0;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(tikSpeed));
    }
    std::cout << "\033[2J\033[H"; //clear console
    std::cout << "game ended..." << std::endl;
    std::cout << "final score: "<< player->getScore() << std::endl;
}
void Game::runManualInput(){
    char input = ' ';
    while(input != 's' && !gameOver){
        update();
        std::cin >> input;
        if(input == 'a'){
            movePlayerLeft();
        }
        if(input == 'd'){
            movePlayerRight();
        }
        if(input == 'w'){
            shootPlayerBullet();
        }
    }
    std::cout << "\033[2J\033[H"; //clear console
    std::cout << "game ended..." << std::endl;
    std::cout << "final score: "<< player->getScore() << std::endl;
}

void Game::update(){
    if(player->getReload() > 0) player->decReload();

    //move all bullets on the field
    moveBullets();

    //render
    std::cout << *this;
}

void Game::movePlayerLeft(){
    field[player->getY()][player->getX()] = nullptr;
    player->goLeft();
    field[player->getY()][player->getX()] = player;
}
void Game::movePlayerRight(){
    field[player->getY()][player->getX()] = nullptr;
    player->goRight();
    field[player->getY()][player->getX()] = player;
}

void Game::shootPlayerBullet(){
    GameObject bulletObj = player->shoot();
    Bullet b(bulletObj.getX(), bulletObj.getY(), 1);
    bullets.push_back(b);

    field[DEFAULT_ROWS-2][player->getX()] = dynamic_cast<GameObject*>(&b);
}


void Game::clearBullets(){
    //delete all bullets from the top and the bottom
    for(int i = 0; i < DEFAULT_COLS; i++){
        if(field[0][i] != nullptr && field[0][i]->getName() == '*'){
            field[0][i] = nullptr;
        }
        if(field[DEFAULT_ROWS-1][i] != nullptr && field[DEFAULT_ROWS-1][i]->getName() == '*'){
            field[DEFAULT_ROWS-1][i] = nullptr;
        }
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
    [this](const Bullet& b) { return b.getY() <= 0 || b.getY() >= this->DEFAULT_ROWS - 1; }),
    bullets.end());
}

void Game::moveBullets(){
    clearBullets();
    for(int i = 0; i < bullets.size(); i++){
        field[bullets[i].getY()][bullets[i].getX()] = nullptr;
        bullets[i].update();

        if(field[bullets[i].getY()][bullets[i].getX()] != nullptr && 
        field[bullets[i].getY()][bullets[i].getX()]->getName() == player->getName()){
            player->decLives();
            if(player->getLives() <= 0){
                gameOver = true;
                return;
            }
        }else{
            field[bullets[i].getY()][bullets[i].getX()] = &bullets[i];
        }
    }
}

std::ostream & operator<<(std::ostream & out, const Game & g){
    g.render(out);
    return out;
}
std::ostream & Game::render(std::ostream & out)const{
    std::string output = "Space Invaders:\n";
    output += "score: ";
    output += std::to_string(player->getScore());
    output += " lives: ";
    output += std::to_string(player->getLives());
    output += "\n";
    int next = 0;

    for(int i = 0; i < DEFAULT_COLS*3; i++){
        output += "_";
    }
    output += "\n";

    for(int i = 0; i < DEFAULT_ROWS; i++){
        output += "| ";
        for(int j = 0; j < DEFAULT_COLS; j++){
            if(field[i][j] == nullptr){
                output += "   ";
            }else{
                output += " ";
                output += field[i][j]->getName();
                output += " ";
            }
        }
        output += " |\n";
    }
    for(int i = 0; i < DEFAULT_COLS*3; i++){
        output += "_";
    }
    output += "\ncontrols: a - go left, d - go right, w - shoot, s - stop";

    out << "\033[H"; //move cursor to the begining of the console
    out << output;
    return out;
}