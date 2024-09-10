fz_error*
setPageInfo(
    soPdfFile*  inFile,
    soPdfFile*  outFile)
{
    fz_error    *error = NULL;
    fz_obj      *outObj;
    char        creator[] = "soPdf ver " SO_PDF_VER;
    char        szTime[128] = "";
	struct tm   tmTemp;
    __time32_t  time;

    _time32(&time);
    _localtime32_s(&tmTemp, &time);
    strftime(szTime, sizeof(szTime), "%Y/%m/%d %H:%M", &tmTemp);

    PUT_INFO("Title", outFile->title);
    PUT_INFO("Author", outFile->author);
    PUT_INFO("Category", outFile->category);
    PUT_INFO("Publisher", outFile->publisher);
    PUT_INFO("Subject", outFile->subject);
    PUT_INFO("Creator", creator);
    PUT_INFO("Producer", creator);
    PUT_INFO("CreationDate", szTime);
    PUT_INFO("ModDate", szTime);

    return error;
}