void sparabrev(void) {
        BPTR fh,lock=NULL;
        struct EditLine *elpek;
        char bugbuf[100],orgfilename[50],*motstr;
        int till,nr,mot;
        Servermem->inne[nodnr].skrivit++;
        Servermem->info.skrivna++;
        Statstr.write++;
        till=atoi(brevspar.to);
        if((nr=updatenextletter(till))==-1) {
                freeeditlist();
                return;
        }
        sprintf(orgfilename,"NiKom:Users/%d/%d/%d.letter",till/100,till,nr);
        if(!(fh=Open(orgfilename,MODE_NEWFILE))) {
                puttekn("\n\n\rKunde inte öppna brevet\n\r",-1);
                freeeditlist();
                return;
        }
        strcpy(bugbuf,"System-ID: NiKom\n");
        FPuts(fh,bugbuf);
        sprintf(bugbuf,"From: %d\n",inloggad);
        FPuts(fh,bugbuf);
        sprintf(bugbuf,"To: %s\n",brevspar.to);
        FPuts(fh,bugbuf);
        if(brevspar.reply[0]) {
                sprintf(bugbuf,"Reply: %s\n",brevspar.reply);
                FPuts(fh,bugbuf);
        }
        sprintf(bugbuf,"Date: %s\n",brevspar.date);
        FPuts(fh,bugbuf);
        sprintf(bugbuf,"Subject: %s\n",brevspar.subject);
        FPuts(fh,bugbuf);
        for(elpek=(struct EditLine *)edit_list.mlh_Head;elpek->line_node.mln_Succ;elpek=(struct EditLine *)elpek->line_node.mln_Succ) {
                if(FPuts(fh,elpek->text)==-1) {
                        puttekn("\n\n\rFel vid skrivandet av brevet\n\r",-1);
                        break;
                }
                FPutC(fh,'\n');
        }
        Close(fh);
        freeeditlist();
        sprintf(outbuffer,"\r\nBrevet fick nummer %d hos %s\r\n",nr,getusername(till));
        puttekn(outbuffer,-1);
        if(Servermem->cfg.logmask & LOG_BREV) {
                strcpy(bugbuf,getusername(inloggad));
                sprintf(outbuffer,"%s skickar brev %d till %s",bugbuf,nr,getusername(till));
                logevent(outbuffer);
        }
        motstr=hittaefter(brevspar.to);
        if(motstr[0]) {
                if(!(lock=Lock(orgfilename,ACCESS_READ))) {
                        puttekn("\n\n\rKunde inte få ett lock för brevet\n\r",-1);
                        return;
                }
        }
        while(motstr[0]) {
                mot=atoi(motstr);
                if((nr=updatenextletter(mot))==-1) {
                        UnLock(lock);
                        return;
                }
                sprintf(bugbuf,"NiKom:Users/%d/%d/%d.letter",mot/100,mot,nr);
                if(!MakeLink(bugbuf,lock,FALSE)) {
                        puttekn("\n\n\rKunde inte skapa länk till brevet\n\r",-1);
                        UnLock(lock);
                        return;
                }
                sprintf(outbuffer,"\r\nBrevet fick nummer %d hos %s\r\n",nr,getusername(mot));
                puttekn(outbuffer,-1);
                if(Servermem->cfg.logmask & LOG_BREV) {
                        strcpy(bugbuf,getusername(inloggad));
                        sprintf(outbuffer,"%s skickar brev %d till %s",bugbuf,nr,getusername(mot));
                        logevent(outbuffer);
                }
                motstr=hittaefter(motstr);
        }
        if(lock) UnLock(lock);
}