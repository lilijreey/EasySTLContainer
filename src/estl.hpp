
#include <vector>
#include <algorithm>
#include <functional>
#include <type_traits>
#include "estl_select_iter.hpp"

namespace estl {

template<
    class T,
    class Allocator = std::allocator<T>
> class Vector : public std::vector<T, Allocator> {
  using base_type =  std::vector<T, Allocator>;
  using const_base_type =  const std::vector<T, Allocator>;
  using self_type = Vector<T, Allocator> ;
public:
  using std::vector<T, Allocator>::vector;

  //read only algorithm
  template<class UnaryPredicate>
  bool is_any_of(UnaryPredicate &&fn) const {
      return std::any_of(this->begin(), this->end(), std::forward<UnaryPredicate>(fn));
  }

  template<class UnaryPredicate>
  bool is_all_of(UnaryPredicate &&fn) const {
      return std::all_of(this->begin(), this->end(), std::forward<UnaryPredicate>(fn));
  }

  template<class UnaryPredicate>
  bool is_none_of(UnaryPredicate &&fn) const {
      return std::none_of(this->begin(), this->end(), std::forward<UnaryPredicate>(fn));
  }



    //T type use std::count
    template<class E,
             typename std::enable_if<std::is_same<
                     typename std::remove_cv<typename std::remove_reference<T>::type>::type,
                     typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
            ,int >::type=0>
   // auto count(E &&e) -> decltype(std::count(this->begin(), this->end(), T{})) const {
   decltype(auto) count(E &&e) { //14
        return std::count(this->begin(), this->end(), std::forward<E>(e));
    }

    //no T type use std::count_if
    template<class Fn,
            typename std::enable_if<!std::is_same<
                    typename std::remove_cv<typename std::remove_reference<T>::type>::type,
                    typename std::remove_cv<typename std::remove_reference<Fn>::type>::type>::value
                    ,int >::type=0>
    auto count(Fn &&fn) -> decltype(std::count(this->begin(), this->end(), T{})) const {
        return std::count_if(this->begin(), this->end(), std::forward<Fn>(fn));
    }


  ///@brief find the first element in container
  ///@param e find the element
  ///@return element iterator or end() if not find.

    //find T, 返回为非const_iter 但是可以复制给const_iter 少些一个非const_iter版本
    template<class E,
            typename std::enable_if<std::is_same<
                    typename std::remove_cv<typename std::remove_reference<T>::type>::type,
                    typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value
                    ,int >::type=0>
    typename base_type::iterator find(E &&e) const {
        return std::find(const_cast<base_type*>(static_cast<const_base_type*>(this))->begin(),
                         const_cast<base_type*>(static_cast<const_base_type*>(this))->end(),
                         std::forward<E>(e));
    }


    //fn
    template<class Fn,
            typename std::enable_if<!std::is_same<
                    typename std::remove_cv<typename std::remove_reference<T>::type>::type,
                    typename std::remove_cv<typename std::remove_reference<Fn>::type>::type>::value
                    ,int >::type=0>
    typename base_type::iterator find(Fn &&fn) const {
        return std::find_if(const_cast<base_type*>(static_cast<const_base_type*>(this))->begin(),
                            const_cast<base_type*>(static_cast<const_base_type*>(this))->end(),
                            std::forward<Fn>(fn));
    }



  bool is_include(const T &e) const {
      return find(e) != this->end();
  }



    template<class Iter>
    bool is_equal(Iter &&begin, Iter &&end, std::random_access_iterator_tag _tag) const {
        return this->size() == std::distance(begin, end)
               &&
               std::equal(this->begin(), this->end(),
                          std::forward<Iter>(begin),
                          std::forward<Iter>(end));
    }


    bool is_equal(const std::initializer_list<T> &o) const {
        return this->size() == o.size() &&
               std::equal(this->begin(), this->end(), std::begin(o), std::end(o));
    }

  template<class Container>
  bool is_equal(const Container &o) const {
      return this->size() == o.size() &&
          std::equal(this->begin(), this->end(), std::begin(o), std::end(o));
  }


  ///@brief Invokes the given fn once for each element of self.
  ///@param Fn void(T&)
  template<class Fn>
  Vector &map_self(Fn &&fn) {
      for (auto &e : *this)
          std::forward<Fn>(fn)(e);

      return *this;
  }

    ///@brief map resualt to new Vector, not change self.
    ///@param Fn T(const T&)
    template<class Fn>
    Vector map(Fn &&fn) const {
        Vector ret;
        ret.reserve(this->size());

        for (auto &e : *this)
            ret.emplace_back(std::forward<Fn>(fn)(e));

        return ret;
    }

    //TODO using base_type::erase; not work correct, why?
    typename base_type::iterator erase(const typename self_type::iterator &it)
    {
        return base_type::erase(it);
    }

    typename base_type::iterator erase(const typename self_type::const_iterator &it)
    {
        return base_type::erase(it);
    }

    typename base_type::iterator erase(const T &e)
    {
        return base_type::erase(std::remove(this->begin(), this->end(), e), this->end());
    }

  template<class Fn>
   typename base_type::iterator erase(const Fn &fn) {
      //return base_type::erase(std::remove_if(this->begin(), this->end(), std::forward<Fn>(fn)), this->end());
      return base_type::erase(std::remove_if(this->begin(), this->end(), fn), this->end());
  }

    //删除前传递给Fn, 返回返回后元素会被删除
    //Fn:: (T&)->void
    template<class Unarypredicate, class Fn>
    size_t erase_take(Unarypredicate &&SelectFn, Fn &&fn) {
        auto it = std::remove_if(this->begin(), this->end(), std::forward<Unarypredicate>(SelectFn));
        size_t eraseCount = 0;
        while (it != this->end())
        {
            fn(*it);
            it = base_type::erase(it);
            ++eraseCount;
        }

        return eraseCount;
    }

  Vector &stable_sort() {
      std::stable_sort(this->begin(), this->end());
      return *this;
  }

  template<class SortFn>
  Vector &stable_sort(SortFn &&fn) {
      std::stable_sort(this->begin(), this->end(), std::forward<SortFn>(fn));
      return *this;
  }


    template <class SelectFn>
    SelectIter<self_type, SelectFn> select_iter(SelectFn &&fn)
    {
        return SelectIter<self_type, SelectFn>(this, std::forward<SelectFn>(fn));
    }

    template<class Fn>
    Vector &select_take(const T &o, Fn &&fn) {
        for (auto &e: *this)
            if (e == o) std::forward<Fn>(fn)(e);

        return *this;
    }

  ///@brief select element and pass to fn, as same as 'take_while' in other luangages
  ///@param selectFn return true if select element
  ///@param fn
  template<class SelectFn, class Fn>
  Vector &select_take(SelectFn &&selectFn, Fn &&fn) {
      for (auto &e: *this)
          if (std::forward<SelectFn>(selectFn)(e))
              std::forward<Fn>(fn)(e);

      return *this;
  }


  template <class R, class BinaryFn>
  R fold(R &&init, BinaryFn &&fn) const {
      R acc = std::forward<R>(init);
      for (const auto &e: *this) {
          acc = std::forward<BinaryFn>(fn)(acc, e);
      }
      return acc;
  }




};

} //end namespace estl
