/* Initialize the fake registry.
 */
void InitializeFakeRegistry(void)
{
	/* There must be a better way of doing this:
	 */
	char row[10*1024], key[10*1024], value[10*1024];
	FILE *f_ptr;
	int i;

	/* Initialize fake registry linked list.
	 */
	reg_head_ptr = reg_tail_ptr = NULL;

	/* Load a previously saved fake registry (if this fails we assume one
	 * does not yet exist and leave creating one up to the save function).
	 */
	if ( GetUserConfigPath(reg_file, FR_FILENAME_LEN) == NULL)
		return;

	/* Append filename of registry to path.
	 */
	strcat(reg_file, REG_FILENAME);

	/* Test file, quit if does not exist (first time beebem ran so
	 * no entries).
	 */
	if ( (f_ptr=fopen(reg_file, "r")) == NULL)
		return;

	/* Load existing registry
	 */
	while (fgets( row, 256, f_ptr ) != NULL){
		i = strlen(row) -1;
		while(i>=0){
 			if (row[i]<32) row[i] = '\0';
				i--;
		}

		if (strlen(row)<=0)
			continue;

		if (row[0] == '#')
			continue;

		for(i=0; i< (int) strlen(row); i++)
			if (row[i] == '#'){
				row[i]='\0';
				break;
			}

		i = strlen(row) -1;
		while(i>=0){
			if (row[i] == '=') break;
			i--;
		}
		if (i<=0)
			continue;

		memcpy(key, row, i);
		key[i]='\0';

		value[0] = '\0';
		if(strlen(row)-i-1>0){
			memcpy(value, row+i+1, strlen(row)-i-1);
			value[strlen(row)-i-1] = '\0';
		}

		i = strlen(value) -1;
		while(value[i]<=32 && i>=0){
			value[i] = '\0';
			i--;
		}

		if (SetFakeRegistryItem(key, value) != TRUE)
                	pERROR(dL"Failed to add '%s' to the registry!\n", dR
			 , key);
	}
	fclose(f_ptr);
}