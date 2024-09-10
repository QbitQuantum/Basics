void CPhysicsMotionController::RemoveCore( IVP_Core *pCore )
{
	int index = m_coreList.Find(pCore);
	if ( !m_coreList.IsValidIndex(index) )
	{
#if DEBUG
		Msg("removed invalid core !!!\n");
#endif
		return;
	}
	m_coreList.Remove( index );
	pCore->rem_core_controller( static_cast<IVP_Controller_Independent *>(this) );
}