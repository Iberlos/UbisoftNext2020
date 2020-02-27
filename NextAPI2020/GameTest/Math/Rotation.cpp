#include "stdafx.h"
#include "MyMath.h"
#include <math.h>

namespace MyMath
{
    Rotation::Rotation()
    {
        SetRadians(0.0f);
    }

    Rotation Rotation::Degrees(float a_degrees)
    {
        Rotation rotation;
        rotation.SetDegrees(a_degrees);
        return rotation;
    }

    Rotation Rotation::Radians(float a_radians)
    {
        Rotation rotation;
        rotation.SetRadians(a_radians);
        return rotation;
    }

    Rotation Rotation::Direction(const Vector2& a_direction)
    {
        Rotation rotation;
        rotation.SetDirection(a_direction);
        return rotation;
    }

    void Rotation::SetDegrees(float a_degrees)
    {
        SetRadians(MyMath::DegreesToRadians(a_degrees));
    }

    void Rotation::SetRadians(float a_radians)
    {
        m_radians = a_radians;

        float twoPi = M_PI * 2.0f;

        //keeping m_radians between 0 and twoPi
        if (m_radians < 0.0f)
        {
            m_radians += twoPi;
        }
        else if (m_radians > twoPi)
        {
            m_radians -= twoPi;
        }
    }

    float Rotation::GetDegrees()
    {
        return MyMath::RadiansToDegrees(m_radians);
    }

    float Rotation::GetRadians()
    {
        return m_radians;
    }

    void Rotation::Rotate(float a_increment, bool a_Bdegrees)
    {
        a_increment = a_Bdegrees ? MyMath::DegreesToRadians(a_increment) : a_increment;
        SetRadians(GetRadians() + a_increment);
    }

    void Rotation::SetDirection(const Vector2& a_direction)
    {
        m_radians = atan2f(a_direction.m_y, a_direction.m_x);
    }

    Vector2 Rotation::GetDirection()
    {
        return Vector2(cosf(m_radians), sinf(m_radians));
    }
}

