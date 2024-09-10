QC_IO_NAMESPACE_BEGIN

//==============================================================================
// FileInputStream::FileInputStream
//
/**
   Constructs a FileInputStream by opening a connection to the file with
   the abstract pathname denoted by @c file.

   @param file the abstract pathname of the file to open
   @throws FileNotFoundException if a file with the specified name does not
           exist on the file system.  
   @throws IOException if the specified file could not be opened.  This includes
           the case where @c file refers to a directory instead of a normal file.
*/
//==============================================================================
FileInputStream::FileInputStream(const File& file)
{
	open(file.getPath());
}