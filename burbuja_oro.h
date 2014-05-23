#ifndef BURBUJA_ORO_H
#define BURBUJA_ORO_H
#include <list>
#include "burbuja.h"
#include <SDL/SDL.h>
using namespace std;

class burbuja_oro : public Burbuja
{
    public:
        burbuja_oro();
        burbuja_oro(SDL_Surface*surface,SDL_Surface*screen,int x,int y);
        virtual void dibujar();
        virtual void logica(int click_x, int click_y, int velocidad);
        virtual ~burbuja_oro();
    protected:
    private:
};

#endif // BURBUJA_ORO_H
