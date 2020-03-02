#pragma once


#define MATRIX_4x4_NUM_ROWS 4
#define MATRIX_4x4_NUM_COLUMNS 4
struct Vector2;
class Rotation;

struct Matrix
{
	static Matrix Identity();

	static Matrix Make(Vector2 a_translation, float a_radians, Vector2 a_scale = Vector2::One);

	static Matrix MakeTranslation(Vector2 a_translation);
	static Matrix MakeTranslation(float a_x, float a_y);

	static Matrix MakeRotation(Rotation a_rotation);
	static Matrix MakeRotation(float a_radians);

	static Matrix MakeScale(Vector2 a_scale);
	static Matrix MakeScale(float a_sx, float a_sy);

	static Matrix Ortographic(float a_left, float a_right, float a_bottom, float a_top, float a_zNear, float a_zFar);

	Matrix();

	Matrix(const Matrix& a_matrix);

	void SetIdentity();

	void SetTranslation(Vector2 a_translation);
	void SetTranslation(float a_x, float a_y);

	void SetRotation(Rotation a_rotation);
	void SetRotation(float a_radians);

	void SetScale(Vector2 a_scale);
	void SetScale(float a_sx, float a_sy);

	Vector2 GetTranslation();

	Rotation GetRotation();
	float GetRadians();
	float GetDegrees();

	Vector2 GetScale();

	Matrix GetTransposed();

	Matrix GetInverse();

	Vector2 operator* (const Vector2 a_vector2) const;

	Matrix operator* (const Matrix a_matrix) const;

	Matrix operator= (const Matrix a_matrix) const;

	float m[MATRIX_4x4_NUM_ROWS][MATRIX_4x4_NUM_COLUMNS];
};
