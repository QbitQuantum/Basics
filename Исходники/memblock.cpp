/// Reads the object from stream \p s
void memblock::read (istream& is)
{
    written_size_type n;
    is >> n;
    is.verify_remaining ("read", "ustl::memblock", n);
    resize (n);
    is.read (data(), writable_size());
    is.align (alignof (n));
}