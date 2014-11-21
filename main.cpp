
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<list>
#include "PersonajeJugador.h"
#include "NPC.h"
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character;
SDL_Rect rect_background,rect_character;
int posx,posy;
    list<Personaje*>personajes;


void guarda();
void carga();
int main( int argc, char* args[] )
{

    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 500/*WIDTH*/, 250/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0; rect_background.y = 0; rect_background.w = w; rect_background.h = h;

    character = IMG_LoadTexture(renderer, "assets/personaje/down.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 100;
    rect_character.w = w;
    rect_character.h = h;
carga();

    personajes.push_back(new PersonajeJugador (posx,posy,renderer,&personajes));
    personajes.push_back(new NPC (50,50,renderer,&personajes));
    personajes.push_back(new NPC (100,200,renderer,&personajes));
    personajes.push_back(new NPC (100,300,renderer,&personajes));
    personajes.push_back(new NPC (150,50,renderer,&personajes));
    personajes.push_back(new NPC (50,150,renderer,&personajes));

    //Main Loop
    int frame=0;
    while(true)
    {
        frame++;
        if(frame%100==0)
            personajes.push_back(new NPC (100,rand() % 100,renderer,&personajes));
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
            guarda();
                return 0;
            }
        }

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->logic((Uint8*)SDL_GetKeyboardState( NULL ));

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Personaje*>::iterator i = personajes.begin();
                i!=personajes.end();
                i++)
            (*i)->render(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(16.66);
    }

	return 0;
}
void guarda()
{
ofstream guardar;
guardar.open("savefile.txt");
stringstream add,add1;
  add << (*personajes.begin())->rectangulo.x << endl;
    add1 << (*personajes.begin())->rectangulo.y;
 guardar << add.str();
    guardar<< add1.str();

guardar.close();

}

void carga()
{
ifstream cargar;

cargar.open("savefile.txt");
cargar>>posx;
cargar>>posy;
cargar.close();

}
