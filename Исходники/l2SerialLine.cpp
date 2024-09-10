   bool CSerialLine::SetMultiplierTimeOuts( unsigned int aReadTimeOut, unsigned int aWriteTimeOut )const
   {
      TRACE_FUN( Routine, "CSerialLine::SetMultiplyTimeOuts" );

      bool ret( false );

      if( isOpen() )
      {
         #ifdef __WIN32__
            COMMTIMEOUTS commTimeOuts;

            if( GetCommTimeouts( _hFile, &commTimeOuts ) )
            {
               TraceRoutine << "commTimeOuts.ReadTotalTimeoutMultiplier: " << commTimeOuts.ReadTotalTimeoutMultiplier << std::endl;
               TraceRoutine << "commTimeOuts.WriteTotalTimeoutMultiplier: " << commTimeOuts.WriteTotalTimeoutMultiplier << std::endl;

               commTimeOuts.ReadTotalTimeoutMultiplier = aReadTimeOut;
               commTimeOuts.WriteTotalTimeoutMultiplier = aWriteTimeOut;

               ret = SetCommTimeouts( _hFile, &commTimeOuts );
            }
         #endif
      }
      return ret;
   }