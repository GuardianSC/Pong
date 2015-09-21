#pragma once
// Taken from Riley/past Sno Isle project
#include "MyMath.h"
#include <cmath>

using namespace myMath;

namespace col
{
	struct MapSegment
	{
		Point p1;
		Point p2;
	public:
		MapSegment(Point a, Point b)
		{
			p1 = a;
			p2 = b;
		}
	public:
		Vector2 GetVector()
		{
			return Vector2{ p2.x - p1.x, p2.y - p1.y };
		}
	public:
		Rectangle CollisionRect()
		{
			return Rectangle{ fmin(p1.x, p2.x), fmin(p1.y, p2.y), abs(p1.x - p2.x), abs(p1.y - p2.y) };
		}
	};
	struct Line2D
	{
		Vector2 p;
		Vector2 v;

	public:
		float yInt()
		{
			return (-v.y * p.x + v.x * p.y) / v.x;
		}
	public:
		float Slope()
		{
			return v.y / v.x;
		}
	};
	struct Circle
	{
		Vector2 P;
		double R;

	public:
		Circle(Vector2 p, double r)
		{
			P = p;
			R = r;
		}
	};
	static float Magnitude(Vector2 v)
	{
		return (float)sqrt(v.x * v.x + v.y * v.y);
	}
	static Vector2 VectorNormal(Vector2 v)
	{
		return Vector2{ -v.y, v.x };
	}
	static Vector2 UnitVector(Vector2 v)
	{
		return Vector2{ v.x / (float)Magnitude(v), v.y / (float)Magnitude(v) };
	}
	static float DotProduct(Vector2 u, Vector2 v)
	{
		return u.x * u.x + u.y * u.y;
	}
	static Vector2 ReflectedVector(Vector2 v, Vector2 a)
	{
		Vector2 n = VectorNormal(a);

		float co = -2 * (DotProduct(v, n) / (Magnitude(n) * Magnitude(n)));
		Vector2 r;
		r.x = v.x + co * n.x;
		r.y = v.y + co * n.y;
		return r;
	}
	static bool CheckSegmentSegmentCollision(MapSegment s1, MapSegment s2)
	{
		Line2D L1, L2;
		L1.p = Vector2{ s1.p1.x, s1.p1.y };
		L2.p = Vector2{ s2.p1.x, s2.p1.y };
		L1.v.x = s1.p2.x - s1.p1.x;
		L1.v.y = s1.p2.y - s1.p1.y;
		L2.v.x = s2.p2.x - s2.p1.x;
		L2.v.y = s2.p2.y - s2.p1.y;

		Vector2 CollisionPoint;

		CollisionPoint.x = { (L2.yInt() - L1.yInt()) / L1.Slope() - L2.Slope() };
		CollisionPoint.y = { L1.Slope() * CollisionPoint.x + L1.yInt() };

		bool cond1 = (fmin(s1.p1.x, s1.p2.x) <= CollisionPoint.x && CollisionPoint.x <= fmax(s1.p1.x, s1.p2.x));
		bool cond2 = (fmin(s2.p1.x, s2.p2.x) <= CollisionPoint.x && CollisionPoint.x <= fmax(s2.p1.x, s2.p2.x));
		bool cond3 = (fmin(s1.p1.y, s1.p2.y) <= CollisionPoint.y && CollisionPoint.y <= fmax(s1.p1.y, s1.p2.y));
		bool cond4 = (fmin(s2.p1.y, s2.p2.y) <= CollisionPoint.y && CollisionPoint.y <= fmax(s2.p1.y, s2.p2.y));

		return cond1 && cond2 && cond3 && cond4;
	}
	static bool CheckCircleSegmentCollision(Circle C, MapSegment S)
	{
		Line2D L;
		L.p.x = S.p1.x;
		L.p.y = S.p1.y;
		L.v.x = S.p2.x - S.p1.x;
		L.v.y = S.p2.y - S.p1.y;

		double OH = abs(((L.v.x * (C.P.x - L.p.y)) - (L.v.y * (C.P.x - L.p.x))) / (sqrt(L.v.x * L.v.x + L.v.y * L.v.y)));

		if (OH < C.R)
		{
			Vector2 CollisionPoint1;
			Vector2 CollisionPoint2;

			if (L.v.x != 0)
			{
				double Dv = L.v.y / L.v.x;
				double E = (L.v.x * L.p.y - L.v.y * L.p.x) / L.v.x - C.P.y;

				double a = 1 + Dv * Dv;
				double b = -2 * C.P.x + 2 * E * Dv;
				double c = C.P.x * C.P.x + E * E - C.R * C.R;

				CollisionPoint1.x = (float)((-b + sqrt(b * b - 4 * a * c)) / (2 * a));
				CollisionPoint2.x = (float)((-b - sqrt(b * b - 4 * a * c)) / (2 * a));

				CollisionPoint1.y = L.Slope() * CollisionPoint1.x + L.yInt();
				CollisionPoint2.y = L.Slope() * CollisionPoint1.x + L.yInt();

				bool cond1 = (fmin(S.p1.x, S.p2.x) <= CollisionPoint1.x && CollisionPoint1.x && CollisionPoint1.x <= (fmax(S.p1.x, S.p2.x)));
				bool cond2 = (fmin(S.p1.y, S.p2.y) <= CollisionPoint1.y && CollisionPoint1.y && CollisionPoint1.x <= (fmax(S.p1.y, S.p2.y)));

				bool cond3 = (fmin(S.p1.x, S.p2.x) <= CollisionPoint2.x && CollisionPoint2.x && CollisionPoint2.x <= (fmax(S.p1.x, S.p2.x)));
				bool cond4 = (fmin(S.p1.y, S.p2.y) <= CollisionPoint2.y && CollisionPoint2.y && CollisionPoint2.x <= (fmax(S.p1.y, S.p2.y)));

				return (cond1 && cond2) || (cond3 && cond4);
			}
		}
		return false;
	}
	static bool CheckCircleCircleCollision(Circle C, Circle D)
	{
		if (C.R + D.R >= Magnitude(D.P - C.P))
		{
			return true;
		}
		return false;
	}
}