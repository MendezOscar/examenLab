#ifndef BURBUJA_EXPLOSIVA_H
#define BURBUJA_EXPLOSIVA_H
#include <list>
#include "burbuja.h"
#include <SDL/SDL.h>
using namespace std;

class burbuja_explosiva : public Burbuja
{
    public:
        burbuja_explosiva();
        burbuja_explosiva(SDL_Surface*surface,SDL_Surface*screen,int x,int y);
        virtual void dibujar();
        virtual void logica(int click_x, int click_y, int velocidad);
        virtual ~burbuja_explosiva();
    protected:
    private:
};

#endif // BURBUJA_EXPLOSIVA_H
