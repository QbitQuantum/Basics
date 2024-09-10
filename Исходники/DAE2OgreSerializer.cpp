	bool OgreSerializer::setPos( fpos_t pos )
	{
		return (fsetpos( mpfFile, &pos) == 0);
	}