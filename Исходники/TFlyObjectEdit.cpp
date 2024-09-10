void TFlyObjectEdit::selectObject( int x, int y , unsigned typeBit )
{
	//int num = scene.GetObjectNumber(TRUE, TRUE);
	//if ( num != 0 )
	//{
	//	m_selectIDVec.resize( num );
	//	num = scene.GetObjects( &m_selectIDVec[0] , TRUE , TRUE , m_selectIDVec.size() );
	//}

	m_selectIDVec.clear();
	for( int i = 0 ; i < g_editDataVec.size() ; ++i )
	{
		EditData& data = g_editDataVec[i];
		if ( data.type & typeBit )
			m_selectIDVec.push_back( data.id );
	}
	OBJECTid id = view.HitObject( 
		&m_selectIDVec[0] , m_selectIDVec.size() , 
		m_camera.Object() , x , y  );

	selectObject( id );
}