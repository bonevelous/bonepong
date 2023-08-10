/****************************************************************************
    This file is a part of SDL Pong.
    
    Copyright (C) 2021  Matt Gobbi

    SDL Pong is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SDL Pong is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SDL Pong.  If not, see <https://www.gnu.org/licenses/>.
*****************************************************************************/
#include <math.h>
#include <time.h>

//Begin with universal constants.
const double M_EULERCONST = exp(1.0);
const double S_LIGHT = 299792458.0;
const double G_EARTH = 9.81;

#ifndef BONEMATH_H
#define BONEMATH_H

//Calculus
#ifndef BONE_CALCULUS
#define BONE_CALCULUS

//The calculus section starts with information for position, velocity, and acceleration, because physics is probably the primary use of calculus for me.
//If an object's position at any time t is given by s(t),
//Position = s(t)
//Velocity = v(t) = s'(t)
//Acceleration = a(t) = v'(t) = s''(t)

//A few more concepts I will need to have at least a baseline understanding of in order to program this:
//Speed is distance divided by time.
//Velocity is displacement divided by time.
//For object position a at time a, and position b at time b:
//Average Velocity = (s(b) - s(a) / B - A)

//Finally, you need to understand derivatives.
//The derivative of X to the power of N is (N * X) to the power of (N - 1).

//NOTE: WHEN FINISHED, MOVE ALL OF THIS TO THE BONEMATHLIBRARY!

//As a note, if the object is moving upwards or to the right, this should return positive.
//Otherwise, it should return negative.
double vFromP(double nextPos, double dTime);

//As a note, if the object is moving upwards or to the right, this should return positive.
//Otherwise, it should return negative.
double aFromP(double nextPos, double dTime);

double nthRoot(double input, double power);

double vFromA(double acceleration, double timeInc);

double pFromV(double velocity, double timeInc);

double findPos(double velocity, double acceleration, double timeInc);

double pFromA(double acceleration, double timeInc);

double powDer(double base, double power);

double sciNot(double power);

double bounce(double gravity, double timeInt, double bounciness);
#endif

//Geometry
#ifndef BONE_GEOMETRY
#define BONE_GEOMETRY
//Taxicab geometry.
double taxicabDistance(double getX1,double getX2, double getY1,double getY2);

double taxicabRadius(double getAngle);

typedef struct
{
    double sideA;
    double sideB;
    double sideC;
} boneTriangle;

//Use this if you only have one right triangle.
double rightTri(double base, double height);

//Calculates the perimeter of a triangle.
double trianglePerimeter(double sideA, double sideB, double sideC);

//This formula will calculate the area of a given triangle through the heron formula, regardless of whether it's a right triangle or not.
double triangleAreaHeron(double sideA, double sideB, double sideC);

//Polygon Heron Formula addition.
//double polygonAreaHeron(boneTriangle getTri[]);

//Calculates any elipse area. For a circle, the x and y axis should be identical.
double areaElipse(double xAxis, double yAxis);

double surfAreaElipsoid(double xAxis, double yAxis, double zAxis);

double volumeElipsoid(double xAxis, double yAxis, double zAxis);

double volumeTetragedron(double baseA, double baseB, double baseC, double height);

//Not sure how useful this function will be, but here it is nonetheless. :/
int getCoord(double getX, double getY);
#endif

//Trigonometry
#ifndef BONE_TRIGONOMETRY
#define BONE_TRIGONOMETRY

#include <math.h>

double euclideanDistance(double getP, double getQ);

double polarDistance(double getP, double getQ, double getAngQ, double getAngP);

double pythagoreanTheorem(double getA, double getB);

double sohAng(double getOppo, double getHypo);

double cahAng(double getAdj, double getHypo);

double toaAng(double getOppo, double getAdj);

double degToRad(double deg);

double radToDeg(double rad);

double polarXCoord(double getXOffset, double radius, double angleInDeg);

double polarYCoord(double getYOffset, double radius, double angleInDeg);

//Trig identities.
double sec(double x);

double csc(double x);

double cot(double x);

//Inverse trig identities, AKA arcus functions.
double asec(double x);

double acsc(double x);

double acot(double x);

double sinWave(double amplitude, double period, double trigTime, double phase);

double cosWave(double amplitude, double period, double trigTime, double phase);

double tanGraph(double amplitude, double period, double trigTime, double phase);

double secGraph(double amplitude, double period, double trigTime, double phase);

double cscGraph(double amplitude, double period, double trigTime, double phase);

double cotGraph(double amplitude, double period, double trigTime, double phase);

//Graphing arcus functions. Note that all of these are graphs, because none of them are waves.
double asinGraph(double amplitude, double period, double trigTime, double phase);

double acosGraph(double amplitude, double period, double trigTime, double phase);

double atanGraph(double amplitude, double period, double trigTime, double phase);

double asecGraph(double amplitude, double period, double trigTime, double phase);

double acscGraph(double amplitude, double period, double trigTime, double phase);

double acotGraph(double amplitude, double period, double trigTime, double phase);
#endif

#endif
