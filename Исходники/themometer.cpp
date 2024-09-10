 void FillCylinder(Graphics* pGfx, RectF rcClient,
     Brush* pFillBrush, Color cOutlineColor)
 {
     RectF rTopPlane(rcClient.X, rcClient.Y - 5, rcClient.Width, 5);
     RectF rBottomPlane(rcClient.X, rcClient.GetBottom() - 5, rcClient.Width, 5);
     // Outline pen
     Pen penOutline(cOutlineColor);
     // Draw body
     GraphicsPath gfxPath;
     gfxPath.AddArc(rTopPlane, 0, 180);
     gfxPath.AddArc(rBottomPlane, 180, -180);
     gfxPath.CloseFigure();
     // Fill body
     pGfx->FillPath(pFillBrush, &gfxPath);
     // Outline body
     pGfx->DrawPath(&penOutline, &gfxPath);
     // Draw top plane
     gfxPath.Reset();
     gfxPath.AddEllipse(rTopPlane);
     // Fill top plane
     pGfx->FillPath(pFillBrush, &gfxPath);
     // Outline top plane
     pGfx->DrawPath(&penOutline, &gfxPath);
 }