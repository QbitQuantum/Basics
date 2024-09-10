/***********************************************************************
 *           call_hook_16
 */
static LRESULT call_hook_16( INT id, INT code, WPARAM wp, LPARAM lp )
{
    struct hook16_queue_info *info = get_user_thread_info()->hook16_info;
    WORD args[4];
    DWORD ret;
    INT prev_id = info->id;
    info->id = id;

    args[3] = code;
    args[2] = wp;
    args[1] = HIWORD(lp);
    args[0] = LOWORD(lp);
    WOWCallback16Ex( (DWORD)info->proc[id - WH_MINHOOK], WCB16_PASCAL, sizeof(args), args, &ret );

    info->id = prev_id;

    /* Grrr. While the hook procedure is supposed to have an LRESULT return
       value even in Win16, it seems that for those hook types where the
       return value is interpreted as BOOL, Windows doesn't actually check
       the HIWORD ...  Some buggy Win16 programs, notably WINFILE, rely on
       that, because they neglect to clear DX ... */
    if (id != WH_JOURNALPLAYBACK) ret = LOWORD( ret );
    return ret;
}