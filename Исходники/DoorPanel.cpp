void CDoorPanel::Reset( const bool bEnteringGameMode )
{
	m_fLastVisibleDistanceCheckTime = 0.0f;
	m_bHasDelayedStateEvent = false;

	SDoorPanelResetEvent resetEvent( bEnteringGameMode );
	StateMachineHandleEventBehavior( resetEvent );

	SetStateById( GetInitialBehaviorStateId() );
}