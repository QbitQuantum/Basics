/*
This function outputs the Question
Message and gets the player's input.

If the player inputs "i", the game has Indra speak and
continue down the Conversation Tree.
If the player inputs "p", the game has Phil speak and
continue down the Conversation Tree.
Else, the game gives the Bad Input message and re-prompts
the player to give an input.

@return Result - INDRA if player inputs "i"
                 PHIL if player inputs "p"
*/
Choose Question::OutputText()
{
	bool chose_valid_choice = false;
	//give the Question message.
	question_msg_->OutputText();
	Choose choice;

	while (!chose_valid_choice)
	{
		//prompt the user for input.
		char player_input[kPlayerInputSize];
		cout << "> ";
		cin >> player_input;

		//if the user inputted "i" or "I"
		if (_strcmpi(player_input, "i") == 0)
		{
			choice = INDRA;
			chose_valid_choice = true;
		}
		//if the user inputted "p" or "P"
		else if (_strcmpi(player_input, "p") == 0)
		{
			choice = PHIL;
			chose_valid_choice = true;
		}
		else
		{
			//give the Bad Input Message.
			bad_input_msg_->OutputText();
		}
	}
	return choice;
}