#ifndef BURBUJA_CONGELADA_H
#define BURBUJA_CONGELADA_H
#include <list>
#include "burbuja.h"
#include <SDL/SDL.h>
using namespace std;

class burbuja_congelada : public Burbuja
{
    public:
        burbuja_congelada();
        burbuja_congelada(SDL_Surface*surface,SDL_Surface*screen,int x,int y);
        virtual void dibujar();
        virtual void logica(int click_x, int click_y, int velocidad);
        virtual ~burbuja_congelada();
    protected:
    private:
};

#endif // BURBUJA_CONGELADA_H
