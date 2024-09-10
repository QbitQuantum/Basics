Stack<Error>* Corrector::CheckExpression(Lexema *input) {
	int i = 0;
	int count_bracket = 0;
	while (input[i].GetType() != Type_Lexems::terminal) {
		if (IsDigit(input[i])) {
			if(IsDigitRight(input[i]) == false){
				AddError(input[i].GetPosition(), "Ошибка в числе. Позиция ошибки: ");
			}
		}
		if (IsBinaryOperaion(input[i]))
		{
			if (input[i+1].GetType() == Type_Lexems::terminal)
			{
				AddError(input[i].GetPosition(), "Ошибка в бинарной операции. Позиция ошибки: ");
			}
			if (input[i + 1].GetType() != Type_Lexems::terminal && IsBinaryOperaion(input[i+1])) {
				AddError(input[i].GetPosition(), "Ошибка в повторе бинарной операций. Позиция ошибки: ");
			}
			if (input[i + 1].GetType() != Type_Lexems::terminal && input[i + 1].GetType() == Type_Lexems::close_bracket) {
				AddError(input[i].GetPosition(), "Ошибка в бинарной операции, пропущен аргумент. Позиция ошибки: ");
			}
		}
		if (IsOperationUnary(input[i]))
		{
			if (input[i + 1].GetType() == Type_Lexems::terminal) {
				AddError(input[i].GetPosition(), "Ошибка в унарной операции. Позиция ошибки: ");
			}
			if (input[i + 1].GetType() != Type_Lexems::terminal && input[i + 1].GetType() == Type_Lexems::close_bracket)
			{
				AddError(input[i].GetPosition(), "Ошибка в унарной операции, пропущен аргумент. Позиция ошибки: ");
			}
		}
		if (IsOpenBracket(input[i]))
		{
			count_bracket++;
		}
		if (IsCloseBracket(input[i]))
		{
			count_bracket--;
			if (count_bracket<0)
			{
				AddError(input[i].GetPosition(), "Ошибка в закрывающей скобке. Позиция ошибки: ");
			}
		}
		i++;
	}
	if (count_bracket != 0)
	{
		AddError("Ошибка в скобках.");
	}
	return &errors;
}