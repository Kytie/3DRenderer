#pragma once
#include <string>

class Vector3D
{
	public:
		Vector3D(void);
		Vector3D(float x, float y, float z);
		Vector3D(const Vector3D& v);
		~Vector3D(void);

		float GetX(void) const;
		void SetX(float x);
		float GetY(void) const;
		void SetY(float y);
		float GetZ(void) const;
		void SetZ(float z);
		float GetW(void) const;
		void SetW(float w);

		Vector3D& operator= (const Vector3D &rhs);
		const Vector3D operator+(const Vector3D &other) const;
		const Vector3D operator-(const Vector3D &other) const;
		const float GetDotProduct(const Vector3D &other) const;
		const Vector3D GetCrossProduct(const Vector3D &other) const;
		const Vector3D Normalise(const Vector3D vector) const;

		std::string ToString(void) const;

	private:
		float _x;
		float _y;
		float _z;
		float _w;

		void Init(float x, float y, float z);
		void Copy(const Vector3D& v);
		
};


