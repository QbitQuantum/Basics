//---------------------------------------------------------------------------
void __fastcall TFormDisciplines::StringToAudHours(AudHours* h, AnsiString &str_hours)
{
    int cur_sem = 0;
    int begin = 1;
    for(int pos = 1; pos <= str_hours.Length(); pos++)
    {
        if (str_hours[pos] == ';')
        {
            h->hours[cur_sem++] = str_hours.SubString(begin, pos - begin);
            begin = pos + 1;
        }
    }
}