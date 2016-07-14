#ifndef MYCAMERA_H
#define MYCAMERA_H

#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "MyFunctions.h"



Eigen::Matrix4f RotateX();
Eigen::Matrix4f RotateY();
Eigen::Matrix4f RotateZ();

Eigen::Matrix4f RotateTotal();
    //Matrix4f wc_to_vc();

std::vector<cood> to_perspective(cood prp, cood vp, std::vector<cood> v);
std::vector<cood> to_perspective1(cood prp, cood vp, std::vector<cood> v);
//Eigen::Matrix4f get_view_port(cood, cood);
cood to_perspective(cood, cood);

# endif




