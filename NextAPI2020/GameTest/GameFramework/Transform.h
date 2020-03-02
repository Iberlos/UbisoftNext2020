#pragma once

class Transform
{
public:
	Transform();
	Transform(const Transform& a_transform);
	virtual ~Transform();

	Matrix GetTransformMatrix();
	Vector2 GetPosition() const;
	void SetPosition(Vector2 a_position);
	Rotation GetRotation() const;
	float GetDegrees() const;
	void SetDegrees(float a_degrees);
	float GetRadians() const;
	void SetRadians(float a_radians);
	Vector2 GetDirection() const;
	void SetDirection(Vector2 a_direction);
	Vector2 GetScale() const;
	void SetScale(Vector2 a_scale);
	Transform* GetParent() const;

	void Translate(const Vector2& a_offset);
	void Rotate(const Rotation& a_rotation);
	void AttachTo(Transform* a_parent);

protected:
	Transform* m_parent;
	Matrix m_transform;
	Vector2 m_position;
	Rotation m_rotation;
	Vector2 m_scale;
	bool m_bTransformMatrixStale;
};
