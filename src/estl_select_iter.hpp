//
// 提供一个条件选择迭代器对象，支持begin, ++, end, 可与range_base-for 结合使用
//

#ifndef EASYSTL_ESTL_SELECT_ITER_HPP_H
#define EASYSTL_ESTL_SELECT_ITER_HPP_H

namespace estl {

// SelectFn::(const T&)->bool
    template<class Container, class SelectFn>
    struct SelectIter {
        SelectIter(Container *container, const SelectFn &fn)
                :_container(container), _fn(fn), _it(container->find(fn)){}

        SelectIter begin() const {
            auto ret = *this;
            ret._it = _container->find(_fn);
            return ret;
        }

        SelectIter end() const {
            SelectIter ret = *this;
            ret._it = _container->end();
            return ret;
        }

        bool operator==(const typename Container::iterator &o) const {
            return _it == o;
        }

        bool operator!=(const SelectIter &o) const {
            return _container != o._container ||
                   _it != o._it;
        }

        SelectIter &operator++() {
            _it = std::find_if(++_it, _container->end(), _fn);
            return *this;
        }

        SelectIter operator++(int) {
            SelectIter ret = *this;
            _it = std::find_if(++_it, _container->end(), _fn);
            return ret;
        }


        typename Container::value_type &operator*() const {
            return *_it;
        }

    private:
        Container *_container;
        const SelectFn &_fn;
        typename Container::iterator _it;
    };

} //end namespace
#endif //EASYSTL_ESTL_SELECT_ITER_HPP_H

