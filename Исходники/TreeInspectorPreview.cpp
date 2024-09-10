    void TreeInspectorPreview::init(spActor item)
    {
        //_item = item;
        STDRenderer r(&_videoCache);
        RenderState rs;
        rs.renderer = &r;
        rs.transform = item->getTransform();
        r.begin(0);
        //r.setTransform(rs.transform);
        item->doRender(rs);
        r.end();
        r.drawBatch();

        setSize(30, 30);

        RectF itemRect = _videoCache._bounds;
        if (itemRect.isEmpty())
        {
            itemRect = item->getDestRect();
            if (itemRect.isEmpty())
                itemRect.setSize(Vector2(10, 4));
        }

        Vector2 ns = fitSize(Vector2(50.0f, 50.0f), itemRect.size);
        float scale = ns.x / itemRect.size.x;

        _cacheTransform.identity();

        _cacheTransform.scale(Vector2(scale, scale));
        _cacheTransform.translate(-itemRect.pos);



        AnimationFrame fr = _tree->_resSystem->getResAnim("checker")->getFrame(0, 0);
        //Point itemSize(30, 30);// = _getItemRect().size;

        RectF srcRect = fr.getSrcRect();
        const Diffuse& df = fr.getDiffuse();
        srcRect.size.x = ns.x / (float)df.base->getWidth();
        srcRect.size.y = ns.y / (float)df.base->getHeight();
        RectF destRect = fr.getDestRect();
        destRect.size = ns;

        AnimationFrame cfr;
        cfr.init(0, df, srcRect, destRect, ns);

        setAnimFrame(cfr);


        /*
        spEventHandler bh = new EventHandler();

        bh->setCallbackEnter(CLOSURE(this, &TreeInspectorPreview::_onEvent));
        bh->setCallbackExit(CLOSURE(this, &TreeInspectorPreview::_onEvent));
        bh->setCallbackPressDown(CLOSURE(this, &TreeInspectorPreview::_onEvent));
        bh->setCallbackPressUp(CLOSURE(this, &TreeInspectorPreview::_onEvent));
        addEventHandler(bh);
        */
    }