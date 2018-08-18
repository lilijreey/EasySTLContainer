
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


    //XXX use &&
    template <class Unarypredicate>
    typename stl_container_type::const_iterator find(const Unarypredicate &fn) const
    {
        return std::find_if(this->begin(), this->end(), fn);
    }

    template <class Unarypredicate>
    typename stl_container_type::iterator find(const Unarypredicate &fn)
    {
        return std::find_if(this->begin(), this->end(), fn);
    }


    bool is_include(const T& e) const
    {
        return find(e) != this->end();
    }

    //TODO support {1,2,3,4} litter
    template <class Container>
    bool is_equal(const Container &o) const
    {
        return this->size() == std::size(o) &&
               std::equal(this->begin(), this->end(), std::begin(o), std::end(o));
    }


    ///@brief Invokes the given fn once for each element of self.
    template <class Fn>
    Vector& map_self(Fn &&fn)
    {
        const size_t size = this->size();
        for (size_t i=0; i < size; ++i)
            std::forward<Fn>(fn)(this->operator[](i));

        return *this;
    }


    ///@brief
//    template <class Fn>
//    Vector& select(MapFn &&fn)
//    {
//        const size_t size = this->size();
//        for (size_t i=0; i < size; ++i)
//            fn(this->operator[](i));
//
//        return *this;
//    }


    //collect
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
