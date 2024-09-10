void CMemoryWatcherDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		if (!h)
		{
			if (m_ProcessID)
				h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, m_ProcessID);
			else
				h = GetCurrentProcess();
			if (!h)
				return;
		}
		PROCESS_MEMORY_COUNTERS pmc;
		if (GetProcessMemoryInfo(h, &pmc, sizeof(pmc)))
		{
			points.push(pmc.WorkingSetSize);
			points_pagefile.push(pmc.PagefileUsage);
			peak = pmc.PeakWorkingSetSize;
			peak_pagefile = pmc.PeakPagefileUsage;
		}
		else
		{
			points.push(0);
			points_pagefile.push(0);
		}
		if (points.size() > m_NumSteps + 1)
		{
			points.pop();
			points_pagefile.pop();
		}
		SIZE_T l, total;
		CDC * idc = CDC::FromHandle(img->GetDC());
		CPen pen, * oldpen, * oldpen2, pen2, pen3;
		CString s;
		// setting pen color
		pen.CreatePen(PS_SOLID, 3, RGB(0, 200, 0));
		oldpen = idc->SelectObject(&pen);
		double dx = double(img->GetWidth()) / (m_NumSteps - 1), dy = double(img->GetHeight()) / (m_MaxMem - 1);
		int x, y;
		// clearing image
		idc->FillSolidRect(-1, -1, img->GetWidth() + 2, img->GetHeight() + 2, RGB(0, 0, 0));
		// drawing grid
		pen2.CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
		oldpen2 = idc->SelectObject(&pen2);
		for (UINT i = 0; i < points.size(); i++)
		{
			x = int(i * dx);
			idc->MoveTo(x, 0);
			idc->LineTo(x, img->GetHeight());
		}
		for (double i = 0.0; i < img->GetHeight(); i += img->GetHeight() / 10.0)
		{
			idc->MoveTo(0, int(i));
			idc->LineTo(img->GetWidth(), int(i));
		}
		idc->SelectObject(oldpen2);
		// setting text color
		idc->SetTextColor(RGB(0, 200, 0));
		// drawing points
		for (UINT i = 0; i < points.size(); i++)
		{
			l = points._Get_container()[i];
			x = int(i * dx);
			y = img->GetHeight() - int(l * dy) - 1;
			if (!i)
			{
				idc->MoveTo(x, y);
			}
			else
			{
				idc->LineTo(x, y);
			}
			if (i == points.size() - 1)
			{
				s.Format(L"Memory: %u KB of %u KB, peak %u KB", l / 1024, m_MaxMem / 1024, peak / 1024);
				idc->TextOutW(1, 1, s);
				total = l;
			}
		}
		// drawing points_pagefile
		// setting other pen color
		pen3.CreatePen(PS_SOLID, 3, RGB(200, 0, 0));
		oldpen2 = idc->SelectObject(&pen3);
		// setting text color
		idc->SetTextColor(RGB(200, 0, 0));
		for (UINT i = 0; i < points_pagefile.size(); i++)
		{
			l = points_pagefile._Get_container()[i];
			x = int(i * dx);
			y = img->GetHeight() - int(l * dy) - 1;
			if (!i)
			{
				idc->MoveTo(x, y);
			}
			else
			{
				idc->LineTo(x, y);
			}
			if (i == points_pagefile.size() - 1)
			{
				s.Format(L"Swap: %u KB, peak %u KB", l / 1024, peak_pagefile / 1024);
				idc->TextOutW(1, 17, s);
				total += l;
			}
		}
		// setting text color
		idc->SetTextColor(RGB(200, 200, 0));
		s.Format(L"Total: %u KB, peak %u KB", total / 1024, (peak_pagefile + peak) / 1024);
		idc->TextOutW(1, 33, s);
		idc->SelectObject(oldpen2);
		idc->SelectObject(oldpen);
		img->ReleaseDC();
		// displaying image
		DrawImage();
		// saving to file
		f << l << L"\n";
	}
	CDialog::OnTimer(nIDEvent);
}