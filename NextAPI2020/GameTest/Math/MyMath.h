#pragma once
#include "Vector2.h"
#include "Rotation.h"
#include "Random.h"
#include "Matrix4x4.h"


#define M_PI 3.14159265359f
#define DtoR_CONVERTER 0.01745329251f
#define RtoD_CONVERTER 57.29577795131f


struct MyMath
{
	static float DegreesToRadians(float a_degrees);
	static float RadiansToDegrees(float a_radians);

	static float Clamp(float a_value, float a_min, float a_max);
	static Vector2 Clamp(const Vector2& a_value, const Vector2& a_min, const Vector2& a_max);

	static int RandomInt(int a_min, int a_max);

	static float RandomFloat();
	static float RandomFloat(float a_min, float a_max);

	static bool IsClose(float a_value, float a_target, float a_resolution);
	static bool IsClose(const Vector2& a_value, const Vector2& a_target, const Vector2& a_resolution);
	static bool IsClose(const Vector2& a_value, const Vector2& a_target, float a_radius);

	static Vector2 CalculateOrbit(const Vector2& pivot, Rotation a_angle, float a_radius);

private:
	static Random s_random;
};