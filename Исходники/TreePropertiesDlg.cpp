void TreePropertiesDlg::Init()
{
	// set the title of the properties dialog
	this->SetLabel( wxString(m_treeLayer->GetName().c_str()) + wxT( " : Tree Properties" ) );

	// *** Set state of controls on General page
	m_txtLayerName->SetValue(wxString(m_treeLayer->GetName().c_str()));
	m_txtLayerDescription->SetValue(wxString(m_treeLayer->GetDescription().c_str()));
	m_txtAuthours->SetValue(wxString(m_treeLayer->GetAuthours().c_str()));

	// *** Set state of controls on Symbology page
	GeoTreeViewPtr geoTreeView = m_treeLayer->GetGeoTreeView();

	// tree layout properties
	if(geoTreeView->GetLayout() == GeoTreeView::SLANTED_CLADOGRAM_3D)
		m_cboTreeLayout->SetValue(_T("3D slanted cladogram"));
	else if(geoTreeView->GetLayout() == GeoTreeView::CLADOGRAM_3D)
		m_cboTreeLayout->SetValue(_T("3D cladogram"));
	else if(geoTreeView->GetLayout() == GeoTreeView::SLANTED_PHYLOGRAM_3D)
		m_cboTreeLayout->SetValue(_T("3D slanted phylogram"));
	else if(geoTreeView->GetLayout() == GeoTreeView::CLADOGRAM_2D)
		m_cboTreeLayout->SetValue(_T("2D cladogram"));
	else if(geoTreeView->GetLayout() == GeoTreeView::PHYLOGRAM_2D)
		m_cboTreeLayout->SetValue(_T("2D phylogram"));
	else if(geoTreeView->GetLayout() == GeoTreeView::ELLIPSE_QUADRANT)
		m_cboTreeLayout->SetValue(_T("Elliptical Layout"));

	m_spinTreeThickness->SetValue(geoTreeView->GetLineThickness());
	m_txtTreeHeight->SetValue(wxString::Format(wxT("%f"), geoTreeView->GetHeight()));

	if(geoTreeView->GetOrientation() == GeoTreeView::VERTICAL)
		m_cbo2dOrientation->SetValue(_T("Vertical"));
	else if(geoTreeView->GetOrientation() == GeoTreeView::HORIZONTAL)
		m_cbo2dOrientation->SetValue(_T("Horizontal"));

	m_chkDrawLayoutPrimative->SetValue(geoTreeView->GetLayoutPrimativeVisibility());

	// tree style properties
	Colour treeColour = geoTreeView->GetColour();
	m_colourTree->SetColour(wxColour(treeColour.GetRedInt(), treeColour.GetGreenInt(), treeColour.GetBlueInt(), treeColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourTree, treeColour );

	if(geoTreeView->GetTreeColourStyle() == GeoTreeView::COLOUR_SINGLE)
		m_cboTreeColourStyle->SetValue(_T("Single colour"));
	else if(geoTreeView->GetTreeColourStyle() == GeoTreeView::COLOUR_DISCRETE)
		m_cboTreeColourStyle->SetValue(_T("Propogate discrete colours"));
	else if(geoTreeView->GetTreeColourStyle() == GeoTreeView::COLOUR_CONTINUOUS)
		m_cboTreeColourStyle->SetValue(_T("Propogate continuous colours"));

	m_spinLeafNodeSize->SetValue(geoTreeView->GetLeafNodeSize());
	m_spinInternalNodeSize->SetValue(geoTreeView->GetInternalNodeSize());

	m_spinBranchBorderSize->SetValue(geoTreeView->GetBranchBorderSize());
	m_spinLeafNodeBorderSize->SetValue(geoTreeView->GetLeafNodeBorderSize());
	m_spinInternalNodeBorderSize->SetValue(geoTreeView->GetInternalNodeBorderSize());
	m_spinGeoPointBorderSize->SetValue(geoTreeView->GetGeoPtsBorderSize());
	m_spinLocationLineBorderSize->SetValue(geoTreeView->GetLocationLineBorderSize());
	m_spinCorrelationLineBorderSize->SetValue(geoTreeView->GetCorrelationLineBorderSize());

	Colour leafNodeBorderColour = geoTreeView->GetLeafNodeBorderColour();
	m_colourLeafNodeBorder->SetColour(wxColour(leafNodeBorderColour.GetRedInt(), leafNodeBorderColour.GetGreenInt(), 
		leafNodeBorderColour.GetBlueInt(), leafNodeBorderColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourLeafNodeBorder, leafNodeBorderColour );

	Colour internalNodeBorderColour = geoTreeView->GetInternalNodeBorderColour();
	m_colourInternalNodeBorder->SetColour(wxColour(internalNodeBorderColour.GetRedInt(), internalNodeBorderColour.GetGreenInt(), 
		internalNodeBorderColour.GetBlueInt(), internalNodeBorderColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourInternalNodeBorder, internalNodeBorderColour );

	Colour geoPtsBorderColour = geoTreeView->GetGeoPtsBorderColour();
	m_colourGeoPointBorder->SetColour(wxColour(geoPtsBorderColour.GetRedInt(), geoPtsBorderColour.GetGreenInt(), 
		geoPtsBorderColour.GetBlueInt(), geoPtsBorderColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourGeoPointBorder, geoPtsBorderColour );

	Colour branchBorderColour = geoTreeView->GetBranchBorderColour();
	m_colourBranchBorder->SetColour(wxColour(branchBorderColour.GetRedInt(), branchBorderColour.GetGreenInt(), 
		branchBorderColour.GetBlueInt(), branchBorderColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourBranchBorder, branchBorderColour );

	Colour locationLineBorderColour = geoTreeView->GetLocationLineBorderColour();
	m_colourLocationLineBorder->SetColour(wxColour(locationLineBorderColour.GetRedInt(), locationLineBorderColour.GetGreenInt(), 
		locationLineBorderColour.GetBlueInt(), locationLineBorderColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourLocationLineBorder, locationLineBorderColour );

	Colour correlationLineBorderColour = geoTreeView->GetCorrelationLineBorderColour();
	m_colourCorrelationLineBorder->SetColour(wxColour(correlationLineBorderColour.GetRedInt(), correlationLineBorderColour.GetGreenInt(), 
		correlationLineBorderColour.GetBlueInt(), correlationLineBorderColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourCorrelationLineBorder, correlationLineBorderColour );

	// location line properties
	m_spinLocationLineThickness->SetValue(geoTreeView->LocationLines().GetThickness());

	if(geoTreeView->LocationLines().GetLineStyle() == VisualLine::SOLID)
		m_cboLocationLineStyle->SetValue(_T("Solid"));
	else if(geoTreeView->LocationLines().GetLineStyle() == VisualLine::SHORT_DASH)
		m_cboLocationLineStyle->SetValue(_T("Short dash"));
	else if(geoTreeView->LocationLines().GetLineStyle() == VisualLine::LONG_DASH)
		m_cboLocationLineStyle->SetValue(_T("Long dash"));
	else if(geoTreeView->LocationLines().GetLineStyle() == VisualLine::HIDDEN)
		m_cboLocationLineStyle->SetValue(_T("Hidden"));


	// correlation line properties
	m_spinCorrelationLineThickness->SetValue(geoTreeView->CorrelationLines().GetThickness());

	if(geoTreeView->CorrelationLines().GetLineStyle() == VisualLine::SOLID)
		m_cboCorrelationLineStyle->SetValue(_T("Solid"));
	else if(geoTreeView->CorrelationLines().GetLineStyle() == VisualLine::SHORT_DASH)
		m_cboCorrelationLineStyle->SetValue(_T("Short dash"));
	else if(geoTreeView->CorrelationLines().GetLineStyle() == VisualLine::LONG_DASH)
		m_cboCorrelationLineStyle->SetValue(_T("Long dash"));
	else if(geoTreeView->CorrelationLines().GetLineStyle() == VisualLine::HIDDEN)
		m_cboCorrelationLineStyle->SetValue(_T("Hidden"));

	// internal drop line properties
	m_spinInternalDropLineThickness->SetValue(geoTreeView->Get3dInternalDropLineStyle().GetSize());

	Colour colour = geoTreeView->Get3dInternalDropLineStyle().GetColour();
	m_colourInternalDropLine->SetColour(wxColour(colour.GetRedInt(), colour.GetGreenInt(), colour.GetBlueInt(), colour.GetAlphaInt()));
	ReplaceColourPicker( m_colourInternalDropLine, colour );

	if(geoTreeView->Get3dInternalDropLineStyle().GetLineStyle() == VisualLine::SOLID)
		m_cboInternalDropLineStyle->SetValue(_T("Solid"));
	else if(geoTreeView->Get3dInternalDropLineStyle().GetLineStyle() == VisualLine::SHORT_DASH)
		m_cboInternalDropLineStyle->SetValue(_T("Short dash"));
	else if(geoTreeView->Get3dInternalDropLineStyle().GetLineStyle() == VisualLine::LONG_DASH)
		m_cboInternalDropLineStyle->SetValue(_T("Long dash"));
	else if(geoTreeView->Get3dInternalDropLineStyle().GetLineStyle() == VisualLine::HIDDEN)
		m_cboInternalDropLineStyle->SetValue(_T("Hidden"));

	// leaf drop line properties
	if(geoTreeView->Get3dLeafDropLineStyle().GetLineStyle() == VisualLine::SOLID)
		m_cboLeafDropLineStyle->SetValue(_T("Solid"));
	else if(geoTreeView->Get3dLeafDropLineStyle().GetLineStyle() == VisualLine::SHORT_DASH)
		m_cboLeafDropLineStyle->SetValue(_T("Short dash"));
	else if(geoTreeView->Get3dLeafDropLineStyle().GetLineStyle() == VisualLine::LONG_DASH)
		m_cboLeafDropLineStyle->SetValue(_T("Long dash"));
	else if(geoTreeView->Get3dLeafDropLineStyle().GetLineStyle() == VisualLine::HIDDEN)
		m_cboLeafDropLineStyle->SetValue(_T("Hidden"));

	// geography line properties
	m_spinGeoLineOffset->SetValue(uint(geoTreeView->GetGeographyLineOffsetPercentage()*100 + 0.5));

	m_spinGeoLineThickness->SetValue(geoTreeView->GeographyLine().GetSize());

	if(geoTreeView->GeographyLine().GetLineStyle() == VisualLine::SOLID)
		m_cboGeoLineStyle->SetValue(_T("Solid"));
	else if(geoTreeView->GeographyLine().GetLineStyle() == VisualLine::SHORT_DASH)
		m_cboGeoLineStyle->SetValue(_T("Short dash"));
	else if(geoTreeView->GeographyLine().GetLineStyle() == VisualLine::LONG_DASH)
		m_cboGeoLineStyle->SetValue(_T("Long dash"));
	else if(geoTreeView->GeographyLine().GetLineStyle() == VisualLine::HIDDEN)
		m_cboGeoLineStyle->SetValue(_T("Hidden"));

	colour = geoTreeView->GeographyLine().GetColour();
	m_colourGeoLine->SetColour(wxColour(colour.GetRedInt(), colour.GetGreenInt(), colour.GetBlueInt(), colour.GetAlphaInt()));
	ReplaceColourPicker( m_colourGeoLine, colour );

	// geographic point properties
	m_spinGeoPointSize->SetValue(geoTreeView->GeographicPoints().GetSize());

	m_chkDrawGeoPoint->SetValue(geoTreeView->GeographicPoints().GetVisibility());
	m_chkEvenlySpeadGeoPts->SetValue(geoTreeView->GetSpreadGeographyPts());

	m_chkDrawGeoAxis->SetValue(geoTreeView->GetGeographicAxisVisibility());

	m_chkOptimizeLeafNodes->SetValue(geoTreeView->GetOptimizeTopology());


	// *** Set state of controls on Label page
	m_spinLabelSize->SetValue(geoTreeView->GetFontSize());

	Colour fontColour = geoTreeView->GetFontColour();
	m_colourLabel->SetColour(wxColour(fontColour.GetRedInt(), fontColour.GetGreenInt(), fontColour.GetBlueInt(), fontColour.GetAlphaInt()));
	ReplaceColourPicker( m_colourLabel, fontColour );

	m_chkShowLabels->SetValue(geoTreeView->GetLabelVisibility());

	// set state of controls on Metadata page
	m_txtLayerSource->SetValue(wxString(m_treeLayer->GetPath().c_str()) + _T("\\") + wxString(m_treeLayer->GetFilename().c_str()));
	SetMetaData();
}