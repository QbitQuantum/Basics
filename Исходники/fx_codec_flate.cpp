 void FPDFAPI_FlateCompress(unsigned char* dest_buf, unsigned long* dest_size, const unsigned char* src_buf, unsigned long src_size)
 {
     compress(dest_buf, dest_size, src_buf, src_size);
 }