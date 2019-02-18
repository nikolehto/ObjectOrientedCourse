#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "concretematrix.h"
#include "symbolicmatrix.h"

/**
 *  @file tests.cpp
 *  @version 3.0
 *  @brief Test Case for all classes
 *  @author Niko Lehto
 *  */

/**
*  \brief Unit tests for IntElement, will run in main generated by catch.hpp
*  \return 0 if tests passes
*/
 TEST_CASE("IntElement", "[isValidInt]") {

	REQUIRE_THROWS_WITH(IntElement("3,"), "Element not an integer, or it contains character");
    REQUIRE_THROWS_WITH(IntElement(",3"), "Element starts with invalid character");
    REQUIRE_THROWS_WITH(IntElement("++3"), "Element starts with invalid character");
    REQUIRE_NOTHROW(IntElement("+3"));
    REQUIRE_NOTHROW(IntElement("3"));

	int a, b, result;
	std::stringstream out_1, out_2;

	a = 3;
	b = 5;

	IntElement aie(a), bie(b), result_ie(0), result2_ie(0);

    REQUIRE_NOTHROW(std::shared_ptr<Element>(aie.clone()));

    std::shared_ptr<Element> test_ptr(aie.clone());
    REQUIRE(*std::static_pointer_cast<IntElement>(test_ptr) == aie);

    IntElement saie("3");

    REQUIRE(saie == a);

	a += b;
	aie += bie;

	REQUIRE(a == aie.getVal());

	a -= b;
	aie -= bie;

	REQUIRE(a == aie.getVal());

	a *= b;
	aie *= bie;

	REQUIRE(a == aie.getVal());

	out_1 << a;
	out_2 << aie;

	REQUIRE(out_1.str() == out_2.str());

	result = a + b;
	result_ie = aie + bie;

	REQUIRE(result_ie == IntElement(result));

	result = a - b;
	result_ie = aie - bie;

	REQUIRE(result_ie == IntElement(result));

	result = a * b;
	result2_ie.setVal(result);
	result_ie = aie * bie;

	REQUIRE(result_ie == result2_ie);
}

/**
*  \brief Unit tests for VariableElement, will run in main generated by catch.hpp
*  \return 0 if tests passes
*/
 TEST_CASE("VariableElement", "[isValidVar]") {
    // String constructor
	REQUIRE_THROWS_WITH(VariableElement("aa"), "Element empty or not a char");
    REQUIRE_THROWS_WITH(VariableElement("abc"), "Element empty or not a char");
    REQUIRE_NOTHROW(VariableElement("a"));
    REQUIRE_NOTHROW(VariableElement("3")); // not intended, but not dangerous if handled correctly - actually "3" is a char as well as integer

    // Char constructor
	char a, b;
	a = 'a';
	b = 'b';
	VariableElement aie(a), bie(b);

    // VariableElement Clone Constructor
    std::shared_ptr<Element> test_ptr(aie.clone());

    //Element Clone Constructor
    std::shared_ptr<Element>  test2_ptr(test_ptr->clone());
    VariableElement ve = *std::static_pointer_cast<VariableElement>(test2_ptr);

    REQUIRE(ve == aie);

    // string operator
    std::stringstream out_1, out_2, out_3;
    out_1 << a;
	out_2 << aie;
    out_3 << *test_ptr;

	REQUIRE(out_1.str() == out_2.str());
    REQUIRE(out_1.str() == out_3.str());


	// empty Constructor and setVal getVal
    VariableElement vale;
    vale.setVal('a');
    REQUIRE(vale.getVal() == 'a');
    REQUIRE(vale == a);

    // valuation test
    Valuation valuation;
    valuation['a'] = 3;
    REQUIRE(aie.evaluate(valuation) == 3);
}

/**
*  \brief Unit tests for CompositeElement, will run in main generated by catch.hpp
*  \return 0 if tests passes
*/
 TEST_CASE("CompositeElement", "[isValidCo]") {
        // parameterized consturctor
        char a, b;
        a = 'a';
        b = 'b';
        VariableElement aie(a), bie(b);

        CompositeElement ce_a_plus_b(aie, bie, std::plus<int>(), '+');
        CompositeElement ce_a_minus_b(aie, bie, std::minus<int>(), '-');
        CompositeElement ce_a_multiplies_b(aie, bie, std::multiplies<int>(), '*');


        // VariableElement Clone Constructor
        std::shared_ptr<Element> test_ptr(ce_a_plus_b.clone());

        //Element Clone Constructor
        std::shared_ptr<Element>  test2_ptr(test_ptr->clone());
        CompositeElement ve = *std::static_pointer_cast<CompositeElement>(test2_ptr);

        // Equality Operator
        REQUIRE(ve == ce_a_plus_b);

        // Equality Operator different types
        REQUIRE(!(ve == aie));

        // string operator
        std::stringstream out_1, out_2, out_3;
        out_1 << "(" << a << "+" << b << ")";
        out_2 << ce_a_plus_b;
        out_3 << *test_ptr;

        REQUIRE(out_1.str() == out_2.str());
        REQUIRE(out_1.str() == out_3.str());

        // valuation test
        Valuation valuation;
        valuation['a'] = 3;
        valuation['b'] = 4;
        REQUIRE(ce_a_plus_b.evaluate(valuation) == 7);
        REQUIRE(ce_a_minus_b.evaluate(valuation) == -1);
        REQUIRE(ce_a_multiplies_b.evaluate(valuation) == 12);

}

