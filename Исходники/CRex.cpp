void CRex::vTerminate()
{
	int i;
	CRexException cre;

	try
	{
		// 継承元クラスに属するメンバ変数の終了処理を実行します。
		CRealCodedGa::vTerminate();

		if( piParentLoc != NULL )
		{
			delete[] piParentLoc;
			piParentLoc = NULL;
		}
		
		if( pplfChildren != NULL )
		{
			for( i = 0;i < iChildrenNumber; i++ )
			{
				if( pplfChildren[i] != NULL )
				{
					delete[] pplfChildren[i];
					pplfChildren[i] = NULL;
				}
			}
			delete[] pplfChildren;
			pplfChildren = NULL;
		}
		if( pplfNormalizeRand != NULL )
		{
			for( i = 0;i < iChildrenNumber; i++ )
			{
				if( pplfNormalizeRand[i] != NULL )
				{
					delete[] pplfNormalizeRand[i];
					pplfNormalizeRand[i] = NULL;
				}
			}
			delete[] pplfNormalizeRand;
			pplfNormalizeRand = NULL;
		}
		if( plfTempVector != NULL )
		{
			delete[] plfTempVector;
			plfTempVector = NULL;
		}
		if( plfCentroid != NULL )
		{
			delete[] plfCentroid;
			plfCentroid = NULL;
		}
		if( plfChildVector != NULL )
		{
			delete[] plfChildVector;
			plfChildVector = NULL;
		}
		if( plfNormalizeRand != NULL )
		{
			delete[] plfNormalizeRand;
			plfNormalizeRand = NULL;
		}
		if( plfChildrenCentroid != NULL )
		{
			delete[] plfChildrenCentroid;
			plfChildrenCentroid = NULL;
		}
		if( plfUpperEvalChildrenCentroid != NULL )
		{
			delete[] plfUpperEvalChildrenCentroid;
			plfUpperEvalChildrenCentroid = NULL;
		}
		if( plfCentroidSteep != NULL )
		{
			delete[] plfCentroidSteep;
			plfCentroidSteep = NULL;
		}
	}
	catch( ... )
	{
		cre.SetErrorInfo( REX_MEMORY_RELEASE_ERROR, "vTerminate", "CUndx", "確保したメモリの解放に失敗しました。", __LINE__ );
		throw( cre );
	}
}