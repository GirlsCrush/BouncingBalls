#include "Ball.h"
using namespace std;

Ball::Ball(point _center, point _speed, double _radius, double _mass)
{
	center = _center;
	radius = _radius;
	speed = _speed;
	mass = _mass;
}

Ball::~Ball()
{
}

double Ball::getRadius()
{
	return radius;
}

double Ball::getMass()
{
	return mass;
}

point Ball::getNextCenter(double &time)
{
	return point(center.first + speed.first * time, center.second + speed.second * time);
}

void Ball::operator()(double &time)
{
	center.first += speed.first * time;
	center.second += speed.second * time;
}
