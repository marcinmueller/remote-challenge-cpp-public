#pragma once

#include <algorithm>
#include <vector>

#include "point.h"
#include "wrapping_iterator.h"

namespace chal {

	constexpr bool ENABLE_TASK2 = true;

	inline auto left_and_right_most_iters(const std::vector<Point>& input_polygon)
	{
		auto itLeft = input_polygon.begin();
		auto itRight = input_polygon.begin();
		for (auto it = std::next(input_polygon.begin()); it != input_polygon.end(); ++it)
		{
			if (*it < *itLeft)
				itLeft = it;
			else if (*it > *itRight)
				itRight = it;
		}
		return std::make_pair(
			wrapping_iterator{input_polygon, itLeft},
			wrapping_iterator{input_polygon, itRight});
	}

	enum class HullType {
		Lower,
		Upper
	};

	template<HullType> struct ComesBefore;
	template<> struct ComesBefore<HullType::Lower> : public std::less<Point::value_type> {};
	template<> struct ComesBefore<HullType::Upper> : public std::greater<Point::value_type> {};

	template<HullType H, typename It>
	inline void create_hull(It it, It itEnd, std::vector<Point>& hull)
	{
		hull.emplace_back(*it);
		for (++it; it != itEnd; ++it) {
			// Check if line to next point would point in backward direction (non-monotone)
			if (ComesBefore<H>()((*it).x, hull.back().x)) {
				// If yes, check if next point is an interior point or should be part of the visible hull
				if (ComesBefore<H>()((*it).y, hull.back().y)) {
					// If it's an outer hull point, remove points from the hull up to the current x coordinate
					do {
						if constexpr (ENABLE_TASK2) {
							// Task 2 extension: truncate previous line(s) up to the current x coordinate
							if (ComesBefore<H>()(hull[hull.size()-2].x, (*it).x)) {
								hull.back() = point_between(hull[hull.size()-2], hull[hull.size()-1], *it);
								break;
							}
						}
						// Remove last hull point
						hull.pop_back();
					} while (ComesBefore<H>()((*it).x, hull.back().x));
				}
				else {
					// If it's an iterior point, we can discard it
					if constexpr (ENABLE_TASK2) {					
						// Task 2 extension: create line to next hull point from the current x coordinate
						auto itNext = std::next(it);
						if (ComesBefore<H>()(hull.back().x, (*itNext).x)) {
							hull.emplace_back(point_between(*it, *itNext, hull.back()));
						}
					}
					continue;
				}
			}			
			// Finally append the point to the hull
			hull.emplace_back(*it);
		}
	}

	inline std::vector<Point> do_the_challenge_thing(const std::vector<Point>& input_polygon)
	{
		// Further optimizations to explore:
		//
		// Check in case input is already x-monoton
		//	* no need to create a copy for the output, could return an iterator to the left-most point only
		//
		// Use multi-threading:
		// 	* finding left/right-most points can be paralellized over N threads using a reduce type algorithm
		//	* computing the lower and upper hulls can be trivially run simultanously on 2 threads
		//		- could return 2 vectors for upper/lower hull to avoid further copies
		//
		// Implement a function with writes JSON directly to ostream instead of creating the nlohmann::json::JSON data structures in memory
		//	* JSON is a simple enough format to be able to manually write it

		// Compute the left and rightmost points
		auto [itLeft, itRight] = left_and_right_most_iters(input_polygon);

		// Create output container to store new monoton polygon
		std::vector<Point> output_polygon;
		output_polygon.reserve(input_polygon.size());

		// Compute lower and upper hulls
		create_hull<HullType::Lower>(itLeft, itRight, output_polygon);
		create_hull<HullType::Upper>(itRight, itLeft, output_polygon);

		return output_polygon;
	}

} //namespace chal