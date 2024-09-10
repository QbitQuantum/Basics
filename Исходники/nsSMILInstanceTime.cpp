void
nsSMILInstanceTime::HandleChangedInterval(
    const nsSMILTimeContainer* aSrcContainer,
    PRBool aBeginObjectChanged,
    PRBool aEndObjectChanged)
{
  NS_ABORT_IF_FALSE(mBaseInterval,
      "Got call to HandleChangedInterval on an independent instance time.");
  NS_ABORT_IF_FALSE(mCreator, "Base interval is set but creator is not.");

  if (mVisited) {
    // Break the cycle here
    Unlink();
    return;
  }

  PRBool objectChanged = mCreator->DependsOnBegin() ? aBeginObjectChanged :
                                                      aEndObjectChanged;

  AutoBoolSetter setVisited(mVisited);

  nsRefPtr<nsSMILInstanceTime> deathGrip(this);
  mCreator->HandleChangedInstanceTime(*GetBaseTime(), aSrcContainer, *this,
                                      objectChanged);
}