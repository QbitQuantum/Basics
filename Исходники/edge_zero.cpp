PNM* EdgeZeroCrossing::transform()
{
    int width = image->width(),
        height = image->height();

    int    size  = getParameter("size").toInt();
    double sigma = getParameter("sigma").toDouble();
    int    t     = getParameter("threshold").toInt();

	EdgeLaplaceOfGauss ELOG(image);
	ELOG.setParameter("size", getParameter("size"));
	ELOG.setParameter("sigma", getParameter("sigma"));

	PNM* newImage = new PNM(width, height, QImage::Format_Indexed8);
	Transformation laplasjan(ELOG.transform());

	int v_0 = 128;


	if (image->format() == QImage::Format_Indexed8)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				math::matrix<float> maska = laplasjan.getWindow(i, j, size, LChannel, RepeatEdge);

				int min = 255;
				int	max = 0;

				for (int x = 0; x < size; x++)
				{
					for (int y = 0; y < size; y++)
					{
						if (maska(x, y) > max)
							max = maska(x, y);
						if (maska(x, y) < min)
							min = maska(x, y);
					}
				}

				if (min < (v_0 - t) && max > (v_0 + t))
				{
					newImage->setPixel(i, j, maska(size / 2, size / 2));
				}
				else
				{
					newImage->setPixel(i, j, 0);
				}
			}
		}
	}
	else if (image->format() == QImage::Format_RGB32)
	{
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				math::matrix<float> maskaR = laplasjan.getWindow(i, j, size, RChannel, RepeatEdge);
				math::matrix<float> maskaG = laplasjan.getWindow(i, j, size, GChannel, RepeatEdge);
				math::matrix<float> maskaB = laplasjan.getWindow(i, j, size, BChannel, RepeatEdge);


				int minR = 255; int minG = 255; int minB = 255;
				int	maxR = 0; int maxG = 0; int maxB = 0;

				for (int x = 0; x < size; x++)
				{
					for (int y = 0; y < size; y++)
					{
						if (maskaR(x, y) > maxR)
							maxR = maskaR(x, y);
						if (maskaR(x, y) < minR)
							minR = maskaR(x, y);

						if (maskaG(x, y) > maxG)
							maxG = maskaG(x, y);
						if (maskaG(x, y) < minG)
							minG = maskaG(x, y);

						if (maskaB(x, y) > maxB)
							maxB = maskaB(x, y);
						if (maskaB(x, y) < minB)
							minB = maskaB(x, y);
					}
				}

				int r_val, g_val, b_val;

				if (minR < (v_0 - t) && maxR >(v_0 + t))
				{
					r_val = maskaR(size / 2, size / 2);
					newImage->setPixel(i, j, maskaR(size / 2, size / 2));
				}
				else if (minG < (v_0 - t) && maxG >(v_0 + t))
				{
					g_val = maskaG(size / 2, size / 2);
					newImage->setPixel(i, j, g_val);
				}
				else if (minB < (v_0 - t) && maxB >(v_0 + t))
				{
					b_val = maskaB(size / 2, size / 2);
					newImage->setPixel(i, j, b_val);
				}
				else
				{
					newImage->setPixel(i, j, 0);
				}

			}
		}
	}




    return newImage;
}