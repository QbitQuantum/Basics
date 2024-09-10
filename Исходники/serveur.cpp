QString Serveur::parseCommande(QString comm,bool serveur)
{
    if(comm.startsWith("/"))
    {
        comm.remove(0,1);
        QString pref=comm.split(" ").first();
        QStringList args=comm.split(" ");
        args.removeFirst();
        QString destChan=tab->tabText(tab->currentIndex());
        QString msg=args.join(" ");

        if(pref=="me")
            return "PRIVMSG "+destChan+" ACTION " + msg + "";
        else if(pref=="join")
        {
            join(msg);
            return " ";
        }
        else if(pref=="quit")
        {
            if(msg == "")
                return "QUIT "+msgQuit;
            else
                return "QUIT "+msg;
        }
        else if(pref=="part")
        {
            tab->removeTab(tab->currentIndex());

            if(msg == "")
            {
                if(msg.startsWith("#"))
                    destChan=msg.split(" ").first();

                if(msgQuit=="")
                    return "PART "+destChan+" using IrcLightClient";
                else
                    return "PART "+destChan+" "+msgQuit;
            }
            else
                return "PART "+destChan+" "+msg;

            conversations.remove(destChan);
        }
        else if(pref=="kick")
        {
            QStringList tableau=msg.split(" ");
            QString c1,c2,c3;
            if(tableau.count() > 0) c1=" "+tableau.first();
            else c1="";
            if(tableau.count() > 1) c2=" "+tableau.at(1);
            else c2="";
            if(tableau.count() > 2) c3=" "+tableau.at(2);
            else c3="";

            if(c1.startsWith("#"))
                return "KICK"+c1+c2+c3;
            else
                return "KICK "+destChan+c1+c2;
        }
        else if(pref=="update")
        {
            updateUsers=true;
            return "WHO "+destChan;
        }
        else if(pref=="ns")
        {
            return "NICKSERV "+msg;
        }
        else if(pref=="nick")
        {
            emit pseudoChanged(msg);
                        ecrire("-> Nickname changed to "+msg);
            return "NICK "+msg;
        }
        else
            return pref+" "+msg;
    }
    else if(!serveur)
	{
        QString destChan=tab->tabText(tab->currentIndex());
                if(comm.endsWith("<br />"))
                    comm=comm.remove(QRegExp("<br />$"));
                ecrire("<b>&lt;"+pseudo+"&gt;</b> "+comm,destChan);

        if(comm.startsWith(":"))
            comm.insert(0,":");

        return "PRIVMSG "+destChan+" "+comm.replace(" ",".")+"";
    }
	else
	{
		return "";
	}
}