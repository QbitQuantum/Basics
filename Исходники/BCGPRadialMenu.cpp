//***************************************************************************************
void CBCGPRadialMenuObject::OnDraw(CBCGPGraphicsManager* pGM, const CBCGPRect& /*rectClip*/, DWORD dwFlags)
{
	if (dwFlags == BCGP_DRAW_STATIC)
	{
		return;
	}

	m_nShadowDepth = pGM->IsSupported(BCGP_GRAPHICS_MANAGER_COLOR_OPACITY) ? GetShadowDepth() : 0;

	CBCGPRect rect = m_rect;
	if (rect.Width() < rect.Height())
	{
		rect.top += (rect.Height() - rect.Width()) / 2;
		rect.bottom = rect.top + rect.Width();
	}
	else if (rect.Height() < rect.Width())
	{
		rect.left += (rect.Width() - rect.Height()) / 2;
		rect.right = rect.left + rect.Height();
	}

	rect.DeflateRect(2., 2.);

	rect.right -= m_nShadowDepth;
	rect.bottom -= m_nShadowDepth;

	const double radius = rect.Width() / 2;
	const double radiusSmall = INTERNAL_PART * rect.Width() + 1.0;
	const CBCGPPoint center = rect.CenterPoint();

	CBCGPSize sizeIcon((double)m_cxIcon, 16);

	if (!m_Icons.IsNull())
	{
		sizeIcon.cy = pGM->GetImageSize(m_Icons).cy;
	}

	const int nItems = (int)m_arItems.GetSize();

	if (IsDirty())
	{
		int nCircleItems = m_bHasCenterButton ? nItems - 1 : nItems;

		double dblDeltaAngle = nCircleItems == 0 ? 0. : 360. / nCircleItems;
		double dblStartAngle = 90. - dblDeltaAngle / 2;

		for (int i = 0; i < nItems; i++)
		{
			CBCGPRadialMenuItem* pItem = m_arItems[i];
			ASSERT_VALID(pItem);

			pItem->m_bIsCenter = i == nItems -1 && m_bHasCenterButton;

			pItem->m_Shape.Destroy();
			pItem->m_Shape.Clear();

			if (!pItem->m_bIsCenter)
			{
				double dblFinishAngle = dblStartAngle + dblDeltaAngle;

				const double dblStartAngleRad = bcg_deg2rad(dblStartAngle);
				const double dblFinishAngleRad = bcg_deg2rad(dblFinishAngle);
				const double dblMiddleAngleRad = bcg_deg2rad(dblStartAngle + dblDeltaAngle / 2);

				double angleStartCos = cos(dblStartAngleRad);
				double angleStartSin = sin(dblStartAngleRad);
				double angleFinishCos = cos(dblFinishAngleRad);
				double angleFinishSin = sin(dblFinishAngleRad);

				pItem->m_Shape.SetStart(
					CBCGPPoint(center.x + angleStartCos * radius, center.y - angleStartSin * radius));
				pItem->m_Shape.AddArc(
					CBCGPPoint(center.x + angleFinishCos * radius, center.y - angleFinishSin * radius),
					CBCGPSize(radius, radius), dblStartAngle > dblFinishAngle, FALSE);
				pItem->m_Shape.AddLine(
					CBCGPPoint(center.x + angleFinishCos * radiusSmall, center.y - angleFinishSin * radiusSmall));
				pItem->m_Shape.AddArc(
					CBCGPPoint(center.x + angleStartCos * radiusSmall, center.y - angleStartSin * radiusSmall),
					CBCGPSize(radiusSmall, radiusSmall), dblStartAngle < dblFinishAngle, FALSE);

				pItem->m_ptCenter = CBCGPPoint(
					center.x + cos(dblMiddleAngleRad) * 2 * radius / 3,
					center.y - sin(dblMiddleAngleRad) * 2 * radius / 3);

				dblStartAngle = dblFinishAngle;
			}
			else
			{
				pItem->m_Shape.SetStart(center);
				pItem->m_Shape.AddLine(center);
				pGM->CombineGeometry(pItem->m_Shape, pItem->m_Shape, CBCGPEllipseGeometry(CBCGPEllipse(center, radiusSmall, radiusSmall)), RGN_OR);

				pItem->m_ptCenter = center;
			}
		}
	}

	CBCGPEllipse ellipseInt(center, radiusSmall, radiusSmall);

	CBCGPRect rectShadow = rect;
	rectShadow.OffsetRect(m_nShadowDepth, m_nShadowDepth);

	if (!m_bHasCenterButton && m_pCtrl->GetSafeHwnd() != NULL && (m_pCtrl->GetExStyle() & WS_EX_LAYERED))
	{
		if (m_nShadowDepth > 0)
		{
			CBCGPEllipseGeometry egShadow(rectShadow);

			CBCGPPoint centerShadow = center;
			centerShadow.x += m_nShadowDepth;
			centerShadow.y += m_nShadowDepth;

			CBCGPEllipse ellipseIntShadow(centerShadow, radiusSmall, radiusSmall);
			CBCGPEllipseGeometry egInternalShadow(ellipseIntShadow);

			CBCGPComplexGeometry shapeShadow;
			pGM->CombineGeometry(shapeShadow, egShadow, egInternalShadow, RGN_DIFF);

			pGM->FillGeometry(shapeShadow, m_brShadow);
		}

		CBCGPEllipseGeometry eg(rect);
		CBCGPEllipseGeometry egInternal(ellipseInt);

		CBCGPComplexGeometry shape;
		pGM->CombineGeometry(shape, eg, egInternal, RGN_DIFF);

		pGM->FillGeometry(shape, m_brFill);

	}
	else
	{
		if (m_nShadowDepth > 0)
		{
			pGM->FillEllipse(rectShadow, m_brShadow);
		}

		pGM->FillEllipse(rect, m_brFill);
	}

	pGM->DrawEllipse(rect, m_brBorder);

	if (!pGM->IsSupported(BCGP_GRAPHICS_MANAGER_COLOR_OPACITY))
	{
		CBCGPRect rect1 = rect;
		rect1.DeflateRect(1, 1);

		pGM->DrawEllipse(rect1, m_brFill);
	}

	BOOL bIsCtrlDisabled = m_pCtrl->GetSafeHwnd() != NULL && !m_pCtrl->IsWindowEnabled();

	for (int i = 0; i < nItems; i++)
	{
		CBCGPRadialMenuItem* pItem = m_arItems[i];
		ASSERT_VALID(pItem);

		if (i == m_nHighlighted)
		{
			pGM->FillGeometry(pItem->m_Shape, m_nHighlighted == m_nPressed ? m_brPressed : 
				m_brHighlighted.IsEmpty() ? m_brFill : m_brHighlighted);
		}

		pItem->OnDrawIcon(pGM, bIsCtrlDisabled, m_Icons, sizeIcon);

		pGM->DrawGeometry(pItem->m_Shape, m_brBorder);
	}

	pGM->DrawEllipse(ellipseInt, m_brBorder);

	if (!pGM->IsSupported(BCGP_GRAPHICS_MANAGER_ANTIALIAS))
	{
		rect.InflateRect(1, 1);
		pGM->DrawEllipse(rect, m_brBorder);
	}

	if (m_pCtrl->GetSafeHwnd() != NULL && m_pCtrl->IsFocused() && !m_pCtrl->IsPopup())
	{
		rect.InflateRect(1, 1);
		pGM->DrawEllipse(rect, m_brFocusedBorder);
	}
}