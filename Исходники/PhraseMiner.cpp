IntervalSequence<set<Chord> > PhraseMiner::load(const data_symb* ds)
{
    data d = ds[0].datas;
    vector<int> start = d.start;
    vector<int> end   = d.end;
    vector<int> symID = d.symbol;

    map<int, Chord> symbolMap;

    symb s = ds[0].symbs;
    int symb_size = s.symb_size;
    for (int i = 0; i < symb_size; ++i) {
        string label = s.label[i];
        int globalID = s.symbol[i];
        symbolMap.insert(pair<int, Chord>(globalID,
                                          Chord(globalID, set<Tone>(), label)));
    }

    vector<int> newStart;
    vector<int> newEnd;
    vector<int> newSymID;

    int symID_size = symID.size();
    for (int i = 0; i < symID_size; i++) {
        if (symbolMap.find(symID[i]) != symbolMap.end()) {
            newStart.push_back(start[i]);
            newEnd.push_back(end[i]);
            newSymID.push_back(symID[i]);
        }
    }

    IntervalSet<Chord> iSet(newStart, newEnd, newSymID, symbolMap);
    return IntervalSequence<Chord>::convert(IntervalEventSet<Chord>(iSet));

}