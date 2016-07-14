#ifndef MYFUNCTIONS_H
#define MYFUNCTIONS_H

#include <iostream>
#include <cmath>
#include <vector>
#include <SDL/SDL.h>
#include <Eigen/Dense>

#define PI 3.14159265358979323

#define SCREEN_WIDTH 800
#define  SCREEN_HEIGHT 600
#define  SCREEN_BPP 32

#define floor_color 0xff9651
#define red 0xff0000
#define blue 0x0000ff
#define black 0x404040
#define white 0xffffff
#define brown 0xb97a57
#define orange 0xff7f00
#define green 0x00ff00
#define yellow 0xffff00
#define purple 0x800080
#define gray 0x808080
#define light_blue 0x80ffff

static float my_z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

static float light_intensity = .85;
static int light_x = 0;
static int light_y = 1200;
static int light_z = 5000;


inline void my_swap(int &a, int &b)
{
    int tmp=a;
    a=b;
    b=tmp;
}
inline void my_swap(float &a, float &b)
{
    float tmp=a;
    a=b;
    b=tmp;
}
Uint32 intensity(float reflection_coeff, float light_intensity, Uint32 color);

inline float my_max( float , float );
inline float my_min( float , float );


void putpixel(SDL_Surface * screen, int x, int y, Uint32 color);

class cood;
class Camera;

//cood my_transform( Eigen::Matrix4d  a, cood v);
//std::vector<cood> concate(std::vector<cood> dest, std::vector<cood> src);

class Camera
{
    public:
    float z_prp;
    float z_vp;
    float x_prp;
    float y_prp;
    float x_vp;
    float y_vp;

    float near_p = ( z_prp);
    float far_p = (z_vp + 10000);
    float phi = 2 * atan(SCREEN_HEIGHT/(2*(z_vp - z_prp)));
    float theta = 2 * atan(SCREEN_WIDTH/(2*(z_vp - z_prp)));
    //float y_prp;
    public:
    Camera() : z_prp(0), z_vp(50), x_prp(0), y_prp(0), x_vp(0), y_vp(){ }
    Camera(float a, float b, float c, float d, float e, float f) : x_prp(a), y_prp(b), z_prp(c), x_vp(d), y_vp(e), z_vp(f){ }
    ~Camera(){}
    inline float get_z_prp()
    {
        return z_prp;
    }
    inline float get_z_vp()
    {
        return z_vp;
    }
    inline float get_x_prp()
    {
        return x_prp;
    }
    inline float get_y_prp()
    {
        return y_prp;
    }
    inline float get_x_vp()
    {
        return x_vp;
    }
    inline float get_y_vp()
    {
        return y_vp;
    }
    inline float get_phi()
    {
        return phi;
    }
    inline float get_theta()
    {
        return theta;
    }


    inline float get_near_p()
    {
        return near_p;
    }
    inline float get_far_p()
    {
        return far_p;
    }
    inline void put_far_p( float a )
    {
        far_p = a;
    }
    inline void put_near_p( float a )
    {
        near_p = a;
    }


    inline void put_z_prp( float a)
    {
        z_prp = a;
    }
    inline void  put_z_vp( float a )
    {
        z_vp = a;
    }
    inline void  put_x_prp( float a )
    {
        x_prp = a;
    }
    inline void  put_y_prp( float a )
    {
        y_prp = a;
    }
    inline void  put_x_vp( float a )
    {
        x_vp = a;
    }
    inline void put_y_vp( float a )
    {
        y_vp = a;
    }
    inline void zoom( float a)
    {
        z_prp += a;
        z_vp += a;
    }
    inline void  inr_phi( float a )
    {
        if((-phi) < a)
            phi += a;

    }
    inline void  inr_theta( float a )
    {
        theta += a;
    }

     void rotateY(float t)
    {
        z_prp = z_prp * cos(t) - x_prp * sin(t);
        x_prp = z_prp * sin(t) + x_prp * cos(t);
    }
    void rotateX(float t)
    {
        y_prp = y_prp * cos(t) - z_prp * sin(t);
        z_prp = y_prp * sin(t) + z_prp * cos(t);
    }
    void rotateZ(float t)
    {
        x_prp = x_prp * cos(t) - y_prp * sin(t);
        y_prp = x_prp * sin(t) + y_prp * cos(t);
    }

    void change(float a, float b, float c, float d, float e, float f)
    {
        x_prp = a;
        y_prp = b;
        z_prp = c;
        x_vp = d;
        y_vp = e;
        z_vp = f;
    }
};
class cood
{
    private:

    float x;
    float y;
    float z;

    public:
    cood():x(0),y(0),z(0){}

    cood(float m,float n):x(m),y(n){}

    cood(float m,float n,float o):x(m),y(n),z(o){}

    ~cood(){}

    inline float getx()
    {
        return x;
    }

    inline float gety()
    {
        return y;
    }

    inline float getz()
    {
        return z;
    }

    inline void putx( float a )
    {
        x = a;
    }


    inline void puty( float b )
    {
        y = b;
    }

