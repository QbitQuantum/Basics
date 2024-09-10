/// Generate a string representation of this object path with all package and object delimiters converted to valid
/// directory delimiters for the current platform.
///
/// @param[out] rString  File path string representation of this path.
void AssetPath::ToFilePathString( String& rString ) const
{
	rString.Remove( 0, rString.GetSize() );

	if( !m_pEntry )
	{
		return;
	}

	EntryToFilePathString( *m_pEntry, rString );
}