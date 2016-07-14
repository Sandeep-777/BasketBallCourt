#include "MyDraw.h"

std::vector<cood> my_translate(std::vector<cood> vec,float x, float y, float z)
{
    for(int i = 0; i<vec.size(); i++)
    {
        vec[i].putx(vec[i].getx() + x);
        vec[i].puty(vec[i].gety() + y);
        vec[i].putz(vec[i].getz() + z);
    }
    return vec;
}

void draw_line(SDL_Surface *screen, cood c1, cood c2, Uint32 color)
{
    int x0 = c1.getx();
    int y0 = c1.gety();
    int x1 = c2.getx();
    int y1 = c2.gety();
    int x, y;
    cood p;
    putpixel(screen, x, y, color);

    if( x0 == x1 )
    {
        if( y0 < y1)
        for( y = y0; y <= y1; y++ )
        {
            x = x0;
            p.putx(x);
            p.puty(y);
            putpixel(screen, x, y, color);
        }
        else
        for( y = y1; y <= y0; y++ )
        {
            x = x0;
            p.putx(x);
            p.puty(y);
            putpixel(screen, x, y, color);
        }
    }
    else if( y0 == y1 )
    {
        if(x0 < x1)
        for( x = x0; x <= x1; x++ )
        {
            y = y0;
            p.putx(x);
            p.puty(y);
            putpixel(screen, x, y, color);
        }
        else
        for( x = x1; x <= x0; x++ )
        {
            y = y0;
            p.putx(x);
            p.puty(y);
            putpixel(screen, x, y, color);
        }
    }
    else
    {
        bool steep = ((fabs(y1 - y0) > fabs(x1 - x0)) ? 1:0);
        if(steep)
        {
            my_swap(x0,y0);
            my_swap(x1,y1);
        }
        if(x0 >x1)
        {
            my_swap(x0,x1);
            my_swap(y0,y1);
        }

        int dErr = fabs(y1 - y0);
        int ystep = y0 > y1 ? -1 : 1;
        int dx = x1 - x0;

        int err = dx >> 1;
        int y = y0;

        for( int x = x0; x<=x1; x++)
        {
            if(steep)
            {
                p.putx(y);
                p.puty(x);
                putpixel(screen, x, y, color);
            }
            else
            {
                p.putx(x);
                p.puty(y);
                putpixel(screen, x, y, color);
            }
            err -= dErr;
            if(err < 0)
            {
                y += ystep;
                err += dx;
            }
        }
    }
}

std::vector<cood> my_rect_xy(int length, int breadth, float z)
{
    int flag = 1;
    std::vector<cood> rect;
    for(int i = 0; i <= ( breadth - 1 ); i += 40)
    {
        int j = i + 40;
        if( j > breadth )
            j = breadth;
            if(flag > 0){
        for(int k = 0;  k <= length;  k+= 40)
        {
            if(j > length)
                j = length;
            float x = k;
            float y = i;    //note 2.
            cood c1( x, y, z );
            cood c2( x, j, z );
            rect.push_back(c1);
            rect.push_back(c2);
        }
            }
            if(flag < 0)
            {
               for(int k = length;  k >= 0;  k -= 40)
        {
            if(j > length)
                j = length;
            float x = k;
            float y = i;    //note 2.
            cood c1( x, y, z );
            cood c2( x, j, z );
            rect.push_back(c1);
            rect.push_back(c2);
        }
            }
            flag *= -1;
    }
    return rect;

}
std::vector<cood> my_rect_yz(int length, int breadth, float x)
{
    int flag = 1;
    std::vector<cood> rect;
    for(int i = 0; i <= ( breadth - 1 ); i += 40)
    {
        int j = i + 40;
        if( j > breadth )
            j = breadth;
            if(flag > 0){
        for(int k = 0;  k <= length;  k+= 40)
        {
            if(j > length)
                j = length;
            float y = k;   //note 2.
            cood c1( x, y, i );
            cood c2( x, y, j );
            rect.push_back(c1);
            rect.push_back(c2);
        }
            }
            if(flag < 0)
            {
               for(int k = length;  k >= 0;  k -= 40)
        {
            if(j > length)
                j = length;
            float y = k;    //note 2.
            cood c1( x, y, i );
            cood c2( x, y, j );
            rect.push_back(c1);
            rect.push_back(c2);
        }
            }
            flag *= -1;
    }
    return rect;

}

