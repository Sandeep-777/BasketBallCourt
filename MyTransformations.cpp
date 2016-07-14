#include "MyTransformations.h"

Eigen::Matrix4f Translate( cood c )
{
    Eigen::Matrix4f m;
    m << 1,  0,     0,      c.getx(),
         0,  1,     0,      c.gety(),
         0,  0,     1,      c.getz(),
         0,  0,     0,      1;

    return m;
}
Eigen::Matrix4f Rotate_Ball( float t )
{
    Eigen::Matrix4f R;
    R << 1, 0,      0,          0,
         0, cos(t), -sin(t),    0,
         0, sin(t), cos(t),     0,
         0, 0,      0,          1;
    return R;
}

Eigen::Matrix4f Translate( float x, float y, float z )
{
    Eigen::Matrix4f m;
    m << 1,  0,     0,      x,
         0,  1,     0,      y,
         0,  0,     1,      z,
         0,  0,     0,      1;

    return m;
}

Eigen::Matrix4f Rotate_X_3D( cood c1 )// c is point from origin that makes angle alpha w.r.t x axis
{
    float a = c1.getx();
    float b = c1.gety();
    float c = c1.getz();
    float d = sqrt(b*b + c*c);

    Eigen::Matrix4f x;
    x << 1,  0,     0,      0,
         0,  c/d,   -b/d,   0,
         0,  b/d,   c/d,    0,
         0,  0,     0,      1;

    return(x);
}

Eigen::Matrix4f Rotate_Y_3D( cood c1 )
{
    float a = c1.getx();
    float b = c1.gety();
    float c = c1.getz();
    float d = sqrt(b*b + c*c);
    Eigen::Matrix4f x;
    x << d,  0,     -a,      0,
         0,  1,     0,       0,
         a,  0,     d,       0,
         0,  0,     0,      1;

    return(x);
}

Eigen::Matrix4f Rotate_Z_3D( float a )
{
    Eigen::Matrix4f b;
    b << cos(a),    -sin(a),    0,  0,
         sin(a),    cos(a),     0,  0,
         0,         0,          1,  0,
         0,         0,          0,  1;

    return b;
}

Eigen::Matrix4f Rotate_O_3D( Eigen::Vector3f v , float x )
{
    float a = int(v(0));
    float b = int(v(1));
    float c = int(v(2));
    float d = sqrt(b*b + c*c);

    Eigen::Matrix4f m;
    m << a*a + (1 - a*a)*cos(x),          a*b*(1 - cos(x)) - c*sin(x),    a*c*(1 - cos(x)) + b*sin(x),    0,
         a*b*(1 - cos(x)) + c*sin(x),     b*b + (1 - b*b)*cos(x),         b*c*(1 - cos(x)) - a*sin(x),    0,
         a*c*(1 - cos(x)) - b*sin(x),     b*c*(1 - cos(x)) + a*sin(x),    c*c + (1 - c*c)*cos(x),         0,
         0,                               0,                              0,                              1;
    return m;
}

Eigen::Matrix4f my_scale( float sx, float sy, float sz)
{
    Eigen::Matrix4f m;
    m << sx,     0,       0,       0,
         0,      sy,      0,       0,
         0,      0,       sz,      0,
         0,      0,       0,       1;
    return m;
}

Eigen::Matrix4f my_scale( cood c, float sx, float sy, float sz)
{
    Eigen::Matrix4f m;
    m << sx,     0,       0,       (1 - sx)*c.getx(),
         0,      sy,      0,       (1 - sy)*c.gety(),
         0,      0,       sz,      (1 - sz)*c.getz(),
         0,      0,       0,       1;
    return m;
}

