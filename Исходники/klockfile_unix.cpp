KLockFile::LockResult KLockFile::lock(LockFlags options)
{
  if (d->isLocked)
     return KLockFile::LockOK;

  KLockFile::LockResult result;
  int hardErrors = 5;
  int n = 5;
  while(true)
  {
     KDE_struct_stat st_buf;
     result = lockFile(d->file, st_buf, d->linkCountSupport, d->componentData);
     if (result == KLockFile::LockOK)
     {
        d->staleTimer = QTime();
        break;
     }
     else if (result == KLockFile::LockError)
     {
        d->staleTimer = QTime();
        if (--hardErrors == 0)
        {
           break;
        }
     }
     else // KLockFile::Fail -- there is already such a file present (e.g. left by a crashed app)
     {
        if (!d->staleTimer.isNull() && d->statBuf != st_buf)
           d->staleTimer = QTime();

        if (d->staleTimer.isNull())
        {
           memcpy(&(d->statBuf), &st_buf, sizeof(KDE_struct_stat));
           d->staleTimer.start();

           d->pid = -1;
           d->hostname.clear();
           d->instance.clear();

           QFile file(d->file);
           if (file.open(QIODevice::ReadOnly))
           {
              QTextStream ts(&file);
              if (!ts.atEnd())
                 d->pid = ts.readLine().toInt();
              if (!ts.atEnd())
                 d->instance = ts.readLine();
              if (!ts.atEnd())
                 d->hostname = ts.readLine();
           }
        }

        bool isStale = false;
        if ((d->pid > 0) && !d->hostname.isEmpty())
        {
           // Check if hostname is us
           char hostname[256];
           hostname[0] = 0;
           gethostname(hostname, 255);
           hostname[255] = 0;

           if (d->hostname == QLatin1String(hostname))
           {
              // Check if pid still exists
              int res = ::kill(d->pid, 0);
              if ((res == -1) && (errno == ESRCH))
                 isStale = true;
           }
        }
        if (d->staleTimer.elapsed() > (d->staleTime*1000))
           isStale = true;

        if (isStale)
        {
           if ((options & ForceFlag) == 0)
              return KLockFile::LockStale;

           result = deleteStaleLock(d->file, d->statBuf, d->linkCountSupport, d->componentData);

           if (result == KLockFile::LockOK)
           {
              // Lock deletion successful
              d->staleTimer = QTime();
              continue; // Now try to get the new lock
           }
           else if (result != KLockFile::LockFail)
           {
              return result;
           }
        }
     }

     if (options & NoBlockFlag)
        break;

     struct timeval tv;
     tv.tv_sec = 0;
     tv.tv_usec = n*((KRandom::random() % 200)+100);
     if (n < 2000)
        n = n * 2;

     select(0, 0, 0, 0, &tv);
  }
  if (result == LockOK)
     d->isLocked = true;
  return result;
}