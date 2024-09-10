static bRC newPlugin(bpContext *ctx)
{
   exchange_fd_context_t *context;
   bRC retval = bRC_OK;
   DWORD size;

   int JobId = 0;
   ctx->pContext = new exchange_fd_context_t;
   context = (exchange_fd_context_t *)ctx->pContext;
   context->bpContext = ctx;
   context->job_since = 0;
   context->notrunconfull_option = false;
   bfuncs->getBaculaValue(ctx, bVarJobId, (void *)&JobId);
   _DebugMessage(0, "newPlugin JobId=%d\n", JobId);
   bfuncs->registerBaculaEvents(ctx, 1, 2, 0);
   size = MAX_COMPUTERNAME_LENGTH + 1;
   context->computer_name = new WCHAR[size];
   /*
   GetComputerNameW(context->computer_name, &size);
   */
   GetComputerNameExW(ComputerNameNetBIOS, context->computer_name, &size);
   context->current_node = NULL;
   context->root_node = NULL;
   return retval;
}