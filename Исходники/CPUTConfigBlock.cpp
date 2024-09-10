//----------------------------------------------------------------
CPUTResult CPUTConfigFileA::LoadFile(const std::string &szFilename)
{
    int nBytes = 0;
    char *pFileContents = NULL;
#if 1 
#ifdef UNICODE
    CPUTResult result = CPUTFileSystem::ReadFileContentsA(szFilename, (UINT *)&nBytes, (void **)&pFileContents, true);
#else
    CPUTResult result = CPUTFileSystem::ReadFileContents(szFilename, (UINT *)&nBytes, (void **)&pFileContents, true);
#endif
    if(CPUTFAILED(result))
    {
		DEBUG_PRINT(_L("Failed to read file %s"), szFilename.c_str());
		return result;
    }
    
#else
    // Load the file
    FILE               *pFile = NULL;
    CPUTResult result = CPUTFileSystem::OpenFile(szFilename, &pFile);
    if(CPUTFAILED(result))
    {
        return result;
    }

//  _locale_t locale = _get_current_locale();

    /* Determine file size */
    fseek(pFile, 0, SEEK_END);
    int nBytes = ftell(pFile); // for text files, this is an overestimate
    fseek(pFile, 0, SEEK_SET);

    /* Read the whole thing */
    char *pFileContents = new char[nBytes + 1];
    nBytes = (int)fread(pFileContents, 1, nBytes, pFile);
    fclose(pFile);
    
    pFileContents[nBytes] = 0; // add 0-terminator
#endif
    CPUTConfigBlockA   *pCurrBlock = NULL;
    int                 nCurrBlock = 0;
    
    /* Count the number of blocks */
    const char *pCur = pFileContents;
    const char *pStart, *pEnd;
    
    while(ReadLine(&pStart, &pEnd, &pCur))
    {
        const char *pOpen = FindFirst(pStart, pEnd, '[');
        const char *pClose = FindLast(pOpen + 1, pEnd, ']');
        if (pOpen < pClose)
        {
            // This line is a valid block header
            mnBlockCount++;
        }
    }
    
    // For files that don't have any blocks, just add the entire file to one block
    if(mnBlockCount == 0)
    {
        mnBlockCount   = 1;
    }
    
    pCur = pFileContents;
    mpBlocks = new CPUTConfigBlockA[mnBlockCount];
    pCurrBlock = mpBlocks;
    
    /* Find the first block first */
    while(ReadLine(&pStart, &pEnd, &pCur))
    {
        const char *pOpen = FindFirst(pStart, pEnd, '[');
        const char *pClose = FindLast(pOpen + 1, pEnd, ']');
        if (pOpen < pClose)
        {
            // This line is a valid block header
            pCurrBlock = mpBlocks + nCurrBlock++;
            //AssignStr(pCurrBlock->mszName, pOpen + 1, pClose, locale);
            pCurrBlock->mszName.assign(pOpen + 1, pClose);
            std::transform(pCurrBlock->mszName.begin(), pCurrBlock->mszName.end(), pCurrBlock->mszName.begin(), tolow);
        }
        else if (pStart < pEnd)
        {
            // It's a value
            if (pCurrBlock == NULL)
            {
                continue;
            }
            
            const char *pEquals = FindFirst(pStart, pEnd, '=');
            if (pEquals == pEnd)
            {
                // No value, just a key, save it anyway
                // Optimistically, we assume it's new
                std::string &name = pCurrBlock->mpValues[pCurrBlock->mnValueCount].szName;
                //AssignStr(name, pStart, pEnd, locale);
                name.assign(pStart, pEnd);
                
                bool dup = false;
                for(int ii=0;ii<pCurrBlock->mnValueCount;++ii)
                {
                    if(!pCurrBlock->mpValues[ii].szName.compare(name))
                    {
                        dup = true;
                        break;
                    }
                }
                if(!dup)
                {
                    pCurrBlock->mnValueCount++;
                }
            }
            else
            {
                const char *pNameStart = pStart;
                const char *pNameEnd = pEquals;
                const char *pValStart = pEquals + 1;
                const char *pValEnd = pEnd;
                
                RemoveWhitespace(pNameStart, pNameEnd);
                RemoveWhitespace(pValStart, pValEnd);
                
                // Optimistically assume the name is new
                std::string &name = pCurrBlock->mpValues[pCurrBlock->mnValueCount].szName;
                //AssignStr(name, pNameStart, pNameEnd, locale);
                name.assign(pNameStart, pNameEnd);
                std::transform(name.begin(), name.end(), name.begin(), tolow);
                
                bool dup = false;
                for(int ii=0;ii<pCurrBlock->mnValueCount;++ii)
                {
                    if(!pCurrBlock->mpValues[ii].szName.compare(name))
                    {
                        dup = true;
                        break;
                    }
                }
                if(!dup)
                {
                    //                    AssignStr(pCurrBlock->mpValues[pCurrBlock->mnValueCount].szValue, pValStart, pValEnd, locale);
                    pCurrBlock->mpValues[pCurrBlock->mnValueCount].szValue.assign(pValStart, pValEnd);
                    pCurrBlock->mnValueCount++;
                }
            }
        }
    }
    
    delete[] pFileContents;
    return CPUT_SUCCESS;
}