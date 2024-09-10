Bool	EnumCtrl::Optimise(int breakeven)
{
    int	usemax=sillymax;
    if (sillymax>4*max)
        usemax=max;
    else
        max=usemax;
    if (arr)
        return TRUE;
    int	totelts=0;
    int	lastval=0x80000000;
    for (enumlinkelt* t2=links; t2; t2=t2->next)
    {
//		if (t2->value==lastval)
        //		return FALSE;
        totelts++;
        //	lastval=t2->value;
    }
    if (usemax-min>40000000 || totelts*100<(usemax-min)*breakeven)
        return (FALSE);
    arr=new enumarrelt[1+usemax-min];
    lastval=min;
    arr[0].name[0]=0;
    if (usemax==sillymax)
        for (enumlinkelt* t2=links; t2; t2=t2->next)
        {
            while (lastval<t2->value)
                arr[(lastval++)-min].name[0]=0;
            if (t2->value==lastval)
                Strcpy(arr[(lastval++)-min].name,t2->name);//,enumeltnamelen);
            else if	(links==NULL)
                return(FALSE);
        }
    else
        for (enumlinkelt* t2=links,*t3=t2->next; t3; t3=(t2=t3)->next)
        {
            while (lastval<t2->value)
                arr[(lastval++)-min].name[0]=0;
            if (t2->value==lastval)
                Strcpy(arr[(lastval++)-min].name,t2->name);//,enumeltnamelen);
        }

    delete links;
    links=NULL;
    return TRUE;
}