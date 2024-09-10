void TextWindow::ShowStyleInfo(void) {
    Printf(true, "%Fl%f%Ll(back to list of styles)%E", &ScreenShowListOfStyles);

    Style *s = Style::Get(shown.style);

    if(s->h.v < Style::FIRST_CUSTOM) {
        Printf(true, "%FtSTYLE  %E%s ", s->DescriptionString());
    } else {
        Printf(true, "%FtSTYLE  %E%s "
                     "[%Fl%Ll%D%frename%E/%Fl%Ll%D%fdel%E]",
            s->DescriptionString(),
            s->h.v, &ScreenChangeStyleName,
            s->h.v, &ScreenDeleteStyle);
    }

    Printf(true, "%Ft line stroke style%E");
    Printf(false, "%Ba   %Ftcolor %E%Bz  %Ba (%@, %@, %@) %D%f%Ls%Fl[change]%E",
        &s->color,
        s->color.redF(), s->color.greenF(), s->color.blueF(),
        s->h.v, ScreenChangeStyleColor);

    // The line width, and its units
    if(s->widthAs == Style::UNITS_AS_PIXELS) {
        Printf(false, "   %Ftwidth%E %@ %D%f%Lp%Fl[change]%E",
            s->width,
            s->h.v, &ScreenChangeStyleWidthOrTextHeight,
            (s->h.v < Style::FIRST_CUSTOM) ? 'w' : 'W');
    } else {
        Printf(false, "   %Ftwidth%E %s %D%f%Lp%Fl[change]%E",
            SS.MmToString(s->width),
            s->h.v, &ScreenChangeStyleWidthOrTextHeight,
            (s->h.v < Style::FIRST_CUSTOM) ? 'w' : 'W');
    }

    bool widthpx = (s->widthAs == Style::UNITS_AS_PIXELS);
    if(s->h.v < Style::FIRST_CUSTOM) {
        Printf(false,"%Ba   %Ftin units of %Fdpixels%E");
    } else {
        Printf(false,"%Ba   %Ftin units of  %Fd"
                            "%D%f%LW%c pixels%E  "
                            "%D%f%Lw%c %s",
            s->h.v, &ScreenChangeStyleYesNo,
            widthpx ? RADIO_TRUE : RADIO_FALSE,
            s->h.v, &ScreenChangeStyleYesNo,
            !widthpx ? RADIO_TRUE : RADIO_FALSE,
            SS.UnitName());
    }

    if(s->h.v >= Style::FIRST_CUSTOM) {
        // The fill color, and whether contours are filled

        Printf(false, "");
        Printf(false, "%Ft contour fill style%E");
        Printf(false,
            "%Ba   %Ftcolor %E%Bz  %Ba (%@, %@, %@) %D%f%Lf%Fl[change]%E",
            &s->fillColor,
            s->fillColor.redF(), s->fillColor.greenF(), s->fillColor.blueF(),
            s->h.v, ScreenChangeStyleColor);

        Printf(false, "%Bd   %D%f%Lf%c  contours are filled%E",
            s->h.v, &ScreenChangeStyleYesNo,
            s->filled ? CHECK_TRUE : CHECK_FALSE);
    }

    // The text height, and its units
    Printf(false, "");
    Printf(false, "%Ft text comment style%E");

    const char *chng = (s->h.v < Style::FIRST_CUSTOM) ? "" : "[change]";
    if(s->textHeightAs == Style::UNITS_AS_PIXELS) {
        Printf(false, "%Ba   %Ftheight %E%@ %D%f%Lt%Fl%s%E",
            s->textHeight,
            s->h.v, &ScreenChangeStyleWidthOrTextHeight,
            chng);
    } else {
        Printf(false, "%Ba   %Ftheight %E%s %D%f%Lt%Fl%s%E",
            SS.MmToString(s->textHeight),
            s->h.v, &ScreenChangeStyleWidthOrTextHeight,
            chng);
    }

    bool textHeightpx = (s->textHeightAs == Style::UNITS_AS_PIXELS);
    if(s->h.v < Style::FIRST_CUSTOM) {
        Printf(false,"%Bd   %Ftin units of %Fdpixels");
    } else {
        Printf(false,"%Bd   %Ftin units of  %Fd"
                            "%D%f%LG%c pixels%E  "
                            "%D%f%Lg%c %s",
            s->h.v, &ScreenChangeStyleYesNo,
            textHeightpx ? RADIO_TRUE : RADIO_FALSE,
            s->h.v, &ScreenChangeStyleYesNo,
            !textHeightpx ? RADIO_TRUE : RADIO_FALSE,
            SS.UnitName());
    }

    if(s->h.v >= Style::FIRST_CUSTOM) {
        Printf(false, "%Ba   %Ftangle %E%@ %D%f%Ll%Fl[change]%E",
            s->textAngle,
            s->h.v, &ScreenChangeStyleTextAngle);

        Printf(false, "");
        Printf(false, "%Ft text comment alignment%E");
        bool neither;
        neither = !(s->textOrigin & (Style::ORIGIN_LEFT | Style::ORIGIN_RIGHT));
        Printf(false, "%Ba   "
                      "%D%f%LL%c left%E    "
                      "%D%f%LH%c center%E  "
                      "%D%f%LR%c right%E  ",
            s->h.v, &ScreenChangeStyleYesNo,
            (s->textOrigin & Style::ORIGIN_LEFT) ? RADIO_TRUE : RADIO_FALSE,
            s->h.v, &ScreenChangeStyleYesNo,
            neither ? RADIO_TRUE : RADIO_FALSE,
            s->h.v, &ScreenChangeStyleYesNo,
            (s->textOrigin & Style::ORIGIN_RIGHT) ? RADIO_TRUE : RADIO_FALSE);

        neither = !(s->textOrigin & (Style::ORIGIN_BOT | Style::ORIGIN_TOP));
        Printf(false, "%Bd   "
                      "%D%f%LB%c bottom%E  "
                      "%D%f%LV%c center%E  "
                      "%D%f%LT%c top%E  ",
            s->h.v, &ScreenChangeStyleYesNo,
            (s->textOrigin & Style::ORIGIN_BOT) ? RADIO_TRUE : RADIO_FALSE,
            s->h.v, &ScreenChangeStyleYesNo,
            neither ? RADIO_TRUE : RADIO_FALSE,
            s->h.v, &ScreenChangeStyleYesNo,
            (s->textOrigin & Style::ORIGIN_TOP) ? RADIO_TRUE : RADIO_FALSE);
    }

    if(s->h.v >= Style::FIRST_CUSTOM) {
        Printf(false, "");

        Printf(false, "  %Fd%D%f%Lv%c  show these objects on screen%E",
                s->h.v, &ScreenChangeStyleYesNo,
                s->visible ? CHECK_TRUE : CHECK_FALSE);

        Printf(false, "  %Fd%D%f%Le%c  export these objects%E",
                s->h.v, &ScreenChangeStyleYesNo,
                s->exportable ? CHECK_TRUE : CHECK_FALSE);

        Printf(false, "");
        Printf(false, "To assign lines or curves to this style,");
        Printf(false, "right-click them on the drawing.");
    }
}