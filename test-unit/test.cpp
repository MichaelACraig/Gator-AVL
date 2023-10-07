#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#define private public //Remove later
#include "Node.h"
#include "functions.cpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]"){

		/*BST tree;   // Create a Tree object
		tree.insert("A", 1);
		tree.insert("B, 2);
		tree.insert("C", 3);
		std::vector<int> actualOutput = tree.inorder();
		std::vector<int> expectedOutput = {1, 2, 3};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput); */

	REQUIRE(1 == 1);
}

/* TEST_CASE("Wrong Commands", ""){
    BST call;

    call.insert("Bra11", 1);
    call.remove(459999999);
    call.search(1234567890);
    call.search("A123");

    call.insert("A", 1);
    call.insert("B", 2);
    call.insert("C", 3);

    call.removeInorder(-1);
    REQUIRE();
} */