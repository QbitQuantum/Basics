//--------------------------------------------------------------------------
int UnitPakFiles(FileList &source_list, const char *output_path)
{
	if (source_list.containsItems() == 0)
	{
		return(_pak_files_ok);
	}

	Surface surface;

	int frameCount;

	frameCount = source_list.containsItems();

	if (LoadSurface(source_list.getString(0), surface) == _load_surface_invalid_type)
	{
		return _pak_files_invalid_source;
	}

	Surface workSurface(surface.getPixX(), surface.getPixY(), surface.getPixX(), frameCount);
	workSurface.fillAll(0);

	for (int i = 0; i < frameCount; i++)
	{
		workSurface.setFrame(i);

		if (LoadSurface(source_list.getString(i), surface) == _load_surface_invalid_type)
		{
			return _pak_files_invalid_source;
		}

		PIX background = surface.getPixel(0, 0);

		// Walk through the surface image and suck out the shadow.
		for (int x = 0; x < surface.getPixX(); x++)
		{
			for (int y = 0; y < surface.getPixY(); y++)
			{
				PIX color = surface.getPixel(x, y);

				if (color != background)
				{
					workSurface.putPixel(x, y, color);
				}
			}
		}
	}

	PackedSurface packedSurface;
	packedSurface.pack(workSurface);
	packedSurface.save(output_path);

	return _pak_files_ok;
}