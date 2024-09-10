void DetectorTester::mergeInto(vector<pair<float, bool>>& scores, const vector<pair<float, bool>>& additionalScores) const {
	vector<pair<float, bool>> mergedScores;
	mergedScores.reserve(scores.size() + additionalScores.size());
	std::merge(scores.begin(), scores.end(),
			additionalScores.begin(), additionalScores.end(),
			std::back_inserter(mergedScores), std::greater<pair<float, bool>>());
	scores.swap(mergedScores);
}