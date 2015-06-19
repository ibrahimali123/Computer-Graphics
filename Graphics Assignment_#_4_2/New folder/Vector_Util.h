#include <windows.h>

using namespace std;

struct Vector2 {
	double x, y;
	Vector2(double a = 0, double b = 0) {
		x = a;
		y = b;
	}
};

class Vector4 {
	double v[4];
public:
	Vector4(double a = 0, double b = 0, double c = 0, double d = 0) {
		v[0] = a;
		v[1] = b;
		v[2] = c;
		v[3] = d;
	}

	Vector4(double a[]) {
		memcpy(v, a, 4 * sizeof(double));
	}

	double& operator[](int i) {
		return v[i];
	}

	double DotProduct(Vector4& b) {
		return v[0] * b[0] + v[1] * b[1] + v[2] * b[2] + v[3] * b[3];
	}
};

class Matrix4 {
	Vector4 M[4];
public:
	Matrix4(double A[]) {
		memcpy(M, A, 16 * sizeof(double));
	}

	Vector4& operator[](int i) {
		return M[i];
	}

	Vector4 operator*(Vector4& b) {
		Vector4 res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res[i] += M[i][j] * b[j];

		return res;
	}

	Vector4 multiply(Vector4& b) {
		Vector4 res;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				res[i] += M[i][j] * b[j];

		return res;
	}
};
