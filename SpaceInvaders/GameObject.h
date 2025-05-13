#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <iostream>
class GameObject{
    public:
        GameObject();
        GameObject(int, int);
        GameObject(const GameObject &);
        GameObject & operator=(const GameObject &);
        ~GameObject();

        char getName()const;
        int getX()const;
        int getY()const;

        void setName(char);
        void setPossition(int, int);

        friend std::ostream & operator<<(std::ostream &, const GameObject &);
        std::ostream & ins(std::ostream & out)const;

    private:
        int x, y;
        char name;

};
#endif