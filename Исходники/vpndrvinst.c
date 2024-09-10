// Main function
void MainFunction(char *cmd)
{
	char tmp[MAX_SIZE];
	bool first = true;
	bool exit_now = false;

	while (true)
	{
		if (first && StrLen(cmd) != 0 && g_memcheck == false)
		{
			first = false;
			StrCpy(tmp, sizeof(tmp), cmd);
			exit_now = true;
			Print("%s\n", cmd);
		}
		else
		{
			_exit(0);
		}
		Trim(tmp);
		if (StrLen(tmp) != 0)
		{
			UINT i, num;
			bool b = false;
			TOKEN_LIST *token = ParseCmdLine(tmp);
			char *cmd = token->Token[0];

			num = sizeof(test_list) / sizeof(TEST_LIST);
			for (i = 0;i < num;i++)
			{
				if (!StrCmpi(test_list[i].command_str, cmd))
				{
					char **arg = Malloc(sizeof(char *) * (token->NumTokens - 1));
					UINT j;
					for (j = 0;j < token->NumTokens - 1;j++)
					{
						arg[j] = CopyStr(token->Token[j + 1]);
					}
					test_list[i].proc(token->NumTokens - 1, arg);
					for (j = 0;j < token->NumTokens - 1;j++)
					{
						Free(arg[j]);
					}
					Free(arg);
					b = true;
					_exit(1);
					break;
				}
			}
			FreeToken(token);

			if (exit_now)
			{
				break;
			}
		}
	}
}