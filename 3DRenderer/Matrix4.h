#pragma once
#include <string>
#include "Vector3D.h"

class Matrix4
{
	public:
		Matrix4(void);
		Matrix4(float* matrix);
		Matrix4(const Matrix4& v);
		~Matrix4(void);

		float GetMatrix(int row, int col) const;
		void SetMatrix(float value, int row, int col);

		Matrix4& operator= (const Matrix4 &rhs);
		const Matrix4 operator*(const Matrix4 &other) const;
		const Vector3D operator*(const Vector3D &other) const;
		void SetTranslationMatrix(Vector3D vector);
		void SetScaleMatrix(Vector3D vector);
		void SetRotationMatrixX(float theta);
		void SetRotationMatrixY(float theta);
		void SetRotationMatrixZ(float theta);
		Matrix4 CreateViewMatrix(Vector3D v, Vector3D u, Vector3D r, Vector3D eye);
		Matrix4 invert(Matrix4 matrix, Matrix4 inverseMatrix);
		void SetIdentityMatrix();

		std::string ToString(void) const;

	private:

		float _matrixArray[4][4];

		void Init(float *matrix);
		void Copy(const Matrix4& v);
		
};


