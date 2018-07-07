#pragma once

class Star
{
public:
    Star()
    {
        this->x = starUtil.random( -SCREEN_WIDTH, SCREEN_WIDTH );
        this->y = starUtil.random( -SCREEN_HEIGHT, SCREEN_HEIGHT );
        this->z = starUtil.random( 0, SCREEN_WIDTH );
        this->pz = this->z;
        this->color.a = 255;
        this->color.r = 255;
        this->color.g = 0;
        this->color.b = 255;
    }

    void update()
    {
        starUtil.mouseInteract( true );
        this->z -= starUtil.speed;
        if ( this->z < 1 ){
            this->z = SCREEN_WIDTH;
            this->x = starUtil.random( -SCREEN_WIDTH, SCREEN_WIDTH );
            this->y = starUtil.random( -SCREEN_HEIGHT, SCREEN_HEIGHT );
            this->pz = this->z;
        }
    }

    void show()
    {
        SDL_SetRenderDrawColor( gRenderer, this->color.r, this->color.g, this->color.b, this->color.a );

        float sx = starUtil.map( float( this->x / this->z ), 0, 1, 0, SCREEN_WIDTH );
        float sy = starUtil.map( float( this->y / this->z ), 0, 1, 0, SCREEN_HEIGHT );

        float px = starUtil.map( float( this->x / this->pz ), 0, 1, 0, SCREEN_WIDTH );
        float py = starUtil.map( float( this->y / this->pz ), 0, 1, 0, SCREEN_HEIGHT );

        this->pz = this->z;

        SDL_RenderDrawLine( gRenderer, px + starUtil.ox, py + starUtil.oy, sx + starUtil.ox, sy + starUtil.oy );
    }

public:
    float x;
    float y;
    float z;

    float pz;

    SDL_Color color;
};
