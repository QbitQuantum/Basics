bool							clsIGInterface::Open(const String& sDevice)
{
	Close();

	try
		{
		clsCritObj	CO(_Crit);

		if (sDevice.Left(4) == "USB:")
			{
			_pIO = new clsUSBIO(this);
			}
		  else
		if (sDevice.Left(4) == "COM:")
			{
			_pIO = new clsRS232IO(this,57600);
			}
		  else
		if (sDevice.Left(5) == "FTDI:")
			{
			_pIO = new clsFTDIIO(this,57600);
			}
		  else
		if (sDevice.Left(8) == "FTDIW32:")
			{
			_pIO = new clsFTDIW32IO(this,57600);
			}
		  else
			{
			throw clsExcept("port '%s' has unknown format",(LPCTSTR)sDevice);
			}

		if (_pIO == NULL)
			{
			return(false);
			}
		if (!_pIO->IOOpen(sDevice.GetToken(1,':')))
			{
			Close();
			return(false);
			}
		}
	catch (clsExcept& e)
		{
		Close();
		throw;
		}

	return(true);
}