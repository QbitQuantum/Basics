/// Updates the life state of all objects.  Newly-spawned objects are promoted to full "alive" status,
/// and objects marked as "dead" are culled from the manager.
void GameObjectManager::updateObjectLifeStates()
{
  // Promote new objects to "fully alive" and cull dead objects
  for(ObjectSetIter it = m_objects.begin(); it != m_objects.end();)
  {
    switch((*it)->m_lifeState)
    {
      case GameObject::LS_DEAD:
      {
        ObjectSetIter murderDeathKill = it;
        ++it;
        deleteObject(*murderDeathKill);
      } break;
      case GameObject::LS_NEW:
      {
        (*it)->m_lifeState = GameObject::LS_ALIVE;
        ++it;
      } break;
      default:
      {
       ++it;
      } break;
    };
  }
}