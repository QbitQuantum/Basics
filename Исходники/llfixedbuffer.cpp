void LLFixedBuffer::addLine(const LLWString& line)
{
	if (line.empty())
	{
		return;
	}

	removeExtraLines();

	mLines.push_back(line);
	mLineLengths.push_back((S32)line.length());
	mAddTimes.push_back(mTimer.getElapsedTimeF32());
}