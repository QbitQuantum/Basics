int main(int argc, char *argv[])
{
	char *password_file = NULL;
	char *username = NULL;
	bool create_new = false;
	bool delete_user = false;
	FILE *fptr, *ftmp;
	char password[MAX_BUFFER_LEN];
	int rc;
	bool do_update_file = false;
	char *backup_file;

	signal(SIGINT, handle_sigint);
	signal(SIGTERM, handle_sigint);

	OpenSSL_add_all_digests();

	if(argc == 4){
		if(!strcmp(argv[1], "-c")){
			create_new = true;
		}else if(!strcmp(argv[1], "-D")){
			delete_user = true;
		}
		password_file = argv[2];
		username = argv[3];
	}else if(argc == 3){
		if(!strcmp(argv[1], "-U")){
			do_update_file = true;
			password_file = argv[2];
		}else{
			password_file = argv[1];
			username = argv[2];
		}
	}else{
		print_usage();
		return 1;
	}

	if(create_new){
		rc = get_password(password, 1024);
		if(rc) return rc;
		fptr = fopen(password_file, "wt");
		if(!fptr){
			fprintf(stderr, "Error: Unable to open file %s for writing. %s.\n", password_file, strerror(errno));
			return 1;
		}
		rc = output_new_password(fptr, username, password);
		fclose(fptr);
		return rc;
	}else{
		fptr = fopen(password_file, "r+t");
		if(!fptr){
			fprintf(stderr, "Error: Unable to open password file %s. %s.\n", password_file, strerror(errno));
			return 1;
		}

		backup_file = malloc(strlen(password_file)+5);
		snprintf(backup_file, strlen(password_file)+5, "%s.tmp", password_file);

		if(create_backup(backup_file, fptr)){
			fclose(fptr);
			free(backup_file);
			return 1;
		}

		ftmp = tmpfile();
		if(!ftmp){
			fprintf(stderr, "Error: Unable to open temporary file. %s.\n", strerror(errno));
			fclose(fptr);
			free(backup_file);
			return 1;
		}
		if(delete_user){
			rc = delete_pwuser(fptr, ftmp, username);
		}else if(do_update_file){
			rc = update_file(fptr, ftmp);
		}else{
			rc = get_password(password, 1024);
			if(rc){
				fclose(fptr);
				fclose(ftmp);
				unlink(backup_file);
				free(backup_file);
				return rc;
			}
			/* Update password for individual user */
			rc = update_pwuser(fptr, ftmp, username, password);
		}
		if(rc){
			fclose(fptr);
			fclose(ftmp);
			unlink(backup_file);
			free(backup_file);
			return rc;
		}

		if(copy_contents(ftmp, fptr)){
			fclose(fptr);
			fclose(ftmp);
			fprintf(stderr, "Error occurred updating password file.\n");
			fprintf(stderr, "Password file may be corrupt, check the backup file: %s.\n", backup_file);
			free(backup_file);
			return 1;
		}
		fclose(fptr);
		fclose(ftmp);

		/* Everything was ok so backup no longer needed. May contain old
		 * passwords so shouldn't be kept around. */
		unlink(backup_file);
		free(backup_file);
	}

	return 0;
}