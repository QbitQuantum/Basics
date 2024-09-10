Vector3F LinearSpline::getPositionAtTime(unsigned int length, unsigned int time)
{
	float splineLength = 0;
	std::vector<float> segmentLengths;
	for (size_t i = 1; i < mNodes.size(); ++i) {
		float segmentLength = (mNodes[i - 1]->position.value() - mNodes[i]->position.value()).length();
		splineLength += segmentLength;
		segmentLengths.push_back(splineLength);
	}
	float step = splineLength / length;
	float segment = time * step;
	size_t segmentIndex = 0;
	while (segment > segmentLengths[segmentIndex])
		segmentIndex++;

	float segmentRemains = segment - (segmentIndex > 0 ? segmentLengths[segmentIndex - 1] : 0);

	Vector3F segmentToUse = mNodes[segmentIndex + 1]->position.value() - mNodes[segmentIndex]->position.value();
	float segmentToUseLength = segmentToUse.length();

	float segmentPercentage = segmentRemains / segmentToUseLength;

	Vector3F segmentFraction = segmentToUse * segmentPercentage;

	return mNodes[segmentIndex]->position.value() + segmentFraction;
}