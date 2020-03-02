#pragma once

class Rotation;

struct Vector2
{
	Vector2(float a_x, float a_y);
	Vector2(const Vector2& a_vector2);
	Vector2();

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 WindowDimentions;

	////Static Functionality (for convienience)
	static const float Length(const Vector2& a_vector2, bool a_Bsquared = false) { return a_vector2.Length(a_Bsquared); }
	static const Vector2 Normalized(const Vector2& a_vector2) { return a_vector2.Normalized(); }
	static const float Distance(const Vector2& a_from, const Vector2& a_to, bool a_Bsquared = false) { return a_from.Distance(a_to, a_Bsquared); }
	static const float Dot(const Vector2& a_vectorA, const Vector2& a_vectorB) { return a_vectorA.Dot(a_vectorB); }
	static const Vector2 GetPerpendicularVector(const Vector2& a_vector2, bool a_BcounterClockwise = false) { return a_vector2.GetPerpendicularVector(a_BcounterClockwise); }

	//Object Functionality
	Rotation Angle(const Vector2& a_to = Vector2(0.0f, 0.0f)) const;
	float Length(const bool a_Bsquared = false) const;
	void Normalize();
	Vector2 Normalized() const;
	float Distance(const Vector2& a_to, const bool a_Bsquared = false) const;
	float Dot(const Vector2& a_vector2) const;
	Vector2 GetPerpendicularVector(const bool a_BcounterClockwise = false) const;

	//Operators
	Vector2 operator+(const Vector2& vector2) const;
	void operator+=(const Vector2& vector2);

	Vector2 operator-(const Vector2& vector2) const;
	void operator-=(const Vector2& vector2);

	Vector2 operator*(const Vector2& vector2) const;
	void operator*=(const Vector2& vector2);

	Vector2 operator*(const float& vector2) const;
	void operator*=(const float& vector2);

	Vector2 operator/(const Vector2& vector2) const;
	void operator/=(const Vector2& vector2);

	Vector2 operator/(const float& vector2) const;
	void operator/=(const float& vector2);

	Vector2 operator-();

	bool operator==(const Vector2& vector2) const;
	bool operator!=(const Vector2& vector2) const;

	bool operator<(const Vector2& vector2) const;
	bool operator<=(const Vector2& vector2) const;

	bool operator>(const Vector2& vector2) const;
	bool operator>=(const Vector2& vector2) const;

	//Member Varibales
	float m_x;
	float m_y;
};

//Vector2 operator* (float a_scale, const Vector2& a_vector2) const;