std::vector<cood> my_rect_xz(int length, int breadth, float y)
{
    int flag = 1;
    std::vector<cood> rect;
    for(int i = 0; i <= ( breadth - 1 ); i += 40)
    {
        int j = i + 40;
        if( j > breadth )
            j = breadth;
            if(flag > 0){
        for(int k = 0;  k <= length;  k+= 40)
        {
            if(j > length)
                j = length;
            float x = k;   //note 2.
            cood c1( x, y, i );
            cood c2( x, y, j );
            rect.push_back(c1);
            rect.push_back(c2);
        }
            }
            if(flag < 0)
            {
               for(int k = length;  k >= 0;  k -= 40)
        {
            if(j > length)
                j = length;
            float x = k;    //note 2.
            cood c1( x, y, i );
            cood c2( x, y, j );
            rect.push_back(c1);
            rect.push_back(c2);
        }
            }
            flag *= -1;
    }
    return rect;

}

std::vector<cood> my_circle( int rad, int thickness, float y )
{
    int j = rad - thickness;
    std::vector<cood> circle;
    for(int theta = -180;  theta <= 180;  theta+= 3)
    {
        float a = theta*PI/180;
        float x = j*cos(a);
        float z = j*sin(a);    //note 2.
        float x1 = rad*cos(a);
        float z1 = rad*sin(a);
        cood c1( x, y, z );
        cood c2( x1, y, z1 );
        circle.push_back(c1);
        circle.push_back(c2);
    }
    return circle;
}
std::vector<cood> my_semicircle_down( int rad, int thickness, float y)
{
    int j = rad - thickness;
    std::vector<cood> semicircle;
    for(int theta = -180;  theta <= 0;  theta+= 3)
    {
        float a = theta*PI/180;
        float x = j*cos(a);
        float z = j*sin(a);    //note 2.
        float x1 = rad*cos(a);
        float z1 = rad*sin(a);
        cood c1( x, y, z );
        cood c2( x1, y, z1 );
        semicircle.push_back(c1);
        semicircle.push_back(c2);
    }
    return semicircle;
}
std::vector<cood> my_semicircle_up( int rad, int thickness, float y)
{
    int j = rad - thickness;
    std::vector<cood> semicircle;
    for(int theta = 0;  theta <= 180;  theta+= 3)
    {
        float a = theta*PI/180;
        float x = j*cos(a);
        float z = j*sin(a);    //note 2.
        float x1 = rad*cos(a);
        float z1 = rad*sin(a);
        cood c1( x, y, z );
        cood c2( x1, y, z1 );
        semicircle.push_back(c1);
        semicircle.push_back(c2);
    }
    return semicircle;
}

std::vector<cood> my_cylinder_horizontal(int rad, int length)
{
    std::vector<cood> cylinder;
    for(int i = 0; i <= ( length - 1 ); i += 80)
    {
        int j = i + 80;
        if( j > length )
            j = length;
        for(int theta = -180;  theta <= 180;  theta+= 3)
        {
            float a = theta*PI/180;
            float x = rad*cos(a);
            float y = rad*sin(a);    //note 2.
            cood c1( x, y, i );
            cood c2( x, y, j );
            cylinder.push_back(c1);
            cylinder.push_back(c2);
        }
    }
    return cylinder;
}

