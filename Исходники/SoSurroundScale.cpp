void
SoSurroundScale::doAction(SoAction *action)
//
////////////////////////////////////////////////////////////////////////
{
    SoState	*state = action->getState();

    SbMatrix theCtm = SoModelMatrixElement::get(state);

    if (cacheOK == FALSE )
	updateMySurroundParams( action, theCtm.inverse() );

    if (doTranslations)
	SoModelMatrixElement::translateBy(state, this, cachedTranslation );
    else
	cachedTranslation.setValue(0,0,0);

    SoModelMatrixElement::scaleBy(state, this, cachedScale );
}