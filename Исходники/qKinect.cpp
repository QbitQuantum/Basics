void qKinect::grabCloud()
{
	assert(f_ctx && f_dev);
	assert(m_kDlg);

	if (m_timer)
	{
		m_timer->stop();
		QApplication::processEvents();
	}

	bool grabRGB = m_kDlg->grabRGBInfo();
	unsigned char framesAvgCount = m_kDlg->getFrameAveragingCount();

	uint16_t* old_depth_data = s_depth_data;
	const unsigned mapSize = s_wDepth*s_hDepth;
	
	if (framesAvgCount>1)
	{
		uint16_t* depth_frames = new uint16_t[mapSize*framesAvgCount];
		if (!depth_frames)
		{
			m_app->dispToConsole("[qKinect] Not enough memory to compute frame averaging!");
			framesAvgCount=1;
		}
		else
		{
			s_depth_data = depth_frames;
		}
	}

	//Flush buffers
	s_max_depth_count = 0;
	s_depth_count = 1;
	s_rgb_count = 1;
	freenect_process_events(f_ctx);

	//Start
	QElapsedTimer eTimer;
	eTimer.start();

	s_rgb_count = 0;
	s_depth_count = 0;
	s_max_depth_count = framesAvgCount;

	while (s_depth_count<framesAvgCount || (grabRGB && s_rgb_count==0))
	{
	    freenect_process_events(f_ctx);

		if(s_depth_count == 0 && eTimer.elapsed() > 5000 ) //timeout 5s. without any  data
            break;
	}

	//success?
	if (s_depth_count)
	{
		const unsigned mapSize = s_hDepth*s_wDepth;
		
		//first, pocess frame averaging (if any)
		if (s_depth_count>1)
		{
			const unsigned char minFrameCount = (framesAvgCount>>1); //a pixel must be visible in at least half the frames!
			uint16_t *_depth = s_depth_data;
			for (unsigned i = 0; i < mapSize; ++i,++_depth)
			{
				//sum all equivalent pixels
				unsigned pixCount = 0;
				double pixSum = 0.0;
				const uint16_t* kDepth = s_depth_data + i;
				for (unsigned k=0;k<s_depth_count;++k,kDepth+=mapSize)
				{
					if (*kDepth < FREENECT_DEPTH_RAW_NO_VALUE)
					{
						pixSum += (double)s_depth_data[k*mapSize + i];
						++pixCount;
					}
				}

				if (pixCount>=minFrameCount)
				{
					*_depth = (uint16_t)(pixSum/(double)pixCount);
				}
				else
				{
					*_depth = FREENECT_DEPTH_RAW_NO_VALUE;
				}
			}
		}

        /*** Depth calibration info ***/

        //see http://openkinect.org/wiki/Imaging_Information
        /*static const float minDistance = -10.0f;
        static const float scaleFactor = .0021f;
        const float cx = (float)w/2;
        const float cy = (float)h/2;
        const float fx = 1.0f/scaleFactor; //* (480.0/640.0);
        const float fy = 1.0f/scaleFactor; //~476
        //*/

        //see http://nicolas.burrus.name/index.php/Research/KinectCalibration
        static const float minDistance = -10.0f;
        static const float cx = 339.5f;
        static const float cy = 242.7f;
        static const float fx = 594.21f;
        static const float fy = 591.04f;
        //*/

        /*** RGB calibration info ***/
        static const float fx_rgb = 529.21508098293293f;
        static const float fy_rgb = 525.56393630057437f;
        static const float cx_rgb = 328.94272028759258f;
        static const float cy_rgb = 267.48068171871557f;

        float mat[16]={9.9984628826577793e-01f, 1.2635359098409581e-03f, -1.7487233004436643e-02f, 1.9985242312092553e-02f,
                        -1.4779096108364480e-03f, 9.9992385683542895e-01f, -1.2251380107679535e-02f, -7.4423738761617583e-04f,
                        1.7470421412464927e-02f, 1.2275341476520762e-02f, 9.9977202419716948e-01f, -1.0916736334336222e-02f,
                        0.0f, 0.0f, 0.0f, 1.0f};

        ccGLMatrix depth2rgb(mat);
        depth2rgb.transpose();

        ccPointCloud* depthMap = new ccPointCloud();
		bool hasRGB = s_rgb_count && s_last_rgb_data && m_kDlg->grabRGBCheckBox->isChecked();
        if (depthMap->reserve(mapSize))
		{
			if (hasRGB)
			{
				if (depthMap->reserveTheRGBTable())
					depthMap->showColors(true);
				else
				{
					m_app->dispToConsole("[qKinect] Not enough memory to grab colors!",ccMainAppInterface::WRN_CONSOLE_MESSAGE);
					hasRGB=false;
				}
			}

			const uint16_t *depth = s_depth_data;
			const uint8_t* col = 0;
			const uint8_t white[3]={255,255,255};
			CCVector3 P,Q;

			bool meanFilter = m_kDlg->meanFilterCheckBox->isChecked();

			for (unsigned j=0; j<s_hDepth; ++j)
			{
				//P.y = (PointCoordinateType)j;
				for (unsigned i=0; i<s_wDepth; ++i,++depth)
				{
					uint16_t d = *depth;

					//mean filter
					if (meanFilter)
					{
						double sum = 0.0;
						unsigned count = 0;
						for (int k=-1; k<=1; ++k)
						{
							int ii = static_cast<int>(i)+k;
							if (ii>=0 && ii<static_cast<int>(s_wDepth))
								for (int l=-1;l<=1;++l)
								{
									int jj = static_cast<int>(j)+l;
									if (jj>=0 && jj<static_cast<int>(s_hDepth))
									{
										const uint16_t& dd = s_depth_data[jj*s_wDepth+ii];
										if (dd < FREENECT_DEPTH_RAW_NO_VALUE)
										{
											sum += static_cast<double>(s_depth_data[jj*s_wDepth+ii]);
											++count;
										}
									}
								}
						}

						if (count > 1)
							d = static_cast<uint16_t>(sum/count);
					}

					if (d < FREENECT_DEPTH_RAW_NO_VALUE)
					{
						//see http://openkinect.org/wiki/Imaging_Information
						P.z = 12.36f * tanf(static_cast<float>(d) / 2842.5f + 1.1863f) - 3.7f;
						//see http://nicolas.burrus.name/index.php/Research/KinectCalibration
						P.x = (static_cast<float>(i) - cx) * (P.z + minDistance) / fx;
						P.y = (static_cast<float>(j) - cy) * (P.z + minDistance) / fy ;

						if (hasRGB)
						{
							assert(s_last_rgb_data);

							Q = depth2rgb * P;

							Q.x = (Q.x * fx_rgb / Q.z) + cx_rgb;
							Q.y = (Q.y * fy_rgb / Q.z) + cy_rgb;
							int i_rgb = (int)Q.x;
							int j_rgb = (int)Q.y;
							if (i_rgb>=0 && i_rgb<(int)s_wDepth && j_rgb>=0 && j_rgb<(int)s_hDepth)
							{
								col = s_last_rgb_data+(i_rgb+j_rgb*s_wRgb)*3;
							}
							else
							{
								col = white;
							}
						}

						P.y = -P.y;
						P.z = -P.z;
						depthMap->addPoint(P);

						if (col)
							depthMap->addRGBColor(col);
					}
				}
			}

			//m_app->dispToConsole(QString("Cloud captured: %1 points").arg(depthMap->size()));

			depthMap->resize(depthMap->size());
			QString cloudName = m_kDlg->getCloudName() + QString::number(++s_grabIndex);
			depthMap->setName(qPrintable(cloudName));
			//associate sensor
			ccGBLSensor* sensor = new ccGBLSensor(ccGBLSensor::THETA_PHI);
			ccGLMatrix rot;
			{
				float* mat = rot.data();
				mat[0] = 1.0f;
				mat[1] = 0.0f;
				mat[2] = 0.0f;

				mat[4] = 0.0f;
				mat[5] = 0.0f;
				mat[6] = -1.0f;

				mat[8] = 0.0f;
				mat[9] = 1.0f;
				mat[10] = 0.0f;

				mat[15] = 1.0f;
			}
			sensor->setRigidTransformation(rot);
			sensor->setDeltaPhi(0.0017f);
			sensor->setDeltaTheta(0.0017f);
			sensor->setUncertainty(1e-3f);
			{
				int errorCode = 0;
				CCLib::SimpleCloud* cloud = sensor->project(depthMap,errorCode,true);
				if (cloud)
					delete cloud;
				cloud = 0;
				if (errorCode == 0)
				{
					sensor->setName("Kinect");
					sensor->setGraphicScale(20.0f);
					sensor->setVisible(true);
					depthMap->addChild(sensor);
				}
				else
				{
					delete sensor;
					sensor = 0;
				}
			}
			//selectedEntities.push_back(depthMap);
			m_app->addToDB(depthMap,false,true,true);
			m_app->refreshAll();
		}
		else
		{
			//not enough memory
			delete depthMap;
			depthMap = 0;
			//result = -5;
		}
    }
	else
	{
		//no data!
		//result = -6;
	}