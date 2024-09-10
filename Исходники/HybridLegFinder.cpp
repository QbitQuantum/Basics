void LegFinder::laserCallback(std::vector<float>& laser_r, std::vector<float>& laser_t)
{
    if(laser_r.size() != laser_t.size())
    {
        std::cout << "LegFinder.->Something went wrong while getting laser readings :'(" << std::endl;
        return;
    }

    this->rec.clear();
    std::vector<float> laser_x;
    std::vector<float> laser_y;

    this->laserFilter_Mean(laser_r);
    
    for(size_t i=0; i < laser_r.size(); i++)
    {
        laser_x.push_back(laser_r[i] * cos(laser_t[i]));
        laser_y.push_back(laser_r[i] * sin(laser_t[i]));
    }

    std::vector<float> laser_flank;
    std::vector<float> flank_id0;
    std::vector<float> flank_id1;
    std::vector<bool> flank_id2;
    int ant2 = 0;
    
    for(int i= 1; i < laser_r.size(); i++)
    {
        pcl::PointXYZ cua;
        float sumax, sumay, px, py, m1, m2, ang;
        int ant = ant2;
        if(fabs(laser_r[i] - laser_r[i-1]) > FLANK_THRESHOLD)
        {
            if((pow(laser_x[ant] - laser_x[i-1], 2) + pow(laser_y[ant] - laser_y[i-1], 2)) > PIERNA_DELGADA &&
               (pow(laser_x[ant] - laser_x[i-1], 2) + pow(laser_y[ant] - laser_y[i-1], 2)) < PIERNA_GRUESA)
            {
                if(esPierna(laser_x[ant], laser_y[ant], laser_x[i-1], laser_y[i-1]) ||
                   esPierna(laser_x[ant+1], laser_y[ant+1], laser_x[i-2], laser_y[i-2]))
                {
                    sumax = 0;
                    sumay = 0;
                    for(int j= ant; j < i; j++)
                    {
                        sumax += laser_x[j];
                        sumay += laser_y[j];
                    }
                    flank_id0.push_back(sumax / (float)(i - ant));
                    flank_id1.push_back(sumay / (float)(i - ant));
                    flank_id2.push_back(false);
                }
            }
            else 
            {
                if((pow(laser_x[ant] - laser_x[i-1], 2) + pow(laser_y[ant] - laser_y[i-1], 2)) > DOS_PIERNAS_DELGADAS &&
                    (pow(laser_x[ant] - laser_x[i-1], 2) + pow(laser_y[ant] - laser_y[i-1], 2)) < DOS_PIERNAS_GRUESAS)
                {
                    if(esPierna(laser_x[ant], laser_y[ant], laser_x[i-1], laser_y[i-1]) ||
                       esPierna(laser_x[ant+1], laser_y[ant+1], laser_x[i-2], laser_y[i-2]))
                    {
                        sumax = 0;
                        sumay = 0;
                        for(int j= ant; j < i; j++)
                        {
                            sumax += laser_x[j];
                            sumay += laser_y[j];
                        }
                        cua.x = sumax / (float)(i - ant);
                        cua.y = sumay / (float)(i - ant);
                        cua.z = 2;
                        this->rec.push_back(cua);
                    }
                }
            }
            ant2 = i;
        }
        else
        {
            laser_flank.push_back(0);
        }
    }
    
    for(int i=0; i < (int)(flank_id1.size())-2; i++)
    {
        for(int j=1; j < 3; j++)
        {
            pcl::PointXYZ cua;
            float px, py;

            if((pow(flank_id0[i] - flank_id0[i+j], 2) + pow(flank_id1[i] - flank_id1[i+j], 2)) > DOS_PIERNAS_CERCAS &&
               (pow(flank_id0[i] - flank_id0[i+j], 2) + pow(flank_id1[i] - flank_id1[i+j], 2)) < DOS_PIERNAS_LEJOS)
            {
                px = (flank_id0[i] + flank_id0[i + j])/2;
                py = (flank_id1[i] + flank_id1[i + j])/2;
                if((px*px + py*py) < HORIZON_THRESHOLD)
                {
                    cua.x = px;
                    cua.y = py;
                    cua.z = 2;
                    this->rec.push_back(cua);
                    flank_id2[i] = true;
                    flank_id2[i+j] = true;
                }
            }
        }
    }
    
    if(flank_id1.size() > 1)
    {
        pcl::PointXYZ cua;
        float px, py;

        if((pow(flank_id0[flank_id1.size()-2] - flank_id0[flank_id1.size()-1], 2) +
            pow(flank_id1[flank_id1.size()-2] - flank_id1[flank_id1.size()-1], 2)) > DOS_PIERNAS_CERCAS &&
           (pow(flank_id0[flank_id1.size()-2] - flank_id0[flank_id1.size()-1], 2) +
            pow(flank_id1[flank_id1.size()-2] - flank_id1[flank_id1.size()-1], 2)) < DOS_PIERNAS_LEJOS)
        {
            px = (flank_id0[flank_id1.size()-2] + flank_id0[flank_id1.size()-1])/2.0;
            py = (flank_id1[flank_id1.size()-2] + flank_id1[flank_id1.size()-1])/2.0;
            if((px*px + py*py) < HORIZON_THRESHOLD)
            {
                cua.x = px;
                cua.y = py;
                cua.z = 2;
                this->rec.push_back(cua);
                flank_id2[flank_id1.size() - 2] = true;
                flank_id2[flank_id1.size() - 1] = true;
            }
        }
    }
    for(int i=0; i < flank_id1.size(); i++)
    {
        if(!flank_id2[i])
        {
            pcl::PointXYZ cua;
            cua.x = flank_id0[i];
            cua.y = flank_id1[i];
            cua.z = 1;
            this->rec.push_back(cua);
        }
    }
}