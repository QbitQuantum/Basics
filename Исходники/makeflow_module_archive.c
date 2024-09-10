int makeflow_archive_copy_preserved_files(struct archive_instance *a, struct batch_task *t, char *task_path ) {
	struct batch_file *f;
	struct stat buf;
	struct list_cursor *cur = list_cursor_create(t->output_files);
	// Iterate through output files
	for(list_seek(cur, 0); list_get(cur, (void**)&f); list_next(cur)) {
		char *file_name = xxstrdup(f->outer_name);
		debug(D_MAKEFLOW_HOOK,"Trying to copy file to %s",file_name);
		char *file_to_check = xxstrdup(file_name);
		//Check to see if the directory was copied as an empty file/incorrectly
		stat(dirname(file_to_check),&buf);
		if(S_ISREG(buf.st_mode)){
			debug(D_MAKEFLOW,"Removing empty file in the place of directory name %s",file_to_check);
			char *dirEmpty = string_format("rm -rf %s",file_to_check);
			system(dirEmpty);
			free(dirEmpty);
		}
		free(file_to_check);
		// Gets path of output file
		char *output_file_path = string_format("%s/output_files/%s",task_path,basename(file_name));
		char *directory_name = xxstrdup(file_name);
		debug(D_MAKEFLOW_HOOK,"Creating directory %s",dirname(directory_name));
		if(strcmp(directory_name,file_name) != 0){
			//Create the upper level directory to copy the output files into if necessary
			if (!create_dir(directory_name, 0777) && errno != EEXIST){
				debug(D_ERROR|D_MAKEFLOW_HOOK,"Failed to create directory %s",directory_name);
				free(directory_name);
				free(output_file_path);
				free(file_name);
				return 1;
			}
		}
		free(directory_name);
		// Copy output file or directory over to specified location
		if(path_is_dir(output_file_path) != 1){
			int success = copy_file_to_file(output_file_path, file_name);
			free(output_file_path);
			free(file_name);
			if (!success) {
				list_cursor_destroy(cur);
				debug(D_ERROR|D_MAKEFLOW_HOOK,"Failed to copy output file %s to %s\n", output_file_path, file_name);
				return 1;
			}
		}
		else{
			if(copy_dir(output_file_path, file_name) != 0){
				list_cursor_destroy(cur);
								debug(D_ERROR|D_MAKEFLOW_HOOK,"Failed to copy output file %s to %s\n", output_file_path, file_name);
				free(output_file_path);
							free(file_name);
								return 1;
						}
			free(output_file_path);
			free(file_name);
		}
		}


	list_cursor_destroy(cur);

	return 0;
}