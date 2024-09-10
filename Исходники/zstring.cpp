//          <6
const char * zstring::ucase()
{ 	unsigned int i;for(i=0;i<=mem_data.mem_length;i++)mem_data.mem_string[i]=toupper(mem_data.mem_string[i]);	
return mem_data.mem_string;
}