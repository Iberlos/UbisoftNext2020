#include "stdafx.h"
#include "Transform.h"
#include "../Math/MyMath.h"

Transform::Transform() :
	m_parent(nullptr),
	m_transform(),
	m_position(Vector2(0, 0)),
	m_rotation(),
	m_scale(Vector2(1, 1)),
	m_bTransformMatrixStale(true)
{
}

Transform::Transform(const Transform& a_transform) :
	m_parent(a_transform.m_parent),
	m_transform(a_transform.m_transform),
	m_position(a_transform.m_position),
	m_rotation(a_transform.m_rotation),
	m_scale(a_transform.m_scale),
	m_bTransformMatrixStale(true)
{
}

Transform::~Transform()
{
}

Matrix Transform::GetTransformMatrix()
{
	if (m_bTransformMatrixStale == true)
	{
		Matrix translationMatrix = Matrix::MakeTranslation(m_position);
		Matrix rotationMatrix = Matrix::MakeRotation(m_rotation);
		Matrix scaleMatrix = Matrix::MakeScale(m_scale);

		m_transform = translationMatrix * rotationMatrix * scaleMatrix;
		m_bTransformMatrixStale = false;
	}

	if (m_parent != nullptr)
	{
		return m_parent->GetTransformMatrix() * m_transform;
	}

	return m_transform;
}

Vector2 Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetPosition(Vector2 a_position)
{
	m_position = a_position;
	m_bTransformMatrixStale = true;
}

Rotation Transform::GetRotation() const
{
	return m_rotation;
}

float Transform::GetDegrees() const
{
	return m_rotation.GetDegrees();
}

void Transform::SetDegrees(float a_degrees)
{
	m_rotation.SetDegrees(a_degrees);
	m_bTransformMatrixStale = true;
}

float Transform::GetRadians() const
{
	return m_rotation.GetRadians();
}

void Transform::SetRadians(float a_radians)
{
	m_rotation.SetRadians(a_radians);
	m_bTransformMatrixStale = true;
}

Vector2 Transform::GetDirection() const
{
	return m_rotation.GetDirection();
}

void Transform::SetDirection(Vector2 a_direction)
{
	m_rotation.SetDirection(a_direction);
	m_bTransformMatrixStale = true;
}

Vector2 Transform::GetScale() const
{
	return m_scale;
}

void Transform::SetScale(Vector2 a_scale)
{
	m_scale = a_scale;
	m_bTransformMatrixStale = true;
}

Transform* Transform::GetParent() const
{
	return m_parent;
}

void Transform::Translate(const Vector2& a_offset)
{
	m_position += a_offset;
	m_bTransformMatrixStale = true;
}

void Transform::Rotate(const Rotation& a_rotation)
{
	m_rotation.SetRadians(m_rotation.GetRadians() + a_rotation.GetRadians());
	m_bTransformMatrixStale = true;
}

void Transform::AttachTo(Transform* a_parent)
{
	m_parent = a_parent;
}