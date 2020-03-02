#include "stdafx.h"
#include "MyMath.h"


Random MyMath::s_random = Random();

float MyMath::DegreesToRadians(float a_degrees)
{
	return a_degrees * DtoR_CONVERTER;
}

float MyMath::RadiansToDegrees(float a_radians)
{
	return a_radians * RtoD_CONVERTER;
}

float MyMath::Clamp(float a_value, float a_min, float a_max)
{
	if (a_value < a_min)
	{
		return a_min;
	}

	if (a_value > a_max)
	{
		return a_max;
	}

	return a_value;
}

Vector2 MyMath::Clamp(const Vector2& a_point, const Vector2& a_lowerLeftCorner, const Vector2& a_upperRightCorner) //should basically detect if a point falls within a rectangle or basically clamp a pointo the constrainst of a rectangle
{
	if (a_point < a_lowerLeftCorner)
	{
		return a_lowerLeftCorner;
	}

	if (a_point > a_upperRightCorner)
	{
		return a_upperRightCorner;
	}

	return a_point;
}

int MyMath::RandomInt(int a_min, int a_max)
{
	return s_random.RandomInt(a_min, a_max);
}

float MyMath::RandomFloat()
{
	return s_random.RandomFloat();
}

float MyMath::RandomFloat(float a_min, float a_max)
{
	return s_random.RandomFloat(a_min, a_max);
}

bool MyMath::IsClose(float a_value, float a_target, float a_resolution)
{
	if (a_value > a_target - a_resolution && a_value < a_target + a_resolution)
	{
		return true;
	}
	return false;
}

bool MyMath::IsClose(const Vector2& a_value, const Vector2& a_target, const Vector2& a_resolution)
{
	if (a_value == MyMath::Clamp(a_value, a_target - a_resolution, a_target + a_resolution))
	{
		return true;
	}
	return false;
}

bool MyMath::IsClose(const Vector2& a_value, const Vector2& a_target, float a_radius)
{
	if (Vector2::Distance(a_value, a_target, true) < (a_radius * a_radius))
	{
		return true;
	}
	return false;
}

Vector2 MyMath::CalculateOrbit(const Vector2& pivot, Rotation a_angle, float a_radius)
{
	float radians = a_angle.GetRadians();
	Vector2 returnValue = pivot;
	returnValue.m_x += cosf(radians) * a_radius;
	returnValue.m_y += sinf(radians) * a_radius;
	return returnValue;
}


