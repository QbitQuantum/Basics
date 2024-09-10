LiveScene::LiveScene() : m_isRoot( true )
{
	tbb::mutex::scoped_lock l( s_mutex );
	
	// initialize to the root path:
	MItDag it;
	it.getPath( m_dagPath );
}