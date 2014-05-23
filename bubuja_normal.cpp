#include "bubuja_normal.h"


Bubuja_Normal::Bubuja_Normal()
{
    //ctor
}

Bubuja_Normal::Bubuja_Normal(SDL_Surface* surface,SDL_Surface*screen,int x,int y)
{
    this->surface=surface;
    this->screen=screen;
    this->x=x;
    this->y=y;
    this->borrar=false;
    this->tipo = "normal";
}

void Bubuja_Normal::dibujar()
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( surface, NULL, screen, &offset );
}

void Bubuja_Normal::logica(int click_x, int click_y, int velocidad)
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
Bubuja_Normal::~Bubuja_Normal()
{
    //dtor
}
