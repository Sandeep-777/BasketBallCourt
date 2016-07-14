#ifndef MY_DRAW_H
#define MY_DRAW_H

#include "MyFunctions.h"
#include <iostream>
#include <vector>

std::vector<cood> my_translate(std::vector<cood> vec, float world_x, float world_y, float world_z);

void draw_line(SDL_Surface * screen, cood c1, cood c2, Uint32 color);
std::vector<cood> my_rect_xy(int length, int breadth, float z);
std::vector<cood> my_rect_yz(int length, int breadth, float x);
std::vector<cood> my_rect_xz(int length, int breadth, float y);
std::vector<cood> my_rect_xz_big(int length, int breadth, float y);

std::vector<cood> my_circle( int rad, int thickness, float y );
std::vector<cood> my_semicircle_up( int rad, int thickness, float y);
std::vector<cood> my_semicircle_down( int rad, int thickness, float y);

std::vector<cood> my_cylinder_vertical(int rad, int height);
std::vector<cood> my_cylinder_horizontal(int rad, int length);
std::vector<cood> my_ring(int rad, int thickness);
std::vector<cood> my_sphere(int rad);

#endif

