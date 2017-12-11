#include "BallsBox.h"
#define IS_SIDE true
#define IS_NOT_SIDE false

void BallsBox::init(vector<point> _center, vector<point> _speed, vector<double> _radius, vector<double> _mass, double _timeInterval)
{
	time = _timeInterval;
	for (int i = 0; i < _center.size(); i++)
	{
		balls.emplace_back(_center[i], _speed[i], _radius[i], _mass[i]);
	}
}

void BallsBox::timeStep()
{
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i](time);
	}

	for (int i = 0; i < balls.size(); i++)
	{
		if (abs(BOX - balls[i].center.first) <= balls[i].getRadius() || abs(-BOX - balls[i].center.first) <= balls[i].getRadius() || abs(BOX - balls[i].center.second) <= balls[i].getRadius() || abs(-BOX - balls[i].center.second) <= balls[i].getRadius())
		{
			if (abs(BOX - balls[i].center.first) < balls[i].getRadius() || abs(-BOX - balls[i].center.first) < balls[i].getRadius())  handleBoundaryBounce(balls[i], IS_SIDE);
			else handleBoundaryBounce(balls[i], IS_NOT_SIDE);
			break;
		}
		else
			for (int j = i + 1; j < balls.size(); j++)
			{
				if (sqrt((balls[i].center.first - balls[j].center.first) * (balls[i].center.first - balls[j].center.first) + (balls[i].center.second - balls[j].center.second) * (balls[i].center.second - balls[j].center.second)) <= balls[i].getRadius() + balls[j].getRadius())
				{
					handleBallsBounce(balls[i], balls[j]);
					break;
				}
			}
	}
}

vector<Ball> BallsBox::getBalls()
{
	return balls;
}

void BallsBox::handleBoundaryBounce(Ball &ball, bool side)
{
	if (side == IS_SIDE)
		ball.speed.first *= -1;
	else
		ball.speed.second *= -1;
}

void BallsBox::handleBallsBounce(Ball &ball1, Ball &ball2)
{
	double m1 = ball1.getMass();
	double m2 = ball2.getMass();
	point v1 = ball1.speed;
	point v2 = ball2.speed;
	point N = point((ball1.center.first - ball2.center.first) /
		sqrt((ball1.center.first - ball2.center.first) * (ball1.center.first - ball2.center.first) +
		(ball1.center.first - ball2.center.second) * (ball1.center.first - ball2.center.second)),
			(ball1.center.second - ball2.center.second) /
		sqrt((ball1.center.first - ball2.center.first) * (ball1.center.first - ball2.center.first) +
		(ball1.center.first - ball2.center.second) * (ball1.center.first - ball2.center.second)));

	double tmp1 = (ball1.center.first + ball2.center.first) / 2;
	double tmp2 = (ball1.center.first - ball2.center.first) / (ball2.center.second - ball1.center.second) * (ball1.center.first + ball2.center.first) / 2;

	point Q = point(tmp1 / sqrt(tmp1 * tmp1 + tmp2 * tmp2), 
		tmp2 / sqrt(tmp1 * tmp1 + tmp2 * tmp2));
	double b1 = (ball1.speed.second - ball1.speed.first * N.second / N.first) / (Q.second - N.second * Q.first / N.first);
	double a1 = (ball1.speed.first - b1 * Q.first) / N.first;
	double b2 = (ball2.speed.second - ball2.speed.first * N.second / N.first) / (Q.second - N.second * Q.first / N.first);
	double a2 = (ball2.speed.first - b2 * Q.first) / N.first;
	double k = (2 * (a1 - a2) / (m1 + m2));
	ball1.speed.first -= k * m2 * N.first;
	ball1.speed.second -= k * m2 * N.second;
	ball2.speed.first += k * m1 * N.first;
	ball2.speed.second += k * m1 * N.second;
	/*double m1 = ball1.getMass();
	double m2 = ball2.getMass();
	double v1 = ball1.speed;
	double v2 = ball2.speed;
	double a = m1 + m2;
	double b = -2 * (v1 + m2 / m1 * v2) * m1;
	double c = m1 * (v1 + m2 / m1 * v2) * (v1 + m2 / m1 * v2) - m1 * v1 * v1 - m2 * v2 * v2;
	double _v2 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	double _v1 = (m1 * v1 + m2 * v2 - m2 * _v2) / m1;
	ball1.speed = _v1;
	ball2.speed = _v2;
	point _vector((ball1.center.first + ball2.center.first) / 2, (ball1.center.first - ball2.center.first) / (ball2.center.second - ball1.center.second) * (ball1.center.first + ball2.center.first) / 2);
	ball1.vector = point(
		(_vector.first - ball1.vector.first) / 
		sqrt((_vector.first - ball1.vector.first) * (_vector.first - ball1.vector.first) + 
		(_vector.second - ball1.vector.second) * (_vector.second - ball1.vector.second)), 
		(_vector.second - ball1.vector.second) / 
		sqrt((_vector.first - ball1.vector.first) * (_vector.first - ball1.vector.first) +
		(_vector.second - ball1.vector.second) * (_vector.second - ball1.vector.second)));
	ball2.vector = point(
		(_vector.first - ball2.vector.first) /
		sqrt((_vector.first - ball2.vector.first) * (_vector.first - ball2.vector.first) +
		(_vector.second - ball2.vector.second) * (_vector.second - ball2.vector.second)),
			(_vector.second - ball2.vector.second) /
		sqrt((_vector.first - ball2.vector.first) * (_vector.first - ball2.vector.first) +
		(_vector.second - ball2.vector.second) * (_vector.second - ball2.vector.second)));*/
}
