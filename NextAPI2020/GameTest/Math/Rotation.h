#pragma once


struct Vector2;

class Rotation
{
public:
	Rotation();
	Rotation(const Rotation& a_rotation);

	static Rotation Degrees(float a_degrees);
	static Rotation Radians(float a_radians);
	static Rotation Direction(const Vector2& a_direction);

	void SetDegrees(float a_degrees);
	void SetRadians(float a_radians);

	float GetDegrees() const;
	float GetRadians() const;

	void Rotate(float a_increment, bool a_Bdegrees = false);

	void SetDirection(const Vector2& a_direction);
	Vector2 GetDirection() const;

private:
	float m_radians;
};
