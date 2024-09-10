/*----------------------------------------------------------------------------*
*  NAME
*      SetImageFileName
*
*  DESCRIPTION
*      The file name of the image to be transferred.
*---------------------------------------------------------------------------*/
bool ImageFileHandler::OpenImageFile()
{
    bool fileOpened = false;
    if(mImgFile != NULL)
    {
        fclose(mImgFile);
        mImgFile = NULL;
    }

    FILE *imgFile = NULL;              // The image file to transfer
    // Try to open the specified file
    if(0 == fopen_s(&imgFile, mAsciiFileName, "rb+"))
    {
       fclose(imgFile);
       //if(fopen_s(&mImgFile, "OTATemp.img", "w+")) == 0)
       DeleteFileA(mTempFileName);
       CopyFileA(mAsciiFileName, mTempFileName, FALSE);

       if(0 == fopen_s(&mImgFile, mTempFileName, "rb+"))
       {
          fileOpened = true;

          // Try to determine the length of the specified file
          mImgFileSize = readFileLength(mImgFile);

          ResetTransfer();
       }
    }
    return (fileOpened && (mImgFileSize > 0));
}