#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include "MyFunctions.h"
#include "MyDraw.h"
#include "MyTransformations.h"
#include <iostream>
#include <vector>

class my_net
{
    public:

    my_object net;

    bool load_files()
    {
        net.load_obj("net.obj");
    }
    void draw(SDL_Surface *screen, Camera cam)
    {
        for(int i = 0; i < net.faces.size(); i++)
        {
            net.my_fill(screen, net.faces[i], white, cam);
        }
    }
    void translate( cood c )
    {
        for(int i = 0; i <net.vertex.size(); i++)
        {
            net.vertex[i].x =  net.vertex[i].x + c.getx();
            net.vertex[i].y =  net.vertex[i].y + c.gety();
            net.vertex[i].z =  net.vertex[i].z + c.getz();
        }
    }
};
class newball
{
    public:

    my_object obj;
    my_object obj1;
    std::vector<cood> ball1 = my_translate(my_sphere(48),0,1210,5010);
    std::vector<cood> ball = my_translate(my_sphere(48),0,0,0);
    my_object logo;
    my_object logo1;
    bool load_files()
    {
        obj.load_obj("ball_ext.obj");
        obj1.load_obj("ball_ext.obj");

        logo.load_obj("nba.obj");
        logo1.load_obj("nba.obj");
    }
    void draw(SDL_Surface *screen, Camera cam)
    {
        for(int i = 0; i < obj1.faces.size(); i+= 2)
        {
            obj1.my_fill(screen, obj1.faces[i], black, cam);
            obj1.my_fill(screen, obj1.faces[i+1], black, cam);
        }
        for(int i = 0; i <(ball1.size()-3); i+=2)
        {
            triangleFill(screen, ball1[i], ball1[i+1], ball1[i+2], 0xff925e, 0.7, 0.7, .6, 10, cam);
            triangleFill(screen, ball1[i+1], ball1[i+2], ball1[i+3], 0xff925e, 0.7, 0.7, .6, 10, cam);
        }

        for(int i = 0; i < logo1.faces.size(); i+= 2)
        {
            logo1.my_fill(screen, logo1.faces[i], red, cam);
            logo1.my_fill(screen, logo1.faces[i+1], red, cam);
        }
    }
    void rotateY(float t)
    {
        for(int i = 0; i<obj1.vertex.size(); i++)
        {
            obj1.vertex[i].z = obj.vertex[i].z * cos(t) - obj.vertex[i].x * sin(t) + 5010;
            obj1.vertex[i].x = obj.vertex[i].z * sin(t) + obj.vertex[i].x * cos(t);
        }

        for(int i = 0; i<ball1.size(); i++)
        {
            ball1[i].putz ( ball[i].getz() * cos(t) - ball[i].getx() * sin(t) + 5010);
            ball1[i].putx ( ball[i].getz() * sin(t) + ball[i].getx() * cos(t));
        }
        for(int i = 0; i<logo1.vertex.size(); i++)
        {
            logo1.vertex[i].z = logo.vertex[i].z * cos(t) - logo.vertex[i].x * sin(t) + 5010;
            logo1.vertex[i].x = logo.vertex[i].z * sin(t) + logo.vertex[i].x * cos(t);
        }
    }

    void rotateZ(float t)
    {
        for(int i = 0; i<obj1.vertex.size(); i++)
        {
            obj1.vertex[i].x = obj.vertex[i].x * cos(t) - obj.vertex[i].y * sin(t);
            obj1.vertex[i].y = obj.vertex[i].x * sin(t) + obj.vertex[i].y * cos(t) + 1210;
        }
//
        for(int i = 0; i<ball1.size(); i++)
        {
            ball1[i].putx ( ball[i].getx() * cos(t) - ball[i].gety() * sin(t));
            ball1[i].puty ( ball[i].getx() * sin(t) + ball[i].gety() * cos(t) + 1210);
        }
        for(int i = 0; i<logo1.vertex.size(); i++)
        {
            logo1.vertex[i].x = logo.vertex[i].x * cos(t) - logo.vertex[i].y * sin(t);
            logo1.vertex[i].y = logo.vertex[i].x * sin(t) + logo.vertex[i].y * cos(t) + 1210;
        }
    }


