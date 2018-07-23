#include "stdafx.h"
#include "Matrix4.h"
#include "Utility.h"

// Constructors

Matrix4::Matrix4(void)
{
	float matrix[4][4] = {{0.0,0.0,0.0,0.0}, {0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0}};
	Init(*matrix);
}

Matrix4::Matrix4(float *matrix)
{
	
	Init(matrix);
}

Matrix4::Matrix4(const Matrix4& v)
{
	Copy(v);
}

Matrix4::~Matrix4(void)
{
}

// Accessors and mutators

float Matrix4::GetMatrix(int row, int col) const
{
	return _matrixArray[row][col];
}

void Matrix4::SetMatrix(float value, int row, int col)
{

	_matrixArray[row][col] = value;
}

// Operator overloads

Matrix4& Matrix4::operator= (const Matrix4 &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

const Matrix4 Matrix4::operator*(const Matrix4 &other) const
{
	Matrix4 result;

	//matrix row 1
	result.SetMatrix(((_matrixArray[0][0]*other.GetMatrix(0,0))+(_matrixArray[0][1]*other.GetMatrix(1,0))+(_matrixArray[0][2]*other.GetMatrix(2,0))+
		(_matrixArray[0][3]*other.GetMatrix(3,0))),0,0);
	result.SetMatrix(((_matrixArray[0][0]*other.GetMatrix(0,1))+(_matrixArray[0][1]*other.GetMatrix(1,1))+(_matrixArray[0][2]*other.GetMatrix(2,1))+
		(_matrixArray[0][3]*other.GetMatrix(3,1))),0,1);
	result.SetMatrix(((_matrixArray[0][0]*other.GetMatrix(0,2))+(_matrixArray[0][1]*other.GetMatrix(1,2))+(_matrixArray[0][2]*other.GetMatrix(2,2))+
		(_matrixArray[0][3]*other.GetMatrix(3,2))),0,2);
	result.SetMatrix(((_matrixArray[0][0]*other.GetMatrix(0,3))+(_matrixArray[0][1]*other.GetMatrix(1,3))+(_matrixArray[0][2]*other.GetMatrix(2,3))+
		(_matrixArray[0][3]*other.GetMatrix(3,3))),0,3);

	//matrix row 2
	result.SetMatrix(((_matrixArray[1][0]*other.GetMatrix(0,0))+(_matrixArray[1][1]*other.GetMatrix(1,0))+(_matrixArray[1][2]*other.GetMatrix(2,0))+
		(_matrixArray[1][3]*other.GetMatrix(3,0))),1,0);
	result.SetMatrix(((_matrixArray[1][0]*other.GetMatrix(0,1))+(_matrixArray[1][1]*other.GetMatrix(1,1))+(_matrixArray[1][2]*other.GetMatrix(2,1))+
		(_matrixArray[1][3]*other.GetMatrix(3,1))),1,1);
	result.SetMatrix(((_matrixArray[1][0]*other.GetMatrix(0,2))+(_matrixArray[1][1]*other.GetMatrix(1,2))+(_matrixArray[1][2]*other.GetMatrix(2,2))+
		(_matrixArray[1][3]*other.GetMatrix(3,2))),1,2);
	result.SetMatrix(((_matrixArray[1][0]*other.GetMatrix(0,3))+(_matrixArray[1][1]*other.GetMatrix(1,3))+(_matrixArray[1][2]*other.GetMatrix(2,3))+
		(_matrixArray[1][3]*other.GetMatrix(3,3))),1,3);

	//matrix row 3
	result.SetMatrix(((_matrixArray[2][0]*other.GetMatrix(0,0))+(_matrixArray[2][1]*other.GetMatrix(1,0))+(_matrixArray[2][2]*other.GetMatrix(2,0))+
		(_matrixArray[2][3]*other.GetMatrix(3,0))),2,0);
	result.SetMatrix(((_matrixArray[2][0]*other.GetMatrix(0,1))+(_matrixArray[2][1]*other.GetMatrix(1,1))+(_matrixArray[2][2]*other.GetMatrix(2,1))+
		(_matrixArray[2][3]*other.GetMatrix(3,1))),2,1);
	result.SetMatrix(((_matrixArray[2][0]*other.GetMatrix(0,2))+(_matrixArray[2][1]*other.GetMatrix(1,2))+(_matrixArray[2][2]*other.GetMatrix(2,2))+
		(_matrixArray[2][3]*other.GetMatrix(3,2))),2,2);
	result.SetMatrix(((_matrixArray[2][0]*other.GetMatrix(0,3))+(_matrixArray[2][1]*other.GetMatrix(1,3))+(_matrixArray[2][2]*other.GetMatrix(2,3))+
		(_matrixArray[2][3]*other.GetMatrix(3,3))),2,3);
	
	//matrix row 4
	result.SetMatrix(((_matrixArray[3][0]*other.GetMatrix(0,0))+(_matrixArray[3][1]*other.GetMatrix(1,0))+(_matrixArray[3][2]*other.GetMatrix(2,0))+
		(_matrixArray[3][3]*other.GetMatrix(3,0))),3,0);
	result.SetMatrix(((_matrixArray[3][0]*other.GetMatrix(0,1))+(_matrixArray[3][1]*other.GetMatrix(1,1))+(_matrixArray[3][2]*other.GetMatrix(2,1))+
		(_matrixArray[3][3]*other.GetMatrix(3,1))),3,1);
	result.SetMatrix(((_matrixArray[3][0]*other.GetMatrix(0,2))+(_matrixArray[3][1]*other.GetMatrix(1,2))+(_matrixArray[3][2]*other.GetMatrix(2,2))+
		(_matrixArray[3][3]*other.GetMatrix(3,2))),3,2);
	result.SetMatrix(((_matrixArray[3][0]*other.GetMatrix(0,3))+(_matrixArray[3][1]*other.GetMatrix(1,3))+(_matrixArray[3][2]*other.GetMatrix(2,3))+
		(_matrixArray[3][3]*other.GetMatrix(3,3))),3,3);
	return result;
}

const Vector3D Matrix4::operator*(const Vector3D &other) const
{
	Vector3D result;
	
	result.SetX((_matrixArray[0][0]*other.GetX()) + (_matrixArray[0][1]*other.GetY()) + (_matrixArray[0][2]*other.GetZ()) + (_matrixArray[0][3]*other.GetW()));
	result.SetY((_matrixArray[1][0]*other.GetX()) + (_matrixArray[1][1]*other.GetY()) + (_matrixArray[1][2]*other.GetZ()) + (_matrixArray[1][3]*other.GetW()));
	result.SetZ((_matrixArray[2][0]*other.GetX()) + (_matrixArray[2][1]*other.GetY()) + (_matrixArray[2][2]*other.GetZ()) + (_matrixArray[2][3]*other.GetW()));
	result.SetW((_matrixArray[3][0]*other.GetX()) + (_matrixArray[3][1]*other.GetY()) + (_matrixArray[3][2]*other.GetZ()) + (_matrixArray[3][3]*other.GetW()));

	return result;
}

void Matrix4::SetIdentityMatrix()
{
	float matrix[4][4] = {{1.0,0.0,0.0,0.0}, {0.0,1.0,0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0}};
	Init(*matrix);
}

void Matrix4::SetTranslationMatrix(Vector3D vector)
{
	float matrix[4][4] = {{1.0,0.0,0.0,vector.GetX()}, {0.0,1.0,0.0,vector.GetY()},{0.0,0.0,1.0,vector.GetZ()},{0.0,0.0,0.0,1.0}};
	Init(*matrix);
}

void Matrix4::SetScaleMatrix(Vector3D vector)
{
	float matrix[4][4] = {{vector.GetX(),0.0,0.0,0.0}, {0.0,vector.GetY(),0.0,0.0},{0.0,0.0,vector.GetZ(),0.0},{0.0,0.0,0.0,vector.GetW()}};
	Init(*matrix);
}

void Matrix4::SetRotationMatrixX(float theta)
{
	float matrix[4][4] = {{1.0,0.0,0.0,0.0}, {0.0,cos(theta),-sin(theta),0.0,},{0.0,sin(theta),cos(theta),0.0},{0.0,0.0,0.0,1.0}};
	Init(*matrix);
}

void Matrix4::SetRotationMatrixY(float theta)
{
	float matrix[4][4] = {{cos(theta),0.0,sin(theta),0.0}, {0.0,1.0,0.0,0.0},{-sin(theta),0.0,cos(theta),0.0},{0.0,0.0,0.0,1.0}};
	Init(*matrix);
}
void Matrix4::SetRotationMatrixZ(float theta)
{
	float matrix[4][4] = {{cos(theta),-sin(theta),0.0,0.0}, {sin(theta),cos(theta),0.0,0.0},{0.0,0.0,1.0,0.0},{0.0,0.0,0.0,1.0}};
	Init(*matrix);
}

Matrix4 Matrix4::CreateViewMatrix(Vector3D v, Vector3D u, Vector3D r, Vector3D eye)
{
	Matrix4 result;
	_matrixArray[0][0] = r.GetX();
	_matrixArray[0][1] = r.GetY();
	_matrixArray[0][2] = r.GetZ();
	_matrixArray[0][3] = eye.GetX();
	_matrixArray[1][0] = u.GetX();
	_matrixArray[1][1] = u.GetY();
	_matrixArray[1][2] = u.GetZ();
	_matrixArray[1][3] = eye.GetY();
	_matrixArray[2][0] = v.GetX();
	_matrixArray[2][1] = v.GetY();
	_matrixArray[2][2] = v.GetZ();
	_matrixArray[2][3] = eye.GetZ();
	_matrixArray[3][0] = 0;
	_matrixArray[3][1] = 0;
	_matrixArray[3][2] = 0;
	_matrixArray[3][3] = 1;
	return result;
}

//invert 4x4 matrix, code influenced by minsi chen.
Matrix4 Matrix4::invert(Matrix4 matrix, Matrix4 inverseMatrix)
{
    float t, matrixVal;
    int i, j, k, swap;
	float tmp[4][4];
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
			tmp[i][j] = matrix.GetMatrix(i, j);
        }
    }

    
    for (i = 0; i < 4; i++) {
        // look for largest element in column to be used as pivot.
        swap = i;
        for (j = i + 1; j < 4; j++) {
            if (fabs(tmp[j][i]) > fabs(tmp[i][i])) {
                swap = j;
            }
        }
        
        if (swap != i) {
            for (k = 0; k < 4; k++) {
                t = tmp[i][k];
                tmp[i][k] = tmp[swap][k];
                tmp[swap][k] = t;
                
				t = inverseMatrix.GetMatrix(i, k);
				inverseMatrix.SetMatrix(inverseMatrix.GetMatrix(swap,k),i,k);
				inverseMatrix.SetMatrix(t, swap, k);
            }
		}
        
		 t = tmp[i][i];
        for (k = 0; k < 4; k++) {
            tmp[i][k] /= t;
			matrixVal = inverseMatrix.GetMatrix(i, k);
			matrixVal /= t;
			inverseMatrix.SetMatrix(matrixVal, i, k);
        }
        for (j = 0; j < 4; j++) {
            if (j != i) {
                t = tmp[j][i];
                for (k = 0; k < 4; k++) {
                    tmp[j][k] -= tmp[i][k]*t;
					matrixVal = inverseMatrix.GetMatrix(i, k);
					matrixVal *= t;
					inverseMatrix.SetMatrix(inverseMatrix.GetMatrix(j, k) - matrixVal, j,k);
                }
            }
        }

    }
	return inverseMatrix;
}


// Private methods

void Matrix4::Init(float* matrix)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			_matrixArray[i][j] = *matrix;
			*matrix++;
		}
	}
}

void Matrix4::Copy(const Matrix4& v)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			_matrixArray[i][j] = v.GetMatrix(i,j);
		}
	}
}

std::string Matrix4::ToString(void) const
{
	std::ostringstream buffer;
	return "()";
}



