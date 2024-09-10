static void Audio_close(Audio *audio, const char *alias)
{
   sprintf(audio->buf, "close _%s wait", alias);
   mciSendStringA(audio->buf, NULL, 0, NULL);
}