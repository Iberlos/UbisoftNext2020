#include "stdafx.h"
#include "MyMath.h"
#include "Matrix4x4.h"

Matrix Matrix::Identity()
{
	Matrix matrix;
	matrix.SetIdentity();
	return matrix;
}

Matrix Matrix::Make(Vector2 a_translation, float a_radians, Vector2 a_scale)
{
	Matrix translation = Matrix::MakeTranslation(a_translation);
	Matrix rotation = Matrix::MakeRotation(a_radians);
	Matrix scale = Matrix::MakeScale(a_scale);
	Matrix transform = translation * rotation * scale;
	return transform;
}

Matrix Matrix::MakeTranslation(Vector2 a_translation)
{
	Matrix matrix = Identity();
	matrix.SetTranslation(a_translation);
	return matrix;
}

Matrix Matrix::MakeTranslation(float a_x, float a_y)
{
	return MakeTranslation(Vector2(a_x, a_y));
}

Matrix Matrix::MakeRotation(Rotation a_rotation)
{
	Matrix matrix = Identity();
	matrix.SetRotation(a_rotation);
	return matrix;
}

Matrix Matrix::MakeRotation(float a_radians)
{
	return MakeRotation(Rotation::Radians(a_radians));
}

Matrix Matrix::MakeScale(Vector2 a_scale)
{
	Matrix matrix = Identity();
	matrix.SetScale(a_scale);
	return matrix;
}

Matrix Matrix::MakeScale(float a_sx, float a_sy)
{
	return MakeScale(Vector2(a_sx, a_sy));
}

Matrix Matrix::Ortographic(float a_left, float a_right, float a_bottom, float a_top, float a_zNear, float a_zFar)
{
	Matrix matrix = Identity();
	matrix.m[0][0] = 2.0f / (a_right - a_left);
	matrix.m[1][1] = 2.0f / (a_top - a_bottom);
	matrix.m[2][2] = -2.0f / (a_zNear - a_zFar);
	matrix.m[3][0] = -(a_right + a_left) / (a_right - a_left);
	matrix.m[3][1] = -(a_top + a_bottom) / (a_top - a_bottom);
	matrix.m[3][2] = -(a_zFar + a_zNear) / (a_zFar - a_zNear);
	return matrix;
}

Matrix::Matrix()
{
	m[0][0] = 0;  m[1][0] = 0;  m[2][0] = 0;  m[3][0] = 0;
	m[0][1] = 0;  m[1][1] = 0;  m[2][1] = 0;  m[3][1] = 0;
	m[0][2] = 0;  m[1][2] = 0;  m[2][2] = 0;  m[3][2] = 0;
	m[0][3] = 0;  m[1][3] = 0;  m[2][3] = 0;  m[3][3] = 0;
}

Matrix::Matrix(const Matrix& a_matrix)
{
	for (int row = 0; row < MATRIX_4x4_NUM_ROWS; row++)
	{
		for (int column = 0; column < MATRIX_4x4_NUM_COLUMNS; column++)
		{
			m[row][column] = a_matrix.m[row][column];
		}
	}
}

void Matrix::SetIdentity()
{
	m[0][0] = 1;  m[1][0] = 0;  m[2][0] = 0;  m[3][0] = 0;
	m[0][1] = 0;  m[1][1] = 1;  m[2][1] = 0;  m[3][1] = 0;
	m[0][2] = 0;  m[1][2] = 0;  m[2][2] = 1;  m[3][2] = 0;
	m[0][3] = 0;  m[1][3] = 0;  m[2][3] = 0;  m[3][3] = 1;
}

void Matrix::SetTranslation(Vector2 a_translation)
{
	m[3][0] = a_translation.m_x;
	m[3][1] = a_translation.m_y;
}

void Matrix::SetTranslation(float a_x, float a_y)
{
	SetTranslation(Vector2(a_x, a_y));
}

void Matrix::SetRotation(Rotation a_rotation)
{
	Matrix rotation = Matrix::Identity();
	rotation.m[0][0] = a_rotation.GetDirection().m_x;  rotation.m[1][0] = -a_rotation.GetDirection().m_y;
	rotation.m[0][1] = a_rotation.GetDirection().m_y;  rotation.m[1][1] = a_rotation.GetDirection().m_x;
	*this = rotation * *this;
}

void Matrix::SetRotation(float a_radians)
{
	SetRotation(Rotation::Radians(a_radians));
}

