Res MutatorContextInitThread(MutatorContext context, HANDLE thread)
{
  BOOL success;

  AVER(context != NULL);

  context->var = MutatorContextTHREAD;
  /* This dumps the relevant registers into the context */
  /* .context.flags */
  context->the.context.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;
  success = GetThreadContext(thread, &context->the.context);
  if (!success)
    return ResFAIL;
  context->sig = MutatorContextSig;

  AVERT(MutatorContext, context);
  return ResOK;
}