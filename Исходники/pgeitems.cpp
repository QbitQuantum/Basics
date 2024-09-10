 void MacroPinItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
 {
   graph::VertexItem* vertexItem = static_cast<graph::VertexItem*>(parentItem());
   Q_ASSERT(vertexItem != 0);
   const graph::Palette& pal = palette();
   QRectF rect = boundingRect();
   switch(vertexItem->itemLayout())
   {
     case graph::Defines::TopToBottom:
     {
       QPainterPath pinPath;
       if (pin().direction() == graph::Defines::Incoming)
       {
         painter->setPen(pal.pen(graph::Palette::PinIncomingBorder));
         pinPath.moveTo(rect.right(),rect.top() + rect.height() / 2.0);
         pinPath.lineTo(rect.topRight());
         pinPath.lineTo(rect.topLeft());
         pinPath.lineTo(rect.left(),rect.top() + rect.height() / 2.0);
         pinPath.arcTo(rect,180.0,180.0);
         pinPath.closeSubpath();
         painter->setBrush(pal.brush(graph::Palette::PinIncomingFill));
         painter->drawPath(pinPath);
       }
       else
       {
         painter->setPen(pal.pen(graph::Palette::PinOutgoingBorder));
         pinPath.moveTo(rect.right(),rect.top() + rect.height() / 2.0);
         pinPath.lineTo(rect.bottomRight());
         pinPath.lineTo(rect.bottomLeft());
         pinPath.lineTo(rect.left(),rect.top() + rect.height() / 2.0);
         pinPath.arcTo(rect,180.0,-180.0);
         pinPath.closeSubpath();
         painter->setBrush(pal.brush(graph::Palette::PinOutgoingFill));
         painter->drawPath(pinPath);
       }
       break;
     }
     case graph::Defines::LeftToRight:
     {
       QPainterPath pinPath;
       if (pin().direction() == graph::Defines::Incoming)
       {
         painter->setPen(pal.pen(graph::Palette::PinIncomingBorder));
         pinPath.moveTo(rect.left() + rect.width() / 2.0,rect.top());
         pinPath.lineTo(rect.topLeft());
         pinPath.lineTo(rect.bottomLeft());
         pinPath.lineTo(rect.left() + rect.width() / 2.0,rect.bottom());
         pinPath.arcTo(rect,270.0,180.0);
         pinPath.closeSubpath();
         painter->setBrush(pal.brush(graph::Palette::PinIncomingFill));
         painter->drawPath(pinPath);
       }
       else
       {
         painter->setPen(pal.pen(graph::Palette::PinOutgoingBorder));
         pinPath.moveTo(rect.left() + rect.width() / 2.0,rect.top());
         pinPath.lineTo(rect.topRight());
         pinPath.lineTo(rect.bottomRight());
         pinPath.lineTo(rect.left() + rect.width() / 2.0,rect.bottom());
         pinPath.arcTo(rect,270.0,-180.0);
         pinPath.closeSubpath();
         painter->setBrush(pal.brush(graph::Palette::PinOutgoingFill));
         painter->drawPath(pinPath);
       }
       break;
     }
     case graph::Defines::RightToLeft:
     {
       QPainterPath pinPath;
       if (pin().direction() == graph::Defines::Incoming)
       {
         painter->setPen(pal.pen(graph::Palette::PinIncomingBorder));
         pinPath.moveTo(rect.left() + rect.width() / 2.0,rect.top());
         pinPath.lineTo(rect.topRight());
         pinPath.lineTo(rect.bottomRight());
         pinPath.lineTo(rect.left() + rect.width() / 2.0,rect.bottom());
         pinPath.arcTo(rect,270.0,-180.0);
         pinPath.closeSubpath();
         painter->setBrush(pal.brush(graph::Palette::PinIncomingFill));
         painter->drawPath(pinPath);
       }
       else
       {
         painter->setPen(pal.pen(graph::Palette::PinOutgoingBorder));
         pinPath.moveTo(rect.left() + rect.width() / 2.0,rect.top());
         pinPath.lineTo(rect.topLeft());
         pinPath.lineTo(rect.bottomLeft());
         pinPath.lineTo(rect.left() + rect.width() / 2.0,rect.bottom());
         pinPath.arcTo(rect,270.0,180.0);
         pinPath.closeSubpath();
         painter->setBrush(pal.brush(graph::Palette::PinOutgoingFill));
         painter->drawPath(pinPath);
       }
       break;
     }
   }
 }