#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Function to calculate the cross product of two vectors
double cross(const Point& a, const Point& b, const Point& c) {
    Point ab = {b.x - a.x, b.y - a.y};
    Point ac = {c.x - a.x, c.y - a.y};
    return ab.x * ac.y - ab.y * ac.x;
}

// Function to check if two line segments intersect
bool intersect(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double d1 = cross(a1, a2, b1);
    double d2 = cross(a1, a2, b2);
    double d3 = cross(b1, b2, a1);
    double d4 = cross(b1, b2, a2);

    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
        return true;
    }

    return false;
}

// Function to check if two quadrilaterals intersect
bool quadrilateralIntersection(const vector<Point>& quad1, const vector<Point>& quad2) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            Point a1 = quad1[i];
            Point a2 = quad1[(i + 1) % 4];
            Point b1 = quad2[j];
            Point b2 = quad2[(j + 1) % 4];

            if (intersect(a1, a2, b1, b2)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<Point> quad1, quad2;
    double x, y;

    cout << "Enter the coordinates of the vertices of the first quadrilateral (A, B, C, D):" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Vertex " << char('A' + i) << ": ";
        cin >> x >> y;
        quad1.emplace_back(x, y);
    }

    cout << "Enter the coordinates of the vertices of the second quadrilateral (E, F, G, H):" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Vertex " << char('E' + i) << ": ";
        cin >> x >> y;
        quad2.emplace_back(x, y);
    }

    if (quadrilateralIntersection(quad1, quad2)) {
        cout << "Intersect" << endl;
    } else {
        cout << "Do Not Intersect" << endl;
    }

    return 0;
}