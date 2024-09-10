    void bisectional_find_test_ints(std::vector<int>& values, int value_to_find) {

        using std::vector;
        using std::cout;
        using std::endl;
        using std::getchar;

        auto begin = values.begin();
        auto end = values.end();

        //works with iterator math
        auto found = bisectional_find<int_vector_iterator, int>(
            values, value_to_find,
            [](vector<int>& v) -> int_vector_iterator { return v.begin(); },
            [](vector<int>& v) -> int_vector_iterator { return v.end(); },
            [](const int& a, const int& b) { return a > 0 && a == b; });
        
        if (found == end)
            cout << "did not find " << value_to_find;
        else
            cout << "found " << value_to_find << " at index " << (found - begin);

        cout << endl;

        getchar();
    }