    void rotateX(float t)
    {
        for(int i = 0; i<obj1.vertex.size(); i++)
        {
            obj1.vertex[i].y = obj.vertex[i].y * cos(t) - obj.vertex[i].z * sin(t) + 1210;
            obj1.vertex[i].z = obj.vertex[i].y * sin(t) + obj.vertex[i].z* cos(t) + 5010;
        }
        for(int i = 0; i<ball1.size(); i++)
        {
            ball1[i].puty ( ball[i].gety() * cos(t) - ball[i].getz() * sin(t) + 1210);
            ball1[i].putz ( ball[i].gety() * sin(t) + ball[i].getz() * cos(t) + 5010);
        }
        for(int i = 0; i<logo1.vertex.size(); i++)
        {
            logo1.vertex[i].y = logo.vertex[i].y * cos(t) - logo.vertex[i].z * sin(t) + 1210;
            logo1.vertex[i].z = logo.vertex[i].y * sin(t) + logo.vertex[i].z * cos(t) + 5010;
        }
    }

    void translate( cood c )
    {
        for(int i = 0; i <obj1.vertex.size(); i++)
        {
            obj1.vertex[i].x =  obj.vertex[i].x + c.getx();
            obj1.vertex[i].y =  obj.vertex[i].y + c.gety();
            obj1.vertex[i].z =  obj.vertex[i].z + c.getz();
        }
        for(int i = 0; i <logo1.vertex.size(); i++)
        {
            logo1.vertex[i].x =  logo.vertex[i].x + c.getx();
            logo1.vertex[i].y =  logo.vertex[i].y + c.gety();
            logo1.vertex[i].z =  obj.vertex[i].z + c.getz();
        }
    }
};


class Basketball
{
    private:
    std::vector<cood> ball = my_translate(my_sphere(50),0,1210,5010);
    std::vector<cood> balls = my_translate(my_sphere(50),0,0,0);
    float t = .1;
    public:
    void my_draw(SDL_Surface *screen, Uint32 color1, Uint32 color2, Camera cam)
    {
        for(int i = 0; i <(ball.size()-3); i+=2)
        {
            triangleFill(screen, ball[i], ball[i+1], ball[i+2], color1, 0.8, 0.9, .99, 300, cam);
            triangleFill(screen, ball[i+1], ball[i+2], ball[i+3], color2, 0.8, 0.9, .99, 300, cam);
        }
    }
    void my_rotate()
    {
        cood cen = ball.back();
        Eigen::Matrix4f R = Rotate_Ball(t);
        ball = Transform(R, balls);
        ball = Transform(Translate(cen), ball);
        t += .5;
    }
    void translate( cood c )
    {
        for(int i = 0; i <(ball.size()-1); i++)
        {
            ball[i].putx( balls[i].getx() + c.getx() );
            ball[i].puty( balls[i].gety() + c.gety() );
            ball[i].putz( balls[i].getz() + c.getz() );
        }
    }
};

class Pole
{
    private:
    //cood of position_v(0,0,5840);
    //cood of  position_h(0,1400,5180);
    std::vector<cood> pole_v = my_translate(my_cylinder_vertical(80,1300), 0, 0, 5840);
    std::vector<cood> pole_h = my_translate(my_cylinder_horizontal(80,660), 0, 1300, 5190);
    public:
    void my_draw(SDL_Surface *screen, Uint32 color1, Uint32 color2, Camera cam)
    {
        for(int i = 0; i <(pole_v.size()-2); i+=2)
        {
            triangleFill(screen, pole_v[i], pole_v[i+1], pole_v[i+2], color1, 0.8, 0.8, .6, 60, cam);
            triangleFill(screen, pole_v[i+1], pole_v[i+2], pole_v[i+3], color2, 0.8, 0.8, .6, 60, cam);
        }
        for(int i = 0; i <(pole_h.size()-2); i+=2)
        {
            triangleFill(screen, pole_h[i], pole_h[i+1], pole_h[i+2], color1, 0.8, 0.8, .6, 60, cam);
            triangleFill(screen, pole_h[i+1], pole_h[i+2], pole_h[i+3], color2, 0.8, 0.8, .6, 60, cam);
        }
    }
};

