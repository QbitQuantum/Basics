//判断牌型是否是四带二
bool CardCombine::is_Four_Two()const
{
    /*
     * 有四张同点数的牌,其余两张点数和这四张不同,但是那两张点数可以相等也可以不等
     * how to judge?
     * 首先牌数必须为6,然后按点数进行计数排序,结果为uint count[16]
     * 然后遍历count[],若存在count[i]==4,则符合要求
    */
    unsigned int N=static_cast<unsigned int>(_list.size());
    if(N!=6)
        return false;
    unsigned int count[16];
    memset(count,0,16*sizeof(unsigned int));
    for(unsigned int i=0;i<N;i++)
        count[_list[i].getPoint()]++;
    for(int i=0;i<16;i++){
        if(count[i]==4)
            return true;
    }
    return false;
}