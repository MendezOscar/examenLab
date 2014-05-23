#ifndef BURBUJA_LOCA_H
#define BURBUJA_LOCA_H
#include <list>
#include "burbuja.h"
#include <SDL/SDL.h>
using namespace std;

class burbuja_loca : public Burbuja
{
    public:
        burbuja_loca();
        burbuja_loca(SDL_Surface*surface,SDL_Surface*screen,int x,int y);
        virtual void dibujar();
        virtual void logica(int click_x, int click_y, int velocidad);
        virtual ~burbuja_loca();
    protected:
    private:
};

#endif // BURBUJA_LOCA_H
