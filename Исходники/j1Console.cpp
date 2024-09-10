bool j1Console::ProcessString(const char* input)
{
	bool ret = false;

	last_message.Clear();
	if(input != nullptr && strlen(input) > 0 && strlen(input) < MAX_INPUT_LINE_SIZE)
	{
		char line[MAX_INPUT_LINE_SIZE];
		strcpy_s(line, MAX_INPUT_LINE_SIZE, input);

		char* context = nullptr;
		char* token = strtok_s(line, " ", &context);

		arguments.Clear();
		do
		{
			arguments.PushBack(p2SString(token));
		} while(token = strtok_s(NULL, " ", &context));

		uint nargs = arguments.Count() - 1;

		const Command* com = FindCommand(arguments[0].GetString());

		if(com != nullptr && com->listener != nullptr)
		{
			if(nargs >= com->min_arguments && nargs <= com->max_arguments)
			{
				// If we reach this point we are ready to call a listener
				if(ret = com->listener->OnCommand(com, arguments, last_message))
					last_error.create("No error");
				else
				{
					last_error = last_message;
					last_message.Clear();
				}
			}
			else
				last_error.create("Command arguments mismatch");
		}
		else
		{
			const CVar* var = FindCVar(arguments[0].GetString());

			if(var == nullptr)
				last_error.create("Command / CVar not found");
			else
			{
				switch(nargs)
				{
					case 1:
					{
						if(((CVar*)var)->SetFromString(arguments[1].GetString()) == true)
						{
							if(var->listener != nullptr)
								var->listener->OnCVar(var);
						}
					}
					case 0:
					{
						char output[COMMAND_NAME_SIZE + 25];
						sprintf_s(output, COMMAND_NAME_SIZE + 25, "%s: %s", var->name, var->Printable());
						last_message += output;
						ret = true;
					} break;
					default:
					last_error.create("Command arguments mismatch");
					break;
				}
			}
		}
			
	}
	else
		last_error.create("Invalid input line");

	if(ret == true)
		Print(last_message.GetString());
	else
		PrintError(last_error.GetString());

	return ret;
}