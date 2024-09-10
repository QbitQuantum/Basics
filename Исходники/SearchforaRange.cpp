ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, T value) {
    while (first != last) {
        auto mid = next(first, distance(first, last) / 2);
        if (value >= *mid)
            first = ++mid;
        else
            last = mid;
    }
    return first;
}