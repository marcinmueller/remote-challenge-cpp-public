#include <iostream>
#include <string>
#include <vector>

#include "input_output.h"
#include "challenge_function.h"
#include "point.h"

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "USAGE: " << argv[0] << " [INPUT_FILE] [OUTPUT_FILE]" << std::endl;
		return -1;
	}

	auto input_file = std::string{argv[1]};
	auto output_file = std::string{argv[2]};

	std::vector<chal::Point> input_polygon = chal::read_polygon_from_json(input_file);
	if (input_polygon.size() < 3) {
		std::cerr << "Input file " << input_file << " must contain at least 3 points" << std::endl;
		return -1;
	}

	std::vector<chal::Point> result_polygon = chal::do_the_challenge_thing(input_polygon);

	chal::write_point_vector_to_json(result_polygon, output_file);
}