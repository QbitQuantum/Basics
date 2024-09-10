void DoOpenUrl(LPSTR tokenResp, LPSTR url)
{
    LPSTR encodedUrl = url_encode(url);
    __try {
        LPSTR encodedToken = url_encode(tokenResp);
        __try {
            LPSTR composedUrl = (LPSTR)malloc(lstrlenA(TOKEN_AUTH_URL) + 1 + lstrlenA(encodedToken) + lstrlenA(encodedUrl));
            __try {
                sprintf(composedUrl, TOKEN_AUTH_URL, encodedToken, encodedUrl);
                ShellExecuteA(0, NULL, composedUrl, NULL, NULL, SW_SHOW);
            }
            __finally {
                free(composedUrl);
            }
        }
        __finally {
            free(encodedToken);
        }
    }
    __finally {
        free(encodedUrl);
    }
}