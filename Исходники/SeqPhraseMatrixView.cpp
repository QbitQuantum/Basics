void SeqPhraseMatrixView::DrawTopLevelPhrase(	BRect clip,
        BView* view,
        const AmTrack* track,
        const AmPhraseEvent* event,
        AmTime end,
        AmPhraseEvent* topPhrase,
        AmPhraseRendererI* renderer)
{
    ArpASSERT(event && topPhrase);
    if (!event || !event->Phrase() ) return;
    const AmPhrase*		phrase = event->Phrase();
    BRect				entireF(0, clip.top + 3, 0, clip.bottom - 3);
    AmTime				phraseEnd = event->EndTime();
    BString				n = event->Phrase()->Name();
    float				labelH = mCurLabelH + 3;
    bool				drawLabel = mCurLabelH > 0 && labelH < entireF.Height() && n.Length() > 0;

    entireF.left = mMtc.TickToPixel(event->StartTime()) - 2;
    entireF.right = mMtc.TickToPixel(phraseEnd) + 2;
    BRect				labelF = arp_invalid_rect();
    BRect				contentF = arp_invalid_rect();
    if (drawLabel) {
        if (entireF.Height() - 4 > labelH + 4) {
            labelF.Set(entireF.left + 2, entireF.top + 2, entireF.right - 2, entireF.bottom - 2);
            contentF = labelF;
            labelF.bottom = labelF.top + labelH - 1;
            contentF.top = labelF.bottom + 1;
        } else labelF.Set(entireF.left + 2, entireF.top + 2, entireF.right - 2, entireF.bottom - 2);
    } else contentF.Set(entireF.left + 2, entireF.top + 2, entireF.right - 2, entireF.bottom - 2);

    rgb_color			bgC = phrase->Color(phrase->BACKGROUND_C);
    rgb_color			fgC = phrase->Color(phrase->FOREGROUND_C);
    if (mDrawMuted) {
        bgC = shade_color(bgC, MUTE_SHADE);
        fgC = shade_color(fgC, MUTE_SHADE);
    }
    if (arp_is_valid_rect(contentF) ) {
        /* Fill the background.
         */
        if (!mDrawMuted) {
            view->SetHighColor(bgC);
            view->FillRect(contentF);
        }
        /* Draw the measure markers.
         */
        AmTrackMeasureBackground		bg(mSongRef, AmTrackRef(track), mMtc);
        if (mDrawMuted) bg.SetFlag(bg.DRAW_BEATS_FLAG, false);
        else {
            rgb_color	c = weighted_shade(bgC, Prefs().Color(AM_MEASURE_FG_C), 5);
            bg.SetBeatColor(c);
        }
        bg.LockedDraw(view, contentF, track->Signatures() );
    }

    mLines.BeginLineArray();
    if (arp_is_valid_rect(labelF) ) {
        rgb_color	c = weighted_shade(bgC, fgC, 3);
        view->SetHighColor(c);
        view->SetLowColor(c);
        view->FillRect(labelF);
        draw_label_border(view, labelF, c, mLines, mDrawMuted, !arp_is_valid_rect(contentF));
        view->SetHighColor(Prefs().Color(AM_MEASURE_FG_C) );
        BPoint		pt(labelF.left + 2, labelF.bottom - 2);
        if (arp_is_valid_rect(contentF) ) pt.y -= 2;
        view->TruncateString(&n, B_TRUNCATE_END, labelF.Width() );
        view->DrawString(n.String(), pt);
    }

    /* Shade the background.
     */
    rgb_color		c;
    c.red = c.green = c.blue = 0;
    if (mDrawMuted) c = shade_color(c, MUTE_SHADE);
    mLines.AddLine(BPoint(entireF.left + 1, entireF.top), BPoint(entireF.right - 1, entireF.top), c);
    mLines.AddLine(BPoint(entireF.left + 1, entireF.bottom), BPoint(entireF.right - 1, entireF.bottom), c);
    mLines.AddLine(BPoint(entireF.left, entireF.top + 1), BPoint(entireF.left, entireF.bottom - 1), c);
    mLines.AddLine(BPoint(entireF.right, entireF.top + 1), BPoint(entireF.right, entireF.bottom - 1), c);

    if (arp_is_valid_rect(contentF) ) {
        draw_content_border(view, contentF, bgC, mLines, mDrawMuted, !arp_is_valid_rect(labelF));
    }

    c = tint_color(Prefs().Color(AM_DATA_BACKDROP_C), B_DARKEN_1_TINT);
    if (mDrawMuted) c = shade_color(c, MUTE_SHADE);
    if (!gPhraseBg) {
        mLines.AddLine(BPoint(entireF.right + 1, entireF.top + 2), BPoint(entireF.right + 1, entireF.bottom + 0), c);
        mLines.AddLine(BPoint(entireF.left + 2, entireF.bottom + 1), BPoint(entireF.right + 0, entireF.bottom + 1), c);
        mLines.AddLine(BPoint(entireF.right + 0, entireF.bottom + 0), BPoint(entireF.right + 0, entireF.bottom + 0), c);
    }

    /* Indicate if this phrase is linked.
     */
    if (phrase->CountLinks() > 0) {
        view->SetHighColor(bgC);
        view->SetLowColor(0, 0, 0);
        view->StrokeRect(entireF, LINK_PATTERN);
    }

    if (arp_is_valid_rect(contentF) ) {
        /* Draw the events.
         */
        if (renderer) {
            BRect					trackR(clip.left, contentF.top, clip.right, contentF.bottom);
            view->SetHighColor(fgC);
            renderer->BeginTrack(trackR, view, track, mLines);
            renderer->DrawPhrase(contentF, view, track, event, end < phraseEnd ? end : phraseEnd, topPhrase, mLines);
            renderer->EndTrack(trackR, view, track, mLines);
        }
    }
    /* Finish.
     */
    mLines.EndLineArray();
}