void EnemyPlane::ShowPlane()
{
	if (g_Time - m_ShowTime < m_Delay)
	{
		return;
	}

	switch (m_iState)
	{
	case P_EXPLODE:
		PlaneExplode();
		break;

	default:
		if (m_PlaneImage)
		{
			BITMAP bitmap;
			GetObject(m_PlaneImage[m_iNowImageIndex], sizeof(bitmap), &bitmap);
			HPEN oldPen = (HPEN)SelectObject(g_hdcMem, m_PlaneImage[m_iNowImageIndex]);
			SetBkColor(g_hdcMem, RGB(0, 123, 139));

			g_bmpMask = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, 1, 1, NULL);
			HPEN oldMaskPen = (HPEN)SelectObject(g_hdcMask, g_bmpMask);
			BitBlt(g_hdcMask, 0, 0, bitmap.bmWidth, bitmap.bmHeight, g_hdcMem, 0, 0, SRCCOPY);

			BitBlt(g_hdcBuffer, m_iX-m_iOffsetX, m_iY-m_iOffsetY, bitmap.bmWidth, bitmap.bmHeight, g_hdcMem, 0, 0, SRCINVERT);
			BitBlt(g_hdcBuffer, m_iX-m_iOffsetX, m_iY-m_iOffsetY, bitmap.bmWidth, bitmap.bmHeight, g_hdcMask, 0, 0, SRCAND);
			BitBlt(g_hdcBuffer, m_iX-m_iOffsetX, m_iY-m_iOffsetY, bitmap.bmWidth, bitmap.bmHeight, g_hdcMem, 0, 0, SRCINVERT);

			SelectObject(g_hdcMask, oldMaskPen);
			DeleteObject(g_bmpMask);
			SelectObject(g_hdcMem, oldPen);

			m_iNowImageIndex++;
			if (m_iNowImageIndex >= m_iImageIndexMax)
			{
				m_iNowImageIndex = 0;
			}
		}
		else
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(g_hdcBuffer, hBrush);

			Rectangle(g_hdcBuffer, m_iX, m_iY, m_ImpactBox.right, m_ImpactBox.bottom);

			SelectObject(g_hdcBuffer, oldPen);
			DeleteObject(hBrush);
		}

		if (m_bIsBoss)
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(g_hdcBuffer, hBrush);

			int length = (ScreenWidth-40)*m_iHp/m_iHpMax;
			Rectangle(g_hdcBuffer, 20, 50, 20+length, 55);

			SelectObject(g_hdcBuffer, oldPen);
			DeleteObject(hBrush);
		}
		break;
	}
}