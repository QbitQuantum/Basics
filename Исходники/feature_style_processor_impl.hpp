void feature_style_processor<Processor>::prepare_layer(layer_rendering_material & mat,
                                                       feature_style_context_map & ctx_map,
                                                       Processor & p,
                                                       double scale,
                                                       double scale_denom,
                                                       unsigned width,
                                                       unsigned height,
                                                       box2d<double> const& extent,
                                                       int buffer_size,
                                                       std::set<std::string>& names)
{
    layer const& lay = mat.lay_;

    std::vector<std::string> const& style_names = lay.styles();

    std::size_t num_styles = style_names.size();
    if (num_styles == 0)
    {
        MAPNIK_LOG_DEBUG(feature_style_processor)
            << "feature_style_processor: No style for layer=" << lay.name();
        return;
    }

    mapnik::datasource_ptr ds = lay.datasource();
    if (!ds)
    {
        MAPNIK_LOG_DEBUG(feature_style_processor)
            << "feature_style_processor: No datasource for layer=" << lay.name();
        return;
    }

    processor_context_ptr current_ctx = ds->get_context(ctx_map);
    proj_transform prj_trans(mat.proj0_,mat.proj1_);

    box2d<double> query_ext = extent; // unbuffered
    box2d<double> buffered_query_ext(query_ext);  // buffered

    double buffer_padding = 2.0 * scale;
    boost::optional<int> layer_buffer_size = lay.buffer_size();
    if (layer_buffer_size) // if layer overrides buffer size, use this value to compute buffered extent
    {
        buffer_padding *= *layer_buffer_size;
    }
    else
    {
        buffer_padding *= buffer_size;
    }
    buffered_query_ext.width(query_ext.width() + buffer_padding);
    buffered_query_ext.height(query_ext.height() + buffer_padding);

    // clip buffered extent by maximum extent, if supplied
    boost::optional<box2d<double> > const& maximum_extent = m_.maximum_extent();
    if (maximum_extent)
    {
        buffered_query_ext.clip(*maximum_extent);
    }

    box2d<double> layer_ext = lay.envelope();
    const box2d<double> buffered_query_ext_map_srs = buffered_query_ext;
    bool fw_success = false;
    bool early_return = false;

    // first, try intersection of map extent forward projected into layer srs
    if (prj_trans.forward(buffered_query_ext, PROJ_ENVELOPE_POINTS) && buffered_query_ext.intersects(layer_ext))
    {
        fw_success = true;
        layer_ext.clip(buffered_query_ext);
    }
    // if no intersection and projections are also equal, early return
    else if (prj_trans.equal())
    {
        early_return = true;
    }
    // next try intersection of layer extent back projected into map srs
    else if (prj_trans.backward(layer_ext, PROJ_ENVELOPE_POINTS) && buffered_query_ext_map_srs.intersects(layer_ext))
    {
        layer_ext.clip(buffered_query_ext_map_srs);
        // forward project layer extent back into native projection
        if (! prj_trans.forward(layer_ext, PROJ_ENVELOPE_POINTS))
        {
            MAPNIK_LOG_ERROR(feature_style_processor)
                << "feature_style_processor: Layer=" << lay.name()
                << " extent=" << layer_ext << " in map projection "
                << " did not reproject properly back to layer projection";
        }
    }
    else
    {
        // if no intersection then nothing to do for layer
        early_return = true;
    }

    std::vector<feature_type_style const*> & active_styles = mat.active_styles_;

    if (early_return)
    {
        // check for styles needing compositing operations applied
        // https://github.com/mapnik/mapnik/issues/1477
        for (std::string const& style_name : style_names)
        {
            boost::optional<feature_type_style const&> style=m_.find_style(style_name);
            if (!style)
            {
                continue;
            }

            if (style->comp_op() || style->image_filters().size() > 0)
            {
                if (style->active(scale_denom))
                {
                    // we'll have to handle compositing ops
                    active_styles.push_back(&(*style));
                }
            }
        }
        return;
    }

    // if we've got this far, now prepare the unbuffered extent
    // which is used as a bbox for clipping geometries
    if (maximum_extent)
    {
        query_ext.clip(*maximum_extent);
    }

    box2d<double> & layer_ext2 = mat.layer_ext2_;

    layer_ext2 = lay.envelope();
    if (fw_success)
    {
        if (prj_trans.forward(query_ext, PROJ_ENVELOPE_POINTS))
        {
            layer_ext2.clip(query_ext);
        }
    }
    else
    {
        if (prj_trans.backward(layer_ext2, PROJ_ENVELOPE_POINTS))
        {
            layer_ext2.clip(query_ext);
            prj_trans.forward(layer_ext2, PROJ_ENVELOPE_POINTS);
        }
    }

    std::vector<rule_cache> & rule_caches = mat.rule_caches_;
    attribute_collector collector(names);

    // iterate through all named styles collecting active styles and attribute names
    for (std::string const& style_name : style_names)
    {
        boost::optional<feature_type_style const&> style=m_.find_style(style_name);
        if (!style)
        {
            MAPNIK_LOG_ERROR(feature_style_processor)
                << "feature_style_processor: Style=" << style_name
                << " required for layer=" << lay.name() << " does not exist.";

            continue;
        }

        std::vector<rule> const& style_rules = style->get_rules();
        bool active_rules = false;
        rule_cache rc;
        for(rule const& r : style_rules)
        {
            if (r.active(scale_denom))
            {
                rc.add_rule(r);
                active_rules = true;
                collector(r);
            }
        }
        if (active_rules)
        {
            rule_caches.push_back(std::move(rc));
            active_styles.push_back(&(*style));
        }
    }

    // Don't even try to do more work if there are no active styles.
    if (active_styles.empty())
    {
        return;
    }

    double qw = query_ext.width()>0 ? query_ext.width() : 1;
    double qh = query_ext.height()>0 ? query_ext.height() : 1;
    query::resolution_type res(width/qw,
                               height/qh);

    query q(layer_ext,res,scale_denom,extent);
    q.set_variables(p.variables());

    if (p.attribute_collection_policy() == COLLECT_ALL)
    {
        layer_descriptor lay_desc = ds->get_descriptor();
        for (attribute_descriptor const& desc : lay_desc.get_descriptors())
        {
            q.add_property_name(desc.get_name());
        }
    }
    else
    {
        for (std::string const& name : names)
        {
            q.add_property_name(name);
        }
    }
    q.set_filter_factor(collector.get_filter_factor());

    // Also query the group by attribute
    std::string const& group_by = lay.group_by();
    if (!group_by.empty())
    {
        q.add_property_name(group_by);
    }

    bool cache_features = lay.cache_features() && active_styles.size() > 1;

    std::vector<featureset_ptr> & featureset_ptr_list = mat.featureset_ptr_list_;
    if (!group_by.empty() || cache_features)
    {
        featureset_ptr_list.push_back(ds->features_with_context(q,current_ctx));
    }
    else
    {
        for(std::size_t i = 0; i < active_styles.size(); ++i)
        {
            featureset_ptr_list.push_back(ds->features_with_context(q,current_ctx));
        }
    }
}