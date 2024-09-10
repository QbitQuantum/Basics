void StdFileInput::SetPosition(std::size_t n)
{
    Rewind();
    
    for (std::size_t i = 0; i < n; ++i)
        Next();
}