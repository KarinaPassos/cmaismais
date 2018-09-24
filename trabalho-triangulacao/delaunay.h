#ifndef H_DELAUNAY
#define H_DELAUNAY

#include "vector2.h"
#include "edge.h"
#include "triangle.h"

#include <vector>
#include <algorithm>

class Delaunay
{
	public:
        Triangle calculateSuperTriangle(const std::vector<Vector2> &vertices) {
            // Determinate the super triangle
            double minX = vertices[0].x;
            double minY = vertices[0].y;
            double maxX = minX;
            double maxY = minY;

            for(std::size_t i = 0; i < vertices.size(); ++i)
            {
                if (vertices[i].x < minX) minX = vertices[i].x;
                if (vertices[i].y < minY) minY = vertices[i].y;
                if (vertices[i].x > maxX) maxX = vertices[i].x;
                if (vertices[i].y > maxY) maxY = vertices[i].y;
            }

            const double dx = maxX - minX;
            const double dy = maxY - minY;
            const double deltaMax = std::max(dx, dy);
            const double midx = half(minX + maxX);
            const double midy = half(minY + maxY);

            const Vector2 p1{midx - 20 * deltaMax, midy - deltaMax};
            const Vector2 p2{midx, midy + 20 * deltaMax};
            const Vector2 p3{midx + 20 * deltaMax, midy - deltaMax};
            return Triangle(p1, p2, p3);
        }

        const std::vector<Edge> getPolygonsFromTriangles(std::vector<Triangle>& triangles, Vector2 p) {
            std::vector<Edge> polygon;
            for(auto & t : triangles)
            {
                if(t.circumCircleContains(p))
                {
                    t.isBad = true;
                    polygon.push_back(t.e1);
                    polygon.push_back(t.e2);
                    polygon.push_back(t.e3);
                }
            }
            return polygon;
        }

        void removeDuplicatedVertexFromPolygon(std::vector<Edge>& polygon) {
            for(auto e1 = begin(polygon); e1 != end(polygon); ++e1)
            {
                for(auto e2 = e1 + 1; e2 != end(polygon); ++e2)
                {
                    if(almost_equal(*e1, *e2))
                    {
                        e1->isBad = true;
                        e2->isBad = true;
                    }
                }
            }

            polygon.erase(std::remove_if(begin(polygon), end(polygon), [](Edge &e){
                return e.isBad;
            }), end(polygon));
        }

        void removeBadTriangles(std::vector<Triangle>& triangles) {
            triangles.erase(
                std::remove_if(
                    begin(triangles), end(triangles),
                    [](Triangle &t){ return t.isBad; }),
                end(triangles)
            );
        }

        void removeSuperTriangles(std::vector<Triangle>& triangles, Triangle superTriangle) {
            triangles.erase(
                std::remove_if(
                    begin(triangles), end(triangles),
                    [superTriangle](Triangle &t){
                        return  t.containsVertex(superTriangle.p1) ||
                                t.containsVertex(superTriangle.p2) ||
                                t.containsVertex(superTriangle.p3); }),
                end(triangles)
            );
        }

        const std::vector<Triangle> triangulate(const std::vector<Vector2> &vertices)
		{
            auto superTriangle = calculateSuperTriangle(vertices);

			// Create a list of triangles, and add the supertriangle in it
            std::vector<Triangle> triangles;
            triangles.push_back(superTriangle);

            for(auto vertex : vertices)
			{
                std::vector<Edge> polygon = getPolygonsFromTriangles(triangles, vertex);
                removeBadTriangles(triangles);

                // usando iteradores porque preciso do indice dos elementos.
                removeDuplicatedVertexFromPolygon(polygon);

                for(const auto& e : polygon) {
                    triangles.push_back(Triangle(e.p1, e.p2, vertex));
                }
			}
            removeSuperTriangles(triangles, superTriangle);
            return triangles;
		}
};

#endif
