HANDLE DoLocalHandle(WORD wHeapDS, WORD wMem)
{
    HANDLE hMem ;

_asm {
     push DS
     mov  AX, wHeapDS
     mov  DS, AX
     }

	hMem = LocalHandle(wMem);

_asm {
     pop DS
     }

    return hMem ;
}