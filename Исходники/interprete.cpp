wxString interprete::ObtenerPolinomioParen(wxString parentesis)
{
    wxString obpa;
    char a=parentesis.GetChar(0);
    if(a=='('||a=='{')
    {
        obpa=parentesis.Mid(1,(parentesis.length()-1));
    }
    else
    {
        return "error";
        //for(i=0;i<parentesis.length();i++){}
    }
    return obpa;
}