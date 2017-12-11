#pragma once
#include "Ball.h"
#define BOX 20
using namespace std;

class BallsBox
{
public:
	void init(vector<point>, vector<point>, vector<double>, vector<double>, double);
	void timeStep();
	vector<Ball> getBalls();
private:
	void handleBoundaryBounce(Ball &, bool);
	void handleBallsBounce(Ball &, Ball &);
	vector<Ball> balls;
	double time;
};