void Matrix::SetScale(Vector2 a_scale)
{
	m[0][0] *= a_scale.m_x;  m[1][0] *= a_scale.m_x;  m[3][0] *= a_scale.m_x;
	m[0][1] *= a_scale.m_y;  m[1][1] *= a_scale.m_y;  m[3][1] *= a_scale.m_y;
}

void Matrix::SetScale(float a_sx, float a_sy)
{
	SetScale(Vector2(a_sx, a_sy));
}

Vector2 Matrix::GetTranslation()
{
	return Vector2(m[3][0], m[3][1]);
}

Rotation Matrix::GetRotation()
{
	return Rotation::Radians(GetRadians());
}

float Matrix::GetRadians()
{
	float radians = atan2f(m[0][1], m[1][1]);
	return radians;
}

float Matrix::GetDegrees()
{
	return MyMath::RadiansToDegrees(GetRadians());
}

Vector2 Matrix::GetScale()
{
	Vector2 scale;
	scale.m_x = Vector2(m[0][0], m[0][1]).Length();
	scale.m_y = Vector2(m[1][0], m[1][1]).Length();
	return scale;
}

Matrix Matrix::GetTransposed()
{
	Matrix matrix(*this);

	matrix.m[0][1] = m[1][0];
	matrix.m[1][0] = m[0][1];

	matrix.m[0][2] = m[2][0];
	matrix.m[2][0] = m[0][2];

	matrix.m[0][3] = m[3][0];
	matrix.m[3][0] = m[0][3];

	matrix.m[1][2] = m[2][1];
	matrix.m[2][1] = m[1][2];

	matrix.m[1][3] = m[3][1];
	matrix.m[3][1] = m[1][3];

	matrix.m[2][3] = m[3][2];
	matrix.m[3][2] = m[2][3];

	return matrix;
}

