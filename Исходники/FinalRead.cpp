int FinalRead::alfaBeta(int alfa, int beta)
{
	if (board.getTurnPlayer() == 1)
	{
		for (int i = 1; i <= board.getAbleNumber(); i++)
		{

			board.put(i);
			switch (board.getSCondition())
			{
			case 0:
				alfa = fmax(alfa, alfaBeta(alfa, beta));
				break;
			case 4:
				board.pass();
				alfa = fmax(alfa, alfaBeta(alfa, beta));
				board.undo();
				break;
			default:
				alfa = board.getNumber(1) - board.getNumber(2);
				count++;
				break;
			}
			board.undo();
			if (alfa >= beta)
			{
				return beta;
			}
			if (alfa > 0)
			{
				return alfa;
			}
		}
		return alfa;
	}
	if (board.getTurnPlayer() == 2)
	{
		for (int i = 1; i <= board.getAbleNumber(); i++)
		{
			board.put(i);
			switch (board.getSCondition())
			{
			case 0:
				beta = fmin(beta, alfaBeta(alfa, beta));
				break;
			case 4:
				board.pass();
				beta = fmin(beta, alfaBeta(alfa, beta));
				board.undo();
				break;
			default:
				beta = board.getNumber(1) - board.getNumber(2);
				count++;
				break;
			}
			board.undo();
			if (alfa >= beta)
			{
				return alfa;
			}
			if (beta < 0)
			{
				return beta;
			}
		}
		return beta;
	}
}int FinalRead::alfaBetaRev(int alfa, int beta)