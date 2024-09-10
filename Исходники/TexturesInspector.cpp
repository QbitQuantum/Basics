        TextureLine(spNativeTexture t)
        {
            setVerticalMode(Box9Sprite::TILING_FULL);
            setHorizontalMode(Box9Sprite::TILING_FULL);
            Sprite::setResAnim(DebugActor::resSystem->getResAnim("checker"));

            AnimationFrame f;
            Vector2 s = fitSize(itemSize, Vector2((float)t->getWidth(), (float)t->getHeight()));

            setSize(s);

            Diffuse df;
            df.base = t;

            f.init(0, df, RectF(0, 0, 1.0f, 1.0f), RectF(0, 0, s.x, s.y), s);
            spSprite image = initActor(new Sprite,
                                       arg_blend = blend_disabled,
                                       arg_resAnim = f);
            addChild(image);

            spColorRectSprite rect = initActor(new ColorRectSprite,
                                               arg_color = Color(Color::White, 255),
                                               arg_attachTo = this);

            rect->addTween(Sprite::TweenColor(Color(Color::White, 0)), 4000, -1, true);

            char path[255];
            path::normalize(t->getName().c_str(), path);

            char txt[255];
            safe_sprintf(txt, "%s\n<div c=\"FF0000\">%s</div>-<div c=\"0000ff\">%dx%d</div>\nid: %d",
                         path,
                         textureFormat2String(t->getFormat()),
                         t->getWidth(), t->getHeight(), t->getObjectID());

            spTextField text = initActor(new TextField,
                                         arg_color = Color::Black,
                                         arg_w = (float)itemSize.x,
                                         arg_vAlign = TextStyle::VALIGN_TOP,
                                         arg_hAlign = TextStyle::HALIGN_LEFT,
                                         arg_multiline = true,
                                         arg_attachTo = rect,
                                         arg_htmlText = txt
                                        );

            text->setBreakLongWords(true);

            rect->setSize(text->getTextRect().size.cast<Vector2>() + Vector2(2, 2));
            rect->setY((itemSize.y - rect->getHeight()) / 2.0f);
        }