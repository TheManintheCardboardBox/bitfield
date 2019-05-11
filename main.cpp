#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "bitfield.hpp"

bool compare_files(const std::string& file1, const std::string& file2);

int main()
{
	std::size_t N;

	std::cout << "Input bitfield length: ";
	if (scanf_s("%zu", &N) != 1)
		throw std::invalid_argument("Invalid input.");

	lab::bitfield bf(N);
	std::vector<std::size_t> primes = bf.eratosthenes();

	std::ofstream file;
	file.open("eratosthenes.txt");
	std::string delim = "";
	for (std::size_t& prime : primes) {
		file << delim << prime;
		delim = ", ";
	}
	file.close();

	assert(compare_files("eratosthenes.txt", "testdata.txt"));

	return 0;
}

bool compare_files(const std::string& file1, const std::string& file2)
{
	std::ifstream fs1(file1);
	std::ifstream fs2(file2);

	std::string line1, line2;

	std::getline(fs1, line1);
	std::getline(fs2, line2);

	std::size_t length = line1.length() < line2.length() ? line1.length() : line2.length();

	if (length == 0 || line1.compare(0, length, line2, 0, length) != 0)
		return false;

	fs1.close();
	fs2.close();

	return true;
}
