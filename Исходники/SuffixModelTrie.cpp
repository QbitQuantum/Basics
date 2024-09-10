/**
 * predict MorphologicalInfo by suffix
 */
vector<MorphologicalInfo> SuffixModelTrie::getMorphologicalPredictionBySuffix(wstring _word)
{
	vector<MorphologicalInfo> result = vector<MorphologicalInfo>();
	SuffixModelNode* currentNode = root;
	int suffixLength = 0;
	for (int i = (int) _word.length() - 1; i >= 0; --i)
	{
		SuffixModelNode* tmpNode = currentNode->findChildNode(_word.at(i));
		if (tmpNode == NULL)
		{
			break;
		}
		currentNode = tmpNode;
		suffixLength++;
        //wcout << _word.at(i) << " : " << currentNode->getFeatureFrequencyMap().size() << endl;
	}
	if (suffixLength == 0)
	{
		return result;
	}
    //wcout << "Suffix length = " << suffixLength << endl;
	map<int, int> _featureFrequencyMap = currentNode->getFeatureFrequencyMap();
    //wcout << "_featureFrequencyMap's size = " << _featureFrequencyMap.size() << endl;
	map<int, int>::iterator iter;
    //@TODO : \u043f\u0435\u0440\u0440\u0441\u0441\u043e\u043d//here was cyrrilic symbols: перрссон
	for (iter = _featureFrequencyMap.begin(); iter != _featureFrequencyMap.end(); ++iter)
	{
		int _featureId = iter->first;
		int _frequency = iter->second;
		int _basicFeatureListId = _featureId / 1000;
		int _featureListId = _featureId % 1000;
		wstring _initial_form = suffixLength < (int) _word.length() ? L"-" + _word.substr(_word.length() - suffixLength) : _word;
		MorphologicalInfo _morphologicalInfo;
		_morphologicalInfo.basicFeatureListId = _basicFeatureListId;
		_morphologicalInfo.featureListId = _featureListId;
		_morphologicalInfo.frequency = _frequency;
		_morphologicalInfo.initial_form = _initial_form;
		_morphologicalInfo.lemmaId = 0;
		_morphologicalInfo.suffix_length = suffixLength;
		result.push_back(_morphologicalInfo);
	}
	return result;
}