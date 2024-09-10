void SymbolModel::init()
{
	const SHPHandle& hSHP = _shpLoader->getHandle();
	const DBFHandle& hDBF = _dbfLoader->getHandle();

	float maxVal = -99999999999, minVal = 99999999999; 

	std::vector<float2> xy; // 2d定位点
	std::vector<std::vector<float> > table; 
	std::vector<float> colsum; 

	for (int i = 0; i < hSHP->nRecords; i++) // 遍历记录
	{
		SHPObject* psShape = SHPReadObject(hSHP, i); // 每个记录存放一个点
		float v[] = { psShape->padfX[0], psShape->padfY[0] }; // 定位点
		xy.push_back(v);
		SHPDestroyObject(psShape);

		std::vector<float> row; 
		float sum = 0; 

		for (int j = 0; j < _fieldIndices.size(); j++)
		{
			float val = DBFReadDoubleAttribute(hDBF, i + 1, _fieldIndices[j]);

			sum += val;
			row.push_back(val);
		}

		if (maxVal < sum) 
		{
			maxVal = sum;
		}
		if (minVal > sum)
		{
			minVal = sum;
		}

		colsum.push_back(sum); 
		table.push_back(row);
	}

	LinearScaler hScaler(_valueScaler.getBottom()/* + 0.1*/, _valueScaler.getTop());
	hScaler.setBound(minVal, maxVal);

	for (int i = 0; i < hSHP->nRecords; i++)
	{
		float pos[] = { xy[i][0], xy[i][1], 0 }; 

		float top = hScaler(colsum[i]); 
		switch (_chartType)
		{
		case SPHERE:
			{
				Sphere* sphere = new Sphere(pos, _colors.front());
				sphere->setLinearScaler(LinearScaler(_valueScaler.getBottom(), top));
				_container.add(sphere);
			}
			break;
		case BAR:
			{
				Fan* fan = new Fan;
				fan->set(0, 360, _colors.front(), pos, 1.1);
				fan->setLinearScaler(LinearScaler(_valueScaler.getBottom(), top));
				fan->init();
				_container.add(fan);
			}
			break;
		case STACKEDBAR:
			{
				StackedBar* bar = new StackedBar;
				bar->set(table[i], _colors, pos, 1.1);
				bar->setLinearScaler(LinearScaler(_valueScaler.getBottom(), top));
				bar->init();
				_container.add(bar);
			}
			break;
		case PIE:
			{
				Pie* pie = new Pie;
				pie->set(table[i], _colors, pos, 1.1);
				pie->setLinearScaler(_valueScaler); // 应该同高度
				pie->init();
				_container.add(pie);
			}
			break;
		default:;
		}
	}
}