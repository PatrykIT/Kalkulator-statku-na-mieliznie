#pragma once
#include "Interpolacja.h"

#include <vector>

std::vector<double> xData_dla_T;
std::vector<double> xData_dla_D;

std::vector<double> yData_dla_D;
std::vector<double> yData_dla_MJ;
std::vector<double> yData_dla_Fw;
std::vector<double> yData_dla_XF;
std::vector<double> yData_dla_KM;

// Returns interpolated value at x from parallel arrays ( xData, yData )
//   Assumes that xData has at least two elements, is sorted and is strictly monotonic increasing
//   boolean argument extrapolate determines behaviour beyond ends of array (if needed)

double interpolate(std::vector<double> &xData, std::vector<double> &yData, double x, bool extrapolate)
{
    int size = xData.size();

    int i = 0; // find left end of interval for interpolation
    if (x >= xData[size - 2]) // special case: beyond right end
    {
        i = size - 2;
    }
    else
    {
        while (x > xData[i + 1]) i++;
    }
    double xL = xData[i], yL = yData[i], xR = xData[i + 1], yR = yData[i + 1]; // points on either side (unless beyond ends)

    if (extrapolate == false) // if beyond ends of array and not extrapolating
    {
        if (x < xL)
        {
            yR = yL;
        }
        if (x > xR)
        {
            yL = yR;
        }
    }

    double dydx = (yR - yL) / (xR - xL); // gradient

    return yL + dydx * (x - xL); // linear interpolation
}

/*
Przyklad uzycia:

std::vector<double> xData = { 1, 3 };
std::vector<double> yData = { 100, 150 };

double y = interpolate(xData, yData, 2, true);
std::cout << y << std::endl;

*/
