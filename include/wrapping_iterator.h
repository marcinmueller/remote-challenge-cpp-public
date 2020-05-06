#pragma once

namespace chal {

    template<typename C, typename ForwardIt>
    struct wrapping_iterator {

        using iterator_category = std::forward_iterator_tag;
        using value_type = typename ForwardIt::value_type;
        using difference_type = typename ForwardIt::difference_type;
        using pointer = typename ForwardIt::pointer;
        using reference = typename ForwardIt::reference;

        wrapping_iterator(C& container, ForwardIt it)
            : _container(container)
            , _it(it)
        {}

        bool operator!=(const wrapping_iterator& other) const {
            return _it != other._it;
        }

        wrapping_iterator& operator++() {
            ++_it;
            if (_it == _container.end())
                _it = _container.begin();
            return *this;
        }

        decltype(auto) operator*() const {
            return *_it;
        }

    private:
        C& _container;
        ForwardIt _it;
    };

} //namespace chal