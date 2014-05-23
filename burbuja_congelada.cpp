#include "burbuja_congelada.h"

burbuja_congelada::burbuja_congelada()
{
    //ctor
}
burbuja_congelada::burbuja_congelada(SDL_Surface* surface,SDL_Surface*screen,int x,int y)
{
    this->surface=surface;
    this->screen=screen;
    this->x=x;
    this->y=y;
    this->borrar=false;
    this->tipo = "congelada";
}

void burbuja_congelada::dibujar()
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( surface, NULL, screen, &offset );
}

void burbuja_congelada::logica(int click_x, int click_y, int velocidad)
{
    this->x += velocidad;

    if(click_x >= this->x
        && click_x <= this->x + this->surface->w
        && click_y >= this->y
        && click_y <= this->y + this->surface->h)
    {
        borrar=true;
    }
}

burbuja_congelada::~burbuja_congelada()
{
    //dtor
}
