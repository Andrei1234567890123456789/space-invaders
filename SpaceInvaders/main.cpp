#include "Game.h"
int main(){
    Game game;
    /* If you have problems with the button press reading system, 
    use game.runManualInput() instead of game.run().Then you will be 
    able to type the inputs through the console using std::cin */
    game.run();
    // game.runManualInput();
    return 0;
}