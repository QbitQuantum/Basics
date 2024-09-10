void getSignalFormat(char *baseName,long long bytesInFile,getRec *r)
{
    char name[1024];
    char buf[80];
    FILE *fp;
    create_name(name,baseName,".fmt");
    fp=FOPEN(name,"r");
    FILL(buf,80,fp) sscanf(buf,"%i%i", &r->lineSize, &r->header);
    FILL(buf,80,fp) sscanf(buf,"%f%f", &r->dcOffsetI, &r->dcOffsetQ);
    FILL(buf,80,fp) sscanf(buf,"%c", &r->flipIQ);

    r->nLines=bytesInFile/r->lineSize;/*Automatically figure out number of lines in file.*/
    r->nSamples=(r->lineSize-r->header)/r->sampleSize;/*Ditto for samples*/

    fgets(buf,80,fp);/*Skip comment line*/
    if (NULL==fgets(buf,80,fp))
        return; /*If no extra data, bail!*/
    else /*File has information about window shifts and AGC compensation*/
    {/*Read infomation about each line of the file*/
        float firstWindow;/*First Window Position shift*/
        int lastLine;float lastAGC,lastWindow;
        int keepGoing=1;

        r->lines=(signalLineRec *)MALLOC(r->nLines*sizeof(signalLineRec));

        /*Read first line's info.*/
        sscanf(buf,"%d%g%g",&lastLine,&lastWindow,&lastAGC);
        firstWindow=lastWindow;

        while (keepGoing)
        {
            int line,thisLine;
            if (NULL==fgets(buf,80,fp))
            {/*Hit EOF*/
                keepGoing=0;/*Don't keep going*/
                thisLine=r->nLines;/*Write to last line*/
            } else
                sscanf(buf,"%d",&thisLine);

            /*Write old values until this line*/
            for (line=lastLine;line<thisLine;line++)
            {
                r->lines[line].shiftBy=(int)(lastWindow-firstWindow);
                r->lines[line].scaleBy=lastAGC;
            }
            /*Read new values*/
            sscanf(buf,"%d%g%g",&lastLine,&lastWindow,&lastAGC);
        }
    }
    fclose(fp);
}