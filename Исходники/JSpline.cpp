void JSpline::Render(float x, float y, PIXEL_TYPE color, PIXEL_TYPE controlColor)
{
	if (mCount > 0)
	{
		JRenderer* renderer = JRenderer::GetInstance();
//		renderer->SetLineWidth(1.2f);

		int size = mPixels.size();
		
		for (int i=0;i<size-1;i++)
			renderer->DrawLine(x+mPixels[i].x, y+mPixels[i].y, x+mPixels[i+1].x, y+mPixels[i+1].y, color);

		size = mMidPoints.size();
		for (int i=0; i < size; i++)
			renderer->FillRect(mMidPoints[i].x-3, mMidPoints[i].y-3, 6, 6, controlColor);
	}
	
}