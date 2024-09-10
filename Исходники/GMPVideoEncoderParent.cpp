static void
ShutdownEncodedThread(nsCOMPtr<nsIThread>& aThread)
{
  aThread->Shutdown();
}