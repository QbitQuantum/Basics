	inline void readEnum(
			std::streambuf & istrm, Handler & result,
			const ReaderFunc & read, const UInt8 beginsig, const UInt8 endsig)
	{
		verifySignature(istrm, beginsig);
		bool done = false;
		while (!done)
		{
			try
			{
				result.handle(read(istrm));
			}
			catch (const BadSignatureException& e)
			{
				// read threw because we've read all the objects
				verifySignature(istrm, endsig);
				done = true;
			}
		}
	}