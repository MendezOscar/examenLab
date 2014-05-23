#ifndef BURBUJA_MALVADA_H
#define BURBUJA_MALVADA_H
#include <list>
#include "burbuja.h"
#include <SDL/SDL.h>
using namespace std;

class burbuja_malvada : public Burbuja
{
    public:
        burbuja_malvada();
        burbuja_malvada(SDL_Surface*surface,SDL_Surface*screen,int x,int y);
        virtual void dibujar();
        virtual void logica(int click_x, int click_y, int velocidad);
        virtual ~burbuja_malvada();
    protected:
    private:
};

#endif // BURBUJA_MALVADA_H
