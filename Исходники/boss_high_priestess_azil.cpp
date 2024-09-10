        npc_seismic_shardAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            me->SetDisableGravity(true);
            DoCast(me, SPELL_SEISMIC_SHARD_VISUAL);

            Movement::MoveSplineInit init(me);
            FillPath(me->GetPosition(), init.Path());
            init.SetFly();
            init.Launch();

            events.ScheduleEvent(EVENT_SEISMIC_SHARD_MOUNT, 2400);
        }