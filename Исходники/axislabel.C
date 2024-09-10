TString nPart(Int_t part,TString string)
{
    if (part <= 0) return "";
    for (int i = 1; i < part; i++)    //part-1 times
    {
        if (string.Index(";") < 0) return "";
        string.Replace(0,string.Index(";")+1,"",0);
    }
    if (string.Index(";") >= 0)
        string.Remove(string.Index(";"));
    return string;
}