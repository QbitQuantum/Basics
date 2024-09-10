void FR_DrawText3(const char* text, const Point2Raw* _origin, int alignFlags, short _textFlags)
{
    fontid_t origFont = FR_Font();
    float cx, cy, extraScale;
    drawtextstate_t state;
    const char* fragment;
    int pass, curCase;
    Point2Raw origin;
    Size2Raw textSize;
    size_t charCount;
    float origColor[4];
    char* str, *end;
    boolean escaped = false;

    errorIfNotInited("FR_DrawText");

    if(!text || !text[0]) return;

    origin.x = _origin? _origin->x : 0;
    origin.y = _origin? _origin->y : 0;

    _textFlags &= ~(DTF_INTERNAL_MASK);

    // If we aren't aligning to top-left we need to know the dimensions.
    if(alignFlags & ALIGN_RIGHT)
        FR_TextSize(&textSize, text);

    DENG_ASSERT_IN_MAIN_THREAD();
    DENG_ASSERT_GL_CONTEXT_ACTIVE();

    // We need to change the current color, so remember for restore.
    glGetFloatv(GL_CURRENT_COLOR, origColor);

    for(pass = ((_textFlags & DTF_NO_SHADOW)  != 0? 1 : 0);
        pass < ((_textFlags & DTF_NO_GLITTER) != 0? 2 : 3); ++pass)
    {
        short textFlags = 0;

        // Configure the next pass.
        cx = (float) origin.x;
        cy = (float) origin.y;
        curCase = -1;
        charCount = 0;
        switch(pass)
        {
        case 0: textFlags = _textFlags | (DTF_NO_GLITTER|DTF_NO_CHARACTER); break;
        case 1: textFlags = _textFlags | (DTF_NO_SHADOW |DTF_NO_GLITTER);   break;
        case 2: textFlags = _textFlags | (DTF_NO_SHADOW |DTF_NO_CHARACTER); break;
        }

        // Apply defaults.
        initDrawTextState(&state, textFlags);

        str = (char*)text;
        while(*str)
        {
            if(*str == FR_FORMAT_ESCAPE_CHAR)
            {
                escaped = true;
                ++str;
                continue;
            }
            if(!escaped && *str == '{') // Paramaters included?
            {
                fontid_t lastFont = state.fontNum;
                int lastTracking = state.tracking;
                float lastLeading = state.leading;
                float lastShadowStrength = state.shadowStrength;
                float lastGlitterStrength = state.glitterStrength;
                boolean lastCaseScale = state.caseScale;
                float lastRGBA[4];
                int numBreaks = 0;

                lastRGBA[CR] = state.rgba[CR];
                lastRGBA[CG] = state.rgba[CG];
                lastRGBA[CB] = state.rgba[CB];
                lastRGBA[CA] = state.rgba[CA];

                parseParamaterBlock(&str, &state, &numBreaks);

                if(numBreaks != 0)
                {
                    do
                    {
                        cx = (float) origin.x;
                        cy += state.lastLineHeight * (1+lastLeading);
                    } while(--numBreaks > 0);
                }

                if(state.fontNum != lastFont)
                    FR_SetFont(state.fontNum);
                if(state.tracking != lastTracking)
                    FR_SetTracking(state.tracking);
                if(state.leading != lastLeading)
                    FR_SetLeading(state.leading);
                if(state.rgba[CR] != lastRGBA[CR] || state.rgba[CG] != lastRGBA[CG] || state.rgba[CB] != lastRGBA[CB] || state.rgba[CA] != lastRGBA[CA])
                    FR_SetColorAndAlphav(state.rgba);
                if(state.shadowStrength != lastShadowStrength)
                    FR_SetShadowStrength(state.shadowStrength);
                if(state.glitterStrength != lastGlitterStrength)
                    FR_SetGlitterStrength(state.glitterStrength);
                if(state.caseScale != lastCaseScale)
                    FR_SetCaseScale(state.caseScale);
            }

            for(end = str; *end && *end != FR_FORMAT_ESCAPE_CHAR && (escaped || *end != '{');)
            {
                int newlines = 0, fragmentAlignFlags;
                float alignx = 0;

                // Find the end of the next fragment.
                if(FR_CaseScale())
                {
                    curCase = -1;
                    // Select a substring with characters of the same case (or whitespace).
                    for(; *end && *end != FR_FORMAT_ESCAPE_CHAR && (escaped || *end != '{') &&
                        *end != '\n'; end++)
                    {
                        escaped = false;

                        // We can skip whitespace.
                        if(isspace(*end))
                            continue;

                        if(curCase < 0)
                            curCase = (isupper(*end) != 0);
                        else if(curCase != (isupper(*end) != 0))
                            break;
                    }
                }
                else
                {
                    curCase = 0;
                    for(; *end && *end != FR_FORMAT_ESCAPE_CHAR && (escaped || *end != '{') &&
                        *end != '\n'; end++) { escaped = false; }
                }

                // No longer escaped.
                escaped = false;

                { char* buffer = enlargeTextBuffer(end - str);
                memcpy(buffer, str, end - str);
                buffer[end - str] = '\0';
                fragment = buffer;
                }

                while(*end == '\n')
                {
                    newlines++;
                    end++;
                }

                // Continue from here.
                str = end;

                if(!(alignFlags & (ALIGN_LEFT|ALIGN_RIGHT)))
                {
                    fragmentAlignFlags = alignFlags;
                }
                else
                {
                    // We'll take care of horizontal positioning of the fragment so align left.
                    fragmentAlignFlags = (alignFlags & ~(ALIGN_RIGHT)) | ALIGN_LEFT;
                    if(alignFlags & ALIGN_RIGHT)
                        alignx = -textSize.width * state.scaleX;
                }

                // Setup the scaling.
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();

                // Rotate.
                if(state.angle != 0)
                {
                    // The origin is the specified (x,y) for the patch.
                    // We'll undo the aspect ratio (otherwise the result would be skewed).
                    /// @todo Do not assume the aspect ratio and therefore whether
                    // correction is even needed.
                    glTranslatef((float)origin.x, (float)origin.y, 0);
                    glScalef(1, 200.0f / 240.0f, 1);
                    glRotatef(state.angle, 0, 0, 1);
                    glScalef(1, 240.0f / 200.0f, 1);
                    glTranslatef(-(float)origin.x, -(float)origin.y, 0);
                }

                glTranslatef(cx + state.offX + alignx, cy + state.offY + (FR_CaseScale() ? state.caseMod[curCase].offset : 0), 0);
                extraScale = (FR_CaseScale() ? state.caseMod[curCase].scale : 1);
                glScalef(state.scaleX, state.scaleY * extraScale, 1);

                // Draw it.
                if(fr.fontNum)
                {
                    textFragmentDrawer(fragment, 0, 0, fragmentAlignFlags, textFlags, state.typeIn ? (int) charCount : DEFAULT_INITIALCOUNT);
                }
                charCount += strlen(fragment);

                // Advance the current position?
                if(newlines == 0)
                {
                    cx += ((float) textFragmentWidth(fragment) + currentAttribs()->tracking) * state.scaleX;
                }
                else
                {
                    if(strlen(fragment) > 0)
                        state.lastLineHeight = textFragmentHeight(fragment);

                    cx = (float) origin.x;
                    cy += newlines * (float) state.lastLineHeight * (1+FR_Leading());
                }

                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
            }
        }

        FR_PopAttrib();
    }

    freeTextBuffer();

    FR_SetFont(origFont);
    glColor4fv(origColor);
}