    inline void putz( float c )
    {
        z = c;
    }
    //operator overloading
    inline cood operator +( cood b)
    {
        return cood( x + b.getx(), y + b.gety(), z + b.getz());
    }
    inline cood operator -( cood b)
    {
        return cood( x - b.getx(), y - b.gety(), z - b.getz());
    }
    inline cood operator *( float b )
    {
        return cood( x * b , y * b, z * b);
    }
    inline cood operator /( float b )
    {
        return cood( x / b , y / b, z / b);
    }

    inline float magnitude()
    {
        return sqrt(x * x + y * y + z * z);
    }

    inline float crossZ( cood b )
    {
        return (x * b.gety() - y * b.getx());
    }
    bool to_clip()
    {
        if(fabs(x)>1 ||fabs(y)>1 || z<-1.0 || z>1.0 )
            return 1;
        return 0;
    }

    inline cood cross( cood b);
    inline cood dot( cood b );
    inline float dot1( cood b )
    {
        float rx = x * b.getx();
        float ry = y * b.gety();
        float rz = z * b.getz();
        return (rx + ry + rz);
    }

    inline void translate(int x0, int y0, int z0);
    cood rotateY(float t);
    cood rotateZ(float t);
    cood rotateX(float t);

    cood my_transform( Eigen::Matrix4f a);
    cood to_viewing(Camera cam);
    cood toVC(Camera cam);

    inline void scale()
    {
        x = x*800;
        y = y*600;
    }

    cood to2dview()
    {
        return cood(x + SCREEN_WIDTH / 2, y + SCREEN_HEIGHT / 2, z);
    }
};

void triangleFill(SDL_Surface * screen, cood a, cood b, cood c, Uint32 color, Camera cam);
void triangleFill(SDL_Surface * screen, cood a, cood b, cood c, Uint32 color, float kd, float ka,float ks, float ns, Camera cam);
//void trianglefill(SDL_Surface * screen, cood a, cood b, cood c, Uint32 color, Camera cam);
void clearZBuffer();

void original_light();
void light_position1();
void change_light_x( int a );
void change_light_y( int a );
void change_light_z( int a );
void change_intensity(float a);

Uint32 intensity(float coeff, Uint32 color);





class point
{
    public:

    float x;
    float y;
    float z;

    point():x(0),y(0),z(0){}

    point(float m,float n):x(m),y(n){}

    point(float m,float n,float o):x(m),y(n),z(o){}

    ~point(){}

    //operator overloading
    inline point operator +( point b)
    {
        return point( x + b.x, y + b.y, z + b.z);
    }

    inline point operator -( point b)
    {
        return point( x - b.x, y - b.y, z - b.z);
    }
    inline point operator *( float b )
    {
        return point( x * b , y * b, z * b);
    }
    inline point operator /( float b )
    {
        return point( x / b , y / b, z / b);
    }

    inline float magnitude()
    {
        return sqrt(x * x + y * y + z * z);
    }

    inline float crossZ( point b )
    {
        return (x * b.y - y * b.x);
    }
    bool to_clip()
    {
        if(fabs(x)>1 ||fabs(y)>1 || z<-1.0 || z>1.0 )
            return 1;
        return 0;
    }

    inline point cross( point b);
    inline float dot( point b )
    {
        float rx = x * b.x;
        float ry = y * b.y;
        float rz = z * b.z;
        return (rx + ry + rz);
    }

    inline void translate(int x0, int y0, int z0);
    point rotateY(float t);
    point rotateZ(float t);
    point rotateX(float t);

    point my_transform( Eigen::Matrix4f a);
    point to_viewing(Camera cam);
    point toVC(Camera cam);

    inline void scale()
    {
        x = x*800;
        y = y*600;
    }

    point to2dview()
    {
        return point(x + SCREEN_WIDTH / 2, y + SCREEN_HEIGHT / 2, z);
    }
};

class property
{
    public:
    float kx;
    float ky;
    property( float x = 0, float y = 0):
    kx(x), ky(y) { }
};

class face
{
    public:
    unsigned int v_index[3];
    unsigned int n_index[3];
    unsigned int uv[3];
    face(float vx = 0, float vy = 0, float vz = 0, float nx = 0, float ny = 0, float nz = 0, float uv1 = 0, float uv2 = 0, float uv3 = 0):
    v_index({vx, vy, vz}), n_index({nx, ny, nz}), uv({uv1, uv2, uv3}) { }
};

class my_object
{
    public:
    std::vector< face > faces;
    std::vector< point > vertex;
    std::vector< point > normal;
    std::vector< property > prop;

    bool load_obj( std::string textfile);
    void my_fill(SDL_Surface * screen, face f, Uint32 color,  Camera cam);
};


Uint32 my_lighting( point light,point p, point b, point c, float ka, float kd, float ks, float ns, Uint32 color, Camera cam );
std::vector<point> my_translate(std::vector<point> vec, float x, float y, float z);
std::vector<point> my_scale(std::vector<point> vec, float s);
inline std::vector<point> rotateY(std::vector<point> vec, float t);
inline std::vector<point> rotateX(std::vector<point> vec, float t);

my_object my_scale(my_object o, float s);
my_object my_rotateY(my_object obj, float s);
my_object my_rotateX(my_object obj, float s);

bool pointInsideTriangle( point p, point a, point b, point c);

inline void my_swap(point &a, point &b);
void my_sort(point &a, point &b, point &c, point &na, point &nb, point &nc);









# endif



