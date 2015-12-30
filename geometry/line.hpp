/* Copyright (c) 2015, Niklas Hauser
 * All Rights Reserved.
 *
 * The file is part of the upainter library and is released under the GPLv3
 * license. See the file `LICENSE` for the full license governing this code.
 * ------------------------------------------------------------------------ */

#ifndef MODM_GES_LINE_HPP
#define MODM_GES_LINE_HPP

#include <xpcc/math/geometry/vector2.hpp>
#include "point.hpp"

namespace modm
{

namespace ges
{

class Line
{
public:
	inline
	Line() :
		p1(0,0), p2(0,0) {}

	inline
	Line(coord_t x1, coord_t y1, coord_t x2, coord_t y2) :
		p1(x1, y1), p2(x2, y2) {}

	inline
	Line(const Point &p1, const Point &p2) :
		p1(p1.vector), p2(p2.vector) {}

	inline
	Line(const Point &p) :
		p1(0,0), p2(p.vector) {}

	inline
	Line(const Line &l) :
		p1(l.p1), p2(l.p2) {}


	inline Rect
	getBounds() const
	{ return Rect(Point(p1), Point(p2)); }


	inline coord_t
	getDx() const
	{ return (p2.getX() - p1.getX()); }

	inline coord_t
	getDy() const
	{ return (p2.getY() - p1.getY()); }

	inline Point
	getDelta() const
	{ return (p2 - p1); }


	inline Point
	getP1() const
	{ return p1; }

	inline Point
	getP2() const
	{ return p2; }


	inline void
	setP1(const Point &p1)
	{ this->p1 = p1.vector; }

	inline void
	setP2(const Point &p2)
	{ this->p2 = p2.vector; }

	inline void
	setPoints(const Point &p1, const Point &p2)
	{ this->p1 = p1.vector; this->p2 = p2.vector; }


	inline coord_t
	getX1() const
	{ return p1.getX(); }

	inline coord_t
	getY1() const
	{ return p1.getY(); }

	inline coord_t
	getX2() const
	{ return p2.getX(); }

	inline coord_t
	getY2() const
	{ return p2.getY(); }


	inline void
	setLine(coord_t x1, coord_t y1, coord_t x2, coord_t y2)
	{ p1.set(x1, y1); p2.set(x2, y2); }


	inline float
	getLength() const
	{ return Point(p1).distance(p2); }

	inline uint32_t
	getLengthSquared() const
	{ return Point(p1).distanceSquared(p2); }


	inline void
	translate(const Point &offset)
	{
		p1 += offset.vector;
		p2 += offset.vector;
	}

	inline void
	translate(coord_t dx, coord_t dy)
	{
		p1 += Vector(dx, dy);
		p2 += Vector(dx, dy);
	}


	inline Line
	translated(const Point &offset) const
	{
		return Line(p1 + offset.vector,
					p2 + offset.vector);
	}

	inline Line
	translated(coord_t dx, coord_t dy) const
	{
		return Line(p1 + Vector(dx, dy),
					p2 + Vector(dx, dy));
	}

	inline Line
	normalized() const
	{
		Line line = *this;
		if (unlikely(getX2() < getX1())) {
			line.p2 = p1;
			line.p1 = p2;
		}
		return line;
	}

	inline bool operator == (const Line &rhs) const
	{ return (p1 == rhs.p1 and p2 == rhs.p2); }
	inline bool operator != (const Line &rhs) const
	{ return (p1 != rhs.p1 or p2 != rhs.p2); }

	inline bool
	isNull() const
	{ return (p1 == p2); }

private:
	Vector p1;
	Vector p2;

	friend class Rect;
};

} // namespace ges

} // namespace modm

#endif // MODM_GES_LINE_HPP