class Rim
{
    //rim cood 0,1210,5010
    private:
    std::vector<cood> bar_l = my_translate(my_cylinder_horizontal(10,50), -30, 1210, 5115);
    std::vector<cood> bar_r = my_translate(my_cylinder_horizontal(10,50), 30, 1210, 5115);
    std::vector<cood> ring = my_translate(my_ring(100,20), 0, 1210, 5010);
    public:
    void my_draw(SDL_Surface *screen, Uint32 color1, Uint32 color2, Camera cam)
    {
        for(int i = 0; i <(ring.size()-2); i+=2)
        {
            triangleFill(screen, ring[i], ring[i+1], ring[i+2], color1, 0.8, 0.95, .85, 100, cam);
            triangleFill(screen, ring[i+1], ring[i+2], ring[i+3], color2, 0.8, 0.95, .85, 100, cam);
        }
        for(int i = 0; i <(bar_l.size()-2); i+=2)
        {
            triangleFill(screen, bar_l[i], bar_l[i+1], bar_l[i+2], color1, 0.8, 0.95, .85, 100, cam);
            triangleFill(screen, bar_l[i+1], bar_l[i+2], bar_l[i+3], color2, 0.8, 0.95, .85, 100, cam);
        }
        for(int i = 0; i <(bar_r.size()-2); i+=2)
        {
            triangleFill(screen, bar_r[i], bar_r[i+1], bar_r[i+2], color1, 0.8, 0.95, .85, 100, cam);
            triangleFill(screen, bar_r[i+1], bar_r[i+2], bar_r[i+3], color2, 0.8, 0.95, .85, 100, cam);
        }
    }
};

class Board
{
    private:
    std::vector<cood> face_front_d = my_translate(my_rect_xy(720, 20, 0), -360, 1180, 5160);
    std::vector<cood> face_front_u = my_translate(my_rect_xy(720, 20, 0), -360, 1580, 5160);
    std::vector<cood> face_front_l = my_translate(my_rect_xy(20, 441, 0), -360, 1180, 5158);
    std::vector<cood> face_front_r = my_translate(my_rect_xy(20, 441, 0), 340, 1180, 5158);

    std::vector<cood> face_front_id = my_translate(my_rect_xy(240, 20, 0), -120, 1180, 5158);
    std::vector<cood> face_front_iu = my_translate(my_rect_xy(240, 20, 0), -120, 1360, 5156);
    std::vector<cood> face_front_il = my_translate(my_rect_xy(20, 280, 0), -120, 1180, 5156);
    std::vector<cood> face_front_ir = my_translate(my_rect_xy(20, 280, 0), 100, 1180, 5156);

