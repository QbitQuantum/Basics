bool FdoFgfCurveString::GetIsClosed() const
{
	// Get 1st and last position 
	FdoPtr<FdoIDirectPosition> startPos = this->GetStartPosition();
	FdoPtr<FdoIDirectPosition> endPos = this->GetEndPosition();

    // TODO: the curve isn't really closed if all ordinates are NaN, but rather than
    // fixing it here, a more general validity tests for the whole line should be done.
#ifdef _WIN32
	bool isClosed = ( ((_isnan(startPos->GetX()) && _isnan(endPos->GetX())) || startPos->GetX() == endPos->GetX()) &&
		              ((_isnan(startPos->GetY()) && _isnan(endPos->GetY())) || startPos->GetY() == endPos->GetY()) &&
                      ((_isnan(startPos->GetZ()) && _isnan(endPos->GetZ())) || startPos->GetZ() == endPos->GetZ()) );
#else
	bool isClosed = ( ((isnan(startPos->GetX()) && isnan(endPos->GetX())) || startPos->GetX() == endPos->GetX()) &&
		              ((isnan(startPos->GetY()) && isnan(endPos->GetY())) || startPos->GetY() == endPos->GetY()) &&
                      ((isnan(startPos->GetZ()) && isnan(endPos->GetZ())) || startPos->GetZ() == endPos->GetZ()) );
#endif

	return isClosed;
}