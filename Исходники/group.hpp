    Group(const StdRange& range)
    {
        using std::begin;
        using std::end;
        using std::distance;

        auto b = begin(range);
        auto e = end(range);

        _names.reserve(distance(b, e));

        auto i = b;
        while(i != e)
        {
            _names.push_back(GetName(*i));
            ++i;
        }
    }