/// Reads the exception from stream \p is.
void file_exception::read (istream& is)
{
    libc_exception::read (is);
    string filename;
    is >> filename;
    is.align (8);
    filename.copyto (filename, VectorSize(m_Filename));
}