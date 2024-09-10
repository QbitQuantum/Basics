void ImagesCollectionView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        for (int i = 0; i < 9; i++) {
            QRect rect = images[i].frameGeometry();
            QRect p = QRect(event->pos().x(),event->pos().y(),1,1);

            if (rect.intersects(p)) {
                images[i].setBeingSelected(true);
                selectedIndexofImage = count - 9 + i;
                cout << "press the left mouse button: select the button, index:"
                        << selectedIndexofImage << endl;
            }
            else
                images[i].setBeingSelected(false);
        }
    } else if (event->button() == Qt::RightButton) {
        for (int i = 0; i < 9; i++) {
            QRect rect = images[i].frameGeometry();
            QRect p = QRect(event->pos().x(),event->pos().y(),1,1);

            if (rect.intersects(p) && images[i].getBeingSelected()) {
                images[i].setBeingSelected(false);
                selectedIndexofImage = -1;
                cout << "press the right mouse button: cancel the selected, index:"
                     << selectedIndexofImage << endl;
            }
        }
    }
}