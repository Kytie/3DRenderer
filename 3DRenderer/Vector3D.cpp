#include "stdafx.h"
#include "Vector3D.h"
#include "Utility.h"
#include "math.h"

// Constructors

Vector3D::Vector3D(void)
{
	Init(0.0f, 0.0f, 0.0f);
}

Vector3D::Vector3D(float x, float y, float z)
{
	Init(x, y, z);
}

Vector3D::Vector3D(const Vector3D& v)
{
	Copy(v);
}

Vector3D::~Vector3D(void)
{
}

// Accessors and mutators

float Vector3D::GetX(void) const
{
	return _x;
}

void Vector3D::SetX(float x)
{
	_x = x;
}

float Vector3D::GetY(void) const
{
	return _y;
}

void Vector3D::SetY(float y)
{
	_y = y;
}

float Vector3D::GetZ(void) const
{
	return _z;
}

void Vector3D::SetZ(float z)
{
	_z = z;
}

float Vector3D::GetW(void) const
{
	return _w;
}

void Vector3D::SetW(float w)
{
	_w = w;
}

// Operator overloads

Vector3D& Vector3D::operator= (const Vector3D &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

const Vector3D Vector3D::operator+(const Vector3D &other) const
{
	Vector3D result;
	result.SetX(_x + other.GetX());
	result.SetY(_y + other.GetY());
	result.SetZ(_z + other.GetZ());
	return result;
}

const Vector3D Vector3D::operator-(const Vector3D &other) const
{
	Vector3D result;
	result.SetX(_x + -other.GetX());
	result.SetY(_y + -other.GetY());
	result.SetZ(_z + -other.GetZ());
	return result;
}

const float Vector3D::GetDotProduct(const Vector3D &other) const
{
	float result;
	result = (_x * other.GetX()) + (_y * other.GetY()) + (_z * other.GetZ());
	return result;
}

const Vector3D Vector3D::GetCrossProduct(const Vector3D &other) const
{
	Vector3D result;
	result.SetX((_y * other.GetZ()) - (_z * other.GetY()));
	result.SetY((_z * other.GetX()) - (_x * other.GetZ()));
	result.SetZ((_x * other.GetY()) - (_y * other.GetX()));
	return result;
}

const Vector3D Vector3D::Normalise(const Vector3D vector) const
{
	Vector3D result;
	float x = vector.GetX();
	float y = vector.GetY();
	float z = vector.GetZ();
	float magnitude;

	x = x*x;
	y = y*y;
	z = z*z;
	magnitude = x+y+z;
	magnitude = sqrt(magnitude);

	result.SetX(vector.GetX()/magnitude);
	result.SetY(vector.GetY()/magnitude);
	result.SetZ(vector.GetZ()/magnitude);
	result.SetW(1.0);

	return result;
}




// Private methods

void Vector3D::Init(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

void Vector3D::Copy(const Vector3D& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
}

std::string Vector3D::ToString(void) const
{
	std::ostringstream buffer;
	return "(" + FloatToString(_x) + ", " + FloatToString(_y) + ", " + FloatToString(_z) + ")";
}



