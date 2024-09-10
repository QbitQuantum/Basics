inline void yet_another_watershed( const volume_ptr<ID>& seg_ptr,
                                   const region_graph_ptr<ID,F> rg_ptr,
                                   std::vector<std::size_t>& counts,
                                   const L& lowl)
{
    F low = static_cast<F>(lowl);

    std::vector<std::size_t> new_counts({0});
    std::vector<ID>          remaps(counts.size());

    zi::disjoint_sets<ID>    sets(counts.size());
    std::vector<F>           maxs(counts.size());


    region_graph<ID,F>& rg  = *rg_ptr;

    ID next_id = 1;
    ID merged = 0;


    for ( auto& it: rg )
    {
        if ( std::get<0>(it) <= low )
        {
            break;
        }

        ID s1 = std::get<1>(it);
        ID s2 = std::get<2>(it);

        F f = std::get<0>(it);

        if ( s1 && s2 )
        {
            if ( (remaps[s1] == 0) || (remaps[s2] == 0) )
            {
                if ( remaps[s1] == 0 )
                {
                    std::swap(s1,s2);
                }

                if ( remaps[s1] == 0 )
                {
                    maxs[next_id] = f;
                    remaps[s1] = remaps[s2] = next_id;
                    new_counts.push_back(counts[s1]+counts[s2]);
                    ++next_id;
                }
                else
                {
                    ID actual = sets.find_set(remaps[s1]);
                    remaps[s2] = remaps[s1];
                    new_counts[actual] += counts[s2];
                }
            }
            else
            {
                ID a1 = sets.find_set(remaps[s1]);
                ID a2 = sets.find_set(remaps[s2]);

                if ( 0 && a1 != a2 && ((maxs[a1]==f)||(maxs[a2]==f)) )
                {
                    ++merged;
                    new_counts[a1] += new_counts[a2];
                    new_counts[a2] = 0;
                    maxs[a1] = std::max(maxs[a1],maxs[a2]);
                    maxs[a2] = 0;
                    ID a = sets.join(a1,a2);
                    std::swap(new_counts[a], new_counts[a1]);
                    std::swap(maxs[a], maxs[a1]);
                }
            }
        }
    }

    next_id -= merged;

    std::vector<ID> remaps2(counts.size());

    next_id = 1;

    for ( ID id = 0; id < counts.size(); ++id )
    {
        ID s = sets.find_set(remaps[id]);
        if ( s && (remaps2[s]==0) )
        {
            remaps2[s] = next_id;
            new_counts[next_id] = new_counts[s];
            ++next_id;
        }
    }

    new_counts.resize(next_id);

    std::ptrdiff_t xdim = seg_ptr->shape()[0];
    std::ptrdiff_t ydim = seg_ptr->shape()[1];
    std::ptrdiff_t zdim = seg_ptr->shape()[2];

    std::ptrdiff_t total = xdim * ydim * zdim;

    ID* seg_raw = seg_ptr->data();

    for ( std::ptrdiff_t idx = 0; idx < total; ++idx )
    {
        seg_raw[idx] = remaps2[remaps[seg_raw[idx]]];
    }

    region_graph<ID,F> new_rg;

    for ( auto& it: rg )
    {
        ID s1 = remaps2[remaps[std::get<1>(it)]];
        ID s2 = remaps2[remaps[std::get<2>(it)]];

        if ( s1 != s2 && s1 && s2 )
        {
            auto mm = std::minmax(s1,s2);
            new_rg.emplace_back(std::get<0>(it), mm.first, mm.second);
        }
    }

    rg.swap(new_rg);

    counts.swap(new_counts);

    std::cout << "New count: " << counts.size() << std::endl;

    std::cout << "Done with updating the region graph, size: "
              << rg.size() << std::endl;
}