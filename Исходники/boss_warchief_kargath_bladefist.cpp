    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (Assassins_Timer)
        {
            if (Assassins_Timer <= diff)
            {
                SpawnAssassin();
                Assassins_Timer = 0;
            }
            else Assassins_Timer -= diff;
        }
        if (InBlade)
        {
            if (Wait_Timer)
            {
                if (Wait_Timer <= diff)
                {
                    if (target_num <= 0)
                    {
                        // stop bladedance
                        InBlade = false;
                        me->SetSpeed(MOVE_RUN, 2);
                        (*me).GetMotionMaster()->MoveChase(me->getVictim());
                        Blade_Dance_Timer = 30000;
                        Wait_Timer = 0;
                        if (HeroicMode)
                            Charge_timer = 5000;
                    }
                    else
                    {
                        //move in bladedance
                        float x, y, randx, randy;
                        randx = float(rand() % 40);
                        randy = float(rand() % 40);
                        x = 210 + randx ;
                        y = -60 - randy ;
                        (*me).GetMotionMaster()->MovePoint(1, x, y, me->GetPositionZ());
                        Wait_Timer = 0;
                    }
                }
                else Wait_Timer -= diff;
            }
        }
        else
        {
            if (Blade_Dance_Timer)
            {
                if (Blade_Dance_Timer <= diff)
                {
                    target_num = TARGET_NUM;
                    Wait_Timer = 1;
                    InBlade = true;
                    Blade_Dance_Timer = 0;
                    me->SetSpeed(MOVE_RUN, 4);
                    return;
                }
                else Blade_Dance_Timer -= diff;
            }
            if (Charge_timer)
            {
                if (Charge_timer <= diff)
                {
                    DoCast(SelectUnit(SELECT_TARGET_RANDOM, 0), H_SPELL_CHARGE);
                    Charge_timer = 0;
                }
                else Charge_timer -= diff;
            }
            if (Summon_Assistant_Timer <= diff)
            {
                for (uint32 i = 0; i < summoned; i++)
                {
                    switch (rand() % 3)
                    {
                    case 0:
                        me->SummonCreature(MOB_HEARTHEN_GUARD, AddsEntrance[0], AddsEntrance[1], AddsEntrance[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                        break;
                    case 1:
                        me->SummonCreature(MOB_SHARPSHOOTER_GUARD, AddsEntrance[0], AddsEntrance[1], AddsEntrance[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                        break;
                    case 2:
                        me->SummonCreature(MOB_REAVER_GUARD, AddsEntrance[0], AddsEntrance[1], AddsEntrance[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);
                        break;
                    }
                }
                if (rand() % 100 < 6) summoned++;
                Summon_Assistant_Timer = 15000 + (rand() % 5000) ;
            }
            else Summon_Assistant_Timer -= diff;

            DoMeleeAttackIfReady();
        }

        if (resetcheck_timer <= diff)
        {
            float tempx;
            tempx = me->GetPositionX();
            if (tempx > 255 || tempx < 205)
            {
                EnterEvadeMode();
                return;
            }
            resetcheck_timer = 5000;
        }
        else resetcheck_timer -= diff;
    }