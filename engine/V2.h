#ifndef V2_H
#define V2_H

#include <cmath>

namespace Octo 
{
    template <typename T>
	struct Vec2
	{
		Vec2(T x, T y) : X(x), Y(y) {};
		Vec2() : X(0), Y(0) {};
		T X;
		T Y;
		void Reset()
		{
			X = 0;
			Y = 0;
		}
		Vec2& operator +=(const Vec2& rhs)
		{
            return *this = *this + rhs;
		}
		Vec2 operator +(const Vec2& other) const
		{
			return Vec2(X + other.X, Y + other.Y);
		}
        Vec2 operator -(const Vec2& other) const
        {
            return Vec2(X - other.X, Y - other.Y);
        }
		Vec2& operator -=(const Vec2& rhs)
		{
            return *this = *this - rhs;
		}
        Vec2 operator *(const T& scalar) const
        {
            return Vec2(X * scalar, Y * scalar);
        }
		Vec2& operator *=(const T& scalar)
        {
            return *this = *this * scalar;
		}
        Vec2 operator /(const T& scalar) const
        {
            return Vec2(X / scalar, Y / scalar);
        }
		Vec2& operator /=(T scalar)
		{
            return *this = *this / scalar;
		}
		float GetMagnitude() const
		{
			return std::sqrtf(X * X + Y * Y);
		}
        float DotProduct(const Vec2 &rhs) const
        {
            return X * rhs.X + Y * rhs.Y;
        }
        Vec2 GetNormalized() const
        {
            float oneOverMagnitude = (T)1 / GetMagnitude();
            return Vec2(X * oneOverMagnitude, Y * oneOverMagnitude);
        }
        Vec2& Normalize()
        {
            return *this = *this->GetNormalized();
        }
	};

typedef Vec2<int> Vec2Int;
typedef Vec2<float> Vec2f;
}

#endif
