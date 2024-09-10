void Inspect::Insert(std::ostream& stream, const Reflect::Data* val)
{
	Reflect::ScalarTranslator* scalar = Reflect::ReflectionCast< Reflect::ScalarTranslator >( val->m_Translator );
	if ( scalar )
	{
		String str;
		scalar->Print( val->m_Pointer, str );
		std::string str2 ( str.GetData() );
		Insert( stream, &str2 );
	}
}