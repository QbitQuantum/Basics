static __inline__ gint
nmp_debug_create_log_file(const gchar *file_folder, const gchar *name)
{
    gint err;
    time_t time_now;
    struct tm tm_now;
    gchar file_name[MAX_FILE_NAME];
    gchar log_file_path[PATH_MAX];
    gchar old_file_path[PATH_MAX];

    if (!file_folder || !name)
        return -E_INVAL;

    if ((err = nmp_debug_create_path(file_folder,
        PATH_FOLDER_PERM, log_file_path)))
        return err;

	memset(file_name, 0, sizeof(file_name));
    strncpy(file_name, name, MAX_FILE_NAME - 1);
    strcpy(old_file_path, log_file_path);

    if (strlen(log_file_path) + strlen(file_name)
        + 2 > PATH_MAX)
        return -ENAMETOOLONG;

    time_now = time(NULL);

    strcat(log_file_path, "/");
    strcat(log_file_path, file_name);

    log_file = fopen(log_file_path, "r");
    if (log_file)
    {
        fclose(log_file);
        log_file = NULL;

        if (!localtime_r(&time_now, &tm_now))
            return -errno;

        sprintf(file_name + strlen(file_name), 
            "."HM_LOG_TIME_FORMAT, 
            tm_now.tm_year + 1900, 
            tm_now.tm_mon + 1, 
            tm_now.tm_mday, 
            tm_now.tm_hour, 
            tm_now.tm_min, 
            tm_now.tm_sec
        );

        if (strlen(old_file_path) + strlen(file_name)
            + 2 > PATH_MAX)
            return -ENAMETOOLONG;

        strcat(old_file_path, "/");
        strcat(old_file_path, file_name);
        rename(log_file_path, old_file_path);
    }

    log_file = fopen(log_file_path, "w");
    if (log_file)
    {
        fprintf(log_file, HM_LOG_TITLE, ctime(&time_now));
        fflush(log_file);
    }

    return log_file ? 0 : -errno;
}