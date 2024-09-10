InstrumentFunctionNoteStacking::ChordTable::ChordTable() :
	QVector<Chord>()
{
	for( int i = 0;
		i < static_cast<int>( sizeof s_initTable / sizeof *s_initTable );
		i++ )
	{
		push_back( Chord( s_initTable[i].m_name, s_initTable[i].m_semiTones ) );
	}
}