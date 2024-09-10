bool
executeIOCheckFunc(const char* cmd, char **argv, int argc)
{
	if(!cmd) {
		return false;
	}

	AmazonGahpCommand *one_cmd = NULL;

	amazon_gahp_commands.Rewind();
	while( amazon_gahp_commands.Next(one_cmd) ) {
		if( !strcasecmp(one_cmd->command.c_str(), cmd) && 
		 	one_cmd->iocheckfunction ) {
			return one_cmd->iocheckfunction(argv, argc);
		}
	}

	dprintf (D_ALWAYS, "Unknown command %s\n", cmd);
	return false;
}