#include "MyObjects.h"

void my_shoot(SDL_Surface *screen, Camera cam, Basketball b, cood c1)
{
    std::vector<cood> path = my_path( c1 );
    for(int i =0; i<(path.size()); i++)
    {
        b.translate(path[i]);
        b.my_draw(screen, orange, brown, cam);
        SDL_Flip(screen);
    }
}
