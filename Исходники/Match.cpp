	int Decode(SimpleImage* image,char codes[4])
	{
		float maxConfidence = -1.0;
		char  maxCodes[4] = {0};

		// 变量所有字体，得到最优结果
		for (int i = 0;i < fontArray.size();i++)
		{
			float confidence;
			char  code[4];

			DecodeImage(image,fontArray[i],code,&confidence);
			if (confidence > maxConfidence)
			{
				maxConfidence = confidence;
				memcpy(maxCodes,code,4);
			}
		}

		// 返回结果
		memcpy(codes,maxCodes,4);
		return maxConfidence > 2.0;
	}