bool QPEvents::handleEvent(const EventAction& ev)
{
  if (ev.type == EventAction::Internal)
  {
    if (ev.action == "email")
    {
       QString receiver = ev.arguments[0];
       TeamMember member;
       if (receiver == "teamleader")
         member = Project::ref()->teamLeader();
       else if (receiver.startsWith("subprojectleader-"))
       {
         QString s = receiver.remove("subprojectleader-");
         member = Project::ref()->subprojectLeader(s);
         SubProject subProject;
         QValueList<SubProject> *subprojects = Project::ref()->subprojects();
         for (uint i = 0 ; i < subprojects->count(); i++)
         {
           if ((*subprojects)[i].name == s)
           {
              subProject = (*subprojects)[i];
              break;
           }
         }
         if (!subProject.location.isEmpty() && !ev.arguments[2].startsWith(subProject.location))
         {
            kdDebug(24000) << ev.arguments[2] << " is not part of the " << subProject.name << "subproject \"" << subProject.location << "\". " << endl;
            return true;
         }
       }
       else if (receiver.startsWith("taskleader-"))
         member = Project::ref()->taskLeader(receiver.remove("taskleader-"));

       QString body;
       for (uint i = 2; i < ev.arguments.count(); i++)
          body += ev.arguments[i] + "\n";
       kapp->invokeMailer(member.name + "<" + member.email + ">", "", "", ev.arguments[1], body, "", QStringList(), "");

       return true;
    }
    if (ev.action == "log")
    {
      QString logFile = ev.arguments[0];
      KURL url = KURL::fromPathOrURL(logFile);
      if (url.isValid() && !url.isLocalFile())
      {
        KMessageBox::sorry(0L, i18n("Logging to remote files is not supported."));
        return false;
      }
      if (!logFile.startsWith("/"))
      {
        url = Project::ref()->projectBaseURL();
        url.addPath(logFile);
        if (!url.isLocalFile())
        {
          KMessageBox::sorry(0L, i18n("Logging to files inside a remote project is not supported."));
          return false;
        }
      }
      QFile file(url.path());
      bool result;
      if (ev.arguments[2] == "create_new")
        result = file.open(IO_WriteOnly);
      else
        result = file.open(IO_WriteOnly | IO_Append);
      if (result)
      {
        QTextStream stream(&file);
        stream.setEncoding(QTextStream::UnicodeUTF8);
        //Note: the log text should not be translated.
        QString s = QDateTime::currentDateTime().toString(Qt::ISODate) + ": ";
        s.append( "Event : " + m_eventName + " : ");
        s.append( "Action: " + ev.action + " : ");
        if (ev.arguments[1] == "full")
        {
          s.append( "Arguments: ");
          for (uint i = 1; i < ev.arguments.count(); i++)
            s.append(ev.arguments[i] + " | ");
        }
        s[s.length() - 1] = '\n';
        stream << s;
        file.close();
      }
      if (!result)
      {
        KMessageBox::sorry(0L, i18n("<qt>Logging failed. Check that you have write access to <i>%1</i>.").arg(url.path()));
        return false;
      }
    } else
      KMessageBox::sorry(0L, i18n("<qt>Unsupported internal event action : <b>%1</b>.</qt>").arg(ev.action));
  } else
  if (ev.type == EventAction::External)
  {
      //KMessageBox::sorry(0L, i18n("External event actions are not yet supported."));
      if (ev.action == "script" || ev.action =="action")
      {
          QString name = ev.arguments[0];
          KAction *action = quantaApp->actionCollection()->action(name);
          TagAction *tagAction = dynamic_cast<TagAction*>(action);
          if (tagAction)
          {
            bool blocking = (ev.arguments[1] == "yes");
            EventAction event = ev;
            event.arguments.remove(event.arguments.at(1));
            tagAction->addArguments(event.arguments);
            tagAction->execute(blocking);
          }
          else
          if (action)
          {
            action->activate();
          } else
            KMessageBox::sorry(0L, i18n("<qt>The <b>%1</b> script action was not found on your system.</qt>").arg(name), i18n("Action Execution Error"));
      }  else
      KMessageBox::sorry(0L, i18n("Unsupported external event action."));
  } else
      KMessageBox::sorry(0L, i18n("Unknown event type."));
  return false;
}