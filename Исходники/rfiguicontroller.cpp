void RFIGuiController::PlotDist()
{
	if(IsImageLoaded())
	{
		Plot2D &plot = _plotManager->NewPlot2D("Distribution");

		TimeFrequencyData activeData = ActiveData();
		Image2DCPtr image = activeData.GetSingleImage();
		Mask2DPtr mask =
			Mask2D::CreateSetMaskPtr<false>(image->Width(), image->Height());
		Plot2DPointSet &totalSet = plot.StartLine("Total");
		RFIPlots::MakeDistPlot(totalSet, image, mask);

		Plot2DPointSet &uncontaminatedSet = plot.StartLine("Uncontaminated");
		mask = Mask2D::CreateCopy(activeData.GetSingleMask());
		RFIPlots::MakeDistPlot(uncontaminatedSet, image, mask);

		mask->Invert();
		Plot2DPointSet &rfiSet = plot.StartLine("RFI");
		RFIPlots::MakeDistPlot(rfiSet, image, mask);

		_plotManager->Update();
	}
}