Matrix Matrix::GetInverse()
{
	//This is a complex mathematical formula called the adjugate matrix formula.
	//This math is really complex and a small mistake here could be fatal. So this part is just copied from the source material.
	//Using 3x3 matrixes would have been enough for a two dimentional space, but the 4x4 matrix definition allows for expansion into three dimentional vector transformations that might be useful in the future such as detection of collision with complex colliders using triangles and the cross product formulas that are only defined for three dimentions.

	Matrix inverse;

	inverse.m[0][0] = m[1][1] * m[2][2] * m[3][3] -
		m[1][1] * m[2][3] * m[3][2] -
		m[2][1] * m[1][2] * m[3][3] +
		m[2][1] * m[1][3] * m[3][2] +
		m[3][1] * m[1][2] * m[2][3] -
		m[3][1] * m[1][3] * m[2][2];

	inverse.m[1][0] = -m[1][0] * m[2][2] * m[3][3] +
		m[1][0] * m[2][3] * m[3][2] +
		m[2][0] * m[1][2] * m[3][3] -
		m[2][0] * m[1][3] * m[3][2] -
		m[3][0] * m[1][2] * m[2][3] +
		m[3][0] * m[1][3] * m[2][2];

	inverse.m[2][0] = m[1][0] * m[2][1] * m[3][3] -
		m[1][0] * m[2][3] * m[3][1] -
		m[2][0] * m[1][1] * m[3][3] +
		m[2][0] * m[1][3] * m[3][1] +
		m[3][0] * m[1][1] * m[2][3] -
		m[3][0] * m[1][3] * m[2][1];

	inverse.m[3][0] = -m[1][0] * m[2][1] * m[3][2] +
		m[1][0] * m[2][2] * m[3][1] +
		m[2][0] * m[1][1] * m[3][2] -
		m[2][0] * m[1][2] * m[3][1] -
		m[3][0] * m[1][1] * m[2][2] +
		m[3][0] * m[1][2] * m[2][1];

	inverse.m[0][1] = -m[0][1] * m[2][2] * m[3][3] +
		m[0][1] * m[2][3] * m[3][2] +
		m[2][1] * m[0][2] * m[3][3] -
		m[2][1] * m[0][3] * m[3][2] -
		m[3][1] * m[0][2] * m[2][3] +
		m[3][1] * m[0][3] * m[2][2];

	inverse.m[1][1] = m[0][0] * m[2][2] * m[3][3] -
		m[0][0] * m[2][3] * m[3][2] -
		m[2][0] * m[0][2] * m[3][3] +
		m[2][0] * m[0][3] * m[3][2] +
		m[3][0] * m[0][2] * m[2][3] -
		m[3][0] * m[0][3] * m[2][2];

	inverse.m[2][1] = -m[0][0] * m[2][1] * m[3][3] +
		m[0][0] * m[2][3] * m[3][1] +
		m[2][0] * m[0][1] * m[3][3] -
		m[2][0] * m[0][3] * m[3][1] -
		m[3][0] * m[0][1] * m[2][3] +
		m[3][0] * m[0][3] * m[2][1];

	inverse.m[3][1] = m[0][0] * m[2][1] * m[3][2] -
		m[0][0] * m[2][2] * m[3][1] -
		m[2][0] * m[0][1] * m[3][2] +
		m[2][0] * m[0][2] * m[3][1] +
		m[3][0] * m[0][1] * m[2][2] -
		m[3][0] * m[0][2] * m[2][1];

	inverse.m[0][2] = m[0][1] * m[1][2] * m[3][3] -
		m[0][1] * m[1][3] * m[3][2] -
		m[1][1] * m[0][2] * m[3][3] +
		m[1][1] * m[0][3] * m[3][2] +
		m[3][1] * m[0][2] * m[1][3] -
		m[3][1] * m[0][3] * m[1][2];

	inverse.m[1][2] = -m[0][0] * m[1][2] * m[3][3] +
		m[0][0] * m[1][3] * m[3][2] +
		m[1][0] * m[0][2] * m[3][3] -
		m[1][0] * m[0][3] * m[3][2] -
		m[3][0] * m[0][2] * m[1][3] +
		m[3][0] * m[0][3] * m[1][2];

	inverse.m[2][2] = m[0][0] * m[1][1] * m[3][3] -
		m[0][0] * m[1][3] * m[3][1] -
		m[1][0] * m[0][1] * m[3][3] +
		m[1][0] * m[0][3] * m[3][1] +
		m[3][0] * m[0][1] * m[1][3] -
		m[3][0] * m[0][3] * m[1][1];

	inverse.m[3][2] = -m[0][0] * m[1][1] * m[3][2] +
		m[0][0] * m[1][2] * m[3][1] +
		m[1][0] * m[0][1] * m[3][2] -
		m[1][0] * m[0][2] * m[3][1] -
		m[3][0] * m[0][1] * m[1][2] +
		m[3][0] * m[0][2] * m[1][1];

	inverse.m[0][3] = -m[0][1] * m[1][2] * m[2][3] +
		m[0][1] * m[1][3] * m[2][2] +
		m[1][1] * m[0][2] * m[2][3] -
		m[1][1] * m[0][3] * m[2][2] -
		m[2][1] * m[0][2] * m[1][3] +
		m[2][1] * m[0][3] * m[1][2];

	inverse.m[1][3] = m[0][0] * m[1][2] * m[2][3] -
		m[0][0] * m[1][3] * m[2][2] -
		m[1][0] * m[0][2] * m[2][3] +
		m[1][0] * m[0][3] * m[2][2] +
		m[2][0] * m[0][2] * m[1][3] -
		m[2][0] * m[0][3] * m[1][2];

	inverse.m[2][3] = -m[0][0] * m[1][1] * m[2][3] +
		m[0][0] * m[1][3] * m[2][1] +
		m[1][0] * m[0][1] * m[2][3] -
		m[1][0] * m[0][3] * m[2][1] -
		m[2][0] * m[0][1] * m[1][3] +
		m[2][0] * m[0][3] * m[1][1];

	inverse.m[3][3] = m[0][0] * m[1][1] * m[2][2] -
		m[0][0] * m[1][2] * m[2][1] -
		m[1][0] * m[0][1] * m[2][2] +
		m[1][0] * m[0][2] * m[2][1] +
		m[2][0] * m[0][1] * m[1][2] -
		m[2][0] * m[0][2] * m[1][1];

	float determinant = m[0][0] * inverse.m[0][0] + m[0][1] * inverse.m[1][0] + m[0][2] * inverse.m[2][0] + m[0][3] * inverse.m[3][0];

	if (determinant == 0)
	{
		return Matrix();
	}

	determinant = 1.0f / determinant;

	for (int i = 0; i < MATRIX_4x4_NUM_ROWS; i++)
		for (int j = 0; j < MATRIX_4x4_NUM_COLUMNS; j++)
			inverse.m[i][j] *= determinant;

	return inverse;
}

