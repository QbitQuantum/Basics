void CPsfRarArchive::ReadFileContents(const char* fileName, void* buffer, unsigned int bufferLength)
{
	Archive* arc(ConvertArchive(m_archive));
	if(!arc->IsOpened())
	{
		throw std::runtime_error("Archive isn't opened.");
	}

	std::string fixedFileName(fileName);
	boost::replace_all(fixedFileName, "/", "\\");

	arc->Seek(0, SEEK_SET);

	ComprDataIO dataIo;
	dataIo.Init();

	Unpack unpack(&dataIo);

	while(arc->ReadHeader() > 0)
	{
		if(arc->ShortBlock.HeaderType == HEAD_FILE)
		{
			if(!arc->IsArcDir())
			{
				bool isGoodFile = !stricmp(fixedFileName.c_str(), string_cast<std::string>(arc->FileHead.FileName).c_str());

				dataIo.SetFiles(arc, NULL);
				dataIo.SetPackedSizeToRead(arc->FileHead.PackSize);

				dataIo.CurUnpRead = 0;
				dataIo.CurUnpWrite = 0;
				dataIo.UnpHash.Init(arc->FileHead.FileHash.Type, 1);
				dataIo.PackedDataHash.Init(arc->FileHead.FileHash.Type, 1);
				dataIo.SetTestMode(!isGoodFile);

				if(isGoodFile)
				{
					dataIo.SetUnpackToMemory(reinterpret_cast<byte*>(buffer), bufferLength);
				}

				unpack.Init(arc->FileHead.WinSize, arc->FileHead.Solid);
				unpack.SetDestSize(arc->FileHead.UnpSize);

				if(arc->FileHead.Method == 0x30)
				{
					std::vector<byte> unstoreBuffer;
					unstoreBuffer.resize(0x10000);
					uint toReadSize = arc->FileHead.UnpSize;
					while(1)
					{
						uint code = dataIo.UnpRead(&unstoreBuffer[0], unstoreBuffer.size());
						if(code == 0 || code == -1) break;
						code = code < toReadSize ? code : toReadSize;
						dataIo.UnpWrite(&unstoreBuffer[0], code);
						if(toReadSize >= 0)
						{
							toReadSize -= code;
						}
					}
				}
				else
				{
					unpack.DoUnpack(arc->FileHead.UnpVer, arc->FileHead.Solid);
				}

				if(!dataIo.UnpHash.Cmp(&arc->FileHead.FileHash, arc->FileHead.UseHashKey ? arc->FileHead.HashKey : nullptr))
				{
					throw std::runtime_error("CRC check error.");
				}

				if(isGoodFile)
				{
					return;
				}
			}
		}
		arc->SeekToNext();
	}

	throw std::runtime_error("Couldn't read file from archive.");
}