Eigen::Matrix4f Rotate_line( cood p1, cood p2 ,cood s, int r )//unit vector
{
    float x = s.getx();
    float y = s.gety();
    float z = s.getz();
    cood vec = p2 - p1;
    float a = vec.getx()/vec.magnitude();
    float b = vec.gety()/vec.magnitude();
    float c = vec.getz()/vec.magnitude();

    Eigen::Matrix4f m;
    m << a*a + (b*b + c*c)*cos(r),        a*b*(1 - cos(r)) - c*sin(r),    a*c*(1 - cos(r)) + b*sin(r),    (x*(b*b + c*c) - a*(y*b + z*c))*(1 - cos(r)) + (y*c - z*b)*sin(r),
         a*b*(1 - cos(r)) + c*sin(r),     b*b + (a*a + c*c)*cos(r),       b*c*(1 - cos(r)) - a*sin(r),    (y*(a*a + c*c) - b*(x*a + z*c))*(1 - cos(r)) + (z*a - x*c)*sin(r),
         a*c*(1 - cos(r)) - b*sin(r),     b*c*(1 - cos(r)) + a*sin(r),    c*c + (a*a + b*b)*cos(r),       (z*(a*a + b*b) - c*(x*a + y*b))*(1 - cos(r)) + (x*b - y*a)*sin(r),
         0,                               0,                              0,                              1;
    return m;
}

std::vector<cood> Transform( Eigen::Matrix4f  a, std::vector<cood> v)
{
    std::vector<cood> m;
    cood c;

    for(unsigned int i = 0; i < v.size(); i++)
    {
        float x;
        float y;
        float z;
        float s;
        x = a(0,0)*v[i].getx() + a(0,1)*v[i].gety() + a(0,2)*v[i].getz() + a(0,3)*1;
        y = a(1,0)*v[i].getx() + a(1,1)*v[i].gety() + a(1,2)*v[i].getz() + a(1,3)*1;
        z = a(2,0)*v[i].getx() + a(2,1)*v[i].gety() + a(2,2)*v[i].getz() + a(2,3)*1;
        s = a(3,0)*v[i].getx() + a(3,1)*v[i].gety() + a(3,2)*v[i].getz() + a(3,3)*1;
        c.putx(x/s);
        c.puty(y/s);
        c.putz(z/s);
        m.push_back(c);
    }
    return m;
}

std::vector<cood> my_path(cood c0)
{
    std::vector<cood> M;
    float y0 = c0.gety();
    float z0 = c0.getz();
    float x0 = c0.getx();

    float x;
    float y;
    float z;

    float ym = 1600;//max ht
    float y2 = 1210;//rim ht
    float z2 = 5010;//postion of rim

    float B = 4*ym - y2 - 3*y0;
    float A = 2*y0 - 4*ym + 2*y2;
    float C = y0;

    for(float t=0; t<=1.5; t+= 0.05)
    {
        x = - (x0) * t + x0;
        y = A*t*t + B*t + C;
        z = (z2 -z0) * t + z0;
        if( y > 30)
        {
            cood c(x,y,z);
            M.push_back(c);
        }
    }
    return M;
}


std::vector<cood> ball_path( cood pa )
{
    std::vector<cood> M;
    float m = -(5010 - pa.getz())/(pa.getx());
    float release_height = pa.gety();
    float max_height = 1580;
    float y_max = (max_height - release_height);
    float g = 3860.9;//gravity
    float u = sqrt( 4 * g * y_max );
    float ux = u/sqrt(2);// x vel

    float uy0 = ux;
    float uy;// y vel

    float x = pa.getx();
    float y = release_height;
    float z = pa.getz();
    float time = 2*uy0/g;

    float ux2= -(.1*x)/time;
    float uz = (.1*(5040 - z))/time;
    cood c1(0,100,5000);
    //M.push_back(c1);
    for(float t = 0; t <=time; t += .1)
    {
        x += ux2;
        y = release_height + uy0 * t - 0.5*g*t*t;
        z += uz;
        if(y > release_height)
        {
            cood c(x,y,z);
            M.push_back(c);
        }
    }
    return M;
}
