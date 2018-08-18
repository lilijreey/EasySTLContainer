
#include <list>
#include <gtest/gtest.h>
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

#define lamdba_fn [](const auto &_ele)
#define lamdba_exp(exp) [](const auto &_ele) {return exp;}


TEST(vector, read_only_methods)
{
  Vector<int> v{1,2,3,4};
  ASSERT_TRUE(v.is_any_of(lamdba_fn{ return _ele > 0;}));
    ASSERT_FALSE(v.is_any_of(lamdba_fn{ return _ele < 0;}));
    ASSERT_FALSE(std::move(v).is_any_of(lamdba_fn{ return _ele < 0;}));

    ASSERT_FALSE(v.is_all_of(lamdba_fn{ return _ele < 0;}));
    ASSERT_TRUE(v.is_all_of(lamdba_fn{ return _ele > 0;}));

    ASSERT_TRUE(v.is_none_of(lamdba_fn{ return _ele < 0;}));

    ASSERT_EQ(0, v.count(11));
    ASSERT_EQ(1, v.count(1));
    ASSERT_EQ(v.size(), v.count(lamdba_exp(_ele > 0)));

    v = {2,1,3,1,4,1};
    ASSERT_EQ(v.begin(), v.find(2));
    ASSERT_EQ(v.begin()+1, v.find(1));
    ASSERT_TRUE(v.is_include(3));
    ASSERT_FALSE(v.is_include(13));

//    ASSERT_EQ(v.begin(), v.find(lamdba_exp(_ele > 0)));
//    auto  it = v.find(1);
//    for (auto e : v.find_iter(1))
//    {
//
//    }


}
