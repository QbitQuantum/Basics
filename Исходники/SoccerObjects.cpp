void SoccerGoal::PostPropRead(ObjectCreateStruct* pStruct)
{
	// Sanity checks...
	if( !pStruct )
		return;

	_mbscpy(( unsigned char * )pStruct->m_Filename, ( const unsigned char * )pStruct->m_Name );

	// Set the flags we want...
	pStruct->m_Flags = FLAG_TOUCH_NOTIFY;
	if( m_bBoxPhysics )
		pStruct->m_Flags |= FLAG_BOXPHYSICS;
}