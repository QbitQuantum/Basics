struct tm *getlt(void)
{
    time_t date;
    time (&date);
    return localtime(&date);
}