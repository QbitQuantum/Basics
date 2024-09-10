bool BoolTable::
GenerateMinimalFalseBVList( List< BoolVector > &result )
{
	List< BoolVector > *baseBVList = new List< BoolVector >( );
	List< BoolVector > *oldBVList = new List< BoolVector >( );
	List< BoolVector > *newBVList = new List< BoolVector >( );
	BoolVector *bv = NULL;
	BoolValue bval = FALSE_VALUE;
	GenerateMaximalTrueBVList( *baseBVList );
	if( baseBVList->IsEmpty( ) ) {
		delete baseBVList;
		delete oldBVList;
		delete newBVList;
		return true;
	}

		// NEGATE
	baseBVList->Rewind( );
	while( baseBVList->Next( bv ) ) {
		for( int i = 0; i < numRows; i++ ) {
			bv->GetValue( i, bval );
			if( bval == TRUE_VALUE ) {
				bv->SetValue( i, FALSE_VALUE );
			}
			else {
				bv->SetValue( i, TRUE_VALUE );
			}
		}
	}

		// DISTRIB & COMBINE
	BoolVector *baseBV = NULL;
	BoolVector *newBV = NULL;
	BoolVector *oldBV = NULL;
	baseBVList->Rewind( );

	while( baseBVList->Next( baseBV ) ) {
		for( int i = 0; i < numRows; i++ ) {
			baseBV->GetValue( i, bval );
			if( bval == TRUE_VALUE ) {
				if( oldBVList->IsEmpty( ) ) {
					newBV = new BoolVector( );
					newBV->Init( numRows );
					for( int j = 0; j < numRows; j++ ) {
						if( i == j ) {
							newBV->SetValue( j, TRUE_VALUE );
						}
						else {
							newBV->SetValue( j, FALSE_VALUE );
						}
					}
					newBVList->Append( newBV );
				}
				else {
					oldBVList->Rewind( );
					while( oldBVList->Next( oldBV ) ) {
						newBV = new BoolVector( );
						newBV->Init( oldBV );
						newBV->SetValue( i, TRUE_VALUE );
						newBVList->Append( newBV );
					}
				}
			}
		}
		oldBVList->Rewind( );
		while( oldBVList->Next( oldBV ) ) {
			delete oldBV;
		}
		delete oldBVList;
		oldBVList = newBVList;
		newBVList = new List< BoolVector >( );
	}

		// PRUNE
	oldBVList->Rewind( );
	while( oldBVList->Next( newBV ) ) {
		result.Rewind( );
		bool addBV = true;
		bool isSubset = false;
		while( result.Next( oldBV ) ) {
			oldBV->IsTrueSubsetOf( *newBV, isSubset );
			if( isSubset ) {
				addBV = false;
				break;
			}
			newBV->IsTrueSubsetOf( *oldBV, isSubset );
			if( isSubset ) { 
				result.DeleteCurrent( );
			}
		}
		if( addBV ) {
			result.Append( newBV );
		}
		else delete newBV;
	}

	baseBVList->Rewind( );
	while( baseBVList->Next( oldBV ) ) {
		delete oldBV;
	}
	delete baseBVList;
	delete newBVList;
	delete oldBVList;
	return true;
}