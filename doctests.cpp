//
// Created by dembi on 23/06/2025.
//

#include "doctests.h"
#include "MyContainer.h"
#include "Exceptions.h"
#include <sstream>

using namespace Containers;

// INT CONTAINER TESTS
TEST_CASE("MyContainer<int>") {
    MyContainer<int> c;

    SUBCASE("Default constructor") {
        CHECK(c.Size() == 0);
    }

    SUBCASE("Insert with duplicates") {
        c.Insert(1);
        c.Insert(1);
        c.Insert(2);
        CHECK(c.Size() == 3);
    }

    SUBCASE("Remove existing and non-existing") {
        c.Insert(10);
        c.Insert(20);
        CHECK_NOTHROW(c.Remove(10));
        CHECK_THROWS_AS(c.Remove(99), ValueNotFound);
    }

    SUBCASE("Operator <<") {
        c.Insert(4);
        c.Insert(5);
        std::ostream& os = std::cout;
        os << c;
        CHECK(os.str() == "[4, 5]");
    }

    SUBCASE("Iterators: generic usage") {
        c.Insert(1);
        c.Insert(2);
        c.Insert(3);

        int count = 0;
        for (auto it = c.begin(); it != c.end(); ++it)
            ++count;
        CHECK(count == 3);
    }

    SUBCASE("All iterators produce expected order") {
        c.Insert(1);
        c.Insert(2);
        c.Insert(3);
        c.Insert(4);
        c.Insert(5);

        std::vector<int> expected = std::vector<int>();

        SUBCASE("Order") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginOrder(); it != c.endOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Reverse") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginReverseOrder(); it != c.endReverseOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Ascending") {
            expected = {1, 2, 3, 4, 5};
            int i = 0;
            for (auto it = c.beginAscendingOrder(); it != c.endAscendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("Descending") {
            expected = {5, 4, 3, 2, 1};
            int i = 0;
            for (auto it = c.beginDescendingOrder(); it != c.endDescendingOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("SideCross") {
            expected = {1, 5, 2, 4, 3};
            int i = 0;
            for (auto it = c.beginSideCrossOrder(); it != c.endSideCrossOrder(); ++it)
                CHECK(*it == expected[i++]);
        }

        SUBCASE("MiddleOut") {
            expected = {3, 4, 2, 5, 1};
            int i = 0;
            for (auto it = c.beginMiddleOutOrder(); it != c.endMiddleOutOrder(); ++it)
                CHECK(*it == expected[i++]);
        }
    }

    SUBCASE("Iterator operations: ++, --, ==, !=, *") {
        c.Insert(10);
        c.Insert(20);
        c.Insert(30);

        auto it1 = c.beginOrder();
        auto it2 = it1;
        ++it2;
        CHECK(it1 != it2);
        CHECK(*it2 == 20);
        --it2;
        CHECK(it1 == it2);
    }

    SUBCASE("Iterator operator[] and ->") {
        c.Insert(100);
        c.Insert(200);
        auto it = c.beginOrder();
        CHECK(it[1] == 200);
        CHECK(*it == 100);
    }
    // Remove all duplicates test
    SUBCASE("Remove all duplicates") {
        c.Insert(5);
        c.Insert(5);
        c.Insert(5);
        CHECK(c.Size() == 3);
        c.Remove(5);
        CHECK(c.isEmpty());
        CHECK_THROWS_AS(c.Remove(5), ValueNotFound);
    }

    // Remove from empty container throws
    SUBCASE("Remove from empty container") {
        CHECK_THROWS_AS(c.Remove(10), ValueNotFound);
    }

    // at() throws if container empty
    SUBCASE("at() throws when container empty") {
        CHECK_THROWS_AS(c.at(0), ContainerEmpty);
    }

    // at() throws for out-of-range index
    SUBCASE("at() throws for out-of-range") {
        c.Insert(1);
        CHECK_THROWS_AS(c.at(5), ValueOutOfBound);
    }

    // Iterator increment past end throws
    SUBCASE("Iterator increment past end throws") {
        c.Insert(1);
        auto it = c.begin();
        ++it; // now at the end
        CHECK_THROWS_AS(++it, ValueOutOfBound);
    }

    // Iterator decrement before begin throws
    SUBCASE("Iterator decrement before begin throws") {
        c.Insert(1);
        auto it = c.begin();
        CHECK_THROWS_AS(--it, ValueOutOfBound);
    }

    // Dereferencing end iterator throws
    SUBCASE("Iterator dereference end throws") {
        c.Insert(1);
        auto it = c.end();
        CHECK_THROWS_AS(*it, ValueOutOfBound);
    }

    // Self-assignment does not break container
    SUBCASE("Self-assignment") {
        c.Insert(10);
        c.Insert(20);
        c = c;
        CHECK(c.Size() == 2);
        CHECK(c.contains(10));
        CHECK(c.contains(20));
    }

    // Assign empty container to non-empty container
    SUBCASE("Assign empty to non-empty") {
        MyContainer<int> c2;
        c.Insert(1);
        c2 = c;
        c = MyContainer<int>(); // assign empty
        CHECK(c.isEmpty());
    }

    // Insert and Remove large number of elements to test resizing
    SUBCASE("Large Insert and Remove") {
        const int large_Size = 10000;
        for (int i = 0; i < large_Size; ++i) {
            c.Insert(i);
        }
        CHECK(c.Size() == large_Size);
        for (int i = 0; i < large_Size; ++i) {
            c.Remove(i);
        }
        CHECK(c.isEmpty());
    }

    // Const correctness checks
    SUBCASE("Const correctness") {
        c.Insert(1);
        const MyContainer<int> &cc = c;
        CHECK(cc.Size() == 1);
        CHECK_FALSE(cc.isEmpty());
        CHECK(cc.contains(1));
    }

    // Iterator on empty container returns begin == end
    SUBCASE("Iterator on empty container") {
        CHECK(c.begin() == c.end());
    }

    SUBCASE("Insert during iteration throws ActiveIterator") {
        c.Insert(1);
        c.Insert(2);
        c.Insert(3);

        CHECK_THROWS_AS({
            for (auto it = c.begin(); it != c.end(); ++it) {
                c.Insert(4);
            }
        }, ActiveIterator);
    }

    SUBCASE("Remove during iteration throws ActiveIterator") {
        c.Insert(1);
        c.Insert(2);
        c.Insert(3);

        CHECK_THROWS_AS({
            for (auto it = c.begin(); it != c.end(); ++it) {
                c.Remove(3);
            }
        }, ActiveIterator);
    }

}
