void ModelPoseDebugInfo::AddInfoText( InfoText *x, ModelPoseDebugInfo *pOld )
{
	if ( x )
	{
		// Try to set the proper flags on the info text
		x->m_uiFlags &= ~F_SEEN_LAST_FRAME;
		x->m_uiFlags |= F_SEEN_THIS_FRAME;
	}

	// If we have smth to compare against
	if ( pOld )
	{
		// Search for the same activity/label in the other model pose debug info
		ModelPoseDebugInfo &o = *pOld;
		int k = o.m_iCurrentText;
		if ( x )
		{
			for ( ; k < o.m_arrTxt.Count(); ++ k )
			{
				InfoText &txt = o.m_arrTxt[k];
				if ( ( txt.m_uiFlags & F_SEEN_THIS_FRAME ) &&
					!stricmp( x->m_chActivity, txt.m_chActivity ) &&
					!stricmp( x->m_chLabel, txt.m_chLabel ) &&
					( x->m_iActivity == txt.m_iActivity ) )
				{
					x->m_flTimeAlive = txt.m_flTimeAlive;
					break;
				}
			}
		}
		else
		{
			k = o.m_arrTxt.Count();
		}

		// Range of finished activities
		int iFinishedRange[2] = { o.m_iCurrentText, k };

		// Check whether this is a new message
		if ( k == o.m_arrTxt.Count() )
		{
			if ( !x )
			{
				o.m_iCurrentText = k;
			}
			else
			{
				// Don't update the current when insertion happens and don't have finished commands
				iFinishedRange[1] = iFinishedRange[0];
			}
		}
		else
		{
			o.m_iCurrentText = k + 1;
			if ( x )
			{
				x->m_uiFlags |= F_SEEN_LAST_FRAME;
				x->m_flTimeAlive += gpGlobals->frametime;
			}
		}

		// Everything before finished
		for ( int iFinished = iFinishedRange[0]; iFinished < iFinishedRange[1]; ++ iFinished )
		{
			InfoText &txtFinished = o.m_arrTxt[ iFinished ];

			if ( txtFinished.m_uiFlags & F_SEEN_THIS_FRAME )
				txtFinished.m_uiFlags |= F_SEEN_LAST_FRAME;

			txtFinished.m_uiFlags &= ~F_SEEN_THIS_FRAME;

			txtFinished.m_flTimeToLive -= gpGlobals->frametime;
			txtFinished.m_flTimeAlive += gpGlobals->frametime;

			if ( txtFinished.m_flTimeToLive >= 0.0f )
				m_arrTxt.AddToTail( txtFinished );
		}
	}

	if ( x )
	{
		// Now add it to the array
		x->m_flTimeToLive = ui_posedebug_fade_out_time.GetFloat();
		m_arrTxt.AddToTail( *x );
	}
}