size_t zlib2_compress_entire(const size_t _input_buffer_size, char *_input_buffer,
                            const size_t _output_buffer_size, char *_output_buffer,
                            const int level)
{
    size_t compressed_output_size = _output_buffer_size;
    compress2 ((Bytef*) _output_buffer, &compressed_output_size, (Bytef*) _input_buffer, (uLong) _input_buffer_size, level);
    return compressed_output_size;
}