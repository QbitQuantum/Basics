void GenerateCode::Execute()
{
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();
	Action* pVal = new Validate(pManager);
	string error;

	if (dynamic_cast<Validate*>(pVal)->isValid(error) || error.find("zero") != string::npos)
	{
		ofstream Code;
		Code.open("Code.cpp");

		// Search for Start ID & End ID & Variable Names
		int start_index, end_index;
		set<string> vars;
		set<string>::iterator it;
		for (int i = 0; i < pManager->getStatCount(); ++i)
		{
			string tmp, data;
			tmp = pManager->StatList[i]->CopyData();
			for (int i = 0; i < tmp.size(); i++)
			{
				if (tmp[i] == ' ')
					continue;
				data += tmp[i];
			}
			// Search for Start ID & End ID
			if (dynamic_cast<Start*>(pManager->StatList[i]))
				start_index = i;
			if (dynamic_cast<End*>(pManager->StatList[i]))
				end_index = i;
			// Search for Variable Names
			if (dynamic_cast<Read*>(pManager->StatList[i]))
			{
				char* cData = new char[data.size() + 1];
				strcpy(cData, data.c_str());
				char* var = strtok(cData, ",");
				while (var) {
					vars.insert(var);
					var = strtok(NULL, ",");
				}
				delete[] cData;
			}
			// Search for Variable Names
			if (dynamic_cast<Write*>(pManager->StatList[i]))
			{
				char* cData = new char[data.size() + 1];
				strcpy(cData, data.c_str());
				char* var = strtok(cData, ",");
				while (var) {
					vars.insert(var);
					var = strtok(NULL, ",");
				}
				delete[] cData;
			}
			// Search for Variable Names
			if (dynamic_cast<Assign*>(pManager->StatList[i]))
			{
				string Left = data.substr(0, data.find('='));
				vars.insert(Left);
				string Right = data.substr(data.find('=') + 1);
				string v;
				for (int i = 0; i < Right.size(); i++)
				{
					if ((Right[i] == '+' || Right[i] == '-' || Right[i] == '*' || Right[i] == '/' || Right[i] == '%') && v.size())
					{
						vars.insert(v);
						v.clear();
					}
					else if (isalpha(Right[i]))
						v += Right[i];
				}
				if (v.size())
					vars.insert(v);
			}
			// Search for Variable Names
			if (dynamic_cast<Cond*>(pManager->StatList[i]))
			{
				string cond = dynamic_cast<Cond*>(pManager->StatList[i])->getCond();
				string Left = data.substr(0, data.find(cond));
				string Right = data.substr(data.find(cond) + cond.size());
				string v;
				for (int i = 0; i < Left.size(); i++)
				{
					if ((Left[i] == '+' || Left[i] == '-' || Left[i] == '*' || Left[i] == '/' || Left[i] == '%') && v.size())
					{
						vars.insert(v);
						v.clear();
					}
					else if (isalpha(Left[i]))
						v += Left[i];
				}
				if (v.size())
					vars.insert(v);
				v.clear();
				for (int i = 0; i < Right.size(); i++)
				{
					if ((Right[i] == '+' || Right[i] == '-' || Right[i] == '*' || Right[i] == '/' || Right[i] == '%') && v.size())
					{
						vars.insert(v);
						v.clear();
					}
					else if (isalpha(Right[i]))
						v += Right[i];
				}
				if (v.size())
					vars.insert(v);
			}
		}

		string GeneratedCode;
		int curr_idx, next_idx;
		curr_idx = next_idx = start_index;

		// Generate Start code
		GeneratedCode += pManager->StatList[curr_idx]->GenerateCode(pManager->StatList, pManager->getStatCount(), end_index, curr_idx, next_idx, 0);

		// Generate variables declarations
		if (vars.size())
		{
			GeneratedCode += "\tdouble";
			for (it = vars.begin(); it != vars.end(); ++it)
			{
				GeneratedCode += " " + *it + " = 0";
				if (distance(it, vars.end()) > 1)
					GeneratedCode += ",";
			}
			GeneratedCode += ";\n";
		}

		// Generate code for each statement after Start till End
		while (1)
		{
			curr_idx = next_idx;

			GeneratedCode += pManager->StatList[curr_idx]->GenerateCode(pManager->StatList, pManager->getStatCount(), end_index, curr_idx, next_idx, 1);

			if (curr_idx == end_index)
				break;
		}

		Code << GeneratedCode;

		Code.close();

		pOut->MsgBox("Code generated successfully !", "Info", false);
		pOut->PrintMessage("Code generated successfully !");
	}
	else
		pOut->MsgBox("Sorry. You can only generate code of a valid flowchart. And this is NOT !", "Error", true);
}