string Add(string fNum,string sNum)
{
        if(fNum.length()<sNum.length()) fNum.swap(sNum);
        string Add("0");
    Add+=fNum;
        for(unsigned i=1;i<=fNum.length();i++)
                if(i<=sNum.length())
                        Add[Add.length()-i]+=sNum[sNum.length()-i]-'0';
        for(unsigned i=1;i<Add.length();i++)
        {
                if(Add[Add.length()-i]>'9')
                { Add[Add.length()-i]-=10;Add[Add.length()-i-1]+=1; }
        }
    while(Add[0]=='0') Add.erase(0,1);
        return Add;
}