/**
*  \brief Unit tests for elements, will run in main generated by catch.hpp
*  \return 0 if tests passes
*/
 TEST_CASE("Elements", "[ElementCrosscomparison]")
 {
    IntElement intE = IntElement(1);
    VariableElement varE = VariableElement('1');
    CompositeElement compE(intE, varE, std::plus<int>(), '+');
    CompositeElement anothercompE = CompositeElement(intE, varE, std::plus<int>(), '+');
    CompositeElement yetanothercompE = CompositeElement(intE, varE, std::plus<int>(), '-');

    std::shared_ptr<IntElement> iep = std::make_shared<IntElement>(intE);
    std::shared_ptr<Element> eep  = std::static_pointer_cast<Element>(iep);

    std::shared_ptr<CompositeElement> coe = std::make_shared<CompositeElement>(compE);
    std::shared_ptr<Element> cee  = std::static_pointer_cast<Element>(coe);

    REQUIRE(!(intE == varE));
    REQUIRE(!(intE == compE));
    REQUIRE(!(varE == intE));
    REQUIRE(!(varE == compE));
    REQUIRE(!(compE == intE));
    REQUIRE(!(compE == varE));
    REQUIRE(!(compE == yetanothercompE));

    REQUIRE(compE == anothercompE);
    REQUIRE(*eep == intE);
    REQUIRE(*cee == compE);
    REQUIRE(!(*cee == *eep));
 }

 /**
 *  \brief Matrix unit tests for ConcreteSquareMatrix, focuses to test operators - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("ConcreteSquareMatrix little ones", "[ConcreteSquareMatrix]") {
	ConcreteSquareMatrix a("[[1,2][3,4]]")
		, b("[[2,3][4,5]]")
		, c("[[2,3,4][4,5,6][1,2,63]]")
		, result1("[[3,5][7,9]]")
		, result3("[[10,13][22,29]]")
		, clone_constructed_a = a
		, clone_constructed_b(b)
		, empty_constructed;

	REQUIRE(a == clone_constructed_a);
    REQUIRE(b == clone_constructed_b);
    REQUIRE(!(a == b));
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

    // test empty matrix to string
    ConcreteSquareMatrix emptyM;

    REQUIRE(emptyM.toString() == "");
}

 /**
 *  \brief Matrix unit tests for SymbolicSquareMatrix, focuses to test operators - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("SymbolicSquareMatrix little ones", "[ConcreteSquareMatrix]") {
    Valuation valuation;
    valuation['a'] = 2;
    valuation['b'] = 3;
    valuation['c'] = 4;

    std::string a_string = "[[1,a][b,4]]"
        , b_string = "[[2,3][4,5]]"
        , c_string = "[[b,3,a][a,a,6][1,c,63]]"
        , d_string = "[[3,3,2][2,2,6][1,4,63]]"
        , e_string = "[[a,e,f][1,2,3][1,2,33]]"
        , apb_string = "[[(1+2),(a+3)][(b+4),(4+5)]]"
        , amb_string = "[[(1-2),(a-3)][(b-4),(4-5)]]"
        , aMb_string = "[[((1*2)+(a*4)),((1*3)+(a*5))][((b*2)+(4*4)),((b*3)+(4*5))]]";

	SymbolicSquareMatrix a(a_string)
		, b(b_string)
		, c(c_string)
		, e(e_string)
		, clone_constructed_a = a
		, clone_constructed_b(b)
		, empty_constructed;

	REQUIRE(a == clone_constructed_a);
    REQUIRE(b == clone_constructed_b);
    REQUIRE(!(a == b));


    REQUIRE_THROWS_WITH(a+c, "operator requires same sized matrices");
    REQUIRE_THROWS_WITH(a-c, "operator requires same sized matrices");
    REQUIRE_THROWS_WITH(a*c, "operator requires same sized matrices");

	std::stringstream out_1, out_2, out_1p2, out_1m2, out_1M2;

	out_1 << b;
	out_2 << b_string;
	//plus calc
    out_1p2 << a + b;
    //minus calc
    out_1m2 << a - b;
    //multiplication
    out_1M2 << a * b;

	REQUIRE(out_1.str() == out_2.str());
	REQUIRE(out_1p2.str() == apb_string);
	REQUIRE(out_1m2.str() == amb_string);
	REQUIRE(out_1M2.str() == aMb_string);

	out_1.str("");
	out_2.str("");

	out_1 << a;
	out_2 << a_string;

	REQUIRE(out_1.str() == out_2.str());

	std::stringstream out_3, out_4;

	a.print(out_3);
	REQUIRE(out_1.str() == out_3.str());

	out_4 << a.toString();
	REQUIRE(out_1.str() == out_4.str());

    // test empty matrix to string
    SymbolicSquareMatrix emptyM;

    REQUIRE(emptyM.toString() == "");

    REQUIRE_NOTHROW(ConcreteSquareMatrix(d_string));
    ConcreteSquareMatrix concrete_d(d_string);

    REQUIRE_NOTHROW(c.evaluate(valuation));
    ConcreteSquareMatrix evaluated_c = c.evaluate(valuation);

    REQUIRE(concrete_d == evaluated_c);

    REQUIRE_THROWS_WITH(e.evaluate(valuation), "Symbolic variable cannot be found from given Valuation v");
    // evaluate

}


 /**
 *  \brief Matrix unit tests for ConcreteSquareMatrix and SymbolicSquareMatrix, focuses to test assignments and constructors - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("CopyNMoveConstructorsAndAssignments", "[COPYnASSIGN]")
{
    std::string a_string = "[[1,2][3,4]]"
        , b_string = "[[1]]"
        , c_string = "[[3,4][5,6]]";

    ConcreteSquareMatrix a(a_string)
            , b(b_string)
            , c(c_string);

    SymbolicSquareMatrix as(a_string)
        , bs(b_string)
        , cs(c_string);

    // re-assign test
    a = ConcreteSquareMatrix(b);
    as = SymbolicSquareMatrix(bs);
    REQUIRE(a == b);
    REQUIRE(as == bs);

    // move assignment
    { // limit scope
        ConcreteSquareMatrix temp;
        SymbolicSquareMatrix temps;
        //std::cout << temp.elements.at(0).at(0).use_count(); need elements to be public or getter ( not secure but can be use to follow reference counts) getReferenceCount function could be safer

        temp = std::move(a);
        temps = std::move(as);

        REQUIRE(temp == b);
        REQUIRE(temps == bs);
    } // The values of a should be deleted

    REQUIRE(!(a == b));
    REQUIRE(!(as == bs));
    // and they are

    // copy assignment
    a = ConcreteSquareMatrix("[[1]]");
    as = SymbolicSquareMatrix("[[1]]");
    IntElement intE = IntElement(1);
    VariableElement varE = VariableElement('a');
    CompositeElement compE(intE, varE, std::plus<int>(), '+');
    { // limit scope
        ConcreteSquareMatrix temp;
        SymbolicSquareMatrix temps;
        IntElement tempintE = intE;
        VariableElement tempvarE = varE;
        CompositeElement tempcompE = compE;
        //std::cout << temp.elements.at(0).at(0).use_count(); need elements to be public or getter ( not secure but can be use to follow reference counts) getReferenceCount function could be safer
        temp = a;
        temps = as;
        REQUIRE(temp == ConcreteSquareMatrix("[[1]]"));
        REQUIRE(temps == SymbolicSquareMatrix("[[1]]"));
        REQUIRE(tempintE == IntElement(1));
        REQUIRE(tempvarE == VariableElement('a'));
        REQUIRE(tempcompE == CompositeElement(intE, varE, std::plus<int>(), '+'));
    } // The values of a should remain

    REQUIRE((a == ConcreteSquareMatrix("[[1]]")));
    REQUIRE((as == SymbolicSquareMatrix("[[1]]")));
    REQUIRE(intE == IntElement(1));
    REQUIRE(varE == VariableElement('a'));
    compE = compE;
    REQUIRE(compE == CompositeElement(intE, varE, std::plus<int>(), '+'));
    // and they are


    // test move constructor
    REQUIRE_NOTHROW(ConcreteSquareMatrix(std::move(b)));
    REQUIRE_NOTHROW(SymbolicSquareMatrix(std::move(bs)));
    // pointers of b is now unreferenced but scope continues -> smart to not use them

    // Full move test
    ConcreteSquareMatrix abc_old(c); // clone
    SymbolicSquareMatrix abc_olds(cs);

    REQUIRE(abc_old == c);
    REQUIRE(abc_olds == cs);

    {  // limit scope
        ConcreteSquareMatrix abc_new(std::move(abc_old)); // move
        SymbolicSquareMatrix abc_news(std::move(abc_olds)); // move
        REQUIRE(abc_new == c);
        REQUIRE(abc_news == cs);
    }

    REQUIRE(!(abc_old == c));
    REQUIRE(!(abc_olds == cs));


    // Full copy test
    c = ConcreteSquareMatrix("[[1,2][3,4]]");
    cs = SymbolicSquareMatrix("[[1,2][3,4]]");

    ConcreteSquareMatrix abcopy_old(c); // clone
    SymbolicSquareMatrix abcopy_olds(cs);

    REQUIRE(abcopy_old == c);
    REQUIRE(abcopy_olds == cs);
    {  // limit scope
        ConcreteSquareMatrix abcopy_new(abcopy_old); // clone
        SymbolicSquareMatrix abcopy_news(abcopy_olds);

        REQUIRE(abcopy_new == c);
        REQUIRE(abcopy_news == cs);
    }

    REQUIRE(abcopy_old == c);
    REQUIRE(abcopy_olds == cs);

    // self assignment test
    c = ConcreteSquareMatrix("[[1]]");

    a = c;
    c = c;
    REQUIRE(c == a);

    cs = SymbolicSquareMatrix("[[1]]");
    as = cs;
    cs = cs;
    REQUIRE(cs == as);

    // self assignment test 2
    c = ConcreteSquareMatrix("[[1]]");
    a = c;
    {  // limit scope
        c = std::move(c); // move
    } // c could be empty if not correct handled

    REQUIRE(c == a);

    // self assignment test 2
    cs = SymbolicSquareMatrix("[[1]]");
    as = cs;
    {  // limit scope
        cs = std::move(cs); // move
    } // c could be empty if not correct handled

    REQUIRE(cs == as);
}


 /**
 *  \brief Matrix unit tests for ConcreteSquareMatrix, focuses into string constructor - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("ConcreteSquareMatrix String constructor", "[ConcreteSquareMatrixN-1]")
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
		REQUIRE_NOTHROW(ConcreteSquareMatrix(m));
	}

	// implemented lambda and for_each algorithm here, there was no other place where it could be useful and meaningful
    std::for_each(invalids.begin(), invalids.end(),
        [](TestContainer a)
    {
	    REQUIRE_THROWS_WITH(ConcreteSquareMatrix(a.data), Catch::Matchers::Contains(a.definition));
	});
}

 /**
 *  \brief Matrix unit tests for SymbolicSquareMatrix, focuses into string constructor - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("SymbolicSquareMatrix String constructor", "[SymbolicSquareMatrixN-1]")
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
    corrects.push_back("[[a,2,+5,6,d][3,4,6,-1,5][5,c,7,1,-4][3,y,6,-1,5][5,6,7,z,-4]]");

	invalids.push_back(TestContainer("[[1.1,2,+0.31][-13,-1.4,6.01][5.11,.5,-.7]]", "Element empty or not a char"));

	invalids.push_back(TestContainer("a[2]]", "Should start \"[[\", Started"));

	invalids.push_back(TestContainer("[[]]", "Too few characters to be a Matrix"));

	invalids.push_back(TestContainer("1[2]]", "Should start \"[[\", Started"));

	invalids.push_back(TestContainer("[[2]1", "Should end \"]]\", Ended \""));

	invalids.push_back(TestContainer("[[1,2,]1[3,4,6][5,6,7]]", "Element empty or not a char"));

	invalids.push_back(TestContainer("[[1,2][4,6]]5,6,7]]", "Ends too soon, row \"][\" expected"));

	invalids.push_back(TestContainer("[[1,2][4,c]]]", "")); // no specific expection probably throws 'Element empty or not a char' but does not matter

	invalids.push_back(TestContainer("[[[1,2][a,6]]", "")); // no specific expection probably throws 'Element empty or not a char' but does not matter

	invalids.push_back(TestContainer("[[1,2,5][3,4,6]]", "Not a square matrix. Found:"));

	invalids.push_back(TestContainer("[[1,2][3,4][1,2]]", "Not a square matrix. Found:"));

	invalids.push_back(TestContainer("[[1,2,4][3,4,1][1,2]]", "All columns did not have same dimension"));

	invalids.push_back(TestContainer("[[1,2][1,2,4][3,4,1]]", "All columns did not have same dimension"));

	invalids.push_back(TestContainer("[[1.1,2,0.31][-13,-1.4,6.01][5.11,1.5.2,-.7]]", "Element empty or not a char"));

	invalids.push_back(TestContainer("[[1.1,2,0.31][1-3,-1.4,6.01][5.11,1.5,-.7]]", "Element empty or not a char"));

	invalids.push_back(TestContainer("[[1.1,2,0.31][+-3,1.4,6.01][5.11,1.5,-.7]]", "Element empty or not a char"));

	invalids.push_back(TestContainer("[[1.1,2,0.3e][13,1.4,6.01][5.11,1.5,-.7]]", "Element empty or not a char"));

	//std::cout << "test corrects: \n\n";
	for (std::string m : corrects)
	{
		REQUIRE_NOTHROW(SymbolicSquareMatrix(m));
	}

	// implemented lambda and for_each algorithm here, there was no other place where it could be useful and meaningful
    std::for_each(invalids.begin(), invalids.end(),
        [](TestContainer a)
    {
	    REQUIRE_THROWS_WITH(SymbolicSquareMatrix(a.data), Catch::Matchers::Contains(a.definition));
	});
}

 /**
 *  \brief Matrix unit tests for ConcreteSquareMatrix, focuses into transpose and big matrice testing - could be used also into performance measurement - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("ConcreteSquareMatrix BIG TRANSPOSE", "[ConcreteSquareMatrixN]")
{
    std::stringstream stream1, stream2;
    size_t n = 50; // tested also with 10000 but it took over 1min to operate with ryzen 1600 - even with release build. probably since there would be 100 000 000 stream operations. but it passed

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

    ConcreteSquareMatrix a(stream1.str());
    ConcreteSquareMatrix b(stream2.str());

    REQUIRE(a.transpose().transpose() == a);
    REQUIRE(a.transpose() == b);

    ConcreteSquareMatrix c;
    c = a;
    REQUIRE(c == a);
}

 /**
 *  \brief Matrix unit tests for SymbolicSquareMatrix, focuses into transpose and big matrice testing - could be used also into performance measurement - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("SymbolicSquareMatrix BIG TRANSPOSE", "[SymbolicSquareMatrixN]")
{
    std::stringstream stream1, stream2;
    size_t n = 50; // tested also with 10000 but it took over 1min to operate with ryzen 1600 - even with release build. probably since there would be 100 000 000 stream operations. but it passed

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

    SymbolicSquareMatrix a(stream1.str());
    SymbolicSquareMatrix b(stream2.str());

    REQUIRE(a.transpose().transpose() == a);
    REQUIRE(a.transpose() == b);

    SymbolicSquareMatrix c;
    c = a;
    REQUIRE(c == a);
}

 /**
 *  \brief Matrix unit tests for SymbolicSquareMatrix and ConcreteMatrix, tests Multiplication and evaluation of big matrice - will run in main generated by catch.hpp
 *  \return 0 if tests passes
 */
