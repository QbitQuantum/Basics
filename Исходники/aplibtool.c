int execute_command(cmd_data_t *cmd_data)
{
    int target = 0;
    char *command;
    int a, total_len = 0;
    char *args[4];

    for (a=0; a < cmd_data->num_args; a++) {
        if (cmd_data->arglist[a]) {
            total_len += strlen(cmd_data->arglist[a]) + 1;
        }
    }

    command = (char *)malloc( total_len );
    command[0] = 0;

    for (a=0; a < cmd_data->num_args; a++) {
        if (cmd_data->arglist[a]) {
            strcat(command, cmd_data->arglist[a]);
            strcat(command, " ");
        }
    }

    command[strlen(command)-1] = 0;

    if (!silent) {
        puts(command);
    }

    cmd_data->num_args = target;
    cmd_data->arglist[cmd_data->num_args] = NULL;
    command = shell_esc(command);

    args[0] = SHELL_CMD;
    args[1] = "-c";
    args[2] = command;
    args[3] = NULL;
    return spawnvp(P_WAIT, args[0], args);
}