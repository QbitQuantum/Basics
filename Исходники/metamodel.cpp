void CRegionalMetaModel::Predict( const REAL* prInputs, REAL* prOutputs )
{
	vector< CTrustRegion* >hitRegions;

	//best region or multiple region?
	FindTrustRegions( prInputs, hitRegions );
//	FindBestRegion( prInputs, hitRegions );

	int nOutputs = GetOutputs();
	int nHitRegions = hitRegions.size();
	//for each trusted regional model, predict the result to vcOutputs[i][1...nOutputs]
	vector< vector<REAL> > vcOutputs(nHitRegions);
	for( int i=0; i<nHitRegions; i++ ){
		vcOutputs[i].resize( nOutputs );
		CMetaModel* pModel = m_vcMetaModels[ hitRegions[i]->GetModelId() ];
		pModel->Predict( prInputs, &vcOutputs[i][0] );
	}

	int nInputs = GetInputs();
	REAL rSumWeights = 0;
	vector< REAL > vcSum( nOutputs, 0.0 );
	//modified on 02/012/05 using trust probability
	for( i=0; i<nHitRegions; i++ ){
		ASSERT( nInputs==hitRegions[i]->m_ptCen.size() );
		vector<REAL> vcDistSqr(nInputs, 0.0);
		vector<REAL> vcRadSqr(nInputs, 0.0);
		vector<REAL> vcProbs(nInputs,0.0);
		transform( prInputs, prInputs+nInputs, hitRegions[i]->m_ptCen.begin(), vcDistSqr.begin(), diff_sqr<REAL>() );
//		cout<<"dist sqr:";
//		copy( vcDistSqr.begin(), vcDistSqr.end(), ostream_iterator<REAL>(cout, " ") ); cout<<endl;
		transform( hitRegions[i]->m_vcRadius.begin(), hitRegions[i]->m_vcRadius.end(), hitRegions[i]->m_vcRadius.begin(), vcRadSqr.begin(), multiplies<REAL>() );
//		cout<<"radius sqr:";
//		copy( vcRadSqr.begin(), vcRadSqr.end(), ostream_iterator<REAL>(cout, " ") ); cout<<endl;
		transform( vcDistSqr.begin(), vcDistSqr.end(), vcRadSqr.begin(), vcProbs.begin(), divides<REAL>() );
//		cout<<"probs :";
//		copy( vcProbs.begin(), vcProbs.end(), ostream_iterator<REAL>(cout, " ") ); cout<<endl;
		REAL rProb = accumulate( vcProbs.begin(), vcProbs.end(), 0.0) / nInputs;
		rProb = max( 1-rProb, 0.0 );

		cdump<<"prob "<<i<<" "<<rProb<<"\t";

		REAL rWeight = rProb / hitRegions[i]->GetSphereRadius();
		for( int j=0; j<nOutputs; j++ ){
			vcSum[j] += vcOutputs[i][j]*rWeight;
		}
		rSumWeights += rWeight;
	}
	if( rSumWeights > 0 ){
		transform( vcSum.begin(), vcSum.end(), vcSum.begin(), bind2nd(divides<REAL>(), rSumWeights) );
		copy( vcSum.begin(), vcSum.end(), prOutputs );
	}else{
		copy( vcOutputs[0].begin(), vcOutputs[0].end(), prOutputs );
	}

	//compute the average outputs according to inverse sphere radius
/*	vector< REAL > vcSum( nOutputs, 0.0 );
	REAL rSumInvRadius = 0;
	for( i=0; i<nHitRegions; i++ ){
		REAL rInvRadius = 1.0 / hitRegions[i]->GetSphereRadius();
		for( int j=0; j<nOutputs; j++ ){
			vcSum[j] += vcOutputs[i][j]*rInvRadius;
		}
		rSumInvRadius += rInvRadius;
	}
	transform( vcSum.begin(), vcSum.end(), vcSum.begin(), bind2nd(divides<REAL>(), rSumInvRadius) );
	copy( vcSum.begin(), vcSum.end(), prOutputs );
*/
	cdump<<"pred..."<<nHitRegions<<" nets"<<endl;
}