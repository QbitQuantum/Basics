void VariableSizeBokehBlurOperation::executePixel(float output[4], int x, int y, void *data)
{
	VariableSizeBokehBlurTileData *tileData = (VariableSizeBokehBlurTileData *)data;
	MemoryBuffer *inputProgramBuffer = tileData->color;
	MemoryBuffer *inputBokehBuffer = tileData->bokeh;
	MemoryBuffer *inputSizeBuffer = tileData->size;
	float *inputSizeFloatBuffer = inputSizeBuffer->getBuffer();
	float *inputProgramFloatBuffer = inputProgramBuffer->getBuffer();
	float readColor[4];
	float bokeh[4];
	float tempSize[4];
	float multiplier_accum[4];
	float color_accum[4];

	const float max_dim = max(m_width, m_height);
	const float scalar = this->m_do_size_scale ? (max_dim / 100.0f) : 1.0f;
	int maxBlurScalar = tileData->maxBlurScalar;

	BLI_assert(inputBokehBuffer->getWidth()  == COM_BLUR_BOKEH_PIXELS);
	BLI_assert(inputBokehBuffer->getHeight() == COM_BLUR_BOKEH_PIXELS);

#ifdef COM_DEFOCUS_SEARCH
	float search[4];
	this->m_inputSearchProgram->read(search, x / InverseSearchRadiusOperation::DIVIDER, y / InverseSearchRadiusOperation::DIVIDER, NULL);
	int minx = search[0];
	int miny = search[1];
	int maxx = search[2];
	int maxy = search[3];
#else
	int minx = max(x - maxBlurScalar, 0);
	int miny = max(y - maxBlurScalar, 0);
	int maxx = min(x + maxBlurScalar, (int)m_width);
	int maxy = min(y + maxBlurScalar, (int)m_height);
#endif
	{
		inputSizeBuffer->readNoCheck(tempSize, x, y);
		inputProgramBuffer->readNoCheck(readColor, x, y);

		copy_v4_v4(color_accum, readColor);
		copy_v4_fl(multiplier_accum, 1.0f);
		float size_center = tempSize[0] * scalar;

		const int addXStepValue = QualityStepHelper::getStep();
		const int addYStepValue = addXStepValue;
		const int addXStepColor = addXStepValue * COM_NUM_CHANNELS_COLOR;

		if (size_center > this->m_threshold) {
			for (int ny = miny; ny < maxy; ny += addYStepValue) {
				float dy = ny - y;
				int offsetValueNy = ny * inputSizeBuffer->getWidth();
				int offsetValueNxNy = offsetValueNy + (minx);
				int offsetColorNxNy = offsetValueNxNy * COM_NUM_CHANNELS_COLOR;
				for (int nx = minx; nx < maxx; nx += addXStepValue) {
					if (nx != x || ny != y) {
						float size = min(inputSizeFloatBuffer[offsetValueNxNy] * scalar, size_center);
						if (size > this->m_threshold) {
							float dx = nx - x;
							if (size > fabsf(dx) && size > fabsf(dy)) {
								float uv[2] = {
									(float)(COM_BLUR_BOKEH_PIXELS / 2) + (dx / size) * (float)((COM_BLUR_BOKEH_PIXELS / 2) - 1),
									(float)(COM_BLUR_BOKEH_PIXELS / 2) + (dy / size) * (float)((COM_BLUR_BOKEH_PIXELS / 2) - 1)};
								inputBokehBuffer->read(bokeh, uv[0], uv[1]);
								madd_v4_v4v4(color_accum, bokeh, &inputProgramFloatBuffer[offsetColorNxNy]);
								add_v4_v4(multiplier_accum, bokeh);
							}
						}
					}
					offsetColorNxNy += addXStepColor;
					offsetValueNxNy += addXStepValue;				}
			}
		}

		output[0] = color_accum[0] / multiplier_accum[0];
		output[1] = color_accum[1] / multiplier_accum[1];
		output[2] = color_accum[2] / multiplier_accum[2];
		output[3] = color_accum[3] / multiplier_accum[3];

		/* blend in out values over the threshold, otherwise we get sharp, ugly transitions */
		if ((size_center > this->m_threshold) &&
		    (size_center < this->m_threshold * 2.0f))
		{
			/* factor from 0-1 */
			float fac = (size_center - this->m_threshold) / this->m_threshold;
			interp_v4_v4v4(output, readColor, output, fac);
		}
	}

}