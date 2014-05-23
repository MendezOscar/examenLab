#ifndef BURBUJA_H
#define BURBUJA_H
#include <list>
#include <SDL/SDL.h>
#include<iostream>
using namespace std;

class Burbuja
{
    public:
        string tipo;
        SDL_Surface* surface;
        SDL_Surface* screen;
        int x;
        int y;
        bool borrar;

        Burbuja();
        virtual void dibujar() = 0;
        virtual void logica(int click_x, int click_y, int velocidad) = 0;
        virtual ~Burbuja();
    protected:
    private:
};

#endif // BURBUJA_H
