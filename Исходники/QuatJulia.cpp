void QuatJulia::generate()
{
/// eval at uniform grid
	int i, j, k;
	const float grid = 1.f / (float)m_numGrid;
	const Vector3F origin(-.5f+grid * .5f, 
							-.5f+grid * .5f, 
							-.5f+grid * .5f);
	int n = 0;
	for(k=0; k<m_numGrid; ++k ) {
		for(j=0; j<m_numGrid; ++j ) {
			for(i=0; i<m_numGrid; ++i ) {
				Vector3F sample = origin + Vector3F(grid * i, grid * j, grid * k);
				if( evalAt( sample*3.2f ) > 0.f ) {
					n++;
					cvx::Sphere sp;
					sample *= m_scaling;
					sp.set(sample, .001f);
					m_tree->insert((const float *)&sample, sp);
				}
			}
		}
	}
	m_tree->finishInsert();
}