 void EvalTCPSend(qCtx *ctx, qStr *out, qArgAry *args)
 {
     CStr str = (*args)[0];
     int len = sock.Write(str, str.Length());
     if (len < 0 ) {
         if (len == Sock::ERR_TIMEOUT) {
             ctx->ThrowF(out, 702, "Timeout while waiting to write data from host %sock:%d, %y", sock.GetHost(), sock.GetPort());
         } else {
             ctx->ThrowF(out, 702, "Error while writing data from host %sock:%d, %y", sock.GetHost(), sock.GetPort(), GetLastError());
         }
     }
 }