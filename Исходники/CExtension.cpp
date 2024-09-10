void CExtension::CreateIcon (int cxWidth, int cyHeight, CG32bitImage **retpIcon) const

//	CreateIcon
//
//	Creates a cover icon for the adventure. The caller is responsible for
//	freeing the result.

	{
	//	Load the image

	CG32bitImage *pBackground = GetCoverImage();
	if (pBackground == NULL || pBackground->GetWidth() == 0 || pBackground->GetHeight() == 0)
		{
		int cxSize = Min(cxWidth, cyHeight);
		*retpIcon = new CG32bitImage;
		(*retpIcon)->Create(cxSize, cxSize);
		return;
		}

	//	Figure out the dimensions of the icon based on the image size and the
	//	desired output.
	//
	//	If the background is larger than the icon size then we need to scale it.

	CG32bitImage *pIcon;
	if (pBackground->GetWidth() > cxWidth || pBackground->GetHeight() > cyHeight)
		{
		int xSrc, ySrc, cxSrc, cySrc;
		Metric rScale;

		//	If we have a widescreen cover image and we want a portrait or
		//	square icon, then we zoom in on the key part of the cover.

		if (pBackground->GetWidth() > 2 * pBackground->GetHeight())
			{
			rScale = (Metric)cyHeight / pBackground->GetHeight();

			cxSrc = (int)(cxWidth / rScale);
			xSrc = Min(pBackground->GetWidth() - cxSrc, pBackground->GetWidth() - (RIGHT_COVER_OFFSET + (cxSrc / 2)));

			ySrc = 0;
			cySrc = pBackground->GetHeight();
			}
		else
			{
			rScale = (Metric)cxWidth / pBackground->GetWidth();
			if (rScale * pBackground->GetHeight() > (Metric)cyHeight)
				rScale = (Metric)cyHeight / pBackground->GetHeight();

			xSrc = 0;
			ySrc = 0;
			cxSrc = pBackground->GetWidth();
			cySrc = pBackground->GetHeight();
			}

		//	Create the icon

		pIcon = new CG32bitImage;
		pIcon->CreateFromImageTransformed(*pBackground,
				xSrc,
				ySrc,
				cxSrc,
				cySrc,
				rScale,
				rScale,
				0.0);
		}

	//	Otherwise we center the image on the icon

	else
		{
		//	Create the icon

		pIcon = new CG32bitImage;
		pIcon->Create(cxWidth, cyHeight);

		//	Blt

		pIcon->Blt(0,
				0,
				pBackground->GetWidth(),
				pBackground->GetHeight(),
				*pBackground,
				(cxWidth - pBackground->GetWidth()) / 2,
				(cyHeight - pBackground->GetHeight()) / 2);
		}

	//	Done

	*retpIcon = pIcon;
	}