std::vector<cood> my_cylinder_vertical(int rad, int height)
{
    std::vector<cood> cylinder;
    for(int i = 0; i <= ( height - 1 ); i += 80)
    {
        int j = i + 80;
        if( j > height )
            j = height;
        for(int theta = -180;  theta <= 180;  theta+= 3)
        {
            float a = theta*PI/180;
            float x = rad*cos(a);
            float z = rad*sin(a);    //note 2.
            cood c1( x, i, z );
            cood c2( x, j, z );
            cylinder.push_back(c1);
            cylinder.push_back(c2);
        }
    }
    return cylinder;

}

std::vector<cood> my_ring(int rad, int thickness)
{
    std::vector<cood> ring;
    for(int alpha = -180; alpha <= 175; alpha += 5)
    {
        float a = alpha*PI/180;
        float b = (alpha + 5)*PI/180;
        float r = thickness/2;
        float x0 = rad*cos(a);
        float z0 = rad*sin(a);
        float x1 = rad*cos(b);
        float z1 = rad*sin(b);
        for(int theta = -180;  theta <= 170;  theta+= 10)
        {
            float c = theta*PI/180;
            float x = r*cos(c);
            float y = r*sin(c);    //note 2.
            cood c1( x0 +x, y, z0 );
            cood c2( x1 + x,y, z1 );
            ring.push_back(c1);
            ring.push_back(c2);
        }
    }
    return ring;

}

std::vector<cood> my_sphere(int rad)
{
    /*
    #define Band_Power 6   // 2^Band_Power = Total Points in a band.
    #define Band_Points  64// 16 = 2^Band_Power
    #define Band_Mask (Band_Points-2)
    #define Sections_In_Band ((Band_Points/2)-1)
    #define Total_Points (Sections_In_Band*Band_Points)
    // for each section in a band, we have a band
    #define Section_Arc (6.28/Sections_In_Band)
    */
    int Band_Power = 6;
    int Band_Points = 64;
    int Band_Mask = 62;
    int Sections_In_Band = ((Band_Points/2)-1);
    int Total_Points = (Sections_In_Band*Band_Points);
    double Section_Arc = (6.28/Sections_In_Band);

    std::vector<cood> sphere;
    float x_angle;
    float y_angle;

    for (int i=0;i<Total_Points;i++)
    {
        // using last bit to alternate,+band number (which band)
        x_angle=(float)(i&1)+(i>>Band_Power);

        // (i&Band_Mask)>>1 == Local Y value in the band
        // (i>>Band_Power)*((Band_Points/2)-1) == how many bands
        //  have we processed?
        // Remember - we go "right" one value for every 2 points.
        //  i>>bandpower - tells us our band number
        y_angle=(float)((i&Band_Mask)>>1)+((i>>Band_Power)*(Sections_In_Band));

        x_angle*=(float)Section_Arc/2.0f; // remember - 180° x rot not 360
        y_angle*=(float)Section_Arc;

        float x = rad*sin(x_angle)*sin(y_angle);
        float y = rad*cos(x_angle);
        float z =  rad*sin(x_angle)*cos(y_angle);
        cood c(x,y,z);
        sphere.push_back(c);
    }
    cood center(0, 0, 0);
    sphere.push_back(center);
    return sphere;
}


std::vector<cood> my_rect_xz_big(int length, int breadth, float y)
{
    int flag = 1;
    std::vector<cood> rect;
    for(int i = 0; i <= ( breadth - 1 ); i += 60)
    {
        int j = i + 60;
        if( j > breadth )
            j = breadth;
        if(flag > 0)
        {
            for(int k = 0;  k <= length;  k+= 60)
            {
                if(j > length)
                    j = length;
                float x = k;   //note 2.
                cood c1( x, y, i );
                cood c2( x, y, j );
                rect.push_back(c1);
                rect.push_back(c2);
            }
        }
        if(flag < 0)
        {
            for(int k = length;  k >= 0;  k -= 60)
            {
            if(j > length)
                j = length;
            float x = k;    //note 2.
            cood c1( x, y, i );
            cood c2( x, y, j );
            rect.push_back(c1);
            rect.push_back(c2);
            }
        }
        flag *= -1;
    }
    return rect;

}
