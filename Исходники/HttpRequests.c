int main(void) {
    LPDWORD connectionDescription;

    if(InternetGetConnectedState(connectionDescription,0) == 1)
    {
        DWORD dwAccessType = INTERNET_OPEN_TYPE_DIRECT;

        HINTERNET hINet = InternetOpenA("User-Agent: Internet Explorer 8/Josh", 
                dwAccessType, NULL,NULL,0);

        if(hINet)
        {
            
             int i = 0;

            while(InternetOpenUrlA(hINet, "http://urinfected.local", NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0) == 0 && i < 10)
			{
				puts("Failed to connect....");
				i++;
			}

        }else {
            puts("No joy!");
        }


    } else {
        puts("You gotz no internetz!!!");
    }

    return 0;
}