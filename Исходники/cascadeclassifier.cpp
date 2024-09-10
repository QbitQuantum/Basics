void PostProcess(vector<CRect>& result,const int combine_min)
{
    vector<CRect> res1;
    vector<CRect> resmax;
    vector<int> res2;
    bool yet;
    CRect rectInter;

    for(unsigned int i=0,size_i=result.size(); i<size_i; i++)
    {
        yet = false;
        CRect& result_i = result[i];
        for(unsigned int j=0,size_r=res1.size(); j<size_r; j++)
        {
            CRect& resmax_j = resmax[j];
            if(rectInter.IntersectRect(result_i,resmax_j))
            {
                if(
                    SizeOfRect(rectInter)>0.6*SizeOfRect(result_i)
                    && SizeOfRect(rectInter)>0.6*SizeOfRect(resmax_j)
                )
                {
                    CRect& res1_j = res1[j];
                    resmax_j.UnionRect(resmax_j,result_i);
                    res1_j.bottom += result_i.bottom;
                    res1_j.top += result_i.top;
                    res1_j.left += result_i.left;
                    res1_j.right += result_i.right;
                    res2[j]++;
                    yet = true;
                    break;
                }
            }
        }
        if(yet==false)
        {
            res1.push_back(result_i);
            resmax.push_back(result_i);
            res2.push_back(1);
        }
    }

    for(unsigned int i=0,size=res1.size(); i<size; i++)
    {
        const int count = res2[i];
        CRect& res1_i = res1[i];
        res1_i.top /= count;
        res1_i.bottom /= count;
        res1_i.left /= count;
        res1_i.right /= count;
    }

    result.clear();
    for(unsigned int i=0,size=res1.size(); i<size; i++)
        if(res2[i]>combine_min)
            result.push_back(res1[i]);
}