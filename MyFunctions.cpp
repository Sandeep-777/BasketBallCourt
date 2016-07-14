#include "MyFunctions.h"

void putpixel(SDL_Surface * screen, int x, int y, Uint32 color)
{
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return ;
    Uint32 * pixels = (Uint32*)screen->pixels;
    pixels[y * SCREEN_WIDTH + x] = color;
}
void original_light()
{
    light_x = 0;
    light_y = 1200;
    light_z = 5000;
}
void light_position1()
{
    light_x = 0;
    light_y = 1200;
    light_z = 4400;
}
void change_light_x( int a )
{
    light_x += a;
}
void change_light_y( int a )
{
    light_y += a;
}
void change_light_z( int a )
{
    light_z += a;
}
void change_intensity(float a)
{
    light_intensity += a;
}

Uint32 intensity(float coeff, Uint32 color)
{
    Uint32 temp = color;
    Uint32 new_color;
    temp = temp & 0x0000ff;//for b value only
    new_color = temp*coeff;
    temp = color;
    temp = temp & 0x00ff00;
    temp = temp >> 8;
    temp = temp*coeff;
    temp = temp << 8;
    new_color += temp;
    temp = color;
    temp = temp & 0xff0000;
    temp = temp >> 16;
    temp = temp * coeff;
    temp = temp << 16;
    new_color += temp;
    return new_color;
}


inline float my_max( float x, float y)
{
    if(x > y)
        return x;
    return y;
}
inline float my_min( float x, float y)
{
    if(x < y)
        return x;
    return y;
}


inline cood cood::cross( cood b)
{
    float rx = y * b.getz() - z * b.gety();
    float ry = -(x * b.getz() - z * b.getx());
    float rz = x * b.gety() - y * b.getx();
    return cood(rx, ry, rz);
}
inline cood cood::dot( cood b)
{
    float rx = x * b.getx();
    float ry = y * b.gety();
    float rz = z * b.getz();
    return cood(rx, ry, rz);
}


inline void cood::translate(int x0, int y0, int z0)
{
    x += x0;
    y += y0;
    z += z0;
}


cood cood::my_transform( Eigen::Matrix4f a)
{
    cood m;
    float s;
    float x1 = a(0,0)*x + a(0,1)*y + a(0,2)*z + a(0,3)*1;
    float y1 = a(1,0)*x + a(1,1)*y + a(1,2)*z + a(1,3)*1;
    float z1 = a(2,0)*x + a(2,1)*y + a(2,2)*z + a(2,3)*1;
    s = a(3,0)*x + a(3,1)*y + a(3,2)*z + a(3,3)*1;
    m.putx( x1 / s );
    m.puty( y1 / s );
    m.putz( z1 / s );
    return m;
}

cood cood::to_viewing(Camera cam)
{
    cood n;
    cood u;
    cood v;

    cood VPN(cam.get_x_vp() - cam.get_x_prp(), cam.get_y_vp() - cam.get_y_prp(), cam.get_z_vp() - cam.get_z_prp());
    cood View_up(0,1,0);
    VPN = VPN/VPN.magnitude();
    cood temp1 = VPN*(VPN.dot1(View_up));
    cood temp2 = View_up - temp1;

    n = VPN / (-VPN.magnitude());
    v = temp2/temp2.magnitude();

    cood temp = v.cross(n);
    u = temp / temp.magnitude();

    Eigen::Matrix4f R;
    Eigen::Matrix4f T;
    Eigen::Matrix4f M;

    R << u.getx(),  u.gety(),   u.getz(),    0,
         v.getx(),  v.gety(),   v.getz(),    0,
         n.getx(),  n.gety(),   n.getz(),    0,
         0,         0,          0,           1;

    T << 1, 0, 0, -cam.get_x_prp(),
         0, 1, 0, -cam.get_y_prp(),
         0, 0, 1, -cam.get_z_prp(),
         0, 0, 0, 1;

    float s_factor_h = -1 / tan(cam.get_phi()/2);
    float s_factor_w = 1 / tan(cam.get_theta()/2);

    Eigen::Matrix4f Sxy;
    Sxy << s_factor_w,  0,             0,   0,
           0,           s_factor_h,    0,   0,
           0,           0,             1,   0,
           0,           0,             0,   1;

    //to align far plane to z = -1
    float s_factor_xyz = 1/cam.get_far_p();
    Eigen::Matrix4f Sxyz;
    Sxyz << s_factor_xyz,  0,             0,              0,
            0,             s_factor_xyz,  0,              0,
            0,             0,             s_factor_xyz,   0,
            0,             0,             0,              1;
    cam.put_near_p(cam.get_near_p()*s_factor_xyz);
    cam.put_far_p(1);
    //to transfer z = k plane to z =0 where k is near/far
    float d_factor = cam.get_near_p();
    Eigen::Matrix4f D;
    D << 1, 0,  0,              0,
         0, 1,  0,              0,
         0, 0,  1/(d_factor-1), d_factor/(d_factor - 1),
         0, 0,  -1,             0;


    M = R * T;
    M = Sxy * M;
    M = Sxyz * M;
    M = D * M;

    return (my_transform(M));
}

