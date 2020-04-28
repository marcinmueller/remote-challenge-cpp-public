#pragma once

#include <cassert>

namespace chal {

	struct Point {
		double x;
		double y;

		Point(double _x, double _y) noexcept :
			x{_x},
			y{_y}
		{}

		auto operator[](size_t i) const noexcept
			-> const double&
		{
			if (i == 0) { return x; }
			if (i == 1) { return y; }
			assert(false);
		}

		auto operator[] (size_t i) noexcept
			-> double&
		{
			//avoding code duplication à la Scott Meyers: https://stackoverflow.com/a/123995/8038465
			return const_cast<double&>(const_cast<const Point&>(*this)[i]);
		}
	};

	auto operator==(const Point& a, const Point& b)
		-> bool
	{
		return a.x == b.x and a.y == b.y;
	}
} //namespace chal