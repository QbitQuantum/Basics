static void find_all_symbols(char *filename)
{
	char *vec[4]; /* kerneldoc -list file NULL */
	pid_t pid;
	int ret, i, count, start;
	char real_filename[PATH_MAX + 1];
	int pipefd[2];
	char *data, *str;
	size_t data_len = 0;

	vec[0] = KERNELDOC;
	vec[1] = LIST;
	vec[2] = filename;
	vec[3] = NULL;

	if (pipe(pipefd)) {
		perror("pipe");
		exit(1);
	}

	switch (pid=fork()) {
		case -1:
			perror("fork");
			exit(1);
		case  0:
			close(pipefd[0]);
			dup2(pipefd[1], 1);
			memset(real_filename, 0, sizeof(real_filename));
			strncat(real_filename, kernsrctree, PATH_MAX);
			strncat(real_filename, "/" KERNELDOCPATH KERNELDOC,
					PATH_MAX - strlen(real_filename));
			execvp(real_filename, vec);
			fprintf(stderr, "exec ");
			perror(real_filename);
			exit(1);
		default:
			close(pipefd[1]);
			data = malloc(4096);
			do {
				while ((ret = read(pipefd[0],
						   data + data_len,
						   4096)) > 0) {
					data_len += ret;
					data = realloc(data, data_len + 4096);
				}
			} while (ret == -EAGAIN);
			if (ret != 0) {
				perror("read");
				exit(1);
			}
			waitpid(pid, &ret ,0);
	}
	if (WIFEXITED(ret))
		exitstatus |= WEXITSTATUS(ret);
	else
		exitstatus = 0xff;

	count = 0;
	/* poor man's strtok, but with counting */
	for (i = 0; i < data_len; i++) {
		if (data[i] == '\n') {
			count++;
			data[i] = '\0';
		}
	}
	start = all_list_len;
	all_list_len += count;
	all_list = realloc(all_list, sizeof(char *) * all_list_len);
	str = data;
	for (i = 0; i < data_len && start != all_list_len; i++) {
		if (data[i] == '\0') {
			all_list[start] = str;
			str = data + i + 1;
			start++;
		}
	}
}