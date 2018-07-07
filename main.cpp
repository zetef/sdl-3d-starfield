#include <SDL.h>
#include <iostream>
#include <cstdlib>
//#include <cmath> /* for drawEllipse */
#include <ctime>

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;
const short DEFAULT_DRIVER = -1;
//typedef int32_t s32; /* for drawEllipse */

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

bool init();
bool loadMedia();
void close();
void drawEllipse( SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY );

//#include "mouse.h"
#include "util.h"

Utility starUtil;
//Mouse mouse;

#include "star.h"

bool init()
{
    bool success = true;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        std::cout << "could not init sdl: " << SDL_GetError() << '\n';
        success = false;
    } else {
        if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
            std::cout << "linear texture filtering is not enabled\n";
        }
        gWindow = SDL_CreateWindow( "sdl-starfield",
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN, SDL_WINDOW_FULLSCREEN_DESKTOP );
        if ( gWindow == NULL ){
            std::cout << "could not create window: " << SDL_GetError() << '\n';
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer( gWindow,
                                           DEFAULT_DRIVER,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if ( gRenderer == NULL ){
                std::cout << "could not create renderer: " << SDL_GetError() << '\n';
                success = false;
            } else {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                #ifdef _SDL_IMG_H
                int imgFlags = IMG_INIT_PNG;

                if ( !(IMG_Init( imgFlags ) & imgFlags ) ){
                    std::cout << "could not init sdl_img: " << IMG_GetError() << '\n';
                    success = false;
                }
                #endif //_SDL_IMG_H

                #ifdef _SDL_TTF_H
                if ( TTF_Init() < 0 ){
                    std::cout << "could not init sdl_ttf: " << TTF_GetError() << '\n';
                    success = false;
                }
                #endif // _SDL_TTF_H
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;



    return success;
}

void close()
{
    SDL_DestroyWindow( gWindow );
    SDL_DestroyRenderer( gRenderer );
    gWindow = NULL;
    gRenderer = NULL;

    #ifdef _SDL_IMG_H
    IMG_Quit();
    #endif // _SDL_IMG_H

    #ifdef _SDL_TTF_H
    TTF_Quit();
    #endif // _SDL_TTF_H

    SDL_Quit();
}

/*void drawEllipse( SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY )
{
    float pi  = 3.14159265358979323846264338327950288419716939937510;
    float pih = pi / 2.0; //half of pi

    //drew  28 lines with   4x4  circle with precision of 150 0ms
    //drew 132 lines with  25x14 circle with precision of 150 0ms
    //drew 152 lines with 100x50 circle with precision of 150 3ms
    const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
    float theta = 0;     // angle that will be increased each loop

    //starting point
    int x  = (float)radiusX * cos(theta);//start point
    int y  = (float)radiusY * sin(theta);//start point
    int x1 = x;
    int y1 = y;

    //repeat until theta >= 90;
    float step = pih/(float)prec; // amount to add to theta each time (degrees)
    for(theta=step;  theta <= pih;  theta+=step)//step through only a 90 arc (1 quadrant)
    {
        //get new point location
        x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
        y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

        //draw line from previous point to new point, ONLY if point incremented
        if( (x != x1) || (y != y1) )//only draw if coordinate changed
        {
            SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
            SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
            SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
            SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
        }
        //save previous points
        x = x1;//save new previous point
        y = y1;//save new previous point
    }
    //arc did not finish because of rounding, so finish the arc
    if(x!=0)
    {
        x=0;
        SDL_RenderDrawLine(r, x0 + x, y0 - y,    x0 + x1, y0 - y1 );//quadrant TR
        SDL_RenderDrawLine(r, x0 - x, y0 - y,    x0 - x1, y0 - y1 );//quadrant TL
        SDL_RenderDrawLine(r, x0 - x, y0 + y,    x0 - x1, y0 + y1 );//quadrant BL
        SDL_RenderDrawLine(r, x0 + x, y0 + y,    x0 + x1, y0 + y1 );//quadrant BR
    }
}*/

int main( int argc, char *argv[] )
{
    if ( !init() ){
        std::cout << "could not init!\n";
    } else {
        if ( !loadMedia() ){
            std::cout << "could not load media!\n";
        } else {
            SDL_DisplayMode dm;

            SDL_GetCurrentDisplayMode( 0, &dm );

            SCREEN_WIDTH = dm.w;
            SCREEN_HEIGHT = dm.h;

            bool quit = false;
            srand( time( NULL ) );

            SDL_Event e;

            int starsSize = 1600;
            Star *stars = new Star[ starsSize ];

            SDL_ShowCursor( SDL_DISABLE );

            while ( !quit ){
                while ( SDL_PollEvent( &e ) ){
                    if ( e.type == SDL_QUIT ){
                        quit = true;
                    } else if ( e.key.type == SDL_KEYDOWN ){
                        if ( e.key.keysym.sym == SDLK_ESCAPE ){
                            quit = true;
                        }
                    }
                }

                starUtil.translate( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 );

                SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 255);
                SDL_RenderClear( gRenderer );

                for ( int i = 0; i < starsSize; i++ ){
                    stars[ i ].update();
                    stars[ i ].show();
                }

                SDL_RenderPresent( gRenderer );
            }
        }
    }

    close();

    return 0;
}
