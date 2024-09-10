///
/// reimplemented functions
///
void MemChartPrivate::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    drawBackground(&painter);
    drawCaption(&painter);
    drawFrame(&painter);
    drawLegend(&painter);
    drawHistogram(&painter);
    drawSelectedRegion(&painter);
}