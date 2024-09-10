	bool WAV_Source::load(hstream& output)
	{
		if (Source::load(output) == 0)
		{
			return false;
		}
		int written = output.writeRaw(*this->stream, this->size);
		if (written > 0)
		{
			output.seek(-written);
			return true;
		}
		return false;
	}