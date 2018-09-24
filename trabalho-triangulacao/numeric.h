#ifndef H_NUMERIC
#define H_NUMERIC

#include <cmath>
#include <limits>

class Edge;
struct Vector2;
class Triangle;

/**
 * @brief use of machine epsilon to compare floating-point values for equality
 * http://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
 */
bool almost_equal(double x, double y, int ulp=2);
bool almost_equal (Edge e1, Edge e2);
bool almost_equal(Triangle t1, Triangle t2);
bool almost_equal(Vector2 v1, Vector2 v2, int ulp=2);

double half(double x);

#endif
