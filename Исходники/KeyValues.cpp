//-------------------------------------------------------------------------------------------------
void KeyValues::Erase() {

	for( unsigned int i = 0; i < root.values.size(); i++ ) {
		DeleteSection( root.values[i].section );
	}
	
	Rewind();

}