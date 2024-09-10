 void FightStateScript::ReceiveEvent(BaseType::EntityType *entity, const BaseType::EventType &ev)
 {
     SelfType::ReceiveEvent(entity, ev);
     if(ev.Type() == ET_SCRIPT_USESKILL)
     {
         const ScriptUseSkillEvent &sev = (const ScriptUseSkillEvent&) ev;
         CMonster *monster = dynamic_cast<CMonster*>(entity->GetOwner());
         CServerRegion *region = dynamic_cast<CServerRegion*>(monster->GetFather());
         MonsterAI *ai = dynamic_cast<MonsterAI*>(entity);
         long id = sev.id;
         long lvl = sev.lvl;
         long actTime = monster->GetActModify(sev.id);
         if(sev.type == ScriptUseSkillEvent::SHAPE)
         {
             if(sev.trace)
             {
                 // trace the target
                 m_SkillTracer.Init(id, lvl, sev.targetId, sev.traceTime);
                 m_skillScriptID = sev.scriptId;
                 m_State = TRACING;
                 entity->Resume(0);
                 return ;
             }
             else
             {
                 CMoveShape *target = AIUtils::FindShape(region, sev.targetId);
                 if(target == NULL)
                 {
                     OnUseSkillEnd(SkillTracer::FAILED);
                     return ;
                 }
                 ai->BeginSkill(id, lvl, target);
             }
         }
         else if(sev.type == ScriptUseSkillEvent::CELL)
         {
             ai->BeginSkill(id, lvl, sev.x, sev.y);
         }
         m_skillScriptID = sev.scriptId;
         // register act time timer
         ai->SetTimer(AIDriver::SCRIPT_EVENT, actTime);
     }
     else if(ev.Type() == ET_SCRIPT_SKILLEND)
     {
         OnUseSkillEnd(SkillTracer::Okay);
     }
     else if(ev.Type() == ET_KILL)
     {
         entity->ChangeState(ST_DEAD);
     }
 }