
#include <vector>
#include <algorithm>

namespace estl {

template <
    class T,
    class Allocator = std::allocator<T>
> class Vector : public std::vector<T, Allocator>
{
    using stl_container_type =  std::vector<T, Allocator>;
 public:
   using std::vector<T, Allocator>::vector;

    //read only algorithm
    template <class UnaryPredicate>
    bool is_any_of(UnaryPredicate && fn) const
    {
        return std::any_of(this->begin(), this->end(), std::forward<UnaryPredicate>(fn));
    }

    template <class UnaryPredicate>
    bool is_all_of(UnaryPredicate && fn) const
    {
        return std::all_of(this->begin(), this->end(), std::forward<UnaryPredicate>(fn));
    }

    template <class UnaryPredicate>
    bool is_none_of(UnaryPredicate && fn) const
    {
        return std::none_of(this->begin(), this->end(), std::forward<UnaryPredicate>(fn));
    }

    //count
    auto count(T&& e) -> decltype(std::count(this->begin(), this->end(), T{})) const
    {
        return std::count(this->begin(), this->end(), e);
    }


    template <class Unarypredicate>
    auto count(Unarypredicate && fn) -> decltype(std::count(this->begin(), this->end(), T{})) const
    {
        return std::count_if(this->begin(), this->end(), std::forward<Unarypredicate>(fn));
    }


    ///@brief find the first element in container
    ///@param e find the element
    ///@return element iterator or end() if not find.
    typename stl_container_type::iterator find(const T &e)
    {
        return std::find(this->begin(), this->end(), e);
    }

    typename stl_container_type::const_iterator find(const T &e) const
    {
        return std::find(this->begin(), this->end(), e);
    }


    template <class Unarypredicate>
    typename stl_container_type::const_iterator find(Unarypredicate &fn) const
    {
        return std::find_if(this->begin(), this->end(), std::forward<Unarypredicate>(fn));
    }

    template <class Unarypredicate>
    typename stl_container_type::iterator find(Unarypredicate &&fn)
    {
        return std::find_if(this->begin(), this->end(), std::forward<Unarypredicate>(fn));
    }


    bool is_include(const T& e) const
    {
        return find(e) != this->end();
    }



    //collect
    //map_self
    //reduce
    //select
    //select_until
    //drop
    //drop_until
    //foldl
    //foldr
    //fill

    //remove
    //equal

    //find
    //find_frist
    //find_last

    //TODO
    //it2index
    //mismatch TO


};


} //end namespace estl
