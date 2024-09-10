//-------------------------------------//
void clTextureAtlas::AddTextureToAtlas(tyTextureAtlasPos *outTexturePos, unsigned int * data, int width, int height, int repeatWidth)
{
	if (m_img_buffer == NULL) return;

	int widthSum = width + repeatWidth;

	if (outTexturePos != NULL)
	{
		outTexturePos->x = 0;
		outTexturePos->y = 0;
		outTexturePos->width = 0;
		outTexturePos->height = 0;
	}

	enumTexturSizeSlot slot = getSlotByHeight(height);


	if (slot == enumTexturSizeSlot::_TEXTURE_HEIGHT_COUNT)
	{
		m_error.AddError("Texture can't by coppyed to Texture Atlas! Texture height is out of range.");
		return;
	}

	if (widthSum > m_width)
	{
		m_error.AddError("Texture can't by coppyed to Texture Atlas! Texture width is to large!");
		return;
	}

	if ((m_slot_pos_x[slot] + widthSum) > m_width)
	{

		if ((m_filled_y_pos + SLOT_HEIGHT[slot]) > m_height)
		{
			m_error.AddError("Texture can't by coppyed to Texture Atlas! Texture Atlas is FULL!");
			return;
		}

		//- slot is full - create new!
		m_slot_pos_y[slot] = m_filled_y_pos;
		m_slot_pos_x[slot] = 0;
		m_filled_y_pos += SLOT_HEIGHT[slot];
	}

	//- copy image to slot position
	int outX = m_slot_pos_x[slot];
	int outY = m_slot_pos_y[slot];

	copyimage(m_img_buffer, data, outX, outY, width, height, m_width);

	//- repeat a part of the image at the end of the original image
	if (repeatWidth > 0)
	{
		copyimage(m_img_buffer, data, outX + width, outY, repeatWidth, height, m_width, width);
	}

	//- move slot position
	m_slot_pos_x[slot] += widthSum;


	if (outTexturePos != NULL)
	{
		outTexturePos->x = outX;
		outTexturePos->y = outY;
		outTexturePos->width = widthSum;
		outTexturePos->height = height;
	}

	//- update fill state
	m_fillState += widthSum * height;

}