void ComplexPlanePlotWindow::onPlotPressed()
{
	if(_msWindow.HasImage())
	{
		try {
			Plot2D &plot = _plotManager.NewPlot2D("Complex plane");
			size_t x = (size_t) _xPositionScale.get_value();
			size_t y = (size_t) _yPositionScale.get_value();
			size_t length = (size_t) _lengthScale.get_value();
			size_t avgSize = (size_t) _ySumLengthScale.get_value();
			bool realVersusImaginary = _realVersusImaginaryButton.get_active();
			const TimeFrequencyData &data = _msWindow.GetActiveData();

			if(_allValuesButton.get_active())
			{
				Plot2DPointSet *pointSet;
				if(realVersusImaginary)
					pointSet = &plot.StartLine("Data", Plot2DPointSet::DrawPoints);
				else
					pointSet = &plot.StartLine("Data (real)", Plot2DPointSet::DrawPoints);
				Mask2DPtr mask = Mask2D::CreateSetMaskPtr<false>(_msWindow.AltMask()->Width(), _msWindow.AltMask()->Height());
				RFIPlots::MakeComplexPlanePlot(*pointSet, data, x, length, y, avgSize, mask, realVersusImaginary, false);
	
				if(!realVersusImaginary)
				{
					pointSet = &plot.StartLine("Data (imaginary)", Plot2DPointSet::DrawPoints);
					RFIPlots::MakeComplexPlanePlot(*pointSet, data, x, length, y, avgSize, mask, realVersusImaginary, true);
				}
			}

			if(_unmaskedValuesButton.get_active())
			{
				Plot2DPointSet *pointSet = &plot.StartLine("Without RFI");
				RFIPlots::MakeComplexPlanePlot(*pointSet, data, x, length, y, avgSize, _msWindow.AltMask(), realVersusImaginary, false);
				if(!realVersusImaginary)
				{
					pointSet = &plot.StartLine("Without RFI (I)");
					RFIPlots::MakeComplexPlanePlot(*pointSet, data, x, length, y, avgSize, _msWindow.AltMask(), realVersusImaginary, true);
				}
			}
	
			if(_maskedValuesButton.get_active())
			{
				Plot2DPointSet *pointSet = &plot.StartLine("Only RFI");
				Mask2DPtr mask = Mask2D::CreateCopy(_msWindow.AltMask());
				mask->Invert();
				RFIPlots::MakeComplexPlanePlot(*pointSet, data, x, length, y, avgSize, mask, realVersusImaginary, false);
				if(!realVersusImaginary)
				{
					pointSet = &plot.StartLine("Only RFI (I)");
					RFIPlots::MakeComplexPlanePlot(*pointSet, data, x, length, y, avgSize, mask, realVersusImaginary, true);
				}
			}
	
			if(_fittedValuesButton.get_active())
			{
				Plot2DPointSet *pointSet;
				if(realVersusImaginary)
					pointSet = &plot.StartLine("Fit");
				else
					pointSet = &plot.StartLine("Fit (real)");
				size_t middleY = (2*y + avgSize) / 2;
				Baseline baseline(_msWindow.TimeFrequencyMetaData()->Antenna1(), _msWindow.TimeFrequencyMetaData()->Antenna2());
				long double fringeCount =
					UVImager::GetFringeCount(x, x+length, middleY, _msWindow.TimeFrequencyMetaData());
				long double fringeFrequency = fringeCount / length;
				Mask2DPtr mask = Mask2D::CreateSetMaskPtr<false>(_msWindow.AltMask()->Width(), _msWindow.AltMask()->Height());
				RFIPlots::MakeFittedComplexPlot(*pointSet, data, x, length, y, avgSize, mask, fringeFrequency, realVersusImaginary, false);
				if(!realVersusImaginary)
				{
					pointSet = &plot.StartLine("Fit (imaginary)");
					RFIPlots::MakeFittedComplexPlot(*pointSet, data, x, length, y, avgSize, mask, fringeFrequency, realVersusImaginary, true);
				}
			}

			if(_individualSampleFitButton.get_active())
			{
				FringeStoppingFitter fitter;
				fitter.Initialize(data);
				fitter.SetFitChannelsIndividually(true);
				fitter.SetFringesToConsider(1.0L);
				fitter.SetMaxWindowSize(256);
				fitter.SetReturnFittedValue(true);
				fitter.SetReturnMeanValue(false);
				
				fitter.SetMetaData(_msWindow.TimeFrequencyMetaData());
				fitter.PerformStaticFrequencyFitOnOneChannel(y);

				Plot2DPointSet *pointSet;
				if(realVersusImaginary)
					pointSet = &plot.StartLine("Fit");
				else
					pointSet = &plot.StartLine("Fit (real)");
				Mask2DPtr mask = Mask2D::CreateSetMaskPtr<false>(_msWindow.AltMask()->Width(), _msWindow.AltMask()->Height());
				RFIPlots::MakeComplexPlanePlot(*pointSet, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, false);
	
				fitter.SetReturnFittedValue(false);
				fitter.SetReturnMeanValue(true);
				if(!realVersusImaginary)
				{
					pointSet = &plot.StartLine("Fit (imaginary)");
					RFIPlots::MakeComplexPlanePlot(*pointSet, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, true);
				}

				fitter.PerformStaticFrequencyFitOnOneChannel(y);

				pointSet = &plot.StartLine("Center");
				RFIPlots::MakeComplexPlanePlot(*pointSet, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, false);
	
				if(!realVersusImaginary)
				{
					pointSet = &plot.StartLine("Center (I)");
					RFIPlots::MakeComplexPlanePlot(*pointSet, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, true);
				}
			}
	
			if(_fringeFitButton.get_active() || _dynamicFringeFitButton.get_active())
			{
				/*FringeStoppingFitter fitter;
				Image2DPtr zero = Image2D::CreateZeroImagePtr(data.ImageWidth(), data.ImageHeight());
				Image2DPtr ones = Image2D::CreateZeroImagePtr(data.ImageWidth(), data.ImageHeight());
				for(size_t yi=0;yi<ones->Height();++yi)
					for(size_t xi=0;xi<ones->Width();++xi)
						ones->SetValue(xi, yi, 1.0L);
				TimeFrequencyData data(StokesIPolarisation, ones, zero);
				fitter.Initialize(data);
				fitter.SetFitChannelsIndividually(true);
				
				fitter.SetMetaData(_msWindow.TimeFrequencyMetaData());
				fitter.PerformFringeStop();

				plot.StartLine("Fringe rotation");
				Mask2DPtr mask = Mask2D::CreateSetMaskPtr<false>(_msWindow.AltMask()->Width(), _msWindow.AltMask()->Height());
				RFIPlots::MakeComplexPlanePlot(plot, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, false);
	
				if(!realVersusImaginary)
				{
					plot.StartLine("Fringe rotation (I)");
					RFIPlots::MakeComplexPlanePlot(plot, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, true);
				}*/

				FringeStoppingFitter fitter;
				fitter.Initialize(data);
				
				fitter.SetMetaData(_msWindow.TimeFrequencyMetaData());
				//fitter.PerformFringeStop();
				fitter.SetReturnFittedValue(true);
				if(_dynamicFringeFitButton.get_active())
					fitter.PerformDynamicFrequencyFit(y, y + avgSize, 200);
				else
					fitter.PerformDynamicFrequencyFit(y, y + avgSize);

				Plot2DPointSet *pointSet;
				if(realVersusImaginary)
					pointSet = &plot.StartLine("Fit");
				else
					pointSet = &plot.StartLine("Fit (real)");
				Mask2DPtr mask = Mask2D::CreateSetMaskPtr<false>(_msWindow.AltMask()->Width(), _msWindow.AltMask()->Height());
				RFIPlots::MakeComplexPlanePlot(*pointSet, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, false);
	
				if(!realVersusImaginary)
				{
					pointSet = &plot.StartLine("Fit (imaginary)");
					RFIPlots::MakeComplexPlanePlot(*pointSet, fitter.Background(), x, length, y, avgSize, mask, realVersusImaginary, true);
				}
			}

			_plotManager.Update();
			
		} catch(std::exception &e)
		{
			Gtk::MessageDialog dialog(*this, e.what(), false, Gtk::MESSAGE_ERROR);
			dialog.run();
		}
	}
}