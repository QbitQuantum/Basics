void
GaugeVario::RenderBugs(Canvas &canvas)
{
    static int last_bugs = -1;
    static PixelRect recLabelBk = {-1,-1,-1,-1};
    static PixelRect recValueBk = {-1,-1,-1,-1};
    static RasterPoint orgLabel = {-1,-1};
    static RasterPoint orgValue = {-1,-1};

    if (!bugs_initialised) {
        const PixelRect rc = get_client_rect();
        PixelSize tSize;

        orgLabel.x = 1;
        orgLabel.y = rc.bottom - 2
                     - look.text_font->GetCapitalHeight()
                     - look.text_font->GetAscentHeight();

        orgValue.x = 1;
        orgValue.y = rc.bottom - 1
                     - look.text_font->GetAscentHeight();

        recLabelBk.left = orgLabel.x;
        recLabelBk.top = orgLabel.y
                         + look.text_font->GetAscentHeight()
                         - look.text_font->GetCapitalHeight();
        recValueBk.left = orgValue.x;
        recValueBk.top = orgValue.y
                         + look.text_font->GetAscentHeight()
                         - look.text_font->GetCapitalHeight();

        canvas.Select(*look.text_font);
        tSize = canvas.CalcTextSize(TextBug);

        recLabelBk.right = recLabelBk.left + tSize.cx;
        recLabelBk.bottom = recLabelBk.top
                            + look.text_font->GetCapitalHeight()
                            + look.text_font->GetHeight()
                            - look.text_font->GetAscentHeight();

        tSize = canvas.CalcTextSize(_T("100%"));

        recValueBk.right = recValueBk.left + tSize.cx;
        recValueBk.bottom = recValueBk.top +
                            look.text_font->GetCapitalHeight();

        bugs_initialised = true;
    }

    int bugs = iround((fixed_one - GetComputerSettings().polar.bugs) * 100);
    if (is_persistent() || bugs != last_bugs) {

        canvas.Select(*look.text_font);

        if (is_persistent())
            canvas.SetBackgroundColor(look.background_color);
        else
            canvas.SetBackgroundTransparent();

        if (is_persistent() || last_bugs < 1 || bugs < 1) {
            if (bugs > 0) {
                canvas.SetTextColor(look.dimmed_text_color);
                if (is_persistent())
                    canvas.text_opaque(orgLabel.x, orgLabel.y, recLabelBk, TextBug);
                else
                    canvas.text(orgLabel.x, orgLabel.y, TextBug);
            } else if (is_persistent())
                canvas.DrawFilledRectangle(recLabelBk, look.background_color);
        }

        if (bugs > 0) {
            TCHAR buffer[18];
            _stprintf(buffer, _T("%d%%"), bugs);
            canvas.SetTextColor(look.text_color);
            if (is_persistent())
                canvas.text_opaque(orgValue.x, orgValue.y, recValueBk, buffer);
            else
                canvas.text(orgValue.x, orgValue.y, buffer);
        } else if (is_persistent())
            canvas.DrawFilledRectangle(recValueBk, look.background_color);

        if (is_persistent())
            last_bugs = bugs;
    }
}