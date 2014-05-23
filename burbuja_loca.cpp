#include "burbuja_loca.h"

burbuja_loca::burbuja_loca()
{
    //ctor
}

burbuja_loca::burbuja_loca(SDL_Surface* surface,SDL_Surface*screen,int x,int y)
{
    this->surface=surface;
    this->screen=screen;
    this->x=x;
    this->y=y;
    this->borrar=false;
    this->tipo = "loca";
}

void burbuja_loca::dibujar()
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( surface, NULL, screen, &offset );
}

void burbuja_loca::logica(int click_x, int click_y, int velocidad)
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

burbuja_loca::~burbuja_loca()
{
    //dtor
}
