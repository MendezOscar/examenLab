#include "burbuja_explosiva.h"

burbuja_explosiva::burbuja_explosiva()
{
    //ctor
}

burbuja_explosiva::burbuja_explosiva(SDL_Surface* surface,SDL_Surface*screen,int x,int y)
{
    this->surface=surface;
    this->screen=screen;
    this->x=x;
    this->y=y;
    this->borrar=false;
    this->tipo = "explosiva";
}

void burbuja_explosiva::dibujar()
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( surface, NULL, screen, &offset );
}

void burbuja_explosiva::logica(int click_x, int click_y, int velocidad)
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

burbuja_explosiva::~burbuja_explosiva()
{
    //dtor
}
