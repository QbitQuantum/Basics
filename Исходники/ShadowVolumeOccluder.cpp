// clip the convex hull 'in' to plane to generate a clipped convex hull 'out'
// return true if points remain after clipping.
unsigned int clip(const Plane& plane,const PointList& in, PointList& out,unsigned int planeMask)
{
    std::vector<float> distance;
    distance.reserve(in.size());
    for(PointList::const_iterator itr=in.begin();
        itr!=in.end();
        ++itr)
    {
        distance.push_back(plane.distance(itr->second));
    }

    out.clear();

    for(unsigned int i=0;i<in.size();++i)
    {
        unsigned int i_1 = (i+1)%in.size(); // do the mod to wrap the index round back to the start.
        
        if (distance[i]>=0.0f)
        {
            out.push_back(in[i]);
            
            
            if (distance[i_1]<0.0f)
            {
                unsigned int mask = (in[i].first & in[i_1].first) | planeMask;
                float r = distance[i_1]/(distance[i_1]-distance[i]);
                out.push_back(Point(mask,in[i].second*r+in[i_1].second*(1.0f-r)));
            }
        
        }
        else if (distance[i_1]>0.0f)
        {
            unsigned int mask = (in[i].first & in[i_1].first) | planeMask;
            float r = distance[i_1]/(distance[i_1]-distance[i]);
            out.push_back(Point(mask,in[i].second*r+in[i_1].second*(1.0f-r)));
        }
    }
    
    return out.size();
}