cood cood::toVC( Camera cam )
{
    cood n;
    cood u;
    cood v;

    cood VPN(cam.get_x_vp() - cam.get_x_prp(), cam.get_y_vp() - cam.get_y_prp(), cam.get_z_vp() - cam.get_z_prp());
    cood View_up(0,1,0);
    VPN = VPN/VPN.magnitude();
    cood temp1 = VPN*(VPN.dot1(View_up));
    cood temp2 = View_up - temp1;

    n = VPN / (-VPN.magnitude());
    v = temp2/temp2.magnitude();

    cood temp = v.cross(n);
    u = temp / temp.magnitude();

    Eigen::Matrix4f R;
    Eigen::Matrix4f T;
    Eigen::Matrix4f M;

    R << u.getx(),  u.gety(),   u.getz(),    0,
         v.getx(),  v.gety(),   v.getz(),    0,
         n.getx(),  n.gety(),   n.getz(),    0,
         0,         0,          0,           1;

    T << 1, 0, 0, -cam.get_x_prp(),
         0, 1, 0, -cam.get_y_prp(),
         0, 0, 1, -cam.get_z_prp(),
         0, 0, 0, 1;

    M = R*T;
    return(my_transform(R));
}
cood cood::rotateY(float t)
{
    float nz = z * cos(t) - x * sin(t);
    float nx = z * sin(t) + x * cos(t);
    return cood(nx, y, nz);
}
cood cood::rotateZ(float t)
{
    float nx = x * cos(t) - y * sin(t);
    float ny = x * sin(t) + y * cos(t);
    return cood(nx, ny, z);
}
cood cood::rotateX(float t)
{
    float ny = y * cos(t) - z * sin(t);
    float nz = y * sin(t) + z * cos(t);
    return cood(x, ny, nz);
}

bool pointInsideTriangle( cood p, cood a, cood b, cood c)
{
    float x = (p - a).crossZ(b - a);
    float y = (p - b).crossZ(c - b);
    float z = (p - c).crossZ(a - c);
    return (x >= 0 && y >= 0 && z >= 0) || (x < 0 && y < 0 && z < 0);
}

void my_swap(cood &a, cood &b)
{
    cood temp;
    temp.putx(a.getx());
    temp.puty(a.gety());
    temp.putz(a.getz());
    a.putx(b.getx());
    a.puty(b.gety());
    a.putz(b.getz());
    b.putx(temp.getx());
    b.puty(temp.gety());
    b.putz(temp.getz());
}

