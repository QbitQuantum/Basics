void dspCountSlipsByWarehouse::sFillList()
{
  if (DEBUG)
    qDebug("dspCountSlipsByWarehouse::sFillList() about to populate _cntslip");

  display::sFillList();

  if (_numericSlips->isChecked() && list()->topLevelItemCount() > 1)
  {
    if (DEBUG)
      qDebug("dspCountSlipsByWarehouse::sFillList() looking for slip # gaps "
             "in %d items", list()->topLevelItemCount());
    XTreeWidgetItem *last =list()->topLevelItem(0);
    int slipNumber = last->rawValue("slipnumber").toInt();
    for (int i = 1; i < list()->topLevelItemCount(); i++)
    {
      XTreeWidgetItem *curr = list()->topLevelItem(i);
      if (DEBUG)
        qDebug("row %d has slipNumber %d and current %d",
               i, slipNumber, curr->rawValue("slipnumber").toInt());
      if (slipNumber == (curr->rawValue("slipnumber").toInt() - 1) || slipNumber == -1)
        slipNumber = curr->rawValue("slipnumber").toInt();
      else if (slipNumber >= 0)
      {
        if (slipNumber == curr->rawValue("slipnumber").toInt() - 2)
          curr = new XTreeWidgetItem( list(), last, -1,
                                    QVariant("----"), "----", "----", "----",
                                    tr("Missing Slip #%1").arg(slipNumber + 1),
                                    "----", "----", "----" );
        else
          curr = new XTreeWidgetItem( list(), last, -1,
                                    QVariant("----"), "----", "----", "----",
                                    tr("Missing Slips #%1 to #%2").arg(slipNumber + 1).arg(curr->rawValue("slipnumber").toInt() - 1),
                                    "----", "----", "----" );

        curr->setTextColor(namedColor("error"));
        slipNumber = -1;
        //i++; // 'cause we just added an item!
      }
      last = curr;
    }
  }
}