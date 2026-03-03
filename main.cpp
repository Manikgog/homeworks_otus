#include <iostream>
#include "min.h"
#include "max.h"
#include "mean.h"
#include "stddev.h"
#include "percentile.h"





int main() {

	// const size_t statistics_count = 6;
	// IStatistics *statistics[statistics_count];
	//
	// statistics[0] = new Min{};
	// statistics[1] = new Max{};
	// statistics[2] = new Mean{};
	// statistics[3] = new StdDev{};
	// statistics[4] = new Percentile90{};
	// statistics[5] = new Percentile95{};
	//
	// double val = 0;
	//
	// while (std::cin >> val) {
	// 	for (size_t i = 0; i < statistics_count; ++i) {
	// 		statistics[i]->update(val);
	// 	}
	// }
	//
	// //Handle invalid input data
	// if (!std::cin.eof() && !std::cin.good()) {
	// 	std::cerr << "Invalid input data\n";
	// 	return 1;
	// }
	//
	// // Print results if any
	// for (size_t i = 0; i < statistics_count; ++i) {
	// 	std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	// }
	//
	// // Clear memory - delete all objects created by new
	// for (size_t i = 0; i < statistics_count; ++i) {
	// 	delete statistics[i];
	// }

	Max max;
	max.update(-1);
	std::cout << "max: " << max.eval() << std::endl;

	return 0;
}