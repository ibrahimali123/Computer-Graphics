#include "Vector_Util.h"

class HermiteCurve {
public:
	int curveAlgorithm;
	COLORREF color;

		int round(double x) {
		return (int) (x + 0.5);
	}


	vector<Point> Points;

	HermiteCurve() {
	}

	HermiteCurve(int X1, int X2, int X3, int X4, int Y1, int Y2, int Y3,
			int Y4, int alg, COLORREF col) {
		Point p1(X1, Y1);
		Points.push_back(p1);

		Point p2(X2, Y2);
		Points.push_back(p2);

		Point p3(X3, Y3);
		Points.push_back(p3);

		Point p4(X4, Y4);
		Points.push_back(p4);

		color = col;
		curveAlgorithm = alg;
	}

	Vector4 GetHermiteCoeff(double x0, double s0, double x1, double s1) {
		static double H[16] = { 2, 1, -2, 1, -3, -2, 3, -1, 0, 1, 0, 0, 1, 0,
				0, 0 };
		static Matrix4 basis(H);
		Vector4 v(x0, s0, x1, s1);
		return basis * v;
	}

	void DrawHermiteCurve(HDC hdc, Vector2& P0, Vector2& T0, Vector2& P1,
			Vector2& T1, int numpoints, COLORREF color) {
		Vector4 xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x);
		Vector4 ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y);
		if (numpoints < 2)
			return;
		double dt = 1.0 / (numpoints - 1);

		for (double t = 0; t <= 1; t += dt) {
			Vector4 vt;
			vt[3] = 1;
			for (int i = 2; i >= 0; i--)
				vt[i] = vt[i + 1] * t;
			int x = (int) round(xcoeff.DotProduct(vt));
			int y = (int) round(ycoeff.DotProduct(vt));
			SetPixel(hdc, x, y, color);
		}
	}

	/*
	 void DrawHermiteCurve(HDC hdc, point P0, point T0, point P1, point T1,
	 int numpoints) {
	 Vector4 xcoeff = GetHermiteCoeff(P0.x, T0.x, P1.x, T1.x);
	 Vector4 ycoeff = GetHermiteCoeff(P0.y, T0.y, P1.y, T1.y);
	 if (numpoints < 2)
	 return;
	 double dt = 1.0 / (numpoints - 1);
	 for (double t = 0; t <= 1; t += dt) {
	 Vector4 vt;
	 vt[3] = 1;
	 for (int i = 2; i >= 0; i--)
	 vt[i] = vt[i + 1] * t;
	 int x = (int) round(xcoeff.DotProduct(vt));
	 int y = (int) round(ycoeff.DotProduct(vt));
	 if (t == 0)
	 MoveToEx(hdc, x, y, NULL);
	 else
	 LineTo(hdc, x, y);
	 }
	 }
	 */

	void DrawBezierCurve(HDC hdc, Point P0, Point P1, Point P2, Point P3,
			int numpoints) {
		Point T0(3 * (P1.x - P0.x), 3 * (P1.y - P0.y));
		Point T1(3 * (P3.x - P2.x), 3 * (P3.y - P2.y));

		Vector2 v1(P0.x, P0.y);
		Vector2 v2(T0.x, T0.y);
		Vector2 v3(P3.x, P3.y);
		Vector2 v4(T1.x, T1.y);

		DrawHermiteCurve(hdc, v1, v2, v3, v4, numpoints, color);

		// DrawHermiteCurve(hdc, P0, T0, P3, T1, numpoints);
	}

	void DrawCardinalSpline(HDC hdc, Point P[], int n, double c, int numpix) {
		double c1 = 1 - c;
		Point T0((int) round(c1 * (P[2].x - P[0].x)),
				(int) round(c1 * (P[2].y - P[0].y)));
		for (int i = 2; i < n - 1; i++) {
			Point T1((int) round(c1 * (P[i + 1].x - P[i - 1].x)),
					(int) round(c1 * (P[i + 1].y - P[i - 1].y)));

			Vector2 v1(P[i - 1].x, P[i - 1].y);
			Vector2 v2(T0.x, T0.y);
			Vector2 v3(P[i].x, P[i].y);
			Vector2 v4(T1.x, T1.y);

			DrawHermiteCurve(hdc, v1, v2, v3, v4, numpix, color);

			// DrawHermiteCurve(hdc, P[i - 1], T0, P[i], T1, numpix);
			T0 = T1;
		}
	}

	void DrawCurve(HDC hdc) {
		if (curveAlgorithm == 9) {
			Vector2 v1(Points[0].x, Points[0].y);
			Vector2 v2(Points[1].x, Points[1].y);
			Vector2 v3(Points[2].x, Points[2].y);
			Vector2 v4(Points[3].x, Points[3].y);

			DrawHermiteCurve(hdc, v1, v2, v3, v4, 100, color);
		} else if (curveAlgorithm == 10) {
			DrawBezierCurve(hdc, Points[0], Points[1], Points[2], Points[3],
					100);
		} else if (curveAlgorithm == 11) {
			Point p[4] = { Points[0], Points[1], Points[2], Points[3] };
			DrawCardinalSpline(hdc, p, 4, 0.01, 100);
		}
	}
};
