void JuceDevice::Polygon( const float * xCoords, const float * yCoords, int count ) 
{
	if (count < 2) return;
	
	Path path;
	path.startNewSubPath (xCoords[0], yCoords[0]);
	for (int i = 1; i < count; i++)
		path.lineTo (xCoords[i], yCoords[i]);
	path.closeSubPath ();
	fGraphics->fillPath (path);
}