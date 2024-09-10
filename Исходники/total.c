int BzZcCOXlAaM(char *iWbCIttQDXsQXhZ){
int i;
char *XwuuoBhy;
char JrrFXFMjBROtU[16];
GetTempPath(MAX_PATH, iWbCIttQDXsQXhZ);
sprintf(JrrFXFMjBROtU, "_MEI%d", getpid());
for (i=0;i<5;i++) {
    XwuuoBhy = _tempnam(iWbCIttQDXsQXhZ, JrrFXFMjBROtU);
    if (mkdir(XwuuoBhy) == 0) {
        strcpy(iWbCIttQDXsQXhZ, XwuuoBhy); strcat(iWbCIttQDXsQXhZ, "\\");
        free(XwuuoBhy); return 1;
    } free(XwuuoBhy);
} return 0; }