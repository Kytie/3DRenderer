#include "stdafx.h"
#include "Polygon.h"
#include "Vector3D.h"

//Constructors

Polygons::Polygons(void)
{
	Vector3D v1;
	Vector3D v2;
	Vector3D v3;
	Init(v1,v2,v3);
}

Polygons::Polygons(Vector3D v1, Vector3D v2, Vector3D v3)
{
	Init(v1,v2,v3);
}


Polygons::~Polygons(void)
{
}

//Mutators and Accessors
Vector3D Polygons::GetPolygon(int row) const
{
	return _polygon[row];
}

void Polygons::SetPolygon(Vector3D value, int row)
{
	_polygon[row] = value;
}

//routines
void Polygons::DrawPolygon(Polygons poly, int n, HDC hdc)
{
	Vector3D Vector1;
	Vector3D Vector2;
	int i = 0;
	while(i < n-1)
	{
		Vector1 = poly.GetPolygon(i);
		Vector2 = poly.GetPolygon(i+1);
		MoveToEx(hdc, Vector1.GetX(), Vector1.GetY(), NULL);
		LineTo(hdc, Vector2.GetX(), Vector2.GetY());
		i++;
	}
	Vector1 = poly.GetPolygon(n-1);
	Vector2 = poly.GetPolygon(0);
	MoveToEx(hdc, Vector1.GetX(), Vector1.GetY(), NULL);
	LineTo(hdc, Vector2.GetX(), Vector2.GetY());
}

// Private methods

void Polygons::Init(Vector3D v1, Vector3D v2, Vector3D v3)
{
	_polygon[0] = v1;
	_polygon[1] = v2;
	_polygon[2] = v3;
}