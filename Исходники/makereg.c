static void docommand(FILE *str,char *line)
{
    char *cmd;

    cmd = gettoken(&line);
    if (!cmd) return;

    switch (assoc(commands,cmd)) {
	case CMD_AGENT:
	    doagentcmd(str,line);
	    break;
	default:
	    fatal("Invalid command",cmd);
	    break;
	}
    
}