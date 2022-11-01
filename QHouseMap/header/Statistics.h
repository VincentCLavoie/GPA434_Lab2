#pragma once


#include <type_traits>
#include <limits>


template <typename t = double>
class Statistics
{
    static_assert(std::is_floating_point_v<t>, "Invalid template parameter in Statistics : t must be a floating point.");

public:
    Statistics() : _count{}, _min{ std::numeric_limits<t>::max() }, _max{ std::numeric_limits<t>::lowest() }, _sum{} {}
    Statistics(Statistics<t> const &) = default;
    Statistics(Statistics<t> &&) = default;
    Statistics& operator=(Statistics<t> const &) = default;
    Statistics& operator=(Statistics<t> &&) = default;
    ~Statistics() = default;

    inline bool isValid() const     { return _count > 0; }

    inline size_t count() const     { return _count; }
    inline t min() const            { return _min; }
    inline t max() const            { return _max; }
    inline t sum() const            { return _sum; }
    inline t mean() const           { return isValid() ? _sum / _count : t{}; }

    inline void reset()             { _count = t{}; _min = std::numeric_limits<t>::max(); _max = std::numeric_limits<t>::lowest(); _sum = {}; }
    inline void add(double value)   { ++_count; if (value < _min) _min = value; if (value > _max) _max = value; _sum += value; }

private:
    size_t _count{};
    t _min{};
    t _max{};
    t _sum{};
};

