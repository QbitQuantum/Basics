double compute_archive_ratio(t_idx& idx)
{
    size_t bits_encoding = idx.factor_text.size();
    size_t bits_blockmap = idx.block_map.size_in_bytes() * 8;
    size_t bits_compressed_dict = 0;
    {
        const uint8_t* dict = (const uint8_t*) idx.dict.data();
        size_t dict_size = idx.dict.size();
        std::vector<uint8_t> dict_buf(dict_size*2);
        uint8_t* out_buf = dict_buf.data();
        uint64_t out_len = dict_buf.size();
        int c*k = compress2(out_buf,&out_len,dict,dict_size,9);
        if(c*k != Z_OK) {
            if(c*k == Z_MEM_ERROR) LOG(FATAL) << "error compressing dictionary: Z_MEM_ERROR";
            if(c*k == Z_BUF_ERROR) LOG(FATAL) << "error compressing dictionary: Z_BUF_ERROR";
            if(c*k == Z_STREAM_ERROR) LOG(FATAL) << "error compressing dictionary: Z_STREAM_ERROR";
            LOG(FATAL) << "error compressing ditionary: UNKNOWN ERROR ("<<c*k<<")";
        }
        bits_compressed_dict = out_len * 8;
    }
    size_t encoding_bits_total = bits_encoding + bits_compressed_dict + bits_blockmap;
    size_t text_size_bits = idx.size() * 8;
    
    double archive_ratio = 100.0 * double(encoding_bits_total) / double(text_size_bits);
    return archive_ratio;
}