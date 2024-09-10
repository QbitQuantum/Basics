int main(int argc, char* argv[])
{
    DWORD dwTmAdj;
    
    cout<<"please input time adjustment (unit is 100ns):\n";
    cin>>dwTmAdj;

    cout<<"ok! use time adjustment "<<dwTmAdj<<"\n";

	if(EnableAdjustTimePrivilege(true)){
		if(!SetSystemTimeAdjustment(dwTmAdj,false)){
			cout<<"set time adjustment fail! err code "<<GetLastError()<<"\n";
			return false;
		}else{
			cout<<"set time adjustment succeed!\n";
		}
		EnableAdjustTimePrivilege(false);
	}else{
		return false;
	}
        
    return 0;
}