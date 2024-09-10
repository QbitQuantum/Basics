MultiModLocGen& MultiModLocGen::operator=(MultiModLocGen const &rhs) {
    if (this != &rhs) {
        using std::distance;
        _super::operator=(static_cast<_super const&>(rhs));
        _rangeMap = rhs._rangeMap;
        range_map_type::difference_type dist =
            distance(_rangeMap.begin(), rhs._rangeIt);
        _rangeIt = std::next(_rangeMap.begin(), dist);
    }
    return *this;
}