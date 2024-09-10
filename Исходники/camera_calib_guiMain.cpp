// Shows the image selected in the listbox:
void camera_calib_guiDialog::refreshDisplayedImage()
{
	try
	{

	if (!lbFiles->GetCount())
	{
		// No images:
		return;
	}


	// Assure there's one selected:
	if (lbFiles->GetSelection()==wxNOT_FOUND)
		lbFiles->SetSelection(0);

	const string selFile = string(lbFiles->GetStringSelection().mb_str());

	TCalibrationImageList::iterator it = lst_images.find(selFile);
	if (it==lst_images.end()) return;

	// Zoom:
	const std::string strZoom = string(cbZoom->GetStringSelection().mb_str());
	const double zoomVal = 0.01*atof(strZoom.c_str());

	ASSERT_(zoomVal>0 && zoomVal<30)


	TImageSize  imgSizes(0,0);

	// Generate the images on-the-fly:
	CImage  imgOrgColor;
	it->second.img_original.colorImage(imgOrgColor);

	imgSizes = imgOrgColor.getSize();

	// Rectify:
	CImage  imgRect;
	if (camera_params.intrinsicParams(0,0)==0)
	{
		// Not calibrated yet:
		imgRect = imgOrgColor;
		imgRect.scaleImage(imgSizes.x*zoomVal,imgSizes.y*zoomVal, IMG_INTERP_NN);
	}
	else
	{
		imgOrgColor.rectifyImage(imgRect,camera_params);
		imgRect.scaleImage(imgSizes.x*zoomVal,imgSizes.y*zoomVal, IMG_INTERP_NN);

		// Draw reprojected:
		for (unsigned int k=0;k<it->second.projectedPoints_undistorted.size();k++)
			imgRect.drawCircle( zoomVal*it->second.projectedPoints_undistorted[k].x, zoomVal*it->second.projectedPoints_undistorted[k].y, 4, TColor(0,255,64) );

		imgRect.drawCircle( 10,10, 4, TColor(0,255,64) );
		imgRect.textOut(18,4,"Reprojected corners",TColor::white);
	}

	// Zoom images:
	imgOrgColor.scaleImage(imgSizes.x*zoomVal,imgSizes.y*zoomVal, IMG_INTERP_NN);

	imgSizes = imgOrgColor.getSize();

	CImage  imgCheck = imgOrgColor;

	// Draw the board:
	for (unsigned int k=0;k<it->second.detected_corners.size();k++)
	{
		imgCheck.cross(it->second.detected_corners[k].x *zoomVal, it->second.detected_corners[k].y *zoomVal, TColor::blue, '+', 3 );
		imgCheck.drawCircle( it->second.projectedPoints_distorted[k].x*zoomVal, it->second.projectedPoints_distorted[k].y*zoomVal, 4, TColor(0,255,64) );
	}
	imgCheck.drawCircle( 10,10, 4, TColor(0,255,64) );
	imgCheck.textOut(18,4,"Reprojected corners",TColor::white);

	imgCheck.cross( 10,30, TColor::blue, '+', 3 );
	imgCheck.textOut(18,24,"Detected corners",TColor::white);


	this->bmpOriginal->AssignImage( imgCheck );
	this->bmpRectified->AssignImage( imgRect );

	it->second.img_original.unload();


	// Plot:

	this->bmpOriginal->SetMinSize(wxSize(imgSizes.x,imgSizes.y));
	this->bmpOriginal->SetMaxSize(wxSize(imgSizes.x,imgSizes.y));
	this->bmpOriginal->SetSize(imgSizes.x,imgSizes.y);

	this->bmpRectified->SetMinSize(wxSize(imgSizes.x,imgSizes.y));
	this->bmpRectified->SetMaxSize(wxSize(imgSizes.x,imgSizes.y));
	this->bmpRectified->SetSize(imgSizes.x,imgSizes.y);

	this->FlexGridSizer11->RecalcSizes();
	this->FlexGridSizer14->RecalcSizes();

	//this->ScrolledWindow2->SetVirtualSize(wxSize(imgSizes.x,imgSizes.y));
	//this->ScrolledWindow3->SetVirtualSize(wxSize(imgSizes.x,imgSizes.y));
	this->ScrolledWindow2->SetScrollbars(1,1,imgSizes.x,imgSizes.y);
	this->ScrolledWindow3->SetScrollbars(1,1,imgSizes.x,imgSizes.y);

	this->bmpOriginal->Refresh(false);
	this->bmpRectified->Refresh(false);

	}
	catch(std::exception &e)
	{
		wxMessageBox(_U(e.what()),_("Error"),wxICON_INFORMATION,this);
	}
}