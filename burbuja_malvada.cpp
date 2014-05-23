#include "burbuja_malvada.h"

burbuja_malvada::burbuja_malvada()
{
    //ctor
}

burbuja_malvada::burbuja_malvada(SDL_Surface* surface,SDL_Surface*screen,int x,int y)
{
    this->surface=surface;
    this->screen=screen;
    this->x=x;
    this->y=y;
    this->borrar=false;
    this->tipo="malvada";
}
void burbuja_malvada::dibujar()
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( surface, NULL, screen, &offset );
}

void burbuja_malvada::logica(int click_x, int click_y, int velocidad)
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


burbuja_malvada::~burbuja_malvada()
{
    //dtor
}
