
#include <gtest/gtest.h>
#include <list>
#include "../src/estl.hpp"

using namespace estl;

TEST(vector, construct)
{
    Vector<int> v;
    Vector<int> v1(1);
    ASSERT_EQ(1,v1.size());

    Vector<int> v2(1,1);
    ASSERT_EQ(1,v2.size());
    ASSERT_EQ(1,v2[0]);

    Vector<int> v3{1,2,3};
    ASSERT_EQ(v3.size(), 3);

    std::list<int> l{1,2,3};
    Vector<int> v4(l.begin(), l.end());
    ASSERT_EQ(v4.size(), 3);
    ASSERT_EQ(3, v4[2]);


}
