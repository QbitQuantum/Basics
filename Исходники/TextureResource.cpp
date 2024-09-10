// Attempts to load the texture from the source.
bool TextureResource::Load(RenderInterface* render_interface) const
{
	// Check for special loader tokens.
	if (!source.Empty() &&
		source[0] == '?')
	{
		Vector2i dimensions;

		bool delete_data = false;
		const byte* data = NULL;

		// Find the generation protocol and generate the data accordingly.
		String protocol = source.Substring(1, source.Find("::") - 1);
		if (protocol == "font")
		{
			// The requested texture is a font layer.
			delete_data = true;

			FontFaceHandle* handle;
			FontEffect* layer_id;
			int layout_id;
			int texture_id;

			if (sscanf(source.CString(), "?font::%p/%p/%d/%d", &handle, &layer_id, &layout_id, &texture_id) == 4)
			{
				handle->GenerateLayerTexture(data,
											 dimensions,
											 layer_id,
											 layout_id,
											 texture_id);
			}
		}

		// If texture data was generated, great! Otherwise, fallback to the LoadTexture() code and
		// hope the client knows what the hell to do with the question mark in their file name.
		if (data != NULL)
		{
			TextureHandle handle;
			bool success = render_interface->GenerateTexture(handle, data, dimensions);

			if (delete_data)
				delete[] data;

			if (success)
			{
				texture_data[render_interface] = TextureData(handle, dimensions);
				return true;
			}
			else
			{
				Log::Message(Log::LT_WARNING, "Failed to generate internal texture %s.", source.CString());
				texture_data[render_interface] = TextureData(0, Vector2i(0, 0));

				return false;
			}
		}
	}

	TextureHandle handle;
	Vector2i dimensions;
	if (!render_interface->LoadTexture(handle, dimensions, source))
	{
		Log::Message(Log::LT_WARNING, "Failed to load texture from %s.", source.CString());
		texture_data[render_interface] = TextureData(0, Vector2i(0, 0));

		return false;
	}

	texture_data[render_interface] = TextureData(handle, dimensions);
	return true;
}