void triangleFill(SDL_Surface * screen, cood a, cood b, cood c, Uint32 color, float kd, float ka, float ks, float ns, Camera cam)
{
    cood pa = a.to_viewing(cam);
    cood pb = b.to_viewing(cam);
    cood pc = c.to_viewing(cam);

    bool a1 = pa.to_clip();
    bool b1 = pb.to_clip();
    bool c1 = pc.to_clip();
    bool flag = a1 && b1&& c1;

    pa.scale();
    pb.scale();
    pc.scale();

    //to centre of screen
    pa.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pb.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pc.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );

    /////////////////////////////
    //shading
    if(!flag)
    {
        float Ia = 0.35;
        float Ib = light_intensity;
        float kx;
        cood light(light_x, light_y, light_z);
        cood centers(0,0,0);
        cood centroid = (a +(b+c))/3;
        cood V(0,0,0);
        V.putx( centroid.getx() - cam.get_x_prp() );
        V.puty( centroid.gety() - cam.get_y_prp() );
        V.putz( centroid.getz() - cam.get_z_prp() );
        cood L = light - centroid;
        cood H = (L + V )/(L + V).magnitude();
        float d = L.magnitude();
        cood N = (b - a).cross(c - a);
        float nl = fabs(L.dot1(N)/(L.magnitude()*N.magnitude()));
        float nh = fabs(N.dot1(H)/(N.magnitude()*H.magnitude()));

        float attenuation = 1/(1 + .001d + .0000005*d*d);
        attenuation = my_min(1, attenuation);
        kx = ka*Ia + attenuation*Ib*kd*nl + attenuation*ks*Ib*pow(nh,ns);
        kx = my_min(1,kx);
        color = intensity(kx, color);
    }
    //////////////////////////
    if(!flag)
    {
        float minx = my_min(pa.getx(), my_min(pb.getx(), pc.getx()));
        float miny = my_min(pa.gety(), my_min(pb.gety(), pc.gety()));
        float maxx = my_max(pa.getx(), my_max(pb.getx(), pc.getx()));
        float maxy = my_max(pa.gety(), my_max(pb.gety(), pc.gety()));

        for (int i = miny; i <= maxy; ++i)
        {
            if (i < 0)
                continue;
            if (i >= SCREEN_HEIGHT)
                break;
            bool inside = 0;
            for (int j = my_max(minx, 0.0); j <= maxx; ++j)
            {
                if (j >= SCREEN_WIDTH)
                break;
                if (pointInsideTriangle(cood(j, i, 0), pa, pb, pc))
                {
                    inside = 1;
                    float point_z = (pa.getz()+pb.getz()+pc.getz())/3;
                    if (point_z < my_z_buffer[i][j])
                    {
                        my_z_buffer[i][j] = point_z;
                        putpixel(screen, j, i, color);
                    }
                }
                else if (inside)
                    break;
            }
        }
    }
}

void triangleFill(SDL_Surface * screen, cood a, cood b, cood c, Uint32 color, Camera cam)
{
    cood pa = a.to_viewing(cam);
    cood pb = b.to_viewing(cam);
    cood pc = c.to_viewing(cam);

    bool a1 = pa.to_clip();
    bool b1 = pb.to_clip();
    bool c1 = pc.to_clip();
    bool flag = a1 && b1&& c1;

    pa.scale();
    pb.scale();
    pc.scale();

    //to centre of screen
    pa.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pb.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pc.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );

    /////////////////////////////
    //shading
    if(!flag)
    {
        float kx;
        cood light(light_x, light_y, light_z);
        cood centers(0,0,0);
        cood centroid = (a +(b+c))/3;
        cood lc = light - centers;
        cood ray = light - centroid;
        cood tri_normal = (b - a).cross(c - a);
        float k = fabs(ray.dot1(tri_normal)/(ray.magnitude()*tri_normal.magnitude()));
        if(lc.magnitude()>ray.magnitude())
        {
            kx = 0.05 + k;
            if(kx > 1)
                kx = 1;
        }
        else
        kx = 0.3 + k/(ray - lc).magnitude();
        color = intensity(kx, color);
    }
    //////////////////////////
    if(!flag)
    {
        float minx = my_min(pa.getx(), my_min(pb.getx(), pc.getx()));
        float miny = my_min(pa.gety(), my_min(pb.gety(), pc.gety()));
        float maxx = my_max(pa.getx(), my_max(pb.getx(), pc.getx()));
        float maxy = my_max(pa.gety(), my_max(pb.gety(), pc.gety()));

        for (int i = miny; i <= maxy; ++i)
        {
            if (i < 0)
                continue;
            if (i >= SCREEN_HEIGHT)
                break;
            bool inside = 0;
            for (int j = my_max(minx, 0.0); j <= maxx; ++j)
            {
                if (j >= SCREEN_WIDTH)
                break;
                if (pointInsideTriangle(cood(j, i, 0), pa, pb, pc))
                {
                    inside = 1;
                    float point_z = (pa.getz()+pb.getz()+pc.getz())/3;
                    if (point_z < my_z_buffer[i][j])
                    {
                        my_z_buffer[i][j] = point_z;
                        putpixel(screen, j, i, color);
                    }
                }
                else if (inside)
                    break;
            }
        }
    }
}

