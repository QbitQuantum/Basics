RawImage* MedianFilter::ProcessInput(CommandLineArgModel* arg, RawImage* image)
{
	MedianFilterModel* model = (MedianFilterModel*)arg->ParsedModel;

	if (model->Window == 1) return image;

	Rectangle roi = model->Roi;
	int padding = (model->Window - 1) / 2;
	int window = model->Window;

	RawImage* returnValue = NULL;

	if (padding > 1)
	{
		if (model->Y)
		{
			returnValue = image->Clone();

			for (int x = roi.X; x < roi.Right; x++)
				for (int y = roi.Y; y < roi.Bottom; y++)
					returnValue->SetPixel(x, y, image->GetAverage(x, y - padding, 1, window, roi));
			image = returnValue;
		}

		if (model->X)
		{
			returnValue = image->Clone();
			for (int x = roi.X; x < roi.Right; x++)
				for (int y = roi.Y; y < roi.Bottom; y++)
					returnValue->SetPixel(x, y, image->GetAverage(x - padding, y, window, 1, roi));
		}
	}

	return returnValue == NULL ? image : returnValue;
}