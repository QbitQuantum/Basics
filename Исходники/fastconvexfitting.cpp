bool FastConvexFitting::getEvaluation(Geometry & geometry)
{
    QVector<int> edgeid;
    QVector<int> startid;
    QVector<int> endid;
    if(getBeamRange(geometry,edgeid,startid,endid))
    {
        geometry.score=1;
        int j,m=edgeid.size();
        for(j=0;j<m;j++)
        {
            if(startid[j]>endid[j])
            {
                endid[j]+=beamsnum;
            }
            Eigen::Matrix2d A;
            A.block(0,0,2,1)=orientation*(geometry.edges[edgeid[j]].startcorner-geometry.edges[edgeid[j]].endcorner);
            Eigen::Vector2d B;
            B=position+orientation*(geometry.edges[edgeid[j]].startcorner);
            int k;
            int count=0;
            double score=1;
            for(k=startid[j];k<=endid[j];k++)
            {
                int tmpid=k;
                if(tmpid>=beamsnum)
                {
                    tmpid-=beamsnum;
                }
                if(beams[tmpid]<=MINIMUMDISTANCE)
                {
                    continue;
                }
                A.block(0,1,2,1)=points[tmpid];
                Eigen::Vector2d x=A.inverse()*B;
                score*=getGain(x(0),x(1),beams[tmpid]);
                count++;
            }
            if(count>0)
            {
                geometry.score*=pow(score,1.0/double(count));
            }
            else
            {
                geometry.score=0;
                return 0;
            }
        }
        return 1;
    }
    else
    {
        geometry.score=0;
        return 0;
    }
}