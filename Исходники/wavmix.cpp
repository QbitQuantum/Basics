int main(int argc, char *argv[])
{

    //
    // initial seconds count, set to zero.
    
    int seconds = 0;

    //
    // Here we say who we are...
    cout << "WavMix Version 1.1 built " << __DATE__ << "  " << __TIME__ << endl;
    cout << "Application mixes 44.1khz stereo wav files only." << endl;
    cout << endl;

    if (argc < 5)
    {
        //
        //
        cout << endl;
        cout << "     Usage:" << endl;
        cout << "     Provide two source filenames, a target file name, the number of seconds" << endl;
        cout << "     you wish to mix, optional flag to just produce a sample mix, " << endl;
        cout << "     This program REQUIRES MMPM/2 to be installed." << endl;
        cout << endl;
        cout << " This application mixes 44.1khz stereo wav files only.  It will mix two" << endl;
        cout << " source wav files and create a target wav file.  You set the amount of " << endl;
        cout << " overlap in seconds.  WavMix will mix using the seconds of overlap.  A " << endl;
        cout << " preview mode is provided.  Since wave files of this type are extremely " << endl;
        cout << " large, it will produce  a target wav file of just the overlap so you " << endl;
        cout << " may preview your mixdowns" << endl;
        cout << endl;
        cout << endl;
        cout << " Sample command line" << endl;
        cout << " [r:\\audio\\mixdown] wavmix track01.wav track02.wav output.wav 5 " << endl;
        cout << "      Above line mixes track01.wav and track02.wav using 5 seconds " << endl;
        cout << "      of overlap creating output.wav" << endl;
        cout << endl;
        cout << " [r:\\audio\\mixdown] wavmix track01.wav track02.wav output.wav 5 S" << endl;
        cout << "      Above line mixes 5 seconds of audio from the end of track01.wav and the" << endl;
        cout << "      start of track02.wav creating output.wav" << endl;
        
        cout << endl;
        cout << endl;
        cout << "     Support questions or comments to [email protected]" << endl;
            
            
        cout << "Provide filename1 filename2 destinationfile secondtomix (Longcut)" << endl;
        return 1;
    }

    //
    // set the type of mix we are going to do.  if this is true, we do a full mix, if its
    // false, we only will do a "sample" of the mix part.
   short longcut = TRUE;

   if (argc > 5)
   {
       if (strcmp(argv[5],"S")==0)
       {
           cout << "Output file will only be the overlap." << endl;
           longcut = FALSE;
       }
   }
       
   
   seconds= atoi(argv[4]);

   if (seconds == 0)
   {
       cout << " ERROR:  You cannot set seconds-to-mix to 0. " << endl;
       return 5;
   }

  
   MMAUDIOHEADER mmAudioHeader,mmAudioHeader2;
    
    //
    // open file1
   HMMIO hmmio = mmioOpen(argv[1],NULL,MMIO_READ | MMIO_ALLOCBUF);
   if (hmmio==0)
   {
       cout << "Failed to open file " << argv[1] << endl;
       return 1;
   }

   long BytesRead;
   int rc = mmioGetHeader(hmmio,(PVOID)&mmAudioHeader,sizeof(MMAUDIOHEADER),&BytesRead,NULL,NULL);
   if (rc)
   {
       cout << "Error on mmioGetHeader for file " << argv[1] <<  endl;
   }

   //
   // now open the second file

   HMMIO hmmio2 = mmioOpen(argv[2],NULL,MMIO_READ | MMIO_ALLOCBUF);
   if (hmmio2==0)
   {
       cout << "ERROR: Failed to open file " << argv[2] << endl;
       return 2;
   }
   
   rc = mmioGetHeader(hmmio2,(PVOID)&mmAudioHeader2,sizeof(MMAUDIOHEADER),&BytesRead,NULL,NULL);
   if (rc)
   {
       cout << "ERROR on mmioGetHeader 2 " << endl;
       return 3;
   }
   
   //
   // now we are going to create another wave file

   MMIOINFO mmioinfo;

   memset(&mmioinfo,'\0',sizeof(mmioinfo));

   mmioinfo.ulTranslate = MMIO_TRANSLATEHEADER+MMIO_TRANSLATEDATA;
   mmioinfo.aulInfo[3] = MMIO_MEDIATYPE_AUDIO;
   mmioinfo.fccIOProc = mmioFOURCC('W','A','V','E');
   HMMIO hmmioTo = mmioOpen(argv[3],&mmioinfo,MMIO_CREATE+MMIO_WRITE);
 
   if (!hmmioTo)
   {
       cout << "ERROR : Could not create file." << argv[3] <<  endl;
       return 1;
   }


   // here we calculate the OFFSET from the back of the file for the 5 second overlay
   long audiosize = 176400 * seconds; // seconds of audio
   long filesize1 = mmAudioHeader.mmXWAVHeader.XWAVHeaderInfo.ulAudioLengthInBytes;
   long filesize2 = mmAudioHeader2.mmXWAVHeader.XWAVHeaderInfo.ulAudioLengthInBytes;
   if (audiosize > filesize1)
   {
       cout << "ERROR, you cannot have a mix area that is larger than your source audio file. " << endl;
       return 1;
   }

   if (longcut != TRUE)
   {
       //
       // install the new file size in the buffer
       mmAudioHeader.mmXWAVHeader.XWAVHeaderInfo.ulAudioLengthInBytes = audiosize;
       cout << "Total resulting file size is: " << audiosize << endl;
   }

   if (longcut == TRUE)
   {
       //
       // install the new file size in the buffer
       mmAudioHeader.mmXWAVHeader.XWAVHeaderInfo.ulAudioLengthInBytes = filesize1 + filesize2;
       cout << "Total resulting file size is: " << (filesize1 + filesize2) << endl;
   }
  
  
   //
   // here we calculate the seekto, not necessary really with longcut
   long seekto = filesize1 - audiosize;

   cout << "Attempting to mix " << seconds << " seconds " << endl;

   //
   // first we copy the begining of file 1 to destfile
   if (longcut==TRUE)
   {
       cout << "Copying " << seekto << " bytes" << endl;
       copyaudio(hmmio,hmmioTo,seekto);
   }
   
   
   //
   // now seek to the new location in file 1
   LONG newPos = mmioSeek(hmmio,seekto,0);
   assert(newPos == seekto);

   //
   // allocate a buffer
   PSHORT pAudio = NULL;
   DosAllocMem((void **) &pAudio,audiosize,PAG_WRITE | PAG_COMMIT);

   //
   // now read the FIRST file
   BytesRead = mmioRead(hmmio,(PCHAR)pAudio,audiosize);
   assert(BytesRead == audiosize);

   //
   // now allocate the second buffer

   PSHORT pAudio2 = NULL;
   DosAllocMem((void **) &pAudio2,audiosize,PAG_WRITE | PAG_COMMIT);

   //
   // and read that in
   BytesRead = mmioRead(hmmio2,(PCHAR)pAudio2,audiosize);
   assert(BytesRead == audiosize);

   //
   // now ADD them together?
   long shortsize = audiosize/2;
   for (unsigned long index = 0; index < shortsize ; index++)
   {
       short part1 = *(pAudio+index);
       short part2 = *(pAudio2+index);
       short result = part1 + part2;
       *(pAudio+index) = result;
           //       *(pAudio+index) = *(pAudio2+index) + *(pAudio+index);
   }

 
   //
   // build the header
   rc = mmioSetHeader(hmmioTo,&mmAudioHeader,sizeof(MMAUDIOHEADER),&BytesRead,0,0);
   if (rc)
   {
       cout << "Error in mmioSetHeader" << endl;
       return 1;
   }

   //
   // write the new file
   rc = mmioWrite(hmmioTo,(PCHAR)pAudio,audiosize);
   if (rc < 0)
   {
       cout << "ERROR during a write" << endl;
   }

   //
   // now, copy the rest of file 2
   if (longcut == TRUE)
   {
       cout << "Copying " << filesize2 - audiosize << " bytes" << endl;
       copyaudio(hmmio2,hmmioTo,filesize2 - audiosize);
   }
   DosFreeMem(pAudio);
   DosFreeMem(pAudio2);
   mmioClose(hmmio,0);
   mmioClose(hmmio2,0);
   mmioClose(hmmioTo,0);

   cout << "Finished, output file created" << endl;
    
    
}