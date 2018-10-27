#ifndef H_TRIANGLE
#define H_TRIANGLE

#include "vector2.h"
#include "edge.h"
#include "numeric.h"

class Triangle
{
	public:
        Triangle(Vector2 _p1, Vector2 _p2, Vector2 _p3)
		:	p1(_p1), p2(_p2), p3(_p3),
			e1(_p1, _p2), e2(_p2, _p3), e3(_p3, _p1), isBad(false)
		{}

        bool containsVertex(Vector2 v) const
		{
			return almost_equal(p1, v) || almost_equal(p2, v) || almost_equal(p3, v);
		}

        bool circumCircleContains(const Vector2 &v) const
		{
            const double ab = p1.norm2();
            const double cd = p2.norm2();
            const double ef = p3.norm2();

            const double circum_x = (ab * (p3.y - p2.y) + cd * (p1.y - p3.y) + ef * (p2.y - p1.y)) /
                    (p1.x * (p3.y - p2.y) + p2.x * (p1.y - p3.y) + p3.x * (p2.y - p1.y));
            const double circum_y = (ab * (p3.x - p2.x) + cd * (p1.x - p3.x) + ef * (p2.x - p1.x)) /
                    (p1.y * (p3.x - p2.x) + p2.y * (p1.x - p3.x) + p3.y * (p2.x - p1.x));

            const Vector2 circum{half(circum_x), half(circum_y)};
            const double circum_radius = p1.dist2(circum);
            const double dist = v.dist2(circum);
			return dist <= circum_radius;
		}

        Vector2 p1;
        Vector2 p2;
        Vector2 p3;
        Edge e1;
        Edge e2;
        Edge e3;
		bool isBad;
};

#endif
