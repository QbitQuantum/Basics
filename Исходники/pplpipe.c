PPL_DECLARE (int) ppl_pipe_close (ppl_pipe_t * apipe)
{
  if (apipe == NULL)
    return -1;
  DisconnectNamedPipe (apipe->pipes[0]);
  DisconnectNamedPipe (apipe->pipes[1]);
  CloseHandle(apipe->pipes[0]);
  CloseHandle(apipe->pipes[1]);
  osip_free (apipe);
  return 0;
}