/*
void trianglefill(SDL_Surface * screen, cood a, cood b, cood c, Uint32 color, Camera cam)
{
    //shading
    float kx;
    cood light(300,1200,5000);
    cood centers(0,0,0);
    cood centroid = (a +(b+c))/3;
    cood lc = light - centers;
    cood ra = light - centroid;
    cood ray = ra/ra.magnitude();
    cood tri_normal = (b - a).cross(c - a);
    tri_normal = tri_normal/tri_normal.magnitude();
    cood k = ray.dot(tri_normal);
    if(lc.magnitude()>ra.magnitude())
    {
        kx = 0.05 + k.magnitude();
        if(kx > 1)
            kx = 1;
    }
    else
    kx = 0.3 + k.magnitude()/(ra - lc).magnitude();
    color = intensity(kx, color);
    ////////////////////////////////////
    cood vca = a.toVC(cam);
    cood vcb = b.toVC(cam);
    cood vcc = c.toVC(cam);
    cood normal = (vcb - vca).cross(vcc - vca); //obtain the triangle normal, i.e. a, b, c components of the plane
    float d = -(normal.getx() * vca.getx() + normal.gety() * vca.gety() + normal.getz() * vca.getz()); // ax + by + cz + d = 0, d = -(ax + by + cz), put point vca

    cood pa = a.to_viewing(cam);
    cood pb = b.to_viewing(cam);
    cood pc = c.to_viewing(cam);

    bool a1 = pa.to_clip();
    bool b1 = pb.to_clip();
    bool c1 = pc.to_clip();
    bool flag = a1 && b1&& c1;

    pa.scale();
    pb.scale();
    pc.scale();


    //to centre of screen
    pa.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pb.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pc.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );

    if(!flag)
    {
        float minx = my_min(pa.getx(), my_min(pb.getx(), pc.getx()));
        float miny = my_min(pa.gety(), my_min(pb.gety(), pc.gety()));
        float maxx = my_max(pa.getx(), my_max(pb.getx(), pc.getx()));
        float maxy = my_max(pa.gety(), my_max(pb.gety(), pc.gety()));

        for (int i = miny; i <= maxy; ++i)
        {
            if (i < 0)
                continue;
            if (i >= SCREEN_HEIGHT)
                break;
            bool inside = 0;
            for (int j = my_max(minx, 0.0); j <= maxx; ++j)
            {
                if (j >= SCREEN_WIDTH)
                break;
                if (pointInsideTriangle(cood(j, i, 0), pa, pb, pc))
                {
                    inside = 1;
                    float D = cam.get_z_prp() - cam.get_z_vp();
                    float xp = j - SCREEN_WIDTH / 2;
                    float yp = i - SCREEN_HEIGHT / 2;
                    float F = normal.getx() * xp + normal.gety() * yp - normal.getz() * D;
                    float point_z = ((normal.getx() * xp + normal.gety() * yp) * cam.get_z_prp() + d * D) / F;
                    if (point_z < my_z_buffer[i][j])
                    {
                        my_z_buffer[i][j] = point_z;
                        putpixel(screen, j, i, color);
                    }
                }
                else if (inside)
                    break;
            }
        }
    }

}
*/
std::vector<point> my_translate(std::vector<point> vec,float x, float y, float z)
{
    for(int i = 0; i<vec.size(); i++)
    {
        vec[i].x = (vec[i].x + x);
        vec[i].y = (vec[i].y + y);
        vec[i].z = (vec[i].z + z);
    }
    return vec;
}

inline point point::cross( point b)
{
    float rx = y * b.z - z * b.y;
    float ry = -(x * b.z - z * b.x);
    float rz = x * b.y - y * b.x;
    return point(rx, ry, rz);
}


inline void point::translate(int x0, int y0, int z0)
{
    x += x0;
    y += y0;
    z += z0;
}


point point::my_transform( Eigen::Matrix4f a)
{
    point m;
    float s;
    float x1 = a(0,0)*x + a(0,1)*y + a(0,2)*z + a(0,3)*1;
    float y1 = a(1,0)*x + a(1,1)*y + a(1,2)*z + a(1,3)*1;
    float z1 = a(2,0)*x + a(2,1)*y + a(2,2)*z + a(2,3)*1;
    s = a(3,0)*x + a(3,1)*y + a(3,2)*z + a(3,3)*1;
    m.x = ( x1 / s );
    m.y = ( y1 / s );
    m.z = ( z1 / s );
    return m;
}

