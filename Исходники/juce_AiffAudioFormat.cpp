    //==============================================================================
    AiffAudioFormatReader (InputStream* in)
        : AudioFormatReader (in, TRANS (aiffFormatName))
    {
        using namespace AiffFileHelpers;

        if (input->readInt() == chunkName ("FORM"))
        {
            const int len = input->readIntBigEndian();
            const int64 end = input->getPosition() + len;

            const int nextType = input->readInt();
            if (nextType == chunkName ("AIFF") || nextType == chunkName ("AIFC"))
            {
                bool hasGotVer = false;
                bool hasGotData = false;
                bool hasGotType = false;

                while (input->getPosition() < end)
                {
                    const int type = input->readInt();
                    const uint32 length = (uint32) input->readIntBigEndian();
                    const int64 chunkEnd = input->getPosition() + length;

                    if (type == chunkName ("FVER"))
                    {
                        hasGotVer = true;

                        const int ver = input->readIntBigEndian();
                        if (ver != 0 && ver != (int) 0xa2805140)
                            break;
                    }
                    else if (type == chunkName ("COMM"))
                    {
                        hasGotType = true;

                        numChannels = (unsigned int) input->readShortBigEndian();
                        lengthInSamples = input->readIntBigEndian();
                        bitsPerSample = input->readShortBigEndian();
                        bytesPerFrame = (numChannels * bitsPerSample) >> 3;

                        unsigned char sampleRateBytes[10];
                        input->read (sampleRateBytes, 10);
                        const int byte0 = sampleRateBytes[0];

                        if ((byte0 & 0x80) != 0
                                || byte0 <= 0x3F || byte0 > 0x40
                                || (byte0 == 0x40 && sampleRateBytes[1] > 0x1C))
                            break;

                        unsigned int sampRate = ByteOrder::bigEndianInt (sampleRateBytes + 2);
                        sampRate >>= (16414 - ByteOrder::bigEndianShort (sampleRateBytes));
                        sampleRate = (int) sampRate;

                        if (length <= 18)
                        {
                            // some types don't have a chunk large enough to include a compression
                            // type, so assume it's just big-endian pcm
                            littleEndian = false;
                        }
                        else
                        {
                            const int compType = input->readInt();

                            if (compType == chunkName ("NONE") || compType == chunkName ("twos"))
                            {
                                littleEndian = false;
                            }
                            else if (compType == chunkName ("sowt"))
                            {
                                littleEndian = true;
                            }
                            else
                            {
                                sampleRate = 0;
                                break;
                            }
                        }
                    }
                    else if (type == chunkName ("SSND"))
                    {
                        hasGotData = true;

                        const int offset = input->readIntBigEndian();
                        dataChunkStart = input->getPosition() + 4 + offset;
                        lengthInSamples = (bytesPerFrame > 0) ? jmin (lengthInSamples, (int64) (length / bytesPerFrame)) : 0;
                    }
                    else if (type == chunkName ("MARK"))
                    {
                        const uint16 numCues = (uint16) input->readShortBigEndian();

                        // these two are always the same for AIFF-read files
                        metadataValues.set ("NumCuePoints", String (numCues));
                        metadataValues.set ("NumCueLabels", String (numCues));

                        for (uint16 i = 0; i < numCues; ++i)
                        {
                            uint16 identifier = (uint16) input->readShortBigEndian();
                            uint32 offset = (uint32) input->readIntBigEndian();
                            uint8 stringLength = (uint8) input->readByte();
                            MemoryBlock textBlock;
                            input->readIntoMemoryBlock (textBlock, stringLength);

                            // if the stringLength is even then read one more byte as the
                            // string needs to be an even number of bytes INCLUDING the
                            // leading length character in the pascal string
                            if ((stringLength & 1) == 0)
                                input->readByte();

                            const String prefixCue ("Cue" + String (i));
                            metadataValues.set (prefixCue + "Identifier", String (identifier));
                            metadataValues.set (prefixCue + "Offset", String (offset));

                            const String prefixLabel ("CueLabel" + String (i));
                            metadataValues.set (prefixLabel + "Identifier", String (identifier));
                            metadataValues.set (prefixLabel + "Text", textBlock.toString());
                        }
                    }
                    else if (type == chunkName ("COMT"))
                    {
                        const uint16 numNotes = (uint16) input->readShortBigEndian();
                        metadataValues.set ("NumCueNotes", String (numNotes));

                        for (uint16 i = 0; i < numNotes; ++i)
                        {
                            uint32 timestamp = (uint32) input->readIntBigEndian();
                            uint16 identifier = (uint16) input->readShortBigEndian(); // may be zero in this case
                            uint16 stringLength = (uint16) input->readShortBigEndian();

                            MemoryBlock textBlock;
                            input->readIntoMemoryBlock (textBlock, stringLength + (stringLength & 1));

                            const String prefix ("CueNote" + String (i));
                            metadataValues.set (prefix + "TimeStamp", String (timestamp));
                            metadataValues.set (prefix + "Identifier", String (identifier));
                            metadataValues.set (prefix + "Text", textBlock.toString());
                        }
                    }
                    else if (type == chunkName ("INST"))
                    {
                        HeapBlock <InstChunk> inst;
                        inst.calloc (jmax ((size_t) length + 1, sizeof (InstChunk)), 1);
                        input->read (inst, length);
                        inst->copyTo (metadataValues);
                    }
                    else if ((hasGotVer && hasGotData && hasGotType)
                             || chunkEnd < input->getPosition()
                             || input->isExhausted())
                    {
                        break;
                    }

                    input->setPosition (chunkEnd);
                }