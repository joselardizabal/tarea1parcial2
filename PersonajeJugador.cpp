#include "PersonajeJugador.h"

PersonajeJugador::PersonajeJugador(int x, int y,
                                    SDL_Renderer* renderer,
                                    list<Personaje*>*personajes)
{
    this->rectangulo.x = x;
    this->rectangulo.y = y;
    this->personajes=personajes;

    SDL_Texture *textura = IMG_LoadTexture(renderer, "assets/personaje/down1.png");
    SDL_QueryTexture(textura, NULL, NULL, &this->rectangulo.w, &this->rectangulo.h);
    texturas_down.push_back(textura);

    texturas_down.push_back(IMG_LoadTexture(renderer, "assets/personaje/down2.png"));

    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/up1.png"));
    texturas_up.push_back(IMG_LoadTexture(renderer, "assets/personaje/up2.png"));

    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/left1.png"));
    texturas_left.push_back(IMG_LoadTexture(renderer, "assets/personaje/left2.png"));

    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/right1.png"));
    texturas_right.push_back(IMG_LoadTexture(renderer, "assets/personaje/right2.png"));

    orientacion="down";

    textura_actual=texturas_down.begin();
}

PersonajeJugador::~PersonajeJugador()
{
    //dtor
}

void PersonajeJugador::logic(Uint8* teclas_presionadas)
{
    SDL_Rect temp = this->rectangulo;

    if( teclas_presionadas[ SDL_SCANCODE_UP ] )
    {
        rectangulo.y-=1;
        if(orientacion!="up")
            textura_actual=texturas_up.begin();
        orientacion="up";
    }
    if( teclas_presionadas[ SDL_SCANCODE_DOWN ] )
    {
        rectangulo.y+=1;
        if(orientacion!="down")
            textura_actual=texturas_down.begin();
        orientacion="down";
    }
    if( teclas_presionadas[ SDL_SCANCODE_RIGHT ] )
    {
        rectangulo.x+=1;
        if(orientacion!="right")
            textura_actual=texturas_right.begin();
        orientacion="right";
    }
    if( teclas_presionadas[ SDL_SCANCODE_LEFT ] )
    {
        rectangulo.x-=1;
        if(orientacion!="left")
            textura_actual=texturas_left.begin();
        orientacion="left";
    }

    for(list<Personaje*>::iterator i = personajes->begin();
            i!=personajes->end();
            i++)
    {
        if(this==(*i))
            continue;
        if(colision(this->rectangulo, (*i)->rectangulo))
        {
            //rectangulo=temp;
            personajes->erase(i);
            break;
        }
    }
}






