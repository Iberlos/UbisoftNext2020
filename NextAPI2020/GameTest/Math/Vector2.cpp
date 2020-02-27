#include "stdafx.h"
#include "MyMath.h"
#include <math.h>

namespace MyMath
{
    Vector2::Vector2(float a_x, float a_y) :
        m_x(a_x),
        m_y(a_y)
    {
    }

    Vector2::Vector2(const Vector2& a_vector2)
    {
        Vector2(a_vector2.m_x, a_vector2.m_y);
    }

    Vector2::Vector2()
    {
        Vector2(0.0f, 0.0f);
    }

    Rotation Vector2::Angle(const Vector2& a_to) const
    {
        float a = atan2f(m_x- a_to.m_x, m_y - a_to.m_y) + M_PI * 4.0f;
        float b = M_PI * 2.0f;
        float radians = fmodf(1.0f, a);
        return Rotation::Radians(radians);
    }

    float Vector2::Length(bool a_Bsquared) const
    {
        float lengthSquared = m_x * m_x + m_y * m_y;
        return a_Bsquared ? lengthSquared : sqrtf(lengthSquared);
    }

    void Vector2::Normalize()
    {
        m_x = m_x / Length();
        m_y = m_y / Length();
    }

    Vector2 Vector2::Normalized() const
    {
        return Vector2(m_x / Length(), m_y / Length());
    }

    float Vector2::Distance(const Vector2& a_to, bool a_Bsquared) const
    {
        float lengthSquared = (m_x - a_to.m_x) * (m_x - a_to.m_x) + (m_y - a_to.m_y) * (m_y - a_to.m_y);
        return a_Bsquared?lengthSquared:sqrtf(lengthSquared);
    }

    float Vector2::Dot(const Vector2& a_vector2) const
    {
        return m_x *a_vector2.m_x + m_y *a_vector2.m_y;
    }

    Vector2 Vector2::GetPerpendicularVector(bool a_BcounterClockwise) const
    {
        return a_BcounterClockwise?Vector2(-m_y,m_x):Vector2(m_y,-m_x);
    }

    Vector2 Vector2::operator+(const Vector2& a_vector2) const
    {
        return Vector2(m_x+ a_vector2.m_x, m_y+a_vector2.m_y);
    }

    void Vector2::operator+=(const Vector2& a_vector2)
    {
        m_x += a_vector2.m_x;
        m_y += a_vector2.m_y;
    }

    Vector2 Vector2::operator-(const Vector2& a_vector2) const
    {
        return Vector2(m_x-a_vector2.m_x, m_y-a_vector2.m_y);
    }

    void Vector2::operator-=(const Vector2& a_vector2)
    {
        m_x -= a_vector2.m_x;
        m_y -= a_vector2.m_y;
    }

    Vector2 Vector2::operator*(const Vector2& a_vector2) const
    {
        return Vector2(m_x*a_vector2.m_x, m_y*a_vector2.m_y);
    }

    void Vector2::operator*=(const Vector2& a_vector2)
    {
        m_x *= a_vector2.m_x;
        m_y *= a_vector2.m_y;
    }

    Vector2 Vector2::operator*(const float& a_scale) const
    {
        return Vector2(m_x* a_scale, m_y*a_scale);
    }

    void Vector2::operator*=(const float& a_scale)
    {
        m_x *= a_scale;
        m_y *= a_scale;
    }

    Vector2 Vector2::operator/(const Vector2& a_vector2) const
    {
        return Vector2(m_x / a_vector2.m_x, m_y / a_vector2.m_y);
    }

    void Vector2::operator/=(const Vector2& a_vector2)
    {
        m_x /= a_vector2.m_x;
        m_y /= a_vector2.m_y;
    }

    Vector2 Vector2::operator/(const float& a_scale) const
    {
        return Vector2(m_x / a_scale, m_y / a_scale);
    }

    void Vector2::operator/=(const float& a_scale)
    {
        m_x /= a_scale;
        m_y /= a_scale;
    }

    Vector2 Vector2::operator-()
    {
        return Vector2(-m_x, -m_y);
    }

    bool Vector2::operator==(const Vector2& a_vector2) const
    {
        return m_x==a_vector2.m_x && m_y==a_vector2.m_y;
    }

    bool Vector2::operator!=(const Vector2& a_vector2) const
    {
        return m_x != a_vector2.m_x || m_y != a_vector2.m_y;
    }

    bool Vector2::operator<(const Vector2& a_vector2) const
    {
        return (m_x == a_vector2.m_x) ? (m_y < a_vector2.m_y) : (m_x < a_vector2.m_x);
    }

    bool Vector2::operator<=(const Vector2& a_vector2) const
    {
        return (m_x == a_vector2.m_x) ? (m_y <= a_vector2.m_y) : (m_x <= a_vector2.m_x);
    }

    bool Vector2::operator>(const Vector2& a_vector2) const
    {
        return (m_x == a_vector2.m_x) ? (m_y > a_vector2.m_y) : (m_x > a_vector2.m_x);;
    }

    bool Vector2::operator>=(const Vector2& a_vector2) const
    {
        return (m_x == a_vector2.m_x) ? (m_y >= a_vector2.m_y) : (m_x >= a_vector2.m_x);;
    }

    //Vector2 operator*(float a_scale, const Vector2& a_vector2) const
    //{
    //    return Vector2(a_vector2.m_x * a_scale, a_vector2.m_y * a_scale);
    //}
}

