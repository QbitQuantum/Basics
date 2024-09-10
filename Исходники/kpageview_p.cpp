KPageTabbedView::~KPageTabbedView()
{
  if (model()) {
    for ( int i = 0; i < mTabWidget->count(); ++i ) {
        QWidget *page = qvariant_cast<QWidget*>( model()->data( model()->index( i, 0 ), KPageModel::WidgetRole ) );

        if (page) {
            page->setVisible(false);
            page->setParent(0); // reparent our children before they are deleted
        }
    }
  }
}