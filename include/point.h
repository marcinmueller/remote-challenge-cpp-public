#pragma once

#include <cassert>

namespace chal {

	struct Point {
		using value_type = double;

		value_type x;
		value_type y;

		Point(value_type _x, value_type _y) noexcept :
			x{_x},
			y{_y}
		{}

		auto operator[](size_t i) const noexcept
			-> const value_type&
		{
			if (i == 0) { return x; }
			if (i == 1) { return y; }
			assert(false);
		}

		auto operator[] (size_t i) noexcept
			-> value_type&
		{
			//avoding code duplication à la Scott Meyers: https://stackoverflow.com/a/123995/8038465
			return const_cast<value_type&>(const_cast<const Point&>(*this)[i]);
		}
	};

	inline Point operator-(const Point& a, const Point& b) {
		return {a.x - b.x, a.y - b.y};
	}

	inline bool operator==(const Point& a, const Point& b) {
		return a.x == b.x and a.y == b.y;
	}
	
	inline bool operator<(const Point& a, const Point& b) {
		if (a.x < b.x)
			return true;
		if (a.x == b.x)
			return a.y < b.y;
		return false;
	}
	
	inline bool operator>(const Point& a, const Point& b) {
		if (a.x > b.x)
			return true;
		if (a.x == b.x)
			return a.y > b.y;
		return false;
	}

	inline Point point_between(const Point& A, const Point& B, const Point& C) {
		const auto AB = B - A;
		const auto m = AB.y / AB.x;
		return {C.x, A.y + m * (C.x - A.x)};
	}

} //namespace chal