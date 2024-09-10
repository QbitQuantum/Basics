static void spSort(vector<uint64>& ioWrittenTupleIDs, vector<ZTuple>& ioWrittenTuples)
{
    vector<uint64> newIDs;
    vector<ZTuple> newTuples;
    // Do a lower_bound insertion into newIDs, and
    // to equivalent offset of newTuples.
    for (vector<uint64>::iterator i = ioWrittenTupleIDs.begin(); i != ioWrittenTupleIDs.end(); ++i)
    {
        vector<uint64>::iterator pos = lower_bound(newIDs.begin(), newIDs.end(), *i);

        newTuples.insert(newTuples.begin() + (pos - newIDs.begin()),
                         ioWrittenTuples[i - ioWrittenTupleIDs.begin()]);

        newIDs.insert(pos, *i);
    }
    ioWrittenTupleIDs.swap(newIDs);
    ioWrittenTuples.swap(newTuples);
}