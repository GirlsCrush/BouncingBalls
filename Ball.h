#pragma once
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

#define point pair<double, double>
#define points vector<point>

class Ball
{
public:
	Ball(point, point, double, double);
	~Ball();
	point getNextCenter(double &);
	void operator()(double &);
	double getRadius();
	double getMass(); 
	point center;
	point speed;
private:
	double radius;
	double mass;
};

