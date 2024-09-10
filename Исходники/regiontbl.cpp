// ------------------------------- Function to grow REGIONS using 8 neighbours within threshold
    void segment()
    {

        int curr_region=0;
        while (1)
        {
            pixel seed;
            if (get_free_pixel(seed) >=0 )
            {
                QUE.empty();
                int seedw = seed.w;
                int seedh = seed.h;
                float seedr = seed.r;
                float seedg = seed.g;
                float seedb = seed.b;
                        //adding to current region and adding details to img_region
                img_data[seedh][seedw].region = curr_region;
                img_region[curr_region][RED] += img_data[seedh][seedw].r;
                img_region[curr_region][GREEN] += img_data[seedh][seedw].g;
                img_region[curr_region][BLUE] += img_data[seedh][seedw].b;
                img_region[curr_region][NUM_PIXEL]++;
                        //add good neighbours to region and also adding them to search queue
                add_goodn(seedh,seedw , curr_region , seedr, seedg, seedb);
                while (! QUE.isempty()) //QUE stores the pixels which are already in this region for further searching
                {
                    pixel curr;
                    if(QUE.remove(curr)>=0)
                        {
                            int currh = curr.h;  int currw=curr.w;
                                //look at neighbours and grow
                            add_goodn(currh,currw, curr_region , seedr, seedg, seedb);
                        }
                }
                            //grow next region
                curr_region = curr_region + 1;
            }
            else
            {
                std::cout<<"\nAll pixels are alloted to some region.";
                break;
            }

        }
        img_total_regions = curr_region-1;
        std::cout<<std::endl<<img_total_regions<<" REGIONS found. \n" ;
    }