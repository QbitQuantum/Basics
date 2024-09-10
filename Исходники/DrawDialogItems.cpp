bool	DrawBuildingMaterial (NewDisplay::NativeContext& drawContext, const DG::Rect& rect, short buildMatIndex)
{
	if (buildMatIndex <= 0)
		return false;

	API_Attribute attrBuildMat;
	Attribute_Get (&attrBuildMat, API_BuildingMaterialID, buildMatIndex);

	API_Attribute attrCutFillPen;
	Attribute_Get (&attrCutFillPen, API_PenID, attrBuildMat.buildingMaterial.cutFillPen);
	Gfx::Color penColor;
	API2AC_RGBColor (penColor, attrCutFillPen.pen.rgb);

	Gfx::Color bkPenColor;
	if (attrBuildMat.buildingMaterial.cutFillBackgroundPen > 0) {
		API_Attribute attrCutFillBkPen;
		Attribute_Get (&attrCutFillBkPen, API_PenID, attrBuildMat.buildingMaterial.cutFillBackgroundPen);;
		API2AC_RGBColor (bkPenColor, attrCutFillBkPen.pen.rgb);
	} else
		bkPenColor.Set (255, 255, 255, 1);

	API_Attribute attrCutMaterial;
	Attribute_Get (&attrCutMaterial, API_MaterialID, attrBuildMat.buildingMaterial.cutMaterial);
	Gfx::Color surfaceColor;
	API2AC_RGBColor (surfaceColor, attrCutMaterial.material.surfaceRGB);

	short left		= rect.GetLeft ();
	short top		= rect.GetTop ();
	short right		= rect.GetRight ();
	short bottom	= rect.GetBottom ();

	right = rect.GetLeft () + (short) ((rect.GetRight () - rect.GetLeft ()) * 0.48);

	DrawFillPattern (drawContext, DG::Rect (left, top, right, bottom), attrBuildMat.buildingMaterial.cutFill,
					 penColor, bkPenColor, Gfx::Color (0, 0, 0));

	left = rect.GetLeft () + (short) ((rect.GetRight () - rect.GetLeft ()) * 0.52);
	right = rect.GetRight ();

	const Gfx::Color frColor = Gfx::Color (0, 0, 0);

	drawContext.SetBackColor (bkPenColor.GetRed (), bkPenColor.GetGreen (), bkPenColor.GetBlue ());
	FillRect (drawContext, DG::Rect (left, top, right, bottom), surfaceColor);

	if (attrBuildMat.buildingMaterial.showUncutLines) {
		drawContext.SetForeColor (frColor.GetRed (), frColor.GetGreen (), frColor.GetBlue ());
		drawContext.FrameRect (left, top, right, bottom);
	}

	return true;
}