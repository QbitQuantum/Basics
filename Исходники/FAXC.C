/*-- return:
  1=time out, 0=ok
--------------*/
static int SendCmdChar(unsigned char ch)
{
    int n;

    if(fUseFlow==0)
    {
lbl_send:
        n=0x1ff;
        do {
            if( (inp(PortBase_5)&0x20) !=0 )
            {
                _disable();
                outp(PortBase,ch);
                _enable();
                return 0;
            }
            n--;
        } while(n);
        return 2;        /*- time out -*/
    }

    if(flowCtrl==XOFF)
        return 1;

    if( (inp(PortBase_6)&0x10) !=0 )
        goto lbl_send;

    return 1;
}