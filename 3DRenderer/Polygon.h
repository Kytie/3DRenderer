#pragma once
#include "Vector3D.h"

class Polygons
{
	public:
		Polygons(void);
		Polygons(Vector3D v1, Vector3D v2, Vector3D v3);
		~Polygons(void);

		Vector3D GetPolygon(int row) const;
		void SetPolygon(Vector3D value, int row);

		void DrawPolygon(Polygons poly, int n, HDC hdc);


	private:

		Vector3D _polygon[3];

		void Init(Vector3D v1, Vector3D v2, Vector3D v3);
};