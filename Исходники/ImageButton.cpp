/**
 * Sets the button as the pressed button if it's part of a group,
 * and inverts the colors when pressed.
 * @param action Pointer to an action.
 * @param state State that the action handlers belong to.
 */
void ImageButton::mousePress(Action *action, State *state)
{
	if (_group != 0)
	{
		(*_group)->invert((*_group)->getColor());
		*_group = this;
	}
	invert(_color);
	InteractiveSurface::mousePress(action, state);
}