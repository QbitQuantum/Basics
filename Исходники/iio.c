EXPORT int Hcsr04Init(int Pin)
{
    clearLastError();
    struct HCSR04_resource res;
    int ret = HCSR04_MAX_DISTANCE+1;
    char *hcsr04Path = (char *) malloc(FILE_PATH_LENGTH);
    memset(hcsr04Path, 0, FILE_PATH_LENGTH);
    strcpy(hcsr04Path, HCSR04_PATH);

    res.gpio = pintoGPIO(Pin);
    char *resStr = (char *)&res;
    if (Hcsr04Write(hcsr04Path, resStr) == -1) {
        setLastError("Fail to write resource to hcsr04");
        ret = -1;
    }
    free(hcsr04Path);
    return ret;
}