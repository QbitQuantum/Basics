//---------------------------------------------------------
void CPC_Cluster_Analysis::Write_Result(CSG_Table *pTable, long nElements, int nCluster, double SP)
{
	CSG_String			s;
	CSG_Table_Record	*pRecord;

	pTable->Destroy();
	s	= CSG_String::Format(_TL("Cluster Analysis PC"));
	s	+= CSG_String::Format(SG_T("_%s"), pInput->Get_Name());
	pTable->Set_Name(s);

	pTable->Add_Field(_TL("ClusterID")	, SG_DATATYPE_Int);
	pTable->Add_Field(_TL("Elements")	, SG_DATATYPE_Int);
	pTable->Add_Field(_TL("Variance")	, SG_DATATYPE_Double);

	s.Printf(SG_T("\n%s:\t%ld \n%s:\t%d \n%s:\t%d \n%s:\t%f"),
		_TL("Number of Elements")			, nElements,
		_TL("\nNumber of Variables")		, m_nFeatures,
		_TL("\nNumber of Clusters")			, nCluster,
		_TL("\nValue of Target Function")	, SP
	);

	s.Append(CSG_String::Format(SG_T("%s\t%s\t%s"), _TL("Cluster"), _TL("Elements"), _TL("Variance")));

	for( int j=0; j<m_nFeatures; j++ )
	{
		s.Append(CSG_String::Format(SG_T("\t%02d_%s"), j + 1, pInput->Get_Field_Name(m_Features[j])));
		pTable->Add_Field(pInput->Get_Field_Name(m_Features[j]), SG_DATATYPE_Double);
	}

	Message_Add(s);

	for( int i=0; i<nCluster; i++ )
	{
		s.Printf(SG_T("%d\t%d\t%f"), i, nMembers[i], Variances[i]);

		pRecord	= pTable->Add_Record();
		pRecord->Set_Value(0, i);
		pRecord->Set_Value(1, nMembers[i]);
		pRecord->Set_Value(2, Variances[i]);

		for( int j=0; j<m_nFeatures; j++ )
		{
			s.Append(CSG_String::Format(SG_T("\t%f"), Centroids[i][j]));

			pRecord->Set_Value(j + 3, Centroids[i][j]);
		}

		Message_Add(s);
	}
}