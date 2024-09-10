int shell_to_DOS(void)
{
      char *comspec, prompt[256], *oldprompt;
      int retval;

      comspec = getenv("COMSPEC");
      if(comspec == NULL)
            comspec = "COMMAND.COM";     /* Better than nothing... */

      sprintf(prompt, "PROMPT=[Type EXIT to return to program]\r\n%s",
            oldprompt = getenv("PROMPT"));
      putenv(prompt); 

      retval = spawnlp(0, comspec, comspec, NULL);

      sprintf(prompt, "PROMPT=%s", oldprompt);
      putenv(prompt);

      return retval;
}