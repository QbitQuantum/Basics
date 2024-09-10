	void MonsterAI::OnEvent(const AIEvent &event)
	{
        BaseAI::OnEvent(event);
        CMonster *monster = dynamic_cast<CMonster*>(m_Owner);
		if (monster == NULL)
		{
			LogError(AI_MODULE, "MosterAI has no owner object to process event %s...",
				BaseAI::Event2Str(event.Type()));
			return;
		}
		LogInfo(AI_MODULE, "monster(id=%s) recv ai event:%s",
			monster->GetExID().tostring(),
			BaseAI::Event2Str(event.Type())
);
		switch(event.Type())
		{
		case ET_HURT:
			{
				m_FightObj->OnHurted();
				EscapeSpring();

                const HurtEvent &hevent = (const HurtEvent&) event;
                GBHSpring(hevent.Hurt);

                // notify taunt event.
                TauntEvents events(monster->GetTauntHandler());
                events.Attacked(hevent.AttackerId, hevent.AttackerType, hevent.Hurt);
			}
			break;

        case ET_BORN:
            {
                Resume(0);
                //RunScript(monster->GetBornScriptName().c_str());
            }
            break;

        case ET_TIMERCYCLE:
            {
                //RunScript(monster->GetCycleScript().c_str());
            }
            break;

        case ET_REBORN:
            {
                m_RebornTime = timeGetTime();
                Resume(0);
                //RunScript(monster->GetBornScriptName().c_str());
            }
            break;

        case ET_RETURN:
            {
                m_FightObj->ReturnPeace();
            }
            break;

        case ET_KILL:
            {
                //RunScript(monster->GetDeadScriptName().c_str());
                monster->OnDied();
            }
            break;
		}
	}