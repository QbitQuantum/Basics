//マウス開放イベント
void MapFrame::mouseReleaseEvent(QMouseEvent *event)
{
    Map*        pMap = app.getMap();
    Intsec*     pIntsec;
    Road*       pRoad;
    bool        roadSelected;
    int         intsecIdSmall, intsecIdLarge, intsecIdNew;
    double      x, y;

    //右ボタンクリック／ドラッグならクリック、このチェックはいらないようだが念のため
//  qDebug("MapFrame::mouseReleaseEvent");
    if (event->button()!=Qt::LeftButton || !_clickDrag)
        return;
//  qDebug("MapFrame::mouseReleaseEvent click");
    _clickDrag = false;

    //交差点選択あり、交差点以外は NULL
    pIntsec = getIntsecAt(_clickDragX, _clickDragY);
    if (pIntsec != NULL)
    {
        changeShowSelect(pIntsec->getIntsecId(), MAP_NOID, MAP_NOID);
        showStatus(event->pos().x(), event->pos().y(), pIntsec->getIntsecId());

        //交差点モードなら編集画面
        if (app.getMainWindow()->getEditMode() == MainWindow::intsec)
        {
            IntsecDialog id(this);
//          qDebug("MapFrame::mouseReleaseEvent intsec dialog (%d, %d)", _intsecDialogX, _intsecDialogY);
            id.init(pIntsec);
            if (_intsecDialogX != DIALOG_NOPOS)
                id.move(_intsecDialogX, _intsecDialogY);
            if (id.exec() == QDialog::Accepted)
            {
                if (id.isDelete())
                {
                    pMap->deleteIntsec(pIntsec->getIntsecId());
                    changeShowSelect(MAP_NOID, MAP_NOID, MAP_NOID, true);
                }
                else
                {
                    if (id.isCenter())
                    {
                        app.setViewMap(app.getViewMapX() - pIntsec->getMapPosX(),
                                       app.getViewMapY() - pIntsec->getMapPosY());
                        if (app.getBackImage())
                            app.setBackMap(app.getBackMapX() - pIntsec->getMapPosX(),
                                           app.getBackMapY() - pIntsec->getMapPosY());
                        pMap->setCenter(pIntsec->getMapPosX(), pIntsec->getMapPosY(), 0);
                    }
                    //ID が変わったらマップで入れ替え、再選択
                    intsecIdNew = id.getIntsecId();
                    if (intsecIdNew != pIntsec->getIntsecId())
                    {
                        pIntsec = pMap->changeIntsecId(pIntsec, intsecIdNew);
                        changeShowSelect(intsecIdNew, MAP_NOID, MAP_NOID, true);
                    }
                    showIntsec(pIntsec);        //全体再描画は遅いので先に書いとく
                }
                repaintAll(true);
            }
//          qDebug("MapFrame::mouseReleaseEvent intsec dialog (%d, %d)", id.x(), id.y());
            _intsecDialogX = id.x();
            _intsecDialogY = id.y();
        }

        //単路／単路付け替えモードならモード切り替え（メインウィンドウから）
        else if (app.getMainWindow()->getEditMode() == MainWindow::road    ||
                 app.getMainWindow()->getEditMode() == MainWindow::roadRepl)
            app.getMainWindow()->setEditMode(MainWindow::intsec);
    }

    //交差点選択なし
    else
    {
        //単路選択あり
        pRoad = getRoadAt(_clickDragX, _clickDragY);
        if (pRoad != NULL)
        {
            roadSelected = false;
            if (pRoad->getRoadId() == _roadIdSelect)
                roadSelected = true;
            intsecIdSmall = pRoad->getIntsec(ROAD_IT_SMALL)->getIntsecId();
            intsecIdLarge = pRoad->getIntsec(ROAD_IT_LARGE)->getIntsecId();
            if (intsecIdLarge == _intsecIdSelect)
                changeShowSelect(intsecIdLarge, intsecIdSmall, pRoad->getRoadId());
            else
                changeShowSelect(intsecIdSmall, intsecIdLarge, pRoad->getRoadId());
            showStatus(event->pos().x(), event->pos().y(), MAP_NOID);

            //交差点モードならモード切り替え（メインウィンドウから）
            if (app.getMainWindow()->getEditMode() == MainWindow::intsec)
                app.getMainWindow()->setEditMode(MainWindow::road);

            //単路モードなら編集画面、単路付け替えモードでも選択済みなら編集画面
            else if (app.getMainWindow()->getEditMode() == MainWindow::road                   ||
                    (app.getMainWindow()->getEditMode() == MainWindow::roadRepl && roadSelected))
            {
                RoadDialog	rd(this);
                rd.init(pRoad);
                if (_roadDialogX != DIALOG_NOPOS)
                    rd.move(_roadDialogX, _roadDialogY);
                if (rd.exec() == QDialog::Accepted)
                {
                    if (rd.isDelete())
                    {
                        pMap->deleteRoad(pRoad->getRoadId());
                        changeShowSelect(MAP_NOID, MAP_NOID, MAP_NOID, true);
                    }
                    else if (rd.isDelIntsec())
                    {
                        Intsec* intsec1 = pRoad->getIntsec(ROAD_IT_SMALL);
                        Intsec* intsec2 = pRoad->getIntsec(ROAD_IT_LARGE);
                        pMap->deleteRoad(pRoad->getRoadId());
                        pMap->deleteIntsec(intsec1->getIntsecId());
                        pMap->deleteIntsec(intsec2->getIntsecId());
                        changeShowSelect(MAP_NOID, MAP_NOID, MAP_NOID, true);
                    }
                    repaintAll(true);
                }
                _roadDialogX = rd.x();
                _roadDialogY = rd.y();
            }
        }

        //単路選択なし
        else
        {
            //交差点モードなら交差点新規作成、選択変更とエラーチェックと表示、ここは全体再描画なし
            if (app.getMainWindow()->getEditMode() == MainWindow::intsec)
            {
                pIntsec = pMap->createIntsec();
                x = getMapX(_clickDragX);
                y = getMapY(_clickDragY);
                if (pIntsec == NULL)
                    QMessageBox::critical(this, tr(TITLE), tr("最大交差点IDが大きすぎます。"));
                if      (x < APP_POS_MIN || y < APP_POS_MIN )
                    QMessageBox::critical(this, tr(TITLE), tr("最大位置が小さすぎます。"));
                else if (x > APP_POS_MAX || y > APP_POS_MAX )
                    QMessageBox::critical(this, tr(TITLE), tr("最大位置が大きすぎます。"));
                else
                {
                    pIntsec->setMapPos(x, y, 0);
                    changeShowSelect(pIntsec->getIntsecId(), _intsecIdDest, _roadIdSelect);
                    //　showStatus　なしでも変わるが念のため
                    showStatus(event->pos().x(), event->pos().y(), pIntsec->getIntsecId());
                    pIntsec->checkError();
                    showIntsec(pIntsec);
//                  app.getMap()->debugTrace();
                }
            }
        }
    }
}