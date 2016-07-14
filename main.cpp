#include "MyFunctions.h"
#include "MyDraw.h"
#include "MyObjects.h"
#include "MyTransformations.h"

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

int main(int argc, char ** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface * screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    SDL_Surface * BALL = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    SDL_Event event;
    bool run = 1;

    cood cc(0,500,4000);
    static float ball_rotate = 0.25;

    bool flag = 1;
    bool ball_disp = 0;
    Camera camera(0, 1500, 3100, 0, 1300, 3700);//put |z_prp - z_vp| = 600;

    cood ttt(0,1210,5010);
    Basketball ball;
    Center center;
    Pole pole;
    Paint paint;
    Rim rim;
    my_net net;
    newball nball;
    nball.load_files();
    net.load_files();
    net.translate( ttt );
    nball.translate( ttt );

    Board board;
    Perimeter peri;
    Boundary boundary;

    while (run)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) run = 0;
        }
        //logic
        Uint8 *keys = SDL_GetKeyState(0);

        float alpha = 20;
        float zoom_factor = 1000;
        float del = 10;
        float l = 50;
        float light_change = .1;

        if (keys[SDLK_d]) camera.put_x_prp(camera.get_x_prp()+alpha),flag = 1;
        if (keys[SDLK_a]) camera.put_x_prp(camera.get_x_prp()-alpha),flag = 1;
        if (keys[SDLK_s]) camera.put_y_prp(camera.get_y_prp()+alpha),flag = 1;
        if (keys[SDLK_w]) camera.put_y_prp(camera.get_y_prp()-alpha),flag = 1;
        if (keys[SDLK_z]) camera.put_z_prp(camera.get_z_prp() + zoom_factor),   camera.put_z_vp(camera.get_z_vp() + zoom_factor),flag = 1; //zoom in
        if (keys[SDLK_c]) camera.put_z_prp(camera.get_z_prp() - zoom_factor),   camera.put_z_vp(camera.get_z_vp() - zoom_factor),flag = 1;//zoom out
        if (keys[SDLK_LEFT]) camera.put_x_vp(camera.get_x_vp()+ del),flag = 1;
        if (keys[SDLK_RIGHT]) camera.put_x_vp(camera.get_x_vp()- del),flag = 1;
        if (keys[SDLK_UP]) camera.put_y_vp(camera.get_y_vp()+ del),flag = 1;
        if (keys[SDLK_DOWN]) camera.put_y_vp(camera.get_y_vp()-del),flag = 1;

        //fixed cameras
        if (keys[SDLK_1]) camera.change(0, 100, 1000, 0, 0, 1600),flag = 1;
        if (keys[SDLK_2]) camera.change(1000, 50, 1000, 900, 0, 1600),flag = 1;
        if (keys[SDLK_3]) camera.change(0, 10000, 0, 0, 5000, 600),flag = 1;
        if (keys[SDLK_4]) camera.change(0, 1500, 3000, 0, 1300, 3600),flag = 1;

        //light changing
        if (keys[SDLK_KP5]) original_light(),flag = 1;
        if (keys[SDLK_KP4]) change_light_x( l ),flag = 1;
        if (keys[SDLK_KP6]) change_light_x( -l ),flag = 1;
        if (keys[SDLK_KP8]) change_light_y( l ),flag = 1;
        if (keys[SDLK_KP2]) change_light_y( -l ),flag = 1;
        if (keys[SDLK_KP_MINUS]) change_light_z( l ),flag = 1;
        if (keys[SDLK_KP_PLUS]) change_light_z( -l ),flag = 1;
        if (keys[SDLK_KP1]) light_position1(),flag = 1;

        if (keys[SDLK_n]) change_intensity(-light_change),flag = 1;
        if (keys[SDLK_m]) change_intensity(light_change),flag = 1;

        //animation
        if (keys[SDLK_SPACE]) my_shoot(BALL, camera, ball, cc);

        if (keys[SDLK_LSHIFT]) ball_disp = 1;//to rotate the ball
        if (keys[SDLK_i]) nball.rotateX(ball_rotate), ball_rotate += 0.25, ball_disp = 1;
        if (keys[SDLK_k]) nball.rotateX(-ball_rotate), ball_rotate -= 0.25,ball_disp = 1;
        if (keys[SDLK_j]) nball.rotateY(ball_rotate), ball_rotate += 0.25, ball_disp = 1;
        if (keys[SDLK_l]) nball.rotateY(-ball_rotate), ball_rotate -= 0.25,ball_disp = 1;
        if (keys[SDLK_u]) nball.rotateZ(ball_rotate), ball_rotate += 0.25, ball_disp = 1;
        if (keys[SDLK_o]) nball.rotateZ(-ball_rotate), ball_rotate -= 0.25,ball_disp = 1;

        //rendering
        clearZBuffer();
        if(ball_disp == 1)
        {
            nball.draw(screen, camera);
            ball_disp = 0;
        }
        rim.my_draw(BALL, red, red, camera);
        net.draw(screen, camera);

        if(flag == 1)
        {
            SDL_FillRect(screen, &screen->clip_rect, 0x000000);
            paint.my_draw(screen, red, red, camera);
            board.my_draw(screen, white, white, white, white, black, black, camera);
            pole.my_draw(screen, light_blue, light_blue, camera);
            peri.my_draw(screen, camera);
            center.my_draw(screen, camera);
            boundary.my_draw(screen, 0xff9651, 0xff9651, camera);
            apply_surface(0,0,BALL,screen);
            SDL_Flip(screen);
        }
        SDL_Flip(BALL);
        flag = 0;
    }
    SDL_Quit();
    return 0;
}

