#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "squarematrix.h"
#include "intelement.h"

/**
 *  @file squarematrix_tests.cpp
 *  @version 2.0
 *  @brief Test Case for SquareMatrix class
 *  @author Niko Lehto
 *  */

 /**
 *  \brief Matrix unit tests for SquareMatrix, focuses to test operators - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("SquareMatrix little ones", "[SquareMatrix]") {
	SquareMatrix a("[[1,2][3,4]]")
		, b("[[2,3][4,5]]")
		, c("[[2,3,4][4,5,6][1,2,63]]")
		, result1("[[3,5][7,9]]")
		, result3("[[10,13][22,29]]")
		, clone_constructed_a = a
		, clone_constructed_b(b)
		, empty_constructed;

	REQUIRE(a == clone_constructed_a);

	std::string a_string = "[[1,2][3,4]]";
	std::string b_string = "[[2,3][4,5]]";
	std::string result3_string = "[[10,13][22,29]]";



	std::stringstream out_1, out_2, out_3, out_4;


	a += b;

	REQUIRE(a == result1);

	a -= b;

	REQUIRE(a == clone_constructed_a);
	a *= b;

	REQUIRE(a == result3);

	out_1 << b;
	out_2 << b_string;

	REQUIRE(out_1.str() == out_2.str());

	out_1.str("");
	out_2.str("");

	out_1 << a;
	out_2 << result3_string;

	REQUIRE(out_1.str() == out_2.str());

	result3.print(out_3);
	REQUIRE(out_1.str() == out_3.str());

	out_4 << result3.toString();
	REQUIRE(out_1.str() == out_4.str());

	REQUIRE(clone_constructed_a + b == result1);

	REQUIRE(result1 - b == clone_constructed_a);

	REQUIRE(clone_constructed_a * b == result3);

	REQUIRE_THROWS_WITH(clone_constructed_a + c, "operator requires same sized matrices");

	REQUIRE_THROWS_WITH(a * c, "operator requires same sized matrices");

	REQUIRE_THROWS_WITH(a - c, "operator requires same sized matrices");
    REQUIRE_FALSE(a == c);
    REQUIRE_FALSE(a == b);

    // re-assign test

    a = SquareMatrix("[[1]]");

    REQUIRE(a == SquareMatrix("[[1]]"));

}

 /**
 *  \brief Matrix unit tests for SquareMatrix, focuses into string constructor - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("SquareMatrix String constructor", "[SquareMatrixN-1]")
{
    struct TestContainer {
      std::string data;
      std::string definition;

      TestContainer(std::string a, std::string b)
        : data(a), definition(b) {}
    };

	std::vector<std::string> corrects = {};
	std::vector<TestContainer> invalids = {};


    corrects.push_back("[[1]]"); // 1x1
	corrects.push_back("[[1,2,5][3,4,6][5,6,7]]"); // 3x3
    corrects.push_back("[[-1,2,+5,6,-8][3,4,6,-1,5][5,6,7,1,-4][3,4,6,-1,5][5,6,7,1,-4]]"); // 5x5 with leading + or - characters

	invalids.push_back(TestContainer("[[1.1,2,+0.31][-13,-1.4,6.01][5.11,.5,-.7]]", "Element not an integer, or it contains character"));

	invalids.push_back(TestContainer("a[2]]", "Illegal character in matrix"));

	invalids.push_back(TestContainer("[[]]", "Too few characters to be a Matrix"));

	invalids.push_back(TestContainer("1[2]]", "Should start \"[[\", Started"));

	invalids.push_back(TestContainer("[[2]1", "Should end \"]]\", Ended \""));

	invalids.push_back(TestContainer("[[1,2,]1[3,4,6][5,6,7]]", "Element starts with invalid character"));

	invalids.push_back(TestContainer("[[1,2][4,6]]5,6,7]]", "Ends too soon, row \"][\" expected"));

	invalids.push_back(TestContainer("[[1,2][4,6]]]", "")); // no specific expection probably throws 'Element not an integer, or it contains character' but does not matter

	invalids.push_back(TestContainer("[[[1,2][4,6]]", "")); // no specific expection probably throws 'Element starts with invalid character' but does not matter

	invalids.push_back(TestContainer("[[1,2,5][3,4,6]]", "Not a square matrix. Found:"));

	invalids.push_back(TestContainer("[[1,2][3,4][1,2]]", "Not a square matrix. Found:"));

	invalids.push_back(TestContainer("[[1,2,4][3,4,1][1,2]]", "All columns did not have same dimension"));

	invalids.push_back(TestContainer("[[1,2][1,2,4][3,4,1]]", "All columns did not have same dimension"));

	invalids.push_back(TestContainer("[[1.1,2,0.31][-13,-1.4,6.01][5.11,1.5.2,-.7]]", "Element not an integer, or it contains character"));

	invalids.push_back(TestContainer("[[1.1,2,0.31][1-3,-1.4,6.01][5.11,1.5,-.7]]", "Element not an integer, or it contains character"));

	invalids.push_back(TestContainer("[[1.1,2,0.31][+-3,1.4,6.01][5.11,1.5,-.7]]", "Element not an integer, or it contains character"));

	invalids.push_back(TestContainer("[[1.1,2,0.3e][13,1.4,6.01][5.11,1.5,-.7]]", "Illegal character in matrix:"));

	//std::cout << "test corrects: \n\n";
	for (std::string m : corrects)
	{
		REQUIRE_NOTHROW(SquareMatrix(m));
	}

	// implemented lambda and for_each algorithm here, there was no other place where it could be useful and meaningful
    std::for_each(invalids.begin(), invalids.end(),
        [](TestContainer a)
    {
	    REQUIRE_THROWS_WITH(SquareMatrix(a.data), Catch::Matchers::Contains(a.definition));
	});
}

 /**
 *  \brief Matrix unit tests for SquareMatrix, focuses into transpose and big matrice testing - could be used also into performance measurement - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
 /*
TEST_CASE("SquareMatrix BIG TRANSPOSE", "[SquareMatrixN]")
{
    std::stringstream stream1, stream2;
    size_t n = 1000; // tested also with 10000 but it took over 1min to operate with ryzen 1600 - even with release build. probably since there would be 100 000 000 stream operations. but it passed

	stream1 << "[";
	stream2 << "[";
    for(size_t i = 0; i < n; i++)
    {
        stream1 << "[";
        stream2 << "[";
        for(size_t j = 0; j < n; j++)
        {
            if(j != n - 1)
            {
                stream1 << 2*i*n + j << ",";
                stream2 << 2*j*n + i << ",";
            }
            else
            {
                stream1 << 2*i*n + j;
                stream2 << 2*j*n + i;
            }
        }
        stream1 << "]";
        stream2 << "]";
    }
    stream1 << "]";
    stream2 << "]";

    SquareMatrix a(stream1.str());
    SquareMatrix b(stream2.str());

    REQUIRE(a.transpose().transpose() == a);
    REQUIRE(a.transpose() == b);

    SquareMatrix c;
    c = a;
    REQUIRE(c == a);
}
*/
