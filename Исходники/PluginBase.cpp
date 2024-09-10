void PluginBase::writeTempFile( XMP_IORef srcFileRef, XMP_IORef tmpFileRef, XMP_StringPtr xmpStr )
{
	IOAdapter srcFile( srcFileRef );
	IOAdapter tmpFile( tmpFileRef );
	std::string buffer( xmpStr );

	this->writeTempFile( srcFile, tmpFile, buffer );
}