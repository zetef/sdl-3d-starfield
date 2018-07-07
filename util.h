#pragma once

class Utility
{
public:
    Utility() : ox( 0 ), oy( 0 ), speed( 50 ) {}

    float map( float value, float start1, float stop1, float start2, float stop2 )// 10 0 255 0 128
    {
        return start2 + ( stop2 - start2 ) * ( ( value - start1 ) / ( stop1 - start1 ) );
    }

    void translate( int oldX, int oldY )
    {
        this->ox += this->ox - oldX;
        this->oy += this->oy - oldY;
    }

    int random( int start, int stop )
    {
        return ( start + ( rand() % (int)( stop - start + 1 ) ) );
    }

    bool mouseInteract( bool b = false )
    {
        if ( b ){
            int x;
            SDL_GetMouseState( &x, NULL );

            this->speed = this->map( x, 0, SCREEN_WIDTH, 0, 50 );
        }

        return b;
    }

public:
    int ox;
    int oy;
    float speed;
};
