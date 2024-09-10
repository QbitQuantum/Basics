inline void remove(int town)
{
    int set1 = min_total_index[town] / sizes[town], set2 = (cnt[town] - 1) / sizes[town];
    setW(town, min_total_index[town], getW(town, cnt[town] - 1));
    cnt[town]--;

    updateSet(town, set1);
    if (set2 != set1)
        updateSet(town, set2);
    updateTotal(town);
}