TEST_CASE("SQUARE MATRIX BIG MULTIPLICATION", "[BIGMULTI]")
{
    Valuation valuation;
    valuation['a'] = 1;
    valuation['b'] = 2;
    valuation['c'] = 3;
    valuation['d'] = 4;
    valuation['e'] = 5;
    valuation['f'] = 6;
    valuation['g'] = 7;

    ConcreteSquareMatrix con("[[1,2,3,4,5,6,7][1,2,3,4,5,6,7][1,2,3,4,5,6,7][1,2,3,4,5,6,7][1,2,3,4,5,6,7][1,2,3,4,5,6,7][1,2,3,4,5,6,7]]");
    SymbolicSquareMatrix sym("[[a,b,c,d,e,f,g][a,b,c,d,e,f,g][a,b,c,d,e,f,g][a,b,c,d,e,f,g][a,b,c,d,e,f,g][a,b,c,d,e,f,g][a,b,c,d,e,f,g]]");

    ConcreteSquareMatrix result("[[28,56,84,112,140,168,196][28,56,84,112,140,168,196][28,56,84,112,140,168,196][28,56,84,112,140,168,196][28,56,84,112,140,168,196][28,56,84,112,140,168,196][28,56,84,112,140,168,196]]");

    ConcreteSquareMatrix conPow2(con*con);
    SymbolicSquareMatrix symPow2(sym*sym);

    ConcreteSquareMatrix symPow2Evaluated = symPow2.evaluate(valuation);

    REQUIRE(conPow2 == result);
    REQUIRE(symPow2Evaluated == result);
}