    std::vector<cood> face_front = my_translate(my_rect_xy(680, 380, 0), -340, 1200, 5161);
    std::vector<cood> face_back = my_translate(my_rect_xy(720, 420, 30), -360, 1180, 5160);
    std::vector<cood> face_top = my_translate(my_rect_xz(720, 30, 420), -360, 1180, 5160);
    std::vector<cood> face_bottom = my_translate(my_rect_xz(720, 30, 0), -360, 1180, 5160);
    std::vector<cood> face_left = my_translate(my_rect_yz(420, 30, 0), -360, 1180, 5160);
    std::vector<cood> face_right = my_translate(my_rect_yz(420, 30, 720), -360, 1200, 5160);
    public:
    void my_draw(SDL_Surface *screen, Uint32 color_front, Uint32 color_front1, Uint32 color_back, Uint32 color_back1, Uint32 color_side, Uint32 color_side1, Camera cam)
    {
        for(int i = 0; i <(face_front_iu.size()-2); i+=2)
        {
            triangleFill(screen, face_front_iu[i], face_front_iu[i+1], face_front_iu[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_iu[i+1], face_front_iu[i+2], face_front_iu[i+3], black, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_front_id.size()-2); i+=2)
        {
            triangleFill(screen, face_front_id[i], face_front_id[i+1], face_front_id[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_id[i+1], face_front_id[i+2], face_front_id[i+3], black, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_front_il.size()-2); i+=2)
        {
            triangleFill(screen, face_front_il[i], face_front_il[i+1], face_front_il[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_il[i+1], face_front_il[i+2], face_front_il[i+3], black, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_front_ir.size()-2); i+=2)
        {
            triangleFill(screen, face_front_ir[i], face_front_ir[i+1], face_front_ir[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_ir[i+1], face_front_ir[i+2], face_front_ir[i+3], black, 0.3, 0.4, .3, 10, cam);
        }



        for(int i = 0; i <(face_front_u.size()-2); i+=2)
        {
            triangleFill(screen, face_front_u[i], face_front_u[i+1], face_front_u[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_u[i+1], face_front_u[i+2], face_front_u[i+3], black, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_front_d.size()-2); i+=2)
        {
            triangleFill(screen, face_front_d[i], face_front_d[i+1], face_front_d[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_d[i+1], face_front_d[i+2], face_front_d[i+3], black, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_front_l.size()-2); i+=2)
        {
            triangleFill(screen, face_front_l[i], face_front_l[i+1], face_front_l[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_l[i+1], face_front_l[i+2], face_front_l[i+3], black, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_front_r.size()-2); i+=2)
        {
            triangleFill(screen, face_front_r[i], face_front_r[i+1], face_front_r[i+2], black, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front_r[i+1], face_front_r[i+2], face_front_r[i+3], black, 0.3, 0.4, .3, 10, cam);
        }

        for(int i = 0; i <(face_front.size()-2); i+=2)
        {
            triangleFill(screen, face_front[i], face_front[i+1], face_front[i+2], color_front,0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_front[i+1], face_front[i+2], face_front[i+3], color_front1, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_left.size()-2); i+=2)
        {
            triangleFill(screen, face_left[i], face_left[i+1], face_left[i+2], color_side, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_left[i+1], face_left[i+2], face_left[i+3], color_side1, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_right.size()-2); i+=2)
        {
            triangleFill(screen, face_right[i], face_right[i+1], face_right[i+2], color_side, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_right[i+1], face_right[i+2], face_right[i+3], color_side1, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_top.size()-2); i+=2)
        {
            triangleFill(screen, face_top[i], face_top[i+1], face_top[i+2], color_side, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_top[i+1], face_top[i+2], face_top[i+3], color_side1, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_bottom.size()-2); i+=2)
        {
            triangleFill(screen, face_bottom[i], face_bottom[i+1], face_bottom[i+2], color_side, 0.3, 0.4, .3, 10, cam);
            triangleFill(screen, face_bottom[i+1], face_bottom[i+2], face_bottom[i+3], color_side1, 0.3, 0.4, .3, 10, cam);
        }
        for(int i = 0; i <(face_back.size()-2); i+=2)
        {
            triangleFill(screen, face_back[i], face_back[i+1], face_back[i+2], color_back, cam);
            triangleFill(screen, face_back[i+1], face_back[i+2], face_back[i+3], color_back1, cam);
        }
    }
};

class Paint
{
    private:
    std::vector<cood> my_paint = my_translate(my_rect_xz(1360, 2280, 1), -680, 0, 3380);
    std::vector<cood> bottom = my_translate(my_rect_xz(1440, 40, 2), -720, 0, 3340);
    std::vector<cood> left = my_translate(my_rect_xz(40, 2260, 2), -720, 0, 3380);
    std::vector<cood> right = my_translate(my_rect_xz(40, 2260, 2), 680, 0, 3380);
    public:
    void my_draw(SDL_Surface *screen, Uint32 color1, Uint32 color2, Camera cam)
    {
        for(int i = 0; i <(my_paint.size()-2); i+=2)
        {
            triangleFill(screen, my_paint[i], my_paint[i+1], my_paint[i+2], color1, 0.65, 0.7, .65, 80, cam);
            triangleFill(screen, my_paint[i+1], my_paint[i+2], my_paint[i+3], color2, 0.65, 0.7, .65, 80, cam);
        }
        for(int i = 0; i <(bottom.size()-2); i+=2)
        {
            triangleFill(screen, bottom[i], bottom[i+1], bottom[i+2], white, 0.65, 0.7, .65, 80, cam);
            triangleFill(screen, bottom[i+1], bottom[i+2], bottom[i+3], white, 0.65, 0.7, .65, 80, cam);
        }
        for(int i = 0; i <(left.size()-2); i+=2)
        {
            triangleFill(screen, left[i], left[i+1], left[i+2], white, 0.65, 0.7, .65, 80, cam);
            triangleFill(screen, left[i+1], left[i+2], left[i+3], white, 0.65, 0.7, .65, 80, cam);
        }
        for(int i = 0; i <(right.size()-2); i+=2)
        {
            triangleFill(screen, right[i], right[i+1], right[i+2], white, 0.65, 0.7, .65, 80, cam);
            triangleFill(screen, right[i+1], right[i+2], right[i+3], white, 0.65, 0.7, .65, 80, cam);
        }
    }

};
class Boundary
{
    private:
    std::vector<cood> left = my_translate(my_rect_xz(40, 5640, 1), -3000, 0, 0);
    std::vector<cood> mid = my_translate(my_rect_xz(6040, 40, 1), -3000, 0, 0);
    std::vector<cood> top = my_translate(my_rect_xz(6040, 40, 1), -3000, 0, 5600);
    std::vector<cood> right = my_translate(my_rect_xz(40, 5640, 1), 3000, 0, 0);
    std::vector<cood> floor = my_translate(my_rect_xz(6000, 5640, -5), -2980, 0, 0);
    public:
    void my_draw(SDL_Surface *screen, Uint32 color, Uint32 color1, Camera cam)
    {
        for(int i = 0; i <(top.size()-2); i+=2)
        {
            triangleFill(screen, top[i], top[i+1], top[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, top[i+1], top[i+2], top[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
        for(int i = 0; i <(mid.size()-2); i+=2)
        {
            triangleFill(screen, mid[i], mid[i+1], mid[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, mid[i+1], mid[i+2], mid[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
        for(int i = 0; i <(left.size()-2); i+=2)
        {
            triangleFill(screen, left[i], left[i+1], left[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, left[i+1], left[i+2], left[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
        for(int i = 0; i <(right.size()-2); i+=2)
        {
            triangleFill(screen, right[i], right[i+1], right[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, right[i+1], right[i+2], right[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
        for(int i = 0; i <(floor.size()-2); i+=2)
        {
            triangleFill(screen, floor[i], floor[i+1], floor[i+2], color, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, floor[i+1], floor[i+2], floor[i+3], color1, 0.5, 0.65, .65, 80, cam);
        }
    }
};

class Perimeter
{
    private:
    std::vector<cood> three = my_translate(my_semicircle_down(2410, 40, 1), 0, 0, 5010 );
    std::vector<cood> free_throw = my_translate(my_semicircle_down(720, 40, 1), 0, 0, 3340 );
    std::vector<cood> left = my_translate(my_rect_xz(40, 630, 1), -2410, 0, 5000);
    std::vector<cood> right = my_translate(my_rect_xz(40, 630, 1), 2370, 0, 5000);
    public:
    void my_draw(SDL_Surface *screen, Camera cam)
    {
        for(int i = 0; i <(three.size()-2); i+=2)
        {
            triangleFill(screen, three[i], three[i+1], three[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, three[i+1], three[i+2], three[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
        for(int i = 0; i <(free_throw.size()-2); i+=2)
        {
            triangleFill(screen, free_throw[i], free_throw[i+1], free_throw[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, free_throw[i+1], free_throw[i+2], free_throw[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
        for(int i = 0; i <(left.size()-2); i+=2)
        {
            triangleFill(screen, left[i], left[i+1], left[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, left[i+1], left[i+2], left[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
        for(int i = 0; i <(right.size()-2); i+=2)
        {
            triangleFill(screen, right[i], right[i+1], right[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, right[i+1], right[i+2], right[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
    }
};

class Center
{
    private:
    std::vector<cood> cent = my_translate(my_circle(720, 40, 1), 0, 0, 0);
    public:
    void my_draw(SDL_Surface *screen, Camera cam)
    {
        for(int i = 0; i <(cent.size()-2); i+=2)
        {
            triangleFill(screen, cent[i], cent[i+1], cent[i+2], white, 0.5, 0.65, .65, 80, cam);
            triangleFill(screen, cent[i+1], cent[i+2], cent[i+3], white, 0.5, 0.65, .65, 80, cam);
        }
    }
};

void my_shoot(SDL_Surface *screen, Camera cam, Basketball b, cood c1);

#endif
