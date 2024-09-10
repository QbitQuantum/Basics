FREObject delCapture(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
{
    int32_t _id;
    FREGetObjectAsInt32(argv[0], &_id);


    if(_id < 0 || _id >= MAX_ACTIVE_CAMS)
    {
        return NULL;
    }

    CCapture* cap;
    cap = active_cams[_id];

    if(cap)
    {
        releaseCapture(cap);

        active_cams[_id] = 0;
        active_cams_count--;
    }

    return NULL;
}