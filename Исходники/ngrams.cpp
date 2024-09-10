void putMap(Map<Vector<string>, Vector<string> >& nGramMap, Vector<string> & inputVect, const string &inputWord)
{
    if(!nGramMap.containsKey(inputVect)) {
        nGramMap.add(inputVect, Vector<string>());
    }
        nGramMap[inputVect].add(inputWord);
    inputVect.remove(0);
    inputVect.add(inputWord);
}