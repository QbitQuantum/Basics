static void SendTable_CalcNextVectorElems( SendTable *pTable )
{
	for ( int i=0; i < pTable->GetNumProps(); i++ )
	{
		SendProp *pProp = pTable->GetProp( i );
		
		if ( pProp->GetType() == DPT_DataTable )
		{
			SendTable_CalcNextVectorElems( pProp->GetDataTable() );
		}
		else if ( pProp->GetOffset() < 0 )
		{
			pProp->SetOffset( -pProp->GetOffset() );
			pProp->SetFlags( pProp->GetFlags() | SPROP_IS_A_VECTOR_ELEM );
		}
	}
}