Vector2 Matrix::operator*(const Vector2 a_vector2) const
{
	float x = m[0][0] * a_vector2.m_x + m[1][0] * a_vector2.m_y + 0.0f + m[3][0] * 1.0f;
	float y = m[0][1] * a_vector2.m_x + m[1][1] * a_vector2.m_y + 0.0f + m[3][1] * 1.0f;
	float z = m[0][2] * a_vector2.m_x + m[1][2] * a_vector2.m_y + 0.0f + m[3][2] * 1.0f;
	float w = m[0][3] * a_vector2.m_x + m[1][3] * a_vector2.m_y + 0.0f + m[3][3] * 1.0f;

	if (w == 0.0f)
	{
		return Vector2(x, y);
	}

	return Vector2(x / w, y / w);
}

Matrix Matrix::operator*(const Matrix a_matrix) const
{
	Matrix matrix;

	matrix.m[0][0] = m[0][0] * a_matrix.m[0][0] + m[1][0] * a_matrix.m[0][1] + m[2][0] * a_matrix.m[0][2] + m[3][0] * a_matrix.m[0][3];
	matrix.m[0][1] = m[0][1] * a_matrix.m[0][0] + m[1][1] * a_matrix.m[0][1] + m[2][1] * a_matrix.m[0][2] + m[3][1] * a_matrix.m[0][3];
	matrix.m[0][2] = m[0][2] * a_matrix.m[0][0] + m[1][2] * a_matrix.m[0][1] + m[2][2] * a_matrix.m[0][2] + m[3][2] * a_matrix.m[0][3];
	matrix.m[0][3] = m[0][3] * a_matrix.m[0][0] + m[1][3] * a_matrix.m[0][1] + m[2][3] * a_matrix.m[0][2] + m[3][3] * a_matrix.m[0][3];
	matrix.m[1][0] = m[0][0] * a_matrix.m[1][0] + m[1][0] * a_matrix.m[1][1] + m[2][0] * a_matrix.m[1][2] + m[3][0] * a_matrix.m[1][3];
	matrix.m[1][1] = m[0][1] * a_matrix.m[1][0] + m[1][1] * a_matrix.m[1][1] + m[2][1] * a_matrix.m[1][2] + m[3][1] * a_matrix.m[1][3];
	matrix.m[1][2] = m[0][2] * a_matrix.m[1][0] + m[1][2] * a_matrix.m[1][1] + m[2][2] * a_matrix.m[1][2] + m[3][2] * a_matrix.m[1][3];
	matrix.m[1][3] = m[0][3] * a_matrix.m[1][0] + m[1][3] * a_matrix.m[1][1] + m[2][3] * a_matrix.m[1][2] + m[3][3] * a_matrix.m[1][3];
	matrix.m[2][0] = m[0][0] * a_matrix.m[2][0] + m[1][0] * a_matrix.m[2][1] + m[2][0] * a_matrix.m[2][2] + m[3][0] * a_matrix.m[2][3];
	matrix.m[2][1] = m[0][1] * a_matrix.m[2][0] + m[1][1] * a_matrix.m[2][1] + m[2][1] * a_matrix.m[2][2] + m[3][1] * a_matrix.m[2][3];
	matrix.m[2][2] = m[0][2] * a_matrix.m[2][0] + m[1][2] * a_matrix.m[2][1] + m[2][2] * a_matrix.m[2][2] + m[3][2] * a_matrix.m[2][3];
	matrix.m[2][3] = m[0][3] * a_matrix.m[2][0] + m[1][3] * a_matrix.m[2][1] + m[2][3] * a_matrix.m[2][2] + m[3][3] * a_matrix.m[2][3];
	matrix.m[3][0] = m[0][0] * a_matrix.m[3][0] + m[1][0] * a_matrix.m[3][1] + m[2][0] * a_matrix.m[3][2] + m[3][0] * a_matrix.m[3][3];
	matrix.m[3][1] = m[0][1] * a_matrix.m[3][0] + m[1][1] * a_matrix.m[3][1] + m[2][1] * a_matrix.m[3][2] + m[3][1] * a_matrix.m[3][3];
	matrix.m[3][2] = m[0][2] * a_matrix.m[3][0] + m[1][2] * a_matrix.m[3][1] + m[2][2] * a_matrix.m[3][2] + m[3][2] * a_matrix.m[3][3];
	matrix.m[3][3] = m[0][3] * a_matrix.m[3][0] + m[1][3] * a_matrix.m[3][1] + m[2][3] * a_matrix.m[3][2] + m[3][3] * a_matrix.m[3][3];

	return matrix;
}

Matrix Matrix::operator=(const Matrix a_matrix) const
{
	return Matrix(a_matrix);
}
