void GamePhase::CheckCollision()
{
	
	for (size_t i = 0; i < GamePhase::playerPath.size() - 1; i++)
	{
		if (GamePhase::enemy.first == GamePhase::playerPath[i].first && GamePhase::enemy.second == GamePhase::playerPath[i].second)
		{
			// enemy fail

			// klavesy
			Reader::RemovePair('w', GamePhase::up);
			Reader::RemovePair('a', GamePhase::left);
			Reader::RemovePair('s', GamePhase::down);
			Reader::RemovePair('d', GamePhase::right);

			// timer
			DeleteTimerQueueTimer(NULL, GamePhase::waitHandle, NULL);

			GamePhase::returnFunctionCorrect();

			return;
		}
	}
	
	for (size_t i = 0; i < GamePhase::enemyPath.size() - 1; i++)
	{
		if (GamePhase::player.first == GamePhase::enemyPath[i].first && GamePhase::player.second == GamePhase::enemyPath[i].second)
		{
			// player fail

			// klavesy
			Reader::RemovePair('w', GamePhase::up);
			Reader::RemovePair('a', GamePhase::left);
			Reader::RemovePair('s', GamePhase::down);
			Reader::RemovePair('d', GamePhase::right);

			// timer
			DeleteTimerQueueTimer(NULL, GamePhase::waitHandle, NULL);

			GamePhase::returnFunctionBad();

			return;
		}
	}
}