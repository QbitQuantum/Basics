static int
mac_init_internal(int ignore_errors)
{
    const char *filename;
    char line[LINE_MAX];
    FILE *file;
    int error;

    error = 0;

    LIST_INIT(&label_default_head);

    if (!issetugid() && getenv("MAC_CONFFILE") != NULL)
        filename = getenv("MAC_CONFFILE");
    else
        filename = MAC_CONFFILE;
    file = fopen(filename, "re");
    if (file == NULL)
        return (0);

    while (fgets(line, LINE_MAX, file)) {
        char *comment, *parse, *statement;

        if (line[strlen(line)-1] == '\n')
            line[strlen(line)-1] = '\0';
        else {
            if (ignore_errors)
                continue;
            fclose(file);
            error = EINVAL;
            goto just_return;
        }

        /* Remove any comment. */
        comment = line;
        parse = strsep(&comment, "#");

        /* Blank lines OK. */
        statement = next_token(&parse);
        if (statement == NULL)
            continue;

        if (strcmp(statement, "default_labels") == 0) {
            char *name, *labels;

            name = next_token(&parse);
            labels = next_token(&parse);
            if (name == NULL || labels == NULL ||
                    next_token(&parse) != NULL) {
                if (ignore_errors)
                    continue;
                error = EINVAL;
                fclose(file);
                goto just_return;
            }

            if (mac_add_type(name, labels) == -1) {
                if (ignore_errors)
                    continue;
                fclose(file);
                goto just_return;
            }
        } else if (strcmp(statement, "default_ifnet_labels") == 0 ||
                   strcmp(statement, "default_file_labels") == 0 ||
                   strcmp(statement, "default_process_labels") == 0) {
            char *labels, *type;

            if (strcmp(statement, "default_ifnet_labels") == 0)
                type = "ifnet";
            else if (strcmp(statement, "default_file_labels") == 0)
                type = "file";
            else if (strcmp(statement, "default_process_labels") ==
                     0)
                type = "process";

            labels = next_token(&parse);
            if (labels == NULL || next_token(&parse) != NULL) {
                if (ignore_errors)
                    continue;
                error = EINVAL;
                fclose(file);
                goto just_return;
            }

            if (mac_add_type(type, labels) == -1) {
                if (ignore_errors)
                    continue;
                fclose(file);
                goto just_return;
            }
        } else {
            if (ignore_errors)
                continue;
            fclose(file);
            error = EINVAL;
            goto just_return;
        }
    }

    fclose(file);

    internal_initialized = 1;

just_return:
    if (error != 0)
        mac_destroy_internal();
    return (error);
}