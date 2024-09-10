static int exec_init(void *arg) {
	exec_data_t *data = (exec_data_t *)arg;

	setgid(data->omv_mock.mock_gid);
	setuid(data->omv_mock.omv_uid);
	execvpe("/bin/bash", argv, data->env);

	return 255;
}