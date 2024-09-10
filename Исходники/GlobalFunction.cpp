	//	横拡大縦縮小更新
	void	ScalingLandingUpdate( ImageObj& image, int max_scale )
	{
		if (!image.scalingFlag) return;

		//	パラメータ加算
		image.t += D3DX_PI / 180 * image.scalingspeed;
	
		//-------------------------
		//	拡大
		//-------------------------
		if (image.scalingState)
		{
			//	パラメータ上限設定
			if (image.t >= 1.0f)
			{
				image.t = 1.0f;
				image.scalingState = false;
			}

			Lerp(image.plusScaleX, 0, max_scale, image.t);
			Lerp(image.plusScaleY, 0, -max_scale, image.t);

		}

		//-------------------------
		//	縮小
		//-------------------------
		else
		{
			//	パラメータ上限設定
			if (image.t >= 1.0f)
			{
				image.t = 1.0f;
				image.scalingState = true;
				image.scalingFlag = false;
			}

			Lerp(image.plusScaleX, max_scale, 0, image.t);
			Lerp(image.plusScaleY, -max_scale, 0, image.t);

		}

		if (image.t >= 1.0f)		image.t = 0.0f;
	}