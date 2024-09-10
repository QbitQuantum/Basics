/**
 *	This function checks the state and data of the Action to decide if it is in
 *	a valid state.
 *	To be in a valid state the Action must satisfy the following:
 *	- Have a name
 *	- Reference an animation that exists in the model
 *	- If the Action is a movement action then the referenced animation must
 *		have an overall translation that is non-zero.
 *
 *	@param	model	The model that owns the action. The action need not be yet
 *					added to the model.
 *
 *	@return			Returns true if the Action is in a valid state.
 */
bool ModelAction::valid( const ::Model & model ) const
{
	if (name_.empty())
	{
		//ERROR_MSG(	"Invalid Action: of model '%s'\n"
		//			"    Action has no name\n",
		//			model.resourceID().c_str());
		return false;
	}

	int animationIndex = model.getAnimation( animation_ );
	if (animationIndex == -1)
	{
		//ERROR_MSG(	"Invalid Action: '%s' of model '%s'\n"
		//			"    Referenced animation '%s' not found\n",
		//			name_.c_str(),
		//			model.resourceID().c_str(),
		//			animation_.c_str());
		return false;
	}

	SmartPointer<ModelAnimation> modelAnimation = model.animations_[animationIndex];
	SmartPointer<Moo::Animation> mooAnimation = modelAnimation->getMooAnim();

	if (isMovement_)
	{
		Moo::ChannelBinder * channelBinder = mooAnimation->itinerantRoot();

		Matrix firstFrameTransform;
		Matrix finalFrameTransform;

		channelBinder->channel()->result( 0, firstFrameTransform );
		channelBinder->channel()->result(	mooAnimation->totalTime(),
											finalFrameTransform );

		finalFrameTransform.invert();
		Matrix animationDisplacement;
		animationDisplacement.multiply(	finalFrameTransform,
										firstFrameTransform );

		if (almostZero(animationDisplacement.applyToOrigin().length()))
		{
			//ERROR_MSG(	"Invalid Action: '%s' of model '%s'\n"
			//			"    Action is marked as 'isMovement' but animation\n"
			//			"    '%s' has no overall translation of itinerant\n"
			//			"    root bone '%s'\n",
			//			name_.c_str(),
			//			model.resourceID().c_str(),
			//			animation_.c_str(),
			//			channelBinder->channel()->identifier().c_str());
			return false;
		}
	}

	return true;
}