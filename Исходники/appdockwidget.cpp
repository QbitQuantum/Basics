void AppDockWidget::showBreakpoints1(struct BreakPointList* breakPointList, QString filename, int *number)
{

    struct BreakPointList *p = breakPointList;
    int i = *number;
    QTextBlock block = mainwindow->codeEditor->firstVisibleBlock();

    int height = (int)mainwindow->codeEditor->blockBoundingRect(block).height();

    QTableWidgetItem *item;
    ui.breakpointTableWidget->setColumnWidth(1, 120);//设置第一列的宽度为120

    while (p) {
        if (!p->flag) {
            p = p->next;
            continue;
        }

        int blocknumber = ceil(p->blockNumber / height) + 1;
        item = new QTableWidgetItem(QString::number(i + 1, 10));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);

        ui.breakpointTableWidget->setItem(i, 0, item);

        item = new QTableWidgetItem(
                    filename + " : " + QString::number(blocknumber, 10));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        ui.breakpointTableWidget->setItem(i, 1, item);

        if (p->flag) {
            item = new QTableWidgetItem("Enable");
            item->setTextAlignment(Qt::AlignHCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui.breakpointTableWidget->setItem(i, 2, item);
        } else {
            item = new QTableWidgetItem("Disable");
            item->setTextAlignment(Qt::AlignHCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui.breakpointTableWidget->setItem(i, 2, item);
        }
        if (p->threadid == -1 || p->threadid == -2) {
            item = new QTableWidgetItem("all");
            item->setTextAlignment(Qt::AlignHCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui.breakpointTableWidget->setItem(i, 3, item);
        } else
        {
            item = new QTableWidgetItem(
                        QString::number(p->threadid, 10) + "(" + QString::number(
                            p->truetid, 10) + ")");
            item->setTextAlignment(Qt::AlignHCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui.breakpointTableWidget->setItem(i, 3, item);
        }

        p = p->next;
        i++;
    }
    *number = i;
}