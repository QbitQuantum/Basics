/**
 *	Set property from python version
 */
int EDCALL GenPositionProperty::pySet( PyObject * value, bool transient /* = false */ )
{
	Vector3 v;
	std::string errStr( "GeneralEditor." );
	errStr += name_;

	int ret = Script::setData( value, v, errStr.c_str() );
	if (ret == 0)
	{
		pMatrix_->recordState();

		Matrix invCtx;
		pMatrix_->getMatrixContextInverse( invCtx );

		Matrix curPose;
		pMatrix_->getMatrix( curPose, transient );

		curPose.translation( invCtx.applyPoint( v ) );

		pMatrix_->setMatrix( curPose );

		pMatrix_->commitState();

		// could set python exception if op failed. either change
		// commitState to return a bool (easiest) or get matrix
		// again and compare to what we set.
	}
	return ret;
}