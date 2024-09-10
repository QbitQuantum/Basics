HippoHTTP::HippoHTTP(void)
{
    inetHandle_ = InternetOpen(L"Mugshot Client/1.0", INTERNET_OPEN_TYPE_PRECONFIG,
                               NULL, NULL, INTERNET_FLAG_ASYNC);
    InternetSetStatusCallback(inetHandle_, asyncStatusUpdate);
}