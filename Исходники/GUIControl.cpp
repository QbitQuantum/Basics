void CGUIControl::UpdateVisibility(const CGUIListItem *item)
{
  if (m_visibleCondition)
  {
    bool bWasVisible = m_visibleFromSkinCondition;
    m_visibleFromSkinCondition = m_visibleCondition->Get(item);
    if (!bWasVisible && m_visibleFromSkinCondition)
    { // automatic change of visibility - queue the in effect
  //    CLog::Log(LOGDEBUG, "Visibility changed to visible for control id %i", m_controlID);
      QueueAnimation(ANIM_TYPE_VISIBLE);
    }
    else if (bWasVisible && !m_visibleFromSkinCondition)
    { // automatic change of visibility - do the out effect
  //    CLog::Log(LOGDEBUG, "Visibility changed to hidden for control id %i", m_controlID);
      QueueAnimation(ANIM_TYPE_HIDDEN);
    }
  }
  // check for conditional animations
  for (unsigned int i = 0; i < m_animations.size(); i++)
  {
    CAnimation &anim = m_animations[i];
    if (anim.GetType() == ANIM_TYPE_CONDITIONAL)
      anim.UpdateCondition(item);
  }
  // and check for conditional enabling - note this overrides SetEnabled() from the code currently
  // this may need to be reviewed at a later date
  bool enabled = m_enabled;
  if (m_enableCondition)
    m_enabled = m_enableCondition->Get(item);

  if (m_enabled != enabled)
    MarkDirtyRegion();

  m_allowHiddenFocus.Update(item);
  if (UpdateColors())
    MarkDirtyRegion();
  // and finally, update our control information (if not pushed)
  if (!m_pushedUpdates)
    UpdateInfo(item);
}