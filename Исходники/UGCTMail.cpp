/***************************************************
AddImageList
	This cell type contains two image 
	lists, as we draw icons on both 
	sides of the cell.  This function
	replaces an existing image list with
	an image list from the resources for
	the project that it's being used in.
Params:
	resourceID	- the ID of the resource imagelist to use
	width		- the width of each image in the list
	addTo		- the image list to replace
	mask		- the color to use to generate a mask
Return
	a bool to indicate success or failure
****************************************************/
bool CUGCTMail::AddImageList(UINT resourceID, int width, AddToImageList addTo, COLORREF mask)
{
	bool success = false;

	if (addTo == left)
	{
		if (m_leftImages.GetSafeHandle())
		{
			m_leftImages.DeleteImageList();
		}

		CBitmap bm;
		bm.LoadBitmap(resourceID);

		BITMAP b;
		bm.GetBitmap(&b);

		const int imageCount = b.bmWidth / width;

		success = (m_leftImages.Create(width, b.bmHeight, ILC_COLOR32, imageCount, imageCount) > 0);

		if (success)
		{
			CDC dc;
			dc.CreateCompatibleDC(NULL);

			CDC srcDC;
			srcDC.CreateCompatibleDC(&dc);
			CBitmap * pOldSrcBmp = srcDC.SelectObject(&bm);

			for(int i=0;i<=imageCount; ++i)
			{
				CBitmap bitmap;
				bitmap.CreateBitmap(width, b.bmHeight, 1, 32, NULL);
				CBitmap * pOldDestBmp = dc.SelectObject(&bitmap);

				dc.BitBlt(0, 0, width, b.bmHeight, &srcDC, width * i, 0, SRCCOPY);
				
				dc.SelectObject(pOldDestBmp);
			 	
				m_leftImages.Add(&bitmap, mask);
			}

			srcDC.SelectObject(pOldSrcBmp);
		}
	}
	else
	{
		if (m_rightImages.GetSafeHandle())
		{
			m_rightImages.DeleteImageList();
		}


		CBitmap bm;
		bm.LoadBitmap(resourceID);

		BITMAP b;
		bm.GetBitmap(&b);

		const int imageCount = b.bmWidth / width;

		success = (m_rightImages.Create(width, b.bmHeight, ILC_COLOR32, imageCount, imageCount) > 0);

		if (success)
		{
			CDC dc;
			dc.CreateCompatibleDC(NULL);

			CDC srcDC;
			srcDC.CreateCompatibleDC(&dc);
			CBitmap * pOldSrcBmp = srcDC.SelectObject(&bm);

			for(int i=0;i<=imageCount; ++i)
			{
				CBitmap bitmap;
				bitmap.CreateBitmap(width, b.bmHeight, 1, 32, NULL);
				CBitmap * pOldDestBmp = dc.SelectObject(&bitmap);

				dc.BitBlt(0, 0, width, b.bmHeight, &srcDC, width * i, 0, SRCCOPY);
				
				dc.SelectObject(pOldDestBmp);
			 	
				m_rightImages.Add(&bitmap, mask);
			}

			srcDC.SelectObject(pOldSrcBmp);
		}
	}

	return success;
}