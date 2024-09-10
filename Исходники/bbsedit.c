int update_form(char *board, char *file)
{
        FILE *fp;
        char *buf=getparm("text"), path[80];
        int i,l;//huangxu@060331
        //这里为了安全
        char * pbuf,c;
        char rbuf[512];
        if(!(brd->flag2&NOFILTER_FLAG)&&(bad_words(buf)))
	{
                printf("<script language=\"javascript\">alert('您的文章可能包含不便显示的内容，已经提交审核。请返回并进行修改。');history.go(-1);</script>");
		return 1;
	}
        sprintf(path, "boards/%s/%s", board, file);
        if (!(fp=fopen(path,"r")))
        	http_fatal("错误的文件!");
        fseek(fp,0,2);
        l=ftell(fp);
        fseek(fp,0,0);
        pbuf=rbuf;
        for (i=4;l>0&&i>0;l--)//huangxu@060331
        {
        	*(pbuf++)=c=fgetc(fp);
       		if (c==0x0a)
        		i--;
        }
        fclose(fp);
        if (l<=0)  http_fatal("错误的文件!");
        fp=fopen(path, "w");
        if(fp==0)
                http_fatal("无法存盘");
       	fwrite(rbuf,1,pbuf-rbuf,fp);
        fprintf(fp, "%s", buf);
        //huangxu@060331
				fprintf(fp,
				        "\n[1;36m※ 修改:·%s 于 %16.16s 修改本文·Web[FROM: %-.20s][m\n",
				        currentuser.userid, Ctime(time(0))+ 4, fromhost);
        //fprintf(fp, "\n※ 修改:·%s 於 %s 修改本文·%s Web[FROM: %s] ", currentuser.userid, Ctime(time(0))+4,BBSHOST, (!(currentuser.userdefine & DEF_NOTHIDEIP)&&isdormip(fromhost))?"南开宿舍内网":fromhost);
        fclose(fp);
        printf("修改文章成功.<br><a href=bbsdoc?board=%s>返回本讨论区</a>", board);
}