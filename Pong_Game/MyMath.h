#pragma once

// Taken form Riley
namespace myMath
{
	struct Vector2 { float x; float y; };
	struct Point { float x; float y; };

	//typedef Vector2 Point;
	struct Rectangle { float x; float y; float sizeX; float sizeY; };
	//struct Rectangle {Vector2 pos, dim; };

	Vector2 operator+(Vector2 lhs, Vector2 rhs) { return{ lhs.x + rhs.x, lhs.y + rhs.y }; }
	Vector2 operator-(Vector2 lhs, Vector2 rhs) { return{ lhs.x - rhs.x, lhs.y - rhs.y }; }
	Vector2 operator*(Vector2 lhs, Vector2 rhs) { return{ lhs.x * rhs.x, lhs.y * rhs.y }; }
	Vector2 operator/(Vector2 lhs, Vector2 rhs) { return{ lhs.x / rhs.x, lhs.y / rhs.y }; }
	
}