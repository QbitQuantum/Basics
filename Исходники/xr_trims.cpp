AnsiString FloatTimeToStrTime(float v, bool _h, bool _m, bool _s, bool _ms)
{
    AnsiString buf = "";
    int h = 0, m = 0, s = 0, ms;
    AnsiString t;
    if (_h) { h = iFloor(v / 3600); t.sprintf("%02d", h); buf += t; }
    if (_m) { m = iFloor((v - h * 3600) / 60); t.sprintf("%02d", m); buf += buf.IsEmpty() ? t : ":" + t; }
    if (_s) { s = iFloor(v - h * 3600 - m * 60); t.sprintf("%02d", s); buf += buf.IsEmpty() ? t : ":" + t; }
    if (_ms) { ms = iFloor((v - h * 3600 - m * 60 - s)*1000.f); t.sprintf("%03d", ms); buf += buf.IsEmpty() ? t : "." + t; }
    return buf;
}