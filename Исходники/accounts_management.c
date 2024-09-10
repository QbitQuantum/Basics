AccountsList* loadAccountsFromFile(const char *filename)
{
	int file_descriptor = open(filename, O_RDONLY);

	if(file_descriptor < 0)
	{
		if(errno == ENOENT)
			errorMessage("File \"%s\" doesn't exist.", filename);
		else
			errorMessage("File \"%s\" can't be opened.", filename);
		return NULL;
	}

	unsigned int nb_accounts;
	int return_value = readUIntFromFile(file_descriptor, &nb_accounts, ';');
	if(return_value < 0)
	{
		if(return_value == -2)
			errorMessage("Number of accounts not found in file.");
		else
			errorMessage("An error has occurred while reading file.");

		close(file_descriptor);
		return NULL;
	}
	goAfterCharacterInFile(file_descriptor, ';');

	AccountsList *list = createAccountsList(nb_accounts);
	traceMessage("Accounts list of length %d created", (int) nb_accounts);
	char buffer1[50], buffer2[50], *login, *password;
	unsigned int tmp;
	int x, y;

	int i;
	for(i=0; i<nb_accounts; i++)
	{
		// lecture du login.
		if(readStringFromFile(file_descriptor, buffer1, 50, ':') < 0 || (login = extractStringWithoutSpace(buffer1)) == NULL)
		{
			destroyAccountsList(list);
			close(file_descriptor);
			return NULL;
		}
		if(!isCorrectLoginOrPassword(login))
		{
			warningMessage("Login \"%s\" readed in file is syntactically false. Accounts list can't be load from file.", login);
			destroyAccountsList(list);
			close(file_descriptor);
			return NULL;
		}
		goAfterCharacterInFile(file_descriptor, ':');

		// Lecture du mot de passe.
		if(readStringFromFile(file_descriptor, buffer2, 50, ':') < 0 || (password = extractStringWithoutSpace(buffer2)) == NULL)
		{
			destroyAccountsList(list);
			close(file_descriptor);
			return NULL;
		}
		if(!isCorrectLoginOrPassword(password))
		{
			warningMessage("Password \"%s\" readed in file is syntactically false. Accounts list can't be load from file.", password);
			destroyAccountsList(list);
			close(file_descriptor);
			return NULL;
		}
		goAfterCharacterInFile(file_descriptor, ':');

		// lecture de x.
		return_value = readUIntFromFile(file_descriptor, &tmp, ':');
		if(return_value == -1)
		{
			errorMessage("An error has occurred while reading file.");
			destroyAccountsList(list);
			close(file_descriptor);
			return NULL;
		}
		else if(return_value == -2)
			x = -1;
		else
			x = (int) tmp;
		goAfterCharacterInFile(file_descriptor, ':');

		// Lecture de y si necessaire.
		if(x != -1)
		{
			return_value = readUIntFromFile(file_descriptor, &tmp, ';');
			if(return_value == -1)
			{
				errorMessage("An error has occurred while reading file.");
				destroyAccountsList(list);
				close(file_descriptor);
				return NULL;
			}
			else if(return_value == -2)
				x = y = -1;
			else
				y = (int) tmp;
		}
		else
			y = -1;

		goAfterCharacterInFile(file_descriptor, ';');

		addAccountToList(list, login, password, x, y);
	}

	close(file_descriptor);
	return list;
}