point point::to_viewing(Camera cam)
{
    point n;
    point u;
    point v;

    point VPN(cam.x_vp - cam.x_prp, cam.y_vp - cam.y_prp, cam.z_vp - cam.z_prp);
    point View_up(0,1,0);
    VPN = VPN/VPN.magnitude();
    point temp1 = VPN*(VPN.dot(View_up));
    point temp2 = View_up - temp1;

    n = VPN / (-VPN.magnitude());
    v = temp2/temp2.magnitude();

    point temp = v.cross(n);
    u = temp / temp.magnitude();

    Eigen::Matrix4f R;
    Eigen::Matrix4f T;
    Eigen::Matrix4f M;

    R << u.x,  u.y,   u.z,    0,
         v.x,  v.y,   v.z,    0,
         n.x,  n.y,   n.z,    0,
         0,         0,          0,           1;

    T << 1, 0, 0, -cam.x_prp,
         0, 1, 0, -cam.y_prp,
         0, 0, 1, -cam.z_prp,
         0, 0, 0, 1;

    float s_factor_h = -1 / tan(cam.phi/2);
    float s_factor_w = 1 / tan(cam.theta/2);

    Eigen::Matrix4f Sxy;
    Sxy << s_factor_w,  0,             0,   0,
           0,           s_factor_h,    0,   0,
           0,           0,             1,   0,
           0,           0,             0,   1;

    //to align far plane to z = -1
    float s_factor_xyz = 1/cam.far_p;
    Eigen::Matrix4f Sxyz;
    Sxyz << s_factor_xyz,  0,             0,              0,
            0,             s_factor_xyz,  0,              0,
            0,             0,             s_factor_xyz,   0,
            0,             0,             0,              1;
    cam.near_p = (cam.near_p*s_factor_xyz);
    cam.far_p = 1;
    //to transfer z = k plane to z =0 where k is near/far
    float d_factor = cam.near_p;
    Eigen::Matrix4f D;
    D << 1, 0,  0,              0,
         0, 1,  0,              0,
         0, 0,  1/(d_factor-1), d_factor/(d_factor - 1),
         0, 0,  -1,             0;


    M = R * T;
    M = Sxy * M;
    M = Sxyz * M;
    M = D * M;

    return (my_transform(M));
}

point point::rotateY(float t)
{
    float nz = z * cos(t) - x * sin(t);
    float nx = z * sin(t) + x * cos(t);
    return point(nx, y, nz);
}
point point::rotateZ(float t)
{
    float nx = x * cos(t) - y * sin(t);
    float ny = x * sin(t) + y * cos(t);
    return point(nx, ny, z);
}
point point::rotateX(float t)
{
    float ny = y * cos(t) - z * sin(t);
    float nz = y * sin(t) + z * cos(t);
    return point(x, ny, nz);
}
point point::toVC( Camera cam )
{
    point n;
    point u;
    point v;

    point VPN(cam.x_vp - cam.x_prp, cam.y_vp - cam.y_prp, cam.z_vp - cam.z_prp);
    point View_up(0,1,0);
    VPN = VPN/VPN.magnitude();
    point temp1 = VPN*(VPN.dot(View_up));
    point temp2 = View_up - temp1;

    n = VPN / (-VPN.magnitude());
    v = temp2/temp2.magnitude();

    point temp = v.cross(n);
    u = temp / temp.magnitude();

    Eigen::Matrix4f R;
    Eigen::Matrix4f T;
    Eigen::Matrix4f M;

    R << u.x,  u.y,   u.z,    0,
         v.x,  v.y,   v.z,    0,
         n.x,  n.y,   n.z,    0,
         0,         0,          0,           1;

    T << 1, 0, 0, -cam.x_prp,
         0, 1, 0, -cam.y_prp,
         0, 0, 1, -cam.z_prp,
         0, 0, 0, 1;

    M = R*T;
    return(my_transform(R));
}






bool my_object::load_obj( std::string textfile )
{
    point d(0,0,0);
    property pk(0,0);
    vertex.push_back(d);
    normal.push_back(d);
    prop.push_back(pk);
    std::string path = textfile;

    FILE * file = fopen(path.c_str(), "r");
    if( file == NULL )
    {
        printf("Impossible to open the file !\n");
        return false;
    }
    while( 1 )
    {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        if ( strcmp( lineHeader, "v" ) == 0 )
        {
            point v;
            fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z );
            vertex.push_back(v);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 )
        {
            property uv;
            fscanf(file, "%f %f\n", &uv.kx, &uv.ky );
            prop.push_back(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 )
        {
            point n;
            fscanf(file, "%f %f %f\n", &n.x, &n.y, &n.z );
            normal.push_back(n);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 )
        {
            face f;
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &f.v_index[0], &f.uv[0], &f.n_index[0], &f.v_index[1], &f.uv[1], &f.n_index[1], &f.v_index[2], &f.uv[2], &f.n_index[2] );
            if (matches != 9)
            {
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            faces.push_back(f);
        }
    }
}


