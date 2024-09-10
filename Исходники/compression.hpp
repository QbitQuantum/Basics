output_t decompress_as (const compressed_data& in)
{
    output_t out;
    decompress(in, out);
    return out;
}