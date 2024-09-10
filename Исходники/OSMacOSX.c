/*++
 ********************************************************************************
 
 FUNCTION:
 fSize
 
 DESCRIPTION:
 Return the size of the file
 
 ARGUMENTS:
 File handle
 
 RETURNS:
 Size of file in 64 bits
 
 ********************************************************************************
 --*/
u64 fSize( FILE *handle )
{
	u64 size,pos;
	pos = fTell( handle );
	fEnd( handle );
	size = fTell( handle );
	fPos( pos, handle );
	return size;
}