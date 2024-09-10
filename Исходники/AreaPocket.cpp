void CurveTree::MakeOffsets2()
{
    // make offsets

    if(CArea::m_please_abort)return;
    CArea smaller;
    smaller.m_curves.push_back(curve);
    smaller.Offset(pocket_params->stepover);

    if(CArea::m_please_abort)return;

    // test islands
    for(std::list<const IslandAndOffset*>::iterator It = offset_islands.begin(); It != offset_islands.end();)
    {
        const IslandAndOffset* island_and_offset = *It;

        if(GetOverlapType(island_and_offset->offset, smaller) == eInside)
            It++; // island is still inside
        else
        {
            inners.push_back(new CurveTree(*island_and_offset->island));
            islands_added.push_back(inners.back());
            inners.back()->point_on_parent = curve.NearestPoint(*island_and_offset->island);
            if(CArea::m_please_abort)return;
            Point island_point = island_and_offset->island->NearestPoint(inners.back()->point_on_parent);
            if(CArea::m_please_abort)return;
            inners.back()->curve.ChangeStart(island_point);
            if(CArea::m_please_abort)return;

            // add the island offset's inner curves
            for(std::list<CCurve>::const_iterator It2 = island_and_offset->island_inners.begin(); It2 != island_and_offset->island_inners.end(); It2++)
            {
                const CCurve& island_inner = *It2;
                inners.back()->inners.push_back(new CurveTree(island_inner));
                inners.back()->inners.back()->point_on_parent = inners.back()->curve.NearestPoint(island_inner);
                if(CArea::m_please_abort)return;
                Point island_point = island_inner.NearestPoint(inners.back()->inners.back()->point_on_parent);
                if(CArea::m_please_abort)return;
                inners.back()->inners.back()->curve.ChangeStart(island_point);
                to_do_list_for_MakeOffsets.push_back(inners.back()->inners.back()); // do it later, in a while loop
                if(CArea::m_please_abort)return;
            }

            smaller.Subtract(island_and_offset->offset);

            std::set<const IslandAndOffset*> added;

            std::list<IslandAndOffsetLink> touching_list;
            for(std::list<IslandAndOffset*>::const_iterator It2 = island_and_offset->touching_offsets.begin(); It2 != island_and_offset->touching_offsets.end(); It2++)
            {
                const IslandAndOffset* touching = *It2;
                touching_list.push_back(IslandAndOffsetLink(touching, inners.back()));
                added.insert(touching);
            }

            while(touching_list.size() > 0)
            {
                IslandAndOffsetLink touching = touching_list.front();
                touching_list.pop_front();
                touching.add_to->inners.push_back(new CurveTree(*touching.island_and_offset->island));
                islands_added.push_back(touching.add_to->inners.back());
                touching.add_to->inners.back()->point_on_parent = touching.add_to->curve.NearestPoint(*touching.island_and_offset->island);
                Point island_point = touching.island_and_offset->island->NearestPoint(touching.add_to->inners.back()->point_on_parent);
                touching.add_to->inners.back()->curve.ChangeStart(island_point);
                smaller.Subtract(touching.island_and_offset->offset);

                // add the island offset's inner curves
                for(std::list<CCurve>::const_iterator It2 = touching.island_and_offset->island_inners.begin(); It2 != touching.island_and_offset->island_inners.end(); It2++)
                {
                    const CCurve& island_inner = *It2;
                    touching.add_to->inners.back()->inners.push_back(new CurveTree(island_inner));
                    touching.add_to->inners.back()->inners.back()->point_on_parent = touching.add_to->inners.back()->curve.NearestPoint(island_inner);
                    if(CArea::m_please_abort)return;
                    Point island_point = island_inner.NearestPoint(touching.add_to->inners.back()->inners.back()->point_on_parent);
                    if(CArea::m_please_abort)return;
                    touching.add_to->inners.back()->inners.back()->curve.ChangeStart(island_point);
                    to_do_list_for_MakeOffsets.push_back(touching.add_to->inners.back()->inners.back()); // do it later, in a while loop
                    if(CArea::m_please_abort)return;
                }

                for(std::list<IslandAndOffset*>::const_iterator It2 = touching.island_and_offset->touching_offsets.begin(); It2 != touching.island_and_offset->touching_offsets.end(); It2++)
                {
                    if(added.find(*It2)==added.end() && ((*It2) != island_and_offset))
                    {
                        touching_list.push_back(IslandAndOffsetLink(*It2, touching.add_to->inners.back()));
                        added.insert(*It2);
                    }
                }
            }

            if(CArea::m_please_abort)return;
            It = offset_islands.erase(It);

            for(std::set<const IslandAndOffset*>::iterator It2 = added.begin(); It2 != added.end(); It2++)
            {
                const IslandAndOffset* i = *It2;
                offset_islands.remove(i);
            }

            if(offset_islands.size() == 0)break;
            It = offset_islands.begin();
        }
    }

    CArea::m_processing_done += CArea::m_MakeOffsets_increment;
    if(CArea::m_processing_done > CArea::m_after_MakeOffsets_length)CArea::m_processing_done = CArea::m_after_MakeOffsets_length;

    std::list<CArea> separate_areas;
    smaller.Split(separate_areas);
    if(CArea::m_please_abort)return;
    for(std::list<CArea>::iterator It = separate_areas.begin(); It != separate_areas.end(); It++)
    {
        CArea& separate_area = *It;
        CCurve& first_curve = separate_area.m_curves.front();

        CurveTree* nearest_curve_tree = NULL;
        Point near_point = GetNearestPoint(this, islands_added, first_curve, &nearest_curve_tree);

        nearest_curve_tree->inners.push_back(new CurveTree(first_curve));

        for(std::list<const IslandAndOffset*>::iterator It = offset_islands.begin(); It != offset_islands.end(); It++)
        {
            const IslandAndOffset* island_and_offset = *It;
            if(GetOverlapType(island_and_offset->offset, separate_area) == eInside)
                nearest_curve_tree->inners.back()->offset_islands.push_back(island_and_offset);
            if(CArea::m_please_abort)return;
        }

        nearest_curve_tree->inners.back()->point_on_parent = near_point;

        if(CArea::m_please_abort)return;
        Point first_curve_point = first_curve.NearestPoint(nearest_curve_tree->inners.back()->point_on_parent);
        if(CArea::m_please_abort)return;
        nearest_curve_tree->inners.back()->curve.ChangeStart(first_curve_point);
        if(CArea::m_please_abort)return;
        to_do_list_for_MakeOffsets.push_back(nearest_curve_tree->inners.back()); // do it later, in a while loop
        if(CArea::m_please_abort)return;
    }
}