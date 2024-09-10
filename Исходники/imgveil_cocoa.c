static char *image_int64_descpt(const char *image_path)
{
    FILE *fp = fopen(image_path, "rb");
    assert(fp);
    
    char *result = NULL;
    int8_t buf[kReadByteBlock];

	//contro iavr
	int32_t bytes_read = 0;
    int32_t times_write = 1; //count from 1(data length)
    int8_t new_line = 0;

    long filelen = length_file(fp);
       
    result = string_append(NULL, kInt64BeginDesc);
    
    char len_buf[128];  sprintf(len_buf, kTab""kTab"0x%016llx, ", (int64_t)filelen);
    char *temp = string_append(result, len_buf);
    
    free(result); result = temp;
    
    while ( ! feof(fp) )
    {        
        int32_t i = 0;
        
		size_t read_count = 0;
        size_t int64_count = 0;
        int64_t *pbuf = NULL;
        
		memset(buf, 0, kReadByteBlock);
		
		read_count = fread(buf, 1, kReadByteBlock, fp);
		int64_count = (read_count%8) ? (read_count/8 + 1) : (read_count/8);
		pbuf = (int64_t*)buf;
        
		for(i=0; i<int64_count; i++)
        {
            char bitDesc[128];
                        
            if(bytes_read + 8 < filelen)
            {                
                if((++times_write % 3) == 0)
                {
                    sprintf(bitDesc, "0x%016llx,\n", *(pbuf+i));
                    new_line = 1;
                }
                else
                {
                    sprintf(bitDesc, "%s0x%016llx, ", new_line ? kTab""kTab : "",  *(pbuf+i));

					if(new_line) new_line = 0;
                }
            }
            else
            {
                sprintf(bitDesc, "%s0x%016llx", new_line ? kTab""kTab : "", *(pbuf+i));
				if(new_line) new_line = 0;
            }
            
            char *tmp = string_append(result, bitDesc);
            free(result);
            result = tmp;

			bytes_read += 8;
        }
    }
    
    char *new_result = string_append(result, kInt64EndDesc);
    free(result);
    result = new_result;
    
    fclose(fp);
    
    return result;
}