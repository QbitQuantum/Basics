/** Renders the report as a page collection - the caller
 * is responsible for de-allocating the returned
 * collection
 *
 * copyright : (C) 2002-2008 InfoSiAL S.L.
 * email     : [email protected]
 *
 */
MPageCollection *MReportEngine::renderReport(int initRow, int initCol,
                                             MPageCollection *pages, uint flags)
{
  fillRecords_ = flags & MReportEngine::FillRecords;
  bool pageBreak = flags & MReportEngine::PageBreak;
  bool append = flags & MReportEngine::Append;
  cancelRender = false;
  currRecord_ = 0;
  csvData_ = QString::null;
  p->setStyleName(styleName_);

  // Create the page collection
  QPicture *currentPage = 0;
  QPicture *currentPageCopy = 0;
  bool lastPageFound = false;
  if (pages == 0) {
    pages = new MPageCollection(this);
    currPage = 0;
  } else {
    if (append && !pageBreak) {
      currX = leftMargin ;
      lastPageFound = true;
      currentPage = pages->getLastPage();
      p->painter()->end();
      currentPageCopy = new QPicture(*currentPage);
      p->painter()->begin(currentPage);
      currentPageCopy->play(p->painter());
      delete currentPageCopy;
    }
  }

  // Initialize the basic page data
  currHeight = pageHeight - (bottomMargin + pFooter->getHeight());
  currDate = QDate::currentDate();

  // Initialize the grand total array
  clearGrantTotals();

  for (int i = 0; i < rFooter->getCalcFieldCount(); i++)
    grandTotal->append(new QMemArray<double>);

  // Create the first page
  if (!lastPageFound)
    startPage(pages);
  unsigned int rowCount = records.length();

  if (rowCount <= 1)
    rowCount = 2;

  uint nRecord = 0;

  // Draw the details
  drawDetail(pages, 0, nRecord, initRow, initCol);

  // Finish the last page of the report
  endPage(pages);

  // Destroy the page painter
  p->painter()->end();

  // Set the page collection attributes
  pages->setPageDimensions(QSize(pageWidth, pageHeight));
  pages->setPageSize(pageSize);
  pages->setPageOrientation(pageOrientation);
  pages->setPrintToPos(printToPos);

  fillRecords_ = false;

  // Send final status
  emit signalRenderStatus(rowCount / 2);

  return pages;
}