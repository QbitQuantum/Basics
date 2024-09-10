/// Handles an entity leaving the Trigger area.
void RPG_Trigger::ProcessExit(VisBaseEntity_cl* entity)
{
  // check if this entity is in inside the trigger.
  int foundIndex = m_insideEntities.Find(entity);

  if(foundIndex > -1)
  {
    m_insideEntities.RemoveAt(foundIndex);

    OnExit(entity);
    if(m_onExitSource)
      m_onExitSource->TriggerAllTargets();
    TriggerScriptEvent("OnExit", "*o", entity);
  }
}