//----------------------------------------------------------------//
void USPrism::Transform ( const USMatrix4x4& mtx ) {

	mtx.Transform ( mLoc );
	mtx.TransformVec ( mXAxis );
	mtx.TransformVec ( mYAxis );
	mtx.TransformVec ( mZAxis );
}