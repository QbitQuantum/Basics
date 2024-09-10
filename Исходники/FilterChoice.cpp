void FilterChoice::updateDisplay()
{
  std::vector<Filter*> filters;
  int num = _number->value();
  switch(_blurChoices->currentIndex())
  {
    case 0:
      filters = Filter::uniform(num);
      _number->show();
      _labelNumber->show();
      _labelNumber->setText("Number of Pixels");
      break;
    case 1:
      filters = Filter::gaussian(num);
      _number->show();
      _labelNumber->show();
      _labelNumber->setText("Coefficient");
      break;
    case 2:
      filters = Filter::prewitt(num);
      _number->show();
      _labelNumber->show();
      _labelNumber->setText("Number of Pixels");
      break;
    default:
      filters = _filters[_blurChoices->currentIndex()];
      _number->hide();
      _labelNumber->hide();
  }
  
  if(_blurChoices->currentIndex() > 5)
    _deleteButton->setEnabled(true);
  else
    _deleteButton->setEnabled(false);
  
  int height(0), width(0);
  
  for(unsigned int i = 0; i < filters.size(); i++)
  {
    if(height > 0)
      height++;
    height += filters[i]->height();
    if(filters[i]->width() > width)
      width = filters[i]->width();
  }
  _filterView->setRowCount(height);
  _filterView->setColumnCount(width);
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      QTableWidgetItem* item = new QTableWidgetItem("");
      item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
      _filterView->setItem(i, j, item);
    }
  }
  
  height = 0;
  for(unsigned int i = 0; i < filters.size(); i++)
  {
    for(int j = height; j < filters[i]->width() + height; j++)
    {
      for(int k = 0; k < filters[i]->height(); k++)
      {
        int value = (*filters[i])[j - height][k];
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        _filterView->setItem(j, k, item);
        _filterView->setColumnWidth(k, _filterView->rowHeight(0));
      }
    }
    
    height += filters[i]->width();
    for(int k = 0; k < filters[i]->height(); k++)
    {
      QTableWidgetItem* item = new QTableWidgetItem("");
      item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
      _filterView->setItem(height, k, item);
    }
    
    height++;
  }
  
  _filterView->resizeColumnsToContents();
  _filterView->resizeRowsToContents();
}