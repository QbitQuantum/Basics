VFolder::VFolder( const VFolder& inSource)
{
	fPath = inSource.GetPath();
	xbox_assert( fPath.IsFolder());
	fFolder.Init( this);
}