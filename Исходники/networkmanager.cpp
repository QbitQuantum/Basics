void NetworkManager::GameStart()
{
	PacketType type;
	ErrorType error;
	bool gameOver = false;

	Position attackpos;
	Position hitpos;

	while (!gameOver)
	{
		error = network.GetPacketType(&type);

		switch (type)
		{
		case PKT_SC_ERROR:
			if (error == ET_OPPOSITION_DISCONNECTED)
				puts("상대방의 접속이 끊어졌습니다.");
			else
				puts("알 수 없는 에러입니다.");
			return;
			break;
		case PKT_SC_MY_TURN:
		{
			while (true)
			{
				if (m_player->GetType() == Ai)
				{
					AI* ai = (AI*)m_player;
					attackpos = ai->AttackShip();
				}
				else
				{
					attackpos = m_player->AttackShip();
				}

				printf_s("%c%c\n", attackpos.x, attackpos.y);

				error = network.SubmitAttack(PositionToCoord(attackpos));

				if (error == ET_INVALID_ATTACK)
					puts("유효하지 않은 공격 위치입니다.");
				else
					break;
			}
		}
			break;
		case PKT_SC_ATTACK_RESULT:
		{
			Network::AttackResultData result;
			result = network.GetAttackResult();
			if (result.isMine)
			{
				puts("공격 결과:");

				printf_s("%c%c ", result.pos.mX + 'a', result.pos.mY + '1');

				switch (result.attackResult)
				{
				case AR_DESTROY_AIRCRAFT:
					printf_s("Result: DESTROY_AIRCRAFT\n");
					break;
				case AR_DESTROY_BATTLESHIP:
					printf_s("Result: DESTROY_BATTLESHIP\n");
					break;
				case AR_DESTROY_CRUISER:
					printf_s("Result: DESTROY_CRUISER\n");
					break;
				case AR_DESTROY_DESTROYER:
					printf_s("Result: DESTROY_DESTROYER\n");
					break;
				case AR_HIT:
					printf_s("Result: HIT");
					break;
				case AR_MISS:
					printf_s("Result: MISS");
					break;

				}


				if (m_player->GetType() == Ai)
				{
					AI* ai = (AI*)m_player;
					ai->TakeAttackResult(attackpos, result.attackResult);
				}
				else
				{
					m_player->TakeAttackResult(attackpos, result.attackResult);
				}

			}
			else
			{
				puts("피격 결과:");
				hitpos.x = result.pos.mX + 'a';
				hitpos.y = result.pos.mY + '1';

				m_player->HitCheck(hitpos);
				printf_s("%c%c", hitpos.x, hitpos.y);
			}
		}
			break;
		case PKT_SC_GAME_OVER:
		{
			Network::GameResultData gameresult;
			gameresult = network.GetGameResult();

			if (gameresult.isWinner)
				puts("승리!!!");
			else
				puts("패배...");
			printf_s("턴 수: %d\n", gameresult.turns);
			gameOver = true;
		}
			break;
		default:
			throw Network::UNEXPECTED_PACKET;
			break;
		}

	}


}