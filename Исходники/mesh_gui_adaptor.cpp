/**
 *	Constructor.
 */
MeshGUIAdaptor::MeshGUIAdaptor( PyTypePlus * pType ):
	SimpleGUIComponent( "", pType ),
	attachment_( NULL ),
	transform_( NULL )
{
	PyMatrix* mat = new PyMatrix;
	transform_ = SmartPointer<PyMatrix>(mat, true);
	Matrix m;
	//flatten every attached mesh, and position in the middle of the z-buffer
	//these defaults fix the scaling from gui meshes exported directly from MAX
	//- but if your art pipeline is different, then you will have to set these
	//- explicity from script.
	m.setScale(1.f/32.f,1.f/24.f,0.001f);	
	m.translation( Vector3(0,0,0.1f) );
	mat->set( m );

	if ( !s_lighting_ )
	{
		//MOo::Colour takes either DWORD(argb) or floats (rgba)
		s_lighting_ = new Moo::LightContainer;
		s_lighting_->ambientColour( Moo::Colour(0xff101820) );
		/*s_lighting_->addDirectional( new Moo::DirectionalLight(
			Moo::Colour(0.75f,0.75f,0.75f,1.f), Vector3(0.5f,0.5f,-0.5f)));
		s_lighting_->addOmni( new Moo::OmniLight(
			Moo::Colour(0xff603000), Vector3(-1.f,-3.f,-3.f), 0.f, 50.f ) );
		s_lighting_->addOmni( new Moo::OmniLight(
			Moo::Colour(0xff181860), Vector3(-0.5f,2.f,5.f), 0.f, 50.f ) );*/
	}
}