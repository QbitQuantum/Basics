Error ChildProcess::writeToStdin(const std::string& input, bool eof)
{
   // write synchronously to the pipe
   if (!input.empty())
   {
      if (options().pseudoterminal)
      {
         Error error = WinPty::writeToPty(pImpl_->hStdInWrite, input);
         if (error)
            return error;
      }
      else
      {
         DWORD dwWritten;
         BOOL bSuccess = ::WriteFile(pImpl_->hStdInWrite,
                                     input.data(),
                                     input.length(),
                                     &dwWritten,
                                     NULL);
         if (!bSuccess)
            return systemError(::GetLastError(), ERROR_LOCATION);
      }
   }

   // close pipe if requested
   if (eof)
      return closeHandle(&pImpl_->hStdInWrite, ERROR_LOCATION);
   else
      return Success();
}