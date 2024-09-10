TLFDblVector* TLFAverageNNPredictor::Features(ILFDetectEngine* engine, TLFRect* rect, int id)
{
	if (engine == NULL || rect == NULL)
		return NULL;
	ILFObjectDetector* d = engine->GetDetector(0);
	if (d == NULL)
		return NULL;
	TLFImage* img = d->GetImage();
	img->GetIntegralImage();
	if (img == NULL || img->GetImage() == NULL)
		return NULL;

	//
	int idx = d->GetStagesCount() - 1;
	TLFObjectList* stages = d->GetStrongs();

	ILFStrong* s = dynamic_cast<TCSStrong*>(stages->Get(idx));
	if (s == NULL)
		return NULL;
	int width = rect->Width();
	double scale_coef = (double)width / (double)d->GetBaseWidth();
	TLFRect fragment;
	TLFDblVector* data = new TLFDblVector(id);
	for (int i = 0; i < s->GetCount(); i++)
	{
		ILFWeak  * weak = s->GetWeak(i);
		if (weak != NULL)
		{
			TCSSensor* sensor = dynamic_cast<TCSSensor*>(weak->Fetaure());
			awpRect Fragment = sensor->GetRect();

			fragment.SetRect(Fragment);
			fragment.Scale(scale_coef);
			fragment.Shift(rect->Left(), rect->Top());

			Fragment = fragment.GetRect();
			double s = fragment.Width()*fragment.Height();
			double value = img->CalcLnSum(Fragment.left, Fragment.top, fragment.Width(), fragment.Height());
			value /= s;
			data->AddValue(value);
		}
	}
	return data;
}