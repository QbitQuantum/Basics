/* CTPatchEx::parse
 * Parses a ZDoom TEXTURES format patch definition
 *******************************************************************/
bool CTPatchEx::parse(Tokenizer& tz, uint8_t type)
{
	// Read basic info
	this->type = type;
	name = tz.getToken().Upper();
	tz.getToken();	// Skip ,
	offset_x = tz.getInteger();
	tz.getToken();	// Skip ,
	offset_y = tz.getInteger();

	// Check if there is any extended info
	if (tz.peekToken() == "{")
	{
		// Skip {
		tz.getToken();

		// Parse extended info
		string property = tz.getToken();
		while (property != "}")
		{
			// FlipX
			if (S_CMPNOCASE(property, "FlipX"))
				flip_x = true;

			// FlipY
			if (S_CMPNOCASE(property, "FlipY"))
				flip_y = true;

			// UseOffsets
			if (S_CMPNOCASE(property, "UseOffsets"))
				use_offsets = true;

			// Rotate
			if (S_CMPNOCASE(property, "Rotate"))
				rotation = tz.getInteger();

			// Translation
			if (S_CMPNOCASE(property, "Translation"))
			{
				// Add first translation string
				translation.parse(tz.getToken());

				// Add any subsequent translations (separated by commas)
				while (tz.peekToken() == ",")
				{
					tz.getToken();	// Skip ,
					translation.parse(tz.getToken());
				}

				blendtype = 1;
			}

			// Blend
			if (S_CMPNOCASE(property, "Blend"))
			{
				double val;
				wxColour col;
				blendtype = 2;

				// Read first value
				string first = tz.getToken();

				// If no second value, it's just a colour string
				if (tz.peekToken() != ",")
				{
					col.Set(first);
					colour.set(col.Red(), col.Green(), col.Blue());
				}
				else
				{
					// Second value could be alpha or green
					tz.getToken();	// Skip ,
					double second = tz.getDouble();

					// If no third value, it's an alpha value
					if (tz.peekToken() != ",")
					{
						col.Set(first);
						colour.set(col.Red(), col.Green(), col.Blue(), second*255);
						blendtype = 3;
					}
					else
					{
						// Third value exists, must be R,G,B,A format
						tz.getToken();	// Skip ,
						first.ToDouble(&val);
						colour.r = val*255;
						colour.g = second*255;
						colour.b = tz.getDouble()*255;
						if (tz.peekToken() != ",")
						{
							wxLogMessage("Invalid TEXTURES definition, expected ',', got '%s'", tz.getToken());
							return false;
						}
						tz.getToken();	// Skip ,
						colour.a = tz.getDouble()*255;
						blendtype = 3;
					}
				}
			}

			// Alpha
			if (S_CMPNOCASE(property, "Alpha"))
				alpha = tz.getFloat();

			// Style
			if (S_CMPNOCASE(property, "Style"))
				style = tz.getToken();

			// Read next property name
			property = tz.getToken();
		}
	}

	return true;
}