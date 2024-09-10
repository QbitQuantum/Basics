size_t
reserve_count_for_single_pass_helper(InputIterator first, InputIterator last,
                                     std::random_access_iterator_tag)
{
    using std::distance;
    typename std::iterator_traits<InputIterator>::difference_type n =
        distance(first, last);
    return (size_t)n;
}