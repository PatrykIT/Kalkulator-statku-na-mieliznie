#ifndef INTERPOLACJA_H
#define INTERPOLACJA_H

#pragma once

#include <vector>

extern std::vector<double> xData_dla_T;
extern std::vector<double> xData_dla_D;


extern std::vector<double> yData_dla_D;
extern std::vector<double> yData_dla_MJ;
extern std::vector<double> yData_dla_Fw;
extern std::vector<double> yData_dla_XF;
extern std::vector<double> yData_dla_KM;



// Returns interpolated value at x from parallel arrays ( xData, yData )
//   Assumes that xData has at least two elements, is sorted and is strictly monotonic increasing
//   boolean argument extrapolate determines behaviour beyond ends of array (if needed)


double interpolate(std::vector<double> &xData, std::vector<double> &yData, double x, bool extrapolate);

/*
Przyklad uzycia:

std::vector<double> xData = { 1, 3 };
std::vector<double> yData = { 100, 150 };

double y = interpolate(xData, yData, 2, true);
std::cout << y << std::endl;

*/

#endif // INTERPOLACJA_H
