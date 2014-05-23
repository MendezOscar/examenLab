#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include "burbuja_loca.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "burbuja_oro.h"
#include "burbuja_malvada.h"
#include "burbuja_explosiva.h"
#include "burbuja_congelada.h"
#include "bubuja_normal.h"
#include <list>
#include <stdlib.h>
using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 15;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *s = NULL;
SDL_Surface *seconds = NULL;
SDL_Surface *up = NULL;
SDL_Surface *down = NULL;
SDL_Surface *left = NULL;
SDL_Surface *right = NULL;
SDL_Surface *screen = NULL;

//Mix_Chunk *Ginit = NULL;

SDL_Event event;

//The font
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
    return IMG_Load( filename.c_str() );
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;
    }


    //Set the window caption
    SDL_WM_SetCaption( "Press an Arrow Key", NULL );



    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );

    //Open the font
    font = TTF_OpenFont( "DanceFloor.ttf", 22);

    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;
    }

    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( up );
    SDL_FreeSurface( down );
//    SDL_FreeSurface( left );
//    SDL_FreeSurface( right );
    //Close the font
    TTF_CloseFont( font );

    //Quit SDL_ttf
    Mix_CloseAudio();
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

class Timer
{
private:
    int startTicks;
    int pausedTicks;
    bool paused;
    bool started;
public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();
    bool is_started();
    bool is_paused();
};

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;

}

void Timer::stop()
{
    started = false;
    paused = false;
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
}

int Timer::get_ticks()
{
    if( started == true )
    {
        if( paused == true )
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    return 0;
}

void Timer::pause()
{
    if( ( started == true ) && ( paused == false ) )
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if( paused == true )
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

bool Timer::is_started()
{
    return started;
}
bool Timer::is_paused()
{
    return paused;
}

void eljuego()
{
    srand(time(NULL));
    SDL_Surface* perder = load_image("perder.png");
    SDL_Surface* timer_fin = load_image("timer.png");
    list<Burbuja*> burbujas;
    bool mov = true;
    vector<int>save;
    int velocidad = 1;
    int frame = 0;
    int Sscor = 0;
    bool explot = false;
    bool tiempo = true;
    int perdiste = 0;
    int temporal = 0;
    bool quit = false;
    int loca = 0;
    bool bloca = false;
    Uint32 start = 0;
    Timer myTimer;
    myTimer.start();
    while( quit == false )
    {

        int click_x = -1;
        int click_y = -1;
        frame++;

        if(frame % 100 == 0)
        {
            burbujas.push_back(new Bubuja_Normal(load_image("burbuja.png"), screen, 0, rand() % SCREEN_HEIGHT));
        }
        if(frame % 300 == 0)
        {
            burbujas.push_back(new burbuja_explosiva(load_image("burbuja_explosiva.png"), screen, 0 ,rand() % SCREEN_HEIGHT));
        }
        if (frame % 300 == 0)
        {
            burbujas.push_back(new burbuja_malvada(load_image("burbuja_malvada.png"), screen, 0, rand() % SCREEN_HEIGHT));
        }
        if (frame % 300 == 0)
        {
            burbujas.push_back(new burbuja_congelada(load_image("burbuja_congelada.png"), screen, 0, rand() % SCREEN_HEIGHT));
        }
        if (frame % 700 == 0)
        {
            burbujas.push_back(new burbuja_oro(load_image("burbuja_oro.png"), screen, 0, rand() % SCREEN_HEIGHT));
        }
        if (frame % 500 == 0)
        {
            burbujas.push_back(new burbuja_loca(load_image("burbuja_loca.png"), screen, 0, rand() % SCREEN_WIDTH));
        }
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;

            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    click_x = event.button.x;
                    click_y = event.button.y;

                }
            }
        }

        apply_surface( 0, 0, background, screen );

        list<Burbuja*> :: iterator i = burbujas.begin();
        while( i != burbujas.end())
        {
            if((*i)->borrar)
            {
                if((*i)->tipo == "normal")
                {
                    Burbuja* temp = (*i);
                    i = burbujas.erase(i);
                    Sscor++;
                    delete temp;
                }
                else if((*i)->tipo == "malvada")
                {
                    Burbuja* temp = (*i);
                    i = burbujas.erase(i);
                    Sscor--;
                    perdiste++;
                    delete temp;
                }
                else if ((*i)->tipo == "explosiva")
                {
                    Burbuja* temp = (*i);
                    i = burbujas.erase(i);
                    delete temp;

                    if((*i)->tipo == "normal")
                    {
                        Sscor++;
                    }

                    else if((*i)->tipo == "malvada")
                    {
                        perdiste++;
                        Sscor--;
                    }
                    Burbuja* tmp = (*i);
                    i = burbujas.erase(i);
                    delete tmp;


                }
                else if((*i)->tipo == "congelada")
                {
                    velocidad = 0;
                    Burbuja* temp = (*i);
                    i = burbujas.erase(i);
                    delete temp;
                    mov = false;
                    if (mov == false)
                    {
                        velocidad = 0;
                    }
                }
                else if ((*i)->tipo == "oro")
                {
                    Burbuja* temp = (*i);
                    i = burbujas.erase(i);
                    Sscor+=5;
                    delete temp;

                }
                else if ((*i)->tipo == "loca")
                {

                    Burbuja* temp = (*i);
                    i = burbujas.erase(i);
                    Sscor++;
                    delete temp;
                    if (bloca == false)
                    {
                        velocidad = 7;
                    }
                }

            }
            else
            {
                (*i)-> dibujar();
                (*i)-> logica(click_x, click_y, velocidad);
            }
            i++;

            std:: stringstream scor;
            scor<< "Score :" << Sscor;
            s = TTF_RenderText_Solid( font, scor.str().c_str(), textColor );
            apply_surface(0, 0, s, screen );

            std::stringstream time;
            time << "Timer: " << 30-((myTimer.get_ticks()-start) / 1000);
            if((30-((myTimer.get_ticks()-start) / 1000))==0)
            {
            quit = true;
                int tmp;
                ifstream  escribir("score");
                while(escribir >> tmp)
                {
                    save.push_back(tmp);
                }
                save.push_back(Sscor);
                escribir.close();

                sort(save.begin(), save.end());
                ofstream out("score");

                for (int i = 0; i < save.size(); i++)
                {
                    out << save[i];
                    out << "\n";

                }
                out.close();


            }

            seconds = TTF_RenderText_Solid( font, time.str().c_str(), textColor );
            apply_surface( ( SCREEN_WIDTH - seconds->w ) / 1, 0, seconds, screen );
        }



        if (perdiste == 3)
        {
            apply_surface(0, 0, perder, screen);
        }
        temporal++;
        if (temporal == 300)
        {
            velocidad = 1;
            temporal = 0;
        }
        loca++;
        if (loca == 300)
        {
            velocidad = 1;
            loca = 0;
        }

        if( SDL_Flip( screen ) == -1 )
        {
            return;
        }

    }
}

