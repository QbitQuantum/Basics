TextNode::TextNode(VRMLParser& parser)
    :maxExtent(0.0f)
{
    /* Check for the opening brace: */
    if(!parser.isToken("{"))
        Misc::throwStdErr("TextNode::TextNode: Missing opening brace in node definition");
    parser.getNextToken();

    /* Process attributes until closing brace: */
    while(!parser.isToken("}"))
    {
        if(parser.isToken("string"))
        {
            /* Parse the list of strings: */
            parser.getNextToken();
            string=MFString::parse(parser);
        }
        else if(parser.isToken("fontStyle"))
        {
            /* Parse the font style node: */
            parser.getNextToken();
            fontStyle=parser.getNextNode();
        }
        else if(parser.isToken("length"))
        {
            /* Parse the list of string lengths: */
            parser.getNextToken();
            length=MFFloat::parse(parser);
        }
        else if(parser.isToken("maxExtent"))
        {
            /* Parse the maximum allowed string length: */
            parser.getNextToken();
            maxExtent=SFFloat::parse(parser);
        }
        else
            Misc::throwStdErr("TextNode::TextNode: unknown attribute \"%s\" in node definition",parser.getToken());
    }

    /* Skip the closing brace: */
    parser.getNextToken();

    /* Check if a correct font style node was supplied: */
    FontStyleNode* fs=dynamic_cast<FontStyleNode*>(fontStyle.getPointer());
    if(fs==0)
    {
        /* Create a default font style node: */
        fs=new FontStyleNode;
        fontStyle=fs;
    }

    /* Lay out the strings: */
    Box::Point bbOrigin;
    Box::Size bbSize;
    if(fs->horizontal)
    {
        /* Compute native text boxes for all strings: */
        float maxWidth=0.0f;
        for(size_t i=0; i<string.size(); ++i)
        {
            /* Get the string's box and texture coordinate box: */
            GLFont::Box sBox=fs->font->calcStringBox(string[i].c_str());

            /* Adjust the width to the given value, if there is one: */
            if(i<length.size()&&length[i]>0.0f)
                sBox.size[0]=length[i];
            stringBox.push_back(sBox);
            stringTexBox.push_back(fs->font->calcStringTexCoords(string[i].c_str()));

            /* Update the maximum string width: */
            if(maxWidth<sBox.size[0])
                maxWidth=sBox.size[0];
        }

        /* Align the strings horizontally: */
        float horizontalScale=1.0f;
        if(maxExtent>0.0f&&maxWidth>maxExtent)
        {
            horizontalScale=maxExtent/maxWidth;
            maxWidth=maxExtent;
        }
        bbSize[0]=maxWidth;
        switch(fs->justify[0])
        {
        case FontStyleNode::FIRST:
        case FontStyleNode::BEGIN:
            bbOrigin[0]=0.0f;
            break;

        case FontStyleNode::MIDDLE:
            bbOrigin[0]=-0.5*maxWidth;
            break;

        case FontStyleNode::END:
            bbOrigin[0]=-maxWidth;
            break;
        }
        for(size_t i=0; i<string.size(); ++i)
        {
            stringBox[i].size[0]*=horizontalScale;
            switch(fs->justify[0])
            {
            case FontStyleNode::FIRST:
            case FontStyleNode::BEGIN:
                stringBox[i].origin[0]=0.0f;
                break;

            case FontStyleNode::MIDDLE:
                stringBox[i].origin[0]=-0.5f*stringBox[i].size[0];
                break;

            case FontStyleNode::END:
                stringBox[i].origin[0]=-stringBox[i].size[0];
                break;
            }
        }

        /* Align the strings vertically: */
        float height=(string.size()-1)*fs->spacing+fs->font->getTextHeight();
        bbSize[1]=height;
        float sp=fs->topToBottom?-fs->spacing:fs->spacing;
        float base;
        switch(fs->justify[1])
        {
        case FontStyleNode::FIRST:
            base=0.0f;
            bbOrigin[1]=fs->topToBottom?-height+fs->font->getTextHeight():0.0f;
            break;

        case FontStyleNode::BEGIN:
            base=fs->topToBottom?-fs->font->getTextHeight():0.0f;
            bbOrigin[1]=fs->topToBottom?-height:0.0f;
            break;

        case FontStyleNode::MIDDLE:
            base=fs->topToBottom?0.5f*height-fs->font->getTextHeight():-0.5f*height;
            bbOrigin[1]=-0.5f*height;
            break;

        case FontStyleNode::END:
            base=fs->topToBottom?height-fs->font->getTextHeight():-height;
            bbOrigin[1]=fs->topToBottom?0.0f:-height;
            break;
        }
        for(size_t i=0; i<string.size(); ++i)
            stringBox[i].origin[1]=base+float(i)*sp;
    }

    /* Store the bounding box: */
    bbOrigin[2]=0.0f;
    bbSize[2]=0.0f;
    boundingBox=Box(bbOrigin,bbSize);
}