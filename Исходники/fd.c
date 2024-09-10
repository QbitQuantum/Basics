/* Here we undo the hackery in the setup, and close any handles we
   know fd_exec doesn't use.
   */
static void pipe_cleanup (int inpipes[], int outpipes[], HANDLE old_handles[])
{
  /* Close unnecessary fd's--the ones the child uses */
  if (close(inpipes[0]) != 0
      || close(outpipes[1]) != 0

  /* close the handles we're pretending are our stdin and stdout */
      || !CloseHandle(GetStdHandle(STD_INPUT_HANDLE))
      || !CloseHandle(GetStdHandle(STD_OUTPUT_HANDLE))

  /* now restore the real stdin and stdout */
      || !SetStdHandle(STD_INPUT_HANDLE, old_handles[0])
      || !SetStdHandle(STD_OUTPUT_HANDLE, old_handles[1])) {
    lose("Failed while doing pipe cleanup for fd_exec");
  }
}