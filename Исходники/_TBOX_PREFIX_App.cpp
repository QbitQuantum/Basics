void _TBOX_PREFIX_App::draw()
{
	gl::clear();
	
	// grab 512 samples of the wave data
	float waveData[512];
	mSystem->getWaveData( waveData, 512, 0 );
	
	// render the 512 samples to a VertBatch
	gl::VertBatch vb( GL_LINE_STRIP );
	for( int i = 0; i < 512; ++i )
		vb.vertex( getWindowWidth() / 512.0f * i, getWindowCenter().y + 100 * waveData[i] );

	// draw the points as a line strip
	gl::color( Color( 1.0f, 0.5f, 0.25f ) );
	vb.draw();
}