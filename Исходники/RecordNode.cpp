void RecordNode::setParameter(int parameterIndex, float newValue)
{
    //editor->updateParameterButtons(parameterIndex);

    // 0 = stop recording
    // 1 = start recording
    // 2 = toggle individual channel (0.0f = OFF, anything else = ON)

    if (parameterIndex == 1)
    {

        isRecording = true;
       // std::cout << "START RECORDING." << std::endl;

        if (newDirectoryNeeded)
        {
            createNewDirectory();
            recordingNumber = 0;
        }
        else
        {
            recordingNumber++; // increment recording number within this directory
        }

        if (!rootFolder.exists())
        {
            rootFolder.createDirectory();
            String settingsFileName = rootFolder.getFullPathName() + File::separator + "settings.xml";
            getEditorViewport()->saveState(File(settingsFileName));
        }

        createNewFiles();
        
        openFile(eventChannel);

        blockIndex = 0; // reset index


        // create / open necessary files
        for (int i = 0; i < channelPointers.size(); i++)
        {
           // std::cout << "Checking channel " << i << std::endl;

            if (channelPointers[i]->getRecordState())
            {
                openFile(channelPointers[i]);
            }
        }

    }
    else if (parameterIndex == 0)
    {


       // std::cout << "STOP RECORDING." << std::endl;

        if (isRecording)
        {

            // close necessary files
            signalFilesShouldClose = true;

        }

        isRecording = false;


    }
    else if (parameterIndex == 2)
    {

        if (isProcessing)
        {

            std::cout << "Toggling channel " << currentChannel << std::endl;

            if (newValue == 0.0f)
            {
                channelPointers[currentChannel]->setRecordState(false);

                if (isRecording)
                {

                    if (blockIndex < BLOCK_LENGTH)
                    {
                        // fill out the rest of the current buffer
                        writeContinuousBuffer(zeroBuffer.getSampleData(0), BLOCK_LENGTH - blockIndex, currentChannel);
                    }

                    closeFile(channelPointers[currentChannel]);
                }

            }
            else
            {
                channelPointers[currentChannel]->setRecordState(true);

                if (isRecording)
                {

                    openFile(channelPointers[currentChannel]);

                    if (blockIndex > 0)
                    {
                        writeTimestampAndSampleCount(channelPointers[currentChannel]->file);
                        // fill up the first data block up to sample count
                        writeContinuousBuffer(zeroBuffer.getSampleData(0), blockIndex, currentChannel);
                    }

                }
            }
        }
    }
}