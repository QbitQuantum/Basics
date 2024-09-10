void SPBItem::GetInfo			(AnsiString& txt, float& p, float& m)
{
    if (info.size())txt.sprintf("%s (%s)",text.c_str(),info.c_str());
    else			txt.sprintf("%s",text.c_str());
    p				= progress;
    m				= max;
}  