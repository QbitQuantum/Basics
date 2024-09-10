size_t FormDataStream::read(void* ptr, size_t blockSize, size_t numberOfBlocks)
{
    using namespace EA::WebKit;

	// Check for overflow.
	if (!numberOfBlocks || blockSize > std::numeric_limits<size_t>::max() / numberOfBlocks)
		return 0;

    Vector<FormDataElement> elements;

    if(m_resourceHandle->firstRequest().httpBody())
        elements = m_resourceHandle->firstRequest().httpBody()->elements();

    if(m_formDataElementIndex >= elements.size())
        return 0;

    const FormDataElement& element          = elements[m_formDataElementIndex];
    
	size_t                 toSend           = blockSize * numberOfBlocks;
	size_t                 sent             = 0;

	
    if(element.m_type == FormDataElement::encodedFile)
    {
		EA::WebKit::FileSystem* pFS = GetFileSystem();
        EAW_ASSERT(pFS != NULL);

        if(pFS)
        {
            if(m_file == FileSystem::kFileObjectInvalid)
            {
                m_file = pFS->CreateFileObject();

                if(m_file != FileSystem::kFileObjectInvalid)
                {
                    if(!pFS->OpenFile(m_file, element.m_filename.utf8().data(), FileSystem::kRead))
                    {
                        pFS->DestroyFileObject(m_file);
                        m_file = FileSystem::kFileObjectInvalid;
                    }
                }
            }

            if(m_file != FileSystem::kFileObjectInvalid)
            {
                EAW_ASSERT_FORMATTED(m_file != FileSystem::kFileObjectInvalid, "FormDataStream::read: Failed while trying to open %s for upload\n", element.m_filename.utf8().data());
                return 0;
            }

            const int64_t readSize = pFS->ReadFile(m_file, ptr, (int64_t)toSend);

            if(readSize < 0)  // If there was error...
            {
                EAW_ASSERT_FORMATTED(readSize < 0, "FormDataStream::read: Failed while trying to read %s for upload\n", element.m_filename.utf8().data());
                return 0;
            }

            sent = (size_t)readSize;

            if(pFS->GetFilePosition(m_file) == pFS->GetFileSize(m_file))  // If done reading the file...
            {
                pFS->CloseFile(m_file);
                pFS->DestroyFileObject(m_file);
                m_file = FileSystem::kFileObjectInvalid;

                m_formDataElementIndex++;
            }
        }
    } 
    else if(element.m_type == FormDataElement::data)
    {
		size_t elementSize = element.m_data.size() - m_formDataElementDataOffset;
		sent = elementSize > toSend ? toSend : elementSize;
		memcpy(ptr, element.m_data.data() + m_formDataElementDataOffset, sent);
		if (elementSize > sent)
			m_formDataElementDataOffset += sent;
		else {
			m_formDataElementDataOffset = 0;
			m_formDataElementIndex++;
		}
    }
	else
	{
		EAW_ASSERT_MSG(false, "Unhandled FormDataElement Type");
	}

    return sent;
}