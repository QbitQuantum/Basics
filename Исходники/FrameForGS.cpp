		m_CpuUsage.UpdateStats();

		cpuUsage.Write(L" | EE: %3d%%", m_CpuUsage.GetEEcorePct());
		cpuUsage.Write(L" | GS: %3d%%", m_CpuUsage.GetGsPct());

		if (THREAD_VU1)
			cpuUsage.Write(L" | VU: %3d%%", m_CpuUsage.GetVUPct());

		pxNonReleaseCode(cpuUsage.Write(L" | UI: %3d%%", m_CpuUsage.GetEEcorePct());)
	}

	const u64& smode2 = *(u64*)PS2GS_BASE(GS_SMODE2);

	SetTitle( pxsFmt( L"Slot %d | Speed%ls: %3d%% (%.02f)%ls | %ls-%ls | %s",
		States_GetCurrentSlot(),
		limiterStr, lround(per), fps,
		cpuUsage.c_str(),
		(smode2 & 2) ? L"frame" : L"field",
		(smode2 & 1) ? L"i" : L"p",
		WX_STR(fromUTF8(gsDest)))
	);
}

void GSFrame::OnActivate( wxActivateEvent& evt )
{
	if( IsBeingDeleted() ) return;

	evt.Skip();
	if( wxWindow* gsPanel = GetViewport() ) gsPanel->SetFocus();
}
