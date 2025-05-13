#ifdef _WIN32
    #include <windows.h>
    inline bool isKeyPressed(char key) {
        return (GetAsyncKeyState(key) & 0x8000) != 0;  // Check if key is pressed
    }
    
#else
    #include <termios.h>
    #include <unistd.h>
    //don't use getKey(), it would cause errors on windows
    inline char getKey() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt); // Save old terminal settings
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Disable buffering & echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar(); // Get the character
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore settings
        return ch;
    }
    inline bool isKeyPressed(char key) {
        return getKey() == key;  // Check if key is pressed
    }
    
#endif