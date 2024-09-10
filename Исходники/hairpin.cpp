void HairpinSegment::layout()
      {
      if (hairpin()->useTextLine()) {
            if (parent())
                  rypos() += score()->styleS(StyleIdx::hairpinY).val() * spatium();
            TextLineSegment::layout();
            return;
            }

      QTransform t;
      qreal _spatium = spatium();
      qreal h1 = hairpin()->hairpinHeight().val() * spatium() * .5;
      qreal h2 = hairpin()->hairpinContHeight().val() * spatium() * .5;

      qreal len;
      qreal x = pos2().x();
      if (x < _spatium)             // minimum size of hairpin
            x = _spatium;
      qreal y = pos2().y();
      len     = sqrt(x * x + y * y);
      t.rotateRadians(asin(y/len));

      drawCircledTip =  hairpin()->hairpinCircledTip();
      circledTipRadius = 0;
      if( drawCircledTip )
        circledTipRadius  = 0.6 * _spatium * .5;
      if (hairpin()->hairpinType() == Hairpin::Type::CRESCENDO) {
            // crescendo
            switch (spannerSegmentType()) {
                  case SpannerSegmentType::SINGLE:
                  case SpannerSegmentType::BEGIN:
                        l1.setLine(.0 + circledTipRadius*2, .0, len, h1);
                        l2.setLine(.0 + circledTipRadius*2, .0, len, -h1);
                        circledTip.setX( 0 + circledTipRadius );
                        circledTip.setY( 0 );
                        break;
                  case SpannerSegmentType::MIDDLE:
                  case SpannerSegmentType::END:
                        drawCircledTip = false;
                        l1.setLine(.0,  h2, len, h1);
                        l2.setLine(.0, -h2, len, -h1);
                        break;
                  }
            }
      else {
            // decrescendo
            switch(spannerSegmentType()) {
                  case SpannerSegmentType::SINGLE:
                  case SpannerSegmentType::END:
                        l1.setLine(.0,  h1, len - circledTipRadius*2, 0.0);
                        l2.setLine(.0, -h1, len - circledTipRadius*2, 0.0);
                        circledTip.setX( len - circledTipRadius );
                        circledTip.setY( 0 );
                        break;
                  case SpannerSegmentType::BEGIN:
                  case SpannerSegmentType::MIDDLE:
                        drawCircledTip = false;
                        l1.setLine(.0,  h1, len, + h2);
                        l2.setLine(.0, -h1, len, - h2);
                        break;
                  }
            }
// Do Coord rotation
      l1 = t.map(l1);
      l2 = t.map(l2);
      if( drawCircledTip )
        circledTip = t.map(circledTip);


      QRectF r = QRectF(l1.p1(), l1.p2()).normalized() | QRectF(l2.p1(), l2.p2()).normalized();
      qreal w = point(score()->styleS(StyleIdx::hairpinLineWidth));
      setbbox(r.adjusted(-w*.5, -w*.5, w, w));
      if (parent())
            rypos() += score()->styleS(StyleIdx::hairpinY).val() * _spatium;
      adjustReadPos();
      }