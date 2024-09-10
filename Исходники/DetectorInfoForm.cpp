//---------------------------------------------------------------------------
void __fastcall TDetectorForm::DoDetectorInfo()
{
	this->Series1->Clear();

	ILFDetectEngine* e = Form1->Engine;
	TSCObjectDetector* d = (TSCObjectDetector*)e->GetDetector(0);
	int w = d->GetBaseWidth()*10;
	int h = d->GetBaseHeight()*10;
	awpImage* img = NULL;
	awpCreateImage(&img, w, h, 1, AWP_DOUBLE);
	double* pix = (double*)img->pPixels;
	for (int i = 0; i < d->GetStagesCount(); i++)
	{
		switch(this->ComboBox1->ItemIndex)
		{
			case 0:
					this->Series1->Add(d->GetSensorsCount(i));
			break;
			case 1:
					this->Series1->Add(d->GetStageThreshold(i));
			break;
			case 2:
					this->Series1->Add(d->GetStageWeight(i));
			break;
		}
	}

	TLFObjectList* strongs = d->GetStrongs();
	for (int i = 0; i < strongs->GetCount(); i++)
	{
		ILFStrong* s = (ILFStrong*)strongs->Get(i);
		if (ComboBox2->ItemIndex > 0 && ComboBox2->ItemIndex - 1 != i )
			continue;
		for (int j = 0; j < s->GetCount(); j++)
		{
			ILFWeak* ww = (ILFWeak*)s->GetWeak(j);
			ILFFeature* f = ww->Fetaure();
			awpRect r = f->GetRect();
			r.left *= 10;
			r.top *= 10;
			r.right *= 10;
			r.bottom *= 10;

			if (this->CheckBox2->Checked)
			{
				for (int y = r.top; y < r.bottom; y++)
				{
					 for (int x = r.left; x < r.right; x++)
					 {
						 if (this->CheckBox1->Checked)
							pix[x+y*w] += ww->Weight();
						 else
							pix[x+y*w] += 1;
					 }
				}
			}
			else
			{
				 //awpPoint p =
				 TLFRect rect;
				 rect.SetRect(r);
				 awpPoint p = rect.Center();
				 awpRect r0;
				 r0.left = p.X - 2;
				 r0.top  = p.Y - 2;
				 r0.right = p.X+2;
				 r0.bottom = p.Y + 2;
				 if (this->CheckBox1->Checked)
					awpDrawRect(img, &r0, 0, ww->Weight(), 1);
				 else
					awpDrawRect(img, &r0, 0, 1, 1);
			}
		}

	}
	awpConvert(img, AWP_CONVERT_TO_BYTE_WITH_NORM);
	this->FImage1->Bitmap->SetAWPImage(img);
	FImage1->BestFit();

	awpReleaseImage(&img);
}