  void LocalProcess::kill(QProcess &t_process, bool t_force)
  {
    if (t_process.state() == QProcess::Running)
    {
#ifdef Q_WS_WIN
      PROCESS_INFORMATION *pinfo = (PROCESS_INFORMATION*)t_process.pid();
      if (pinfo)
      {
        QString abort_cmd;
        LOG(Info, "Killing process tree using taskkill " << pinfo->dwProcessId << " force " << t_force);
        if (t_force)
        {
          abort_cmd = QString("taskkill /PID %1 /T /F").arg(pinfo->dwProcessId);
        } else {
          abort_cmd = QString("taskkill /PID %1 /T").arg(pinfo->dwProcessId);
        }
        QProcess::execute(abort_cmd);
      } 
#else
      pid_t pid(t_process.pid());

      if (pid > 0)
      {
        openstudio::path killtree = openstudio::getSharedResourcesPath()/openstudio::toPath("runmanager")/openstudio::toPath("killtree.sh");
        LOG(Info, "Killing process tree using killtree" << openstudio::toString(killtree) << " for pid " << pid << " force " << t_force);

        QStringList qsl;
        qsl.push_back(QString::number(pid));
        if (t_force)
        {
          qsl.push_back(QString::number(SIGKILL));
        } else {
          qsl.push_back(QString::number(SIGTERM));
        }
        QProcess::execute(openstudio::toQString(killtree), qsl);
      }
#endif
    }

    if (t_force)
    {
      t_process.kill();
    } else {
      t_process.terminate();
    }

  }