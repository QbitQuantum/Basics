int save_json_to_file(const char* file_name, struct json_object *obj)
{  
	int len = strlen(json_object_get_string(obj));
	char arr[len+1] ;
	memcpy(arr, json_object_get_string(obj), len);
	
	//fprintf(stdout,"%s Save json to file. filename=%s jsonContent=%s\n", getSystemTime( timeChar), file_name, arr);

	FILE *fp = fopen(file_name, "w");
	if (NULL == fp)
	{ 
		fprintf(stderr, "%s Open file failed ! filename=%s\n", getSystemTime( timeChar),file_name);
	}else
	{ 
		int ret = fwrite(arr, len, 1, fp);
		if ( ret < 1)
		{ 
			fprintf(stderr, "%s write to file failed ! file_name=%s\n",getSystemTime( timeChar), file_name);
		}

		fclose(fp);
	}

	json_object_put(obj); 	//free the space.

	return 0;
}