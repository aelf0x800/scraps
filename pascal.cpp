#include <boost/multiprecision/cpp_int.hpp>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

using boost::multiprecision::uint1024_t;

using boost::multiprecision::number;
using boost::multiprecision::cpp_int_backend;
using boost::multiprecision::unsigned_magnitude;
using boost::multiprecision::checked;

typedef number<cpp_int_backend<8192, 8129, unsigned_magnitude, checked, void>> checked_uint8192_t;

checked_uint8192_t factorial(checked_uint8192_t n) { return n <= 1 ? 1 : n * factorial(n - 1); }
checked_uint8192_t combination(checked_uint8192_t n, checked_uint8192_t r) { return factorial(n) / (factorial(r) * factorial(n - r)); } 
checked_uint8192_t permutation(checked_uint8192_t n, checked_uint8192_t r) { return factorial(n) / factorial(n - r); }

int main()
{
    std::ofstream output{ "output.txt" };
    
    // Pascal's triangle to 170 rows
    for (checked_uint8192_t i{}; i <= 1000; i++)
    {
	std::vector<checked_uint8192_t> row{};
	for (checked_uint8192_t j{}; j <= i; j++)
	    row.push_back(combination(i, j));

	std::string rowString{};
	for (const checked_uint8192_t n : row)
	    output << n <<  " ";
	output << '\n';
    }

    output.close();
}
