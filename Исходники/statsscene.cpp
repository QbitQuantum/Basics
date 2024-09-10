 foreach(QGraphicsGridLayout *layout, _layouts) {
     QGraphicsWidget *form = new QGraphicsWidget;
     form->setLayout(layout);
     addItem(form);
     form->setPos(i, 0);
     i += 200;
 }