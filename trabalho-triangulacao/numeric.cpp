#include "numeric.h"
#include "edge.h"
#include "vector2.h"
#include "triangle.h"

double half(double x){return 0.5 * x;}

bool almost_equal(double x, double y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) <= std::numeric_limits<double>::epsilon() * std::abs(x+y) * ulp
    // unless the result is subnormal
        || std::abs(x-y) < std::numeric_limits<double>::min();
}

bool almost_equal(Vector2 v1, Vector2 v2, int ulp)
{
        return almost_equal(v1.x, v2.x, ulp) && almost_equal(v1.y, v2.y, ulp);
}

bool almost_equal (Edge e1,Edge e2)
{
        return	(almost_equal(e1.p1, e2.p1) && almost_equal(e1.p2, e2.p2)) ||
	                (almost_equal(e1.p1, e2.p2) && almost_equal(e1.p2, e2.p1));
}

bool almost_equal(Triangle t1, Triangle t2)
{
        return	(almost_equal(t1.p1 , t2.p1) || almost_equal(t1.p1 , t2.p2) || almost_equal(t1.p1 , t2.p3)) &&
	                (almost_equal(t1.p2 , t2.p1) || almost_equal(t1.p2 , t2.p2) || almost_equal(t1.p2 , t2.p3)) &&
	                (almost_equal(t1.p3 , t2.p1) || almost_equal(t1.p3 , t2.p2) || almost_equal(t1.p3 , t2.p3));
}
