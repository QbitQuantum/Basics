bool textSource::segment(int level
                        ,int sstatus
                        ,bool PrevIsField  // True if previous sibling block contains a \field
                        ,charprops CharProps
                        )
    {

    wint_t ch;
    curr_pos = Ftell(sourceFile);// After parsing a html-tag, seeking to curr_pos brings you back to the position where the parsed sequence started.                   

    if(Option.keepEOLsequence)
        {
        copyEOLsequence();
        // SourceFile is rewinded
        }

    do
        {
        ch = Getc(sourceFile);
        end_offset = Ftell(sourceFile);
        if(curr_pos >= tagendpos)
            {
            // We are not inside an HTML-tag.
            if(flgs.inhtmltag)
                {
                flgs.firstafterhtmltag = true;
                flgs.inhtmltag = false;
                }
            // Check whether a well-formed HTML tag is ahead. Returns sourceFile
            // in same file position.
            flgs.htmltagcoming = isHTMLtagComing(ch);
//            assert(new_pos == Ftell(sourceFile));
            assert(end_offset == Ftell(sourceFile));
            }
        else if(flgs.htmltagcoming)
            {
            // We are leaving an HTML-tag and entering a new one.
            flgs.inhtmltag = true;
            flgs.htmltagcoming = false;
            }
        /* Scan in advance, checking whether the line to come is a heading and 
        therefore must be preceded with a newline (WritePar will then be set to 
        true.)
        */

        if(  ch ==  '\n'
          || ch == '\r'
          || ch == WEOF
          || ch == 26
          )
            {
            flgs.in_fileName = false;
            heading = isHeading(firsttext,ch,WriteParAfterHeadingOrField);
            if(!skipSegmentation(firsttext,ch))
                {
                doTheSegmentation(CharProps,true,false); // Bart 20040120. true because: Suppose that end of line is end of segment
                if(!WriteParAfterHeadingOrField && heading)
                    {// A normal line after a heading has WritePar==false and heading==true
                    WriteParAfterHeadingOrField = true;
                    heading = false;
                    }
                }
            if(firsttext.EOL)
                firsttext.b.LS = 1;
            }
        else
            {
            updateFlags(ch,flgs);
            int EOL = firsttext.EOL;
            bool sentenceEnd = checkSentenceStartDueToBullet(ch);
            if(  sentenceEnd 
              || flgs.htmltagcoming
              || flgs.inhtmltag
              || (end_offset - begin_offset > MAXSEGMENTLENGTH && isSpace(ch)) // check for buffer overflow
              )
                {
                doTheSegmentation(CharProps,false,false); 
                firsttext.b.SD = 1;
                firsttext.b.LS = 0;
                }
            if(isSpace(ch))
                {
                if(EOL)
                    firsttext.b.LS = 1;
                }
            else
                {
                firsttext.b.LS = 0;
                firsttext.EOL = 0; // resets SD, CR and LF
                }
            }
        curr_pos = end_offset;
        }
    while(ch != WEOF && ch != 26);
    outputtext->PutHandlingLine('\n',flgs); // 20100106 Flush last line
    return false;
    }