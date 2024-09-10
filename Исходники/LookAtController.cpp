/******************************************************************************
* Lets a rotation controller apply its value to an existing transformation matrix.
******************************************************************************/
void LookAtController::applyRotation(TimePoint time, AffineTransformation& result, TimeInterval& validityInterval)
{
	// Save source position for later use.
	_sourcePos = result.translation();
	_sourcePosValidity = validityInterval;

	Controller::applyRotation(time, result, validityInterval);
}