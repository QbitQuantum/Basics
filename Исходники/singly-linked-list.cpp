List<T> removeDuplicates(List<T>  l, compare<T> comp) {
    List<T> removed;
    for (int i = 0; i < l.length(); ++i) {
        T val = l[i];

        bool found = false;
        for (int j = 0; j < removed.length(); ++j) {

            if (comp(removed[j], val))
                found = true;
        }

        if (!found)
            removed.AddToBack(val);
    }

    return removed;
}