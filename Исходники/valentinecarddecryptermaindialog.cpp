const boost::shared_ptr<ribi::TextCanvas> ribi::ValentineCardDecrypterMainDialog::ToSymbolsAsString(const std::string& s) const noexcept
{
    const std::vector<boost::shared_ptr<ValentineCardSymbol>> v {
        ValentineCardSymbols().TextToSymbols(s)
    };
    const int sz = static_cast<int>(v.size());
    if (sz == 0) return nullptr;

    boost::shared_ptr<TextCanvas> canvas {
        new TextCanvas((sz * 3) + sz - 1, 3) //Add spaces
    };
    assert(canvas);
    for (int i=0; i!=sz; ++i)
    {
        assert(i < static_cast<int>(v.size()));
        assert(v[i]);
        assert(v[i]->ToTextCanvas());
        const boost::shared_ptr<TextCanvas> text { v[i]->ToTextCanvas() };
        assert(text);
        assert(text->GetHeight() == 3);
        assert(text->GetWidth() == 3);
        for (int row = 0; row!=3; ++row)
        {
            for (int col = 0; col!=3; ++col)
            {
                canvas->PutChar((4*i) + col,row,text->GetChar(col,row));
            }
            const int col = 3;
            canvas->PutChar((4*i) + col,row,' ');
        }
    }
    return canvas;
}