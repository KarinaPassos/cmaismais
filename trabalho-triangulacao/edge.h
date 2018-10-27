#ifndef H_EDGE
#define H_EDGE

#include "vector2.h"

class Edge
{
	public:
        Edge(const Vector2 &p1, const Vector2 &p2) : p1(p1), p2(p2) {}
        Edge(const Edge &e) : p1(e.p1), p2(e.p2) {}

        Vector2 p1;
        Vector2 p2;

        bool isBad = false;
};

#endif

