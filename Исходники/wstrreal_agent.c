static TACommandVerdict wcstof_cmd(TAThread thread,TAInputStream stream)
{
    int showData = 1;

    wchar_t* st, *endptr;

    size_t size;

    float res;



    size = readInt(&stream);

    st = (wchar_t*)ta_alloc_memory(size * sizeof(wchar_t) + 1);



    readWCharArray(&stream, st, &size);



    st[size] = '\0';


    if ( showData ) { ta_debug_printf( "wcstof_cmd : st is [%ls]\n", st ); }

    START_TARGET_OPERATION(thread);



    errno = 0;

    res = wcstof(st, &endptr);



    END_TARGET_OPERATION(thread);

    if ( showData ) {
        ta_debug_printf( "wcstof_cmd : res    is [%g]\n" , res    );
        ta_debug_printf( "wcstof_cmd : endptr is [%ls]\n", endptr );
        ta_debug_printf( "wcstof_cmd : errno  is [%i]\n" , errno  );
    }


    writeFloat(thread, res);

    writeInt(thread, (int)( endptr - st));

    writeInt(thread, errno);



    ta_dealloc_memory(st);



    sendResponse(thread);



    return taDefaultVerdict;
}