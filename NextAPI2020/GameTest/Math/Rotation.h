#pragma once

namespace MyMath
{
    struct Vector2;

    class Rotation
    {
    public:
        Rotation();

        static Rotation Degrees(float a_degrees);
        static Rotation Radians(float a_radians);
        static Rotation Direction(const Vector2& a_direction);

        void SetDegrees(float a_degrees);
        void SetRadians(float a_radians);

        float GetDegrees();
        float GetRadians();

        void Rotate(float a_increment, bool a_Bdegrees = false);

        void SetDirection(const Vector2& a_direction);
        Vector2 GetDirection();

    private:
        float m_radians;
    };
}