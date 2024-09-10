XipWorldToImageConvert::XipWorldToImageConvert( const SbMatrix& imageModelMatrix,
											    const SbXipImageDimensions& dimensions )
	: mDimensions( dimensions )
{
	mInvMatrix = imageModelMatrix.inverse();
}