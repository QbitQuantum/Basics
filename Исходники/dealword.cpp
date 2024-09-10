AnsiString searchleftright(AnsiString t)
{
        int i,left=0,right=0;
        for(i=1;i<=t.Length();i++)
        {
                if(t[i]=='(' || t[i]=='[' || t[i]=='{')
                        left++;
                if(t[i]==')' || t[i]==']' || t[i]=='}')
                        right++;
                if(right==left)
                        break;
        }
        return t.SubString(2,i);
}