void instruciones()
{
    int frame = 0;
    SDL_Surface* menu_bug = load_image("instrucciones1.png");
    bool quit = false;
    while(quit == false)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
        apply_surface(0, 0, menu_bug, screen);
        if(SDL_Flip(screen) == 1)
        {
            return;
        }
    }
}

void Sscore()
{
    int frame = 0;
    SDL_Surface* menu_bug = load_image("Menu.png");
    bool quit = false;

    while(quit == false)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
        ifstream leer("score");
        int s;
        leer>>s;
        std:: stringstream scor;
        scor<< "Mejor Score:" <<leer;

        apply_surface(0, 0, menu_bug, screen);
        if(SDL_Flip(screen) == 1)
        {
            return;
        }
    }
}

void menu()
{
    int frame = 0;
    SDL_Surface* menu_bug = load_image("Menu.png");
    SDL_Surface* iniciar_juego = load_image("iniciarjuego.png");
    SDL_Surface* instrcciones = load_image("instrucciones.png");
    SDL_Surface* Score = load_image("Score.png");
    SDL_Surface* Salir = load_image("Salir.png");

    int x =200;
    int atras_x = 500;
    int atras_y = 420;
    int pos_x = 200;
    int iniciar_juego_y = 120;
    int instrcciones_y = 200;
    int Score_y = 280;
    int Salir_y = 400;

    bool quit = false;


    while(quit == false)
    {

        while( SDL_PollEvent( &event ) )
        {

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    int click_x = event.button.x;
                    int click_y = event.button.y;
                    if(click_x >= x && click_x <= x + iniciar_juego->w && click_y >= iniciar_juego_y && click_y <= iniciar_juego_y + iniciar_juego->h)
                    {
                        eljuego();
                    }
                    else if(click_x >= x && click_x <= x + instrcciones->w && click_y >= instrcciones_y && click_y <= instrcciones_y + instrcciones->h)
                    {
                        instruciones();
                    }
                    else if(click_x >= x && click_x <= x + Score->w && click_y >= Score_y && click_y <= Score_y + Score->h)
                    {
                        Sscore();
                    }
                    else if(click_x >= pos_x && click_x <= pos_x + Salir->w && click_y >= Salir_y && click_y <= Salir_y + Salir->h)
                    {
                        exit(0);
                    }

                }
            }
        }

        apply_surface(0, 0, menu_bug, screen);
        apply_surface(x, iniciar_juego_y, iniciar_juego, screen);
        apply_surface(x, instrcciones_y, instrcciones, screen);
        apply_surface(x, Score_y, Score, screen);
        apply_surface(pos_x, Salir_y, Salir, screen);

        if(SDL_Flip(screen) == 1)
        {
            return;
        }
    }
}

void Inicio()
{
    int frame = 0;
    SDL_Surface* menu_bug = load_image("Inicio.png");
    bool quit = false;
    while(quit == false)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                menu();
            }
        }

        apply_surface(0, 0, menu_bug, screen);
        if(SDL_Flip(screen) == 1)
        {
            return;
        }
    }
}

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    Inicio();
    clean_up();

    return 0;
}
