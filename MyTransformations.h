#ifndef MY_TRANSFORMATIONS_H
#define MY_TRANSFORMATIONS_H

#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include "MyFunctions.h"

Eigen::Matrix4f Translate( cood );
Eigen::Matrix4f Rotate_Y_3D( cood c1 );

Eigen::Matrix4f Rotate_Ball( float t );
std::vector<cood> Transform( Eigen::Matrix4f  a, std::vector<cood> v);

std::vector<cood> ball_path( cood pa );
std::vector<cood> my_path( cood pa );

#endif
