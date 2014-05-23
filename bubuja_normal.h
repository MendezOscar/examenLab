#ifndef BUBUJA_NORMAL_H
#define BUBUJA_NORMAL_H
#include <list>
#include "burbuja.h"
#include <SDL/SDL.h>
using namespace std;

class Bubuja_Normal : public Burbuja
{
    public:

        Bubuja_Normal();
        Bubuja_Normal(SDL_Surface*surface,SDL_Surface*screen,int x,int y);
        virtual void dibujar();
        virtual void logica(int click_x, int click_y, int velocidad);
        virtual ~Bubuja_Normal();
    protected:
    private:
};

#endif // BUBUJA_NORMAL_H
