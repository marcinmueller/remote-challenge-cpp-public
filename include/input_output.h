#pragma once

#include <exception>
#include <fstream>
#include <iomanip>
#include <vector>

#include <json.hpp>

#include "point.h"

namespace chal {
	using JSON = nlohmann::json;

	inline auto read_polygon_from_json(const std::string& input_file)
		-> std::vector<Point>
	{
		auto stream = std::ifstream{input_file};
		if (not stream.is_open()) {
			throw std::runtime_error("Could not open file '" + input_file + "'!");
		}

		auto json = JSON{};
		stream >> json;

		const auto& points_json = json["points"];

		auto result = std::vector<Point>{};
		result.reserve(points_json.size());
		for (const auto& point_json : points_json) {
			result.emplace_back(point_json["x"], point_json["y"]);
		}

		return result;
	}

	inline void write_point_vector_to_json(const std::vector<Point>& points, const std::string& output_file)
	{
		auto point_jsons = std::vector<JSON>(points.size());
		for (size_t i = 0; i < points.size(); ++i) {
			const auto& point = points[i];
			point_jsons[i] = {
				{"x", point.x},
				{"y", point.y}
			};
		}

		auto result_json = JSON{};
		result_json["points"] = point_jsons;

		auto stream = std::ofstream{output_file};
		if (not stream.is_open()) {
			throw std::runtime_error("Could not open file '" + output_file + "'!");
		}

		//overloaded for pretty printing
		stream << std::setw(2) << result_json;
	}
} //namespace chal