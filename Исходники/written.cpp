/* mode 0 new file
 * mode 1 edit file
 */
int wama_file(int mode)
{
	char path[128];
	clean_screen();
	printf("Ruta del archivo: ");
	gets_s(path, 128);
	clean_screen();
	if (path[0] != '/') {
		char dev_path[128] = "/dev/";
		strcat(dev_path, path);
		strcpy(path, dev_path);
	}
	/* creamos el archivo 'path' */
	if ((touch(path, S_IRUSR | S_IWUSR)) < 0 && mode == NEW_FILE_MODE) {
		return -1;
	}
	int line_count = 1;
	char line[128];
	int fd;
	if ((fd = open(path, O_WRONLY)) < 0) {
		return -1;
	}
	if (mode == EDIT_FILE_MODE) {
		char *ch = read_file(path);
		write(fd, ch, strlen(ch));
		line_count = linecounter(ch);
		line_count++;
	}
	printf("\n\n\n %d ", line_count);
	char *data;
	while ( 1 ) {
		setwindow();
		subwindow(line_count);
		gets_s(line, 128);
		switch (checkWamaCommand(line)) {
			case 0:
				write(fd, line, strlen(line));
				write(fd, "\n", 1);
				break;
			case 1:
				close(fd);
				if (goto_wama_command(path, line_count) < 0) {
					return -1;
				}
				data = read_file(path);
				if ((fd = open(path, O_WRONLY)) < 0) {
					return -1;
				}
				write(fd, data, strlen(data));
				line_count--;
				break;
			case 2:
				close(fd);
				return 0;
				break;
		}
		line_count++;
		printf(" %d ", line_count);
	}
}