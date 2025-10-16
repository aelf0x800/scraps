/*
 * pascal_multi.cpp - Asynchronous Pascal's triangle calculator
 */

#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <future>
#include <iostream>
#include <unordered_map>
#include <vector>

using boost::multiprecision::number;
using boost::multiprecision::cpp_int_backend;
using boost::multiprecision::unsigned_magnitude;
using boost::multiprecision::checked;

// Primitive integer types
typedef int_least32_t I32;
typedef uint_least64_t U64;

// A 16384-bit unsigned integer type
typedef number<cpp_int_backend<16384, 16384, unsigned_magnitude, checked, void>> CU16384;

// Type for storing the triangle
typedef std::vector<CU16384> Row;
typedef std::vector<Row> Triangle;

// Base functions used for the calculations
CU16384 Factorial(CU16384 n) { return n <= 1 ? 1 : n * Factorial(n - 1); }
CU16384 Combination(CU16384 n, CU16384 r) { return Factorial(n) / (Factorial(r) * Factorial(n - r)); } 

// Function for calculating a row of Pascal's triangle
Row CalculateRow(U64 n)
{
    Row row{};
    for (U64 i{}; i <= n; i++)
	row.push_back(Combination(n, i));
    std::cout << "Calculated row " << n << std::endl;
    return row;
}

// Get current time in milliseconds
U64 GetTimeMs()
{
    using std::chrono::milliseconds;
    using std::chrono::duration_cast;
    using std::chrono::system_clock;

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
 
I32 main()
{
    // Start the "stopwatch"
    U64 stopwatchStart{ GetTimeMs() };
    
    // Generate the Pascal's triangle
    Triangle triangle{}; 
    for (U64 i{}; i <= 1000; i++)
	triangle.push_back(CalculateRow(i));

    // Stop the "stopwatch"
    U64 stopwatchStop{ GetTimeMs() };
			  
    // Print the results
    for (const Row& row : triangle)
    {
	for (const CU16384& value : row)
	    std::cout << value << " ";
	std::cout << std::endl;
    }

    // Print the time taken to calculate
    std::cout << "Took " << (stopwatchStop - stopwatchStart) << " ms" << std::endl;
}