void my_object::my_fill(SDL_Surface*screen, face f, Uint32 color,Camera cam)
{

    point light(light_x, light_y, light_z);

    point a = vertex[f.v_index[0]];
    point b = vertex[f.v_index[1]];
    point c = vertex[f.v_index[2]];

    point pa = a.to_viewing(cam);
    point pb = b.to_viewing(cam);
    point pc = c.to_viewing(cam);

    bool a1 = pa.to_clip();
    bool b1 = pb.to_clip();
    bool c1 = pc.to_clip();
    bool flag = a1 && b1&& c1;

    pa.scale();
    pb.scale();
    pc.scale();


    //to centre of screen
    pa.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pb.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );
    pc.translate( SCREEN_WIDTH/2, SCREEN_HEIGHT, 0 );

    /////////////////////////////
    //shading
    Uint32 new_color = my_lighting(light, pa,pb,pc, 0.6, 0.8, 0.85, 200, color, cam);
    //////////////////////////
    if(!flag)
    {
        float minx = my_min(pa.x, my_min(pb.x, pc.x));
        float miny = my_min(pa.y, my_min(pb.y, pc.y));
        float maxx = my_max(pa.x, my_max(pb.x, pc.x));
        float maxy = my_max(pa.y, my_max(pb.y, pc.y));

        for (int i = miny; i <= maxy; ++i)
        {
            if (i < 0)
                continue;
            if (i >= SCREEN_HEIGHT)
                break;
            bool inside = 0;
            for (int j = my_max(minx, 0.0); j <= maxx; ++j)
            {
                if (j >= SCREEN_WIDTH)
                break;
                if (pointInsideTriangle(point(j, i, 0), pa, pb, pc))
                {
                    inside = 1;
                    float point_z = (pa.z+pb.z+pc.z)/3;
                    if (point_z < my_z_buffer[i][j])
                    {
                        my_z_buffer[i][j] = point_z;
                        putpixel(screen, j, i, new_color);
                    }
                }
                else if (inside)
                    break;
            }
        }
    }
}


void my_sort(point &a, point &b, point &c, point &na, point &nb, point &nc)
{
    if(a.y > b.y)
    {
        my_swap(a , b);
        my_swap(na , nb);
    }
    if(b.y > c.y)
    {
        my_swap(b , c);
        my_swap(nb , nc);
        if( a.y > b.y )
        {
            my_swap(a, b);
            my_swap(na, nb);
        }
    }
}

bool pointInsideTriangle( point p, point a, point b, point c)
{
    float x = (p - a).crossZ(b - a);
    float y = (p - b).crossZ(c - b);
    float z = (p - c).crossZ(a - c);
    return (x >= 0 && y >= 0 && z >= 0) || (x < 0 && y < 0 && z < 0);
}

inline void my_swap(point &a, point &b)
{
    point temp;
    temp.x = a.x;
    temp.y = a.y;
    temp.z = a.z;
    a.x = b.x;
    a.y = b.y;
    a.z = b.z;
    b.x = temp.x;
    b.y = temp.y;
    b.z = temp.z;
}

Uint32 my_lighting( point light,point a, point b, point c, float ka, float kd, float ks, float ns, Uint32 color, Camera cam )
{
        float Ia = 0.35;
        float Ib = light_intensity;
        float kx;
        point centers(0,0,0);
        point centroid = (a +(b+c))/3;
        point V(0,0,0);
        V.x = ( centroid.x - cam.get_x_prp() );
        V.y = ( centroid.y - cam.get_y_prp() );
        V.z = ( centroid.z - cam.get_z_prp() );
        point L = light - centroid;
        point H = (L + V )/(L + V).magnitude();
        float d = L.magnitude();
        point N = (b - a).cross(c - a);
        float nl = fabs(L.dot(N)/(L.magnitude()*N.magnitude()));
        float nh = fabs(N.dot(H)/(N.magnitude()*H.magnitude()));

        float attenuation = 1/(1 + .001d + .0000005*d*d);
        attenuation = my_min(1, attenuation);
        kx = ka*Ia + attenuation*Ib*kd*nl + attenuation*ks*Ib*pow(nh,ns);
        kx = my_min(1,kx);
        color = intensity(kx, color);
        return color;
}

void clearZBuffer()
{
    for (int i =  0; i < SCREEN_HEIGHT; ++i)
    {
        for (int j = 0; j < SCREEN_WIDTH; ++j)
            my_z_buffer[i][j] = 999999999.0; //infinity
    }
}
