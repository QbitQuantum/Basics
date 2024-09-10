 //------------------------------------------------------------------------------
 void        SwapWeaponAction::Execute (void)
 {
     GetWindow ()->SwapPart(m_equipmentType, m_mount);
 }