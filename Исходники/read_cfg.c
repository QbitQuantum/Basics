/* search the key and return it's offset 
 * in the file if succeed.*/
int cfg_searchKey(FILE *fp,sftpcfg_t config)
{
	char src_key[CFG_KEY_SIZE];
	char dest_key[CFG_KEY_SIZE];
	char line[CFG_VALUE_SIZE];
	char regexp[REGEXP_SIZE];
	int offset = 0;
	int len = 0;
	
	memset(line,0,sizeof(line));
	memset(src_key,0,sizeof(src_key));
	memset(dest_key,0,sizeof(dest_key));
	memset(regexp,0,sizeof(regexp));

	sprintf(regexp,"%%[^%c]",config.sep_char);
	long curr_offset = 0;
	curr_offset = ftell(fp);

	/* make sure seek from the head of file */
	Fseek(fp,0,SEEK_SET);
	while(fgets(line,LINE_SIZE,fp))
	{
		len = strlen(line);	
		offset += len;
		/* skip comments */
		if(is_comment(line,config.comment_char))
		{
				continue;
		}
		sscanf(line,regexp,src_key);	
		cut_blank(src_key,dest_key);
		if(strcmp(dest_key,config.key) == 0)
		{
			Fseek(fp,curr_offset,SEEK_SET);
			/* back to the head of line */
			offset -= len;
			return offset;	
		}
	memset(dest_key,0,sizeof(dest_key));
	}
	Fseek(fp,curr_offset,SEEK_SET);
	return -1;
}