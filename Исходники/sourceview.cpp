void SourceView::updateJumpArray(uint lineno, SourceItem* si,
				 bool ignoreFrom, bool ignoreTo)
{
    TraceLineJump* lj;
    uint lowLineno, highLineno;
    int iEnd = -1, iStart = -1;

    if (0) qDebug("updateJumpArray(line %d, jump to %s)",
		  lineno,
		  si->lineJump()
		  ? si->lineJump()->lineTo()->name().ascii() : "?" );


    lj=_lowList.current();
    while(lj) {
	lowLineno = lj->lineFrom()->lineno();
	if (lj->lineTo()->lineno() < lowLineno)
	    lowLineno = lj->lineTo()->lineno();

	if (lowLineno > lineno) break;

	if (ignoreFrom && (lowLineno < lj->lineTo()->lineno())) break;
	if (ignoreTo && (lowLineno < lj->lineFrom()->lineno())) break;

	if (si->lineJump() && (lj != si->lineJump())) break;

	int asize = (int)_jump.size();
#if 0
	for(iStart=0;iStart<asize;iStart++)
	    if (_jump[iStart] &&
		(_jump[iStart]->lineTo() == lj->lineTo())) break;
#else
	iStart = asize;
#endif

	if (iStart == asize) {
	    for(iStart=0;iStart<asize;iStart++)
		if (_jump[iStart] == 0) break;

	    if (iStart== asize) {
		asize++;
		_jump.resize(asize);
		if (asize > _arrowLevels) _arrowLevels = asize;
	    }

	    if (0) qDebug(" start %d (%s to %s)",
			  iStart,
			  lj->lineFrom()->name().ascii(),
			  lj->lineTo()->name().ascii());

	    _jump[iStart] = lj;
	}
	lj=_lowList.next();
    }

    si->setJumpArray(_jump);

    lj=_highList.current();
    while(lj) {
	highLineno = lj->lineFrom()->lineno();
	if (lj->lineTo()->lineno() > highLineno) {
	    highLineno = lj->lineTo()->lineno();
	    if (ignoreTo) break;
	}
	else if (ignoreFrom) break;

	if (highLineno > lineno) break;

	for(iEnd=0;iEnd< (int)_jump.size();iEnd++)
	    if (_jump[iEnd] == lj) break;
	if (iEnd == (int)_jump.size()) {
	    qDebug("LineView: no jump start for end at %x ?", highLineno);
	    iEnd = -1;
	}
	lj=_highList.next();

	if (0 && (iEnd>=0))
	    qDebug(" end %d (%s to %s)",
		   iEnd,
		   _jump[iEnd]->lineFrom()->name().ascii(),
		   _jump[iEnd]->lineTo()->name().ascii());

	if (0 && lj) qDebug("next end: %s to %s",
			    lj->lineFrom()->name().ascii(),
			    lj->lineTo()->name().ascii());

	if (highLineno > lineno)
	    break;
	else {
	    if (iEnd>=0) _jump[iEnd] = 0;
	    iEnd = -1;
	}
    }
    if (iEnd>=0) _jump[iEnd] = 0;
}