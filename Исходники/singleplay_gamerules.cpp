	void CSingleplayRules::NPCKilled(CBaseEntity *pVictim, const CTakeDamageInfo &info)
	{
		CBasePlayer *pEntity = UTIL_GetLocalPlayer();
		if (pVictim->m_isRareEntity)
		{
			switch (GetSkillLevel())
			{
			case SKILL_EASY:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(3 * sk_money_multiplier1.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(5 * sk_exp_multiplier1.GetInt());
				}
				break;

			case SKILL_MEDIUM:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(3 * sk_money_multiplier2.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(5 * sk_exp_multiplier2.GetInt());
				}
				break;

			case SKILL_HARD:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(3 * sk_money_multiplier3.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(5 * sk_exp_multiplier3.GetInt());
				}
				break;

			case SKILL_VERYHARD:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(3 * sk_money_multiplier4.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(5 * sk_exp_multiplier4.GetInt());
				}
				break;

			case SKILL_NIGHTMARE:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(3 * sk_money_multiplier5.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(5 * sk_exp_multiplier5.GetInt());
				}
				break;
			}
		}
		else
		{
			switch (GetSkillLevel())
			{
			case SKILL_EASY:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(2 * sk_money_multiplier1.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(3 * sk_exp_multiplier1.GetInt());
				}
				break;

			case SKILL_MEDIUM:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(2 * sk_money_multiplier2.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(3 * sk_exp_multiplier2.GetInt());
				}
				break;

			case SKILL_HARD:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(2 * sk_money_multiplier3.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(3 * sk_exp_multiplier3.GetInt());
				}
				break;

			case SKILL_VERYHARD:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(2 * sk_money_multiplier4.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(3 * sk_exp_multiplier4.GetInt());
				}
				break;

			case SKILL_NIGHTMARE:
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(2 * sk_money_multiplier5.GetInt());
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(3 * sk_exp_multiplier5.GetInt());
				}
				break;
			}
		}
		pEntity->IncrementFragCount(1);

#define KILLING_SPREE_AMOUNT	5
#define KILLING_FRENZY_AMOUNT	10
#define OVERKILL_AMOUNT	15
#define RAMPAGE_AMOUNT	20
#define UNSTOPPABLE_AMOUNT	25
#define INCONCEIVABLE_AMOUNT	30
#define INVINCIBLE_AMOUNT	35
#define GODLIKE_AMOUNT	40

		if (info.GetInflictor() == pEntity)
		{
			if (sv_player_voice.GetBool())
			{
				if (sv_player_voice_kill.GetBool())
				{
					int killvoicerandom = random->RandomInt(0, sv_player_voice_kill_freq.GetInt());
					if (killvoicerandom == 0)
					{
						pEntity->EmitSound("Player.VoiceKill");
					}
				}
			}
		}

		if (sv_killingspree.GetBool())
		{
			int m_iKillsInSpree = pEntity->FragCount();

			if (m_iKillsInSpree == KILLING_SPREE_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_KILLINGSPREE");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(2);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(3);
				}
			}
			if (m_iKillsInSpree == KILLING_FRENZY_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_KILLINGFRENZY");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(4);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(6);
				}
			}
			if (m_iKillsInSpree == OVERKILL_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_OVERKILL");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(6);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(9);
				}
			}
			if (m_iKillsInSpree == RAMPAGE_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_RAMPAGE");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(8);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(12);
				}
			}
			if (m_iKillsInSpree == UNSTOPPABLE_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_UNSTOPPABLE");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(10);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(15);
				}
			}
			if (m_iKillsInSpree == INCONCEIVABLE_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_INCONCEIVABLE");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(12);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(18);
				}
			}
			if (m_iKillsInSpree == INVINCIBLE_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_INVINCIBLE");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(14);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(21);
				}
			}
			if (m_iKillsInSpree == GODLIKE_AMOUNT)
			{
				CFmtStr hint;
				hint.sprintf("#Valve_Hud_GODLIKE");
				pEntity->ShowLevelMessage(hint.Access());
				if (g_fr_economy.GetBool())
				{
					pEntity->AddMoney(16);
				}
				if (!g_fr_classic.GetBool())
				{
					pEntity->AddXP(24);
				}
			}
		}

		if (pVictim->m_isRareEntity)
		{
			if (g_fr_classic.GetBool())
			{
				pEntity->LevelUpClassic();
			}
		}
	}