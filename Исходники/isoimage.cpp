bool isoimage::ReadDir(const wxString &path, stat_vector_t& stat_vector)
{
    const wxCharBuffer buffer = path.ToAscii();
    const char *spath = buffer.data();

    return m_image.readdir(spath, stat_vector);
}