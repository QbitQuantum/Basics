void Chipset::sendToRamString(const std::string &msg)
{
	std::string word;
	std::vector<std::string> words;

	std::stringstream stream(msg);
	while (std::getline(stream, word, ' '))
	{
		if (word.length() > 0)
			words.push_back(word.c_str());
	}

	bool foundInstruction = false;
	size_t i;
	for (i = 0; i < _instVect.size(); i++)
	{
		if (words[0] == _instVect[i].name)
		{
			foundInstruction = true;
			break;
		}
	}

	if (foundInstruction == false)
		raiseException(BadInstException());
	if (_instVect[i].nb_param != (words.size() - 1))
		raiseException(SyntaxException());

	Inst *new_Instruction;
	if (_instVect[i].nb_param >= 1)
	{
		eOperandType type = checkNumber(words[1]);
		size_t nb_end = words[1].find(")");
		size_t nb_begin = words[1].find("(");
		std::string numberOnly = words[1].substr(nb_begin + 1, (nb_end - nb_begin) - 1);

		new_Instruction = new Inst(_instVect[i].inst, numberOnly, type);
	}
	else
	{
		new_Instruction = new Inst(_instVect[i].inst);
	}
	if (new_Instruction->getOpCode() == EXIT)
		_isExited = true;
	_ram.PutInst(new_Instruction);
}