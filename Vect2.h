#pragma once
class Vect2
{
public:

	float x;
	float y;

	Vect2()
		:x(0.0f)
		,y(0.0f)
	{}

	explicit Vect2(float X, float Y)
		:x(X)
		,y(Y)
	{}


	void Set(float X, float Y)
	{
		x = X;
		y = Y;
	}



};