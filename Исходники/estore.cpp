void estore::on_confirm_clicked()
{

    int num = ui->num->text().toInt();
    QSqlTableModel model;
    model.setTable("commodity");
    model.setFilter(tr("number = '%1'").arg(num));
    model.select();
    if(model.rowCount()==1)//查询到有一个结果
    {
        QString name =model.record(0).value("name").toString();
        QString description =model.record(0).value("description").toString();
        double primeprice = model.record(0).value("primeprice").toDouble();
        double saleprice = model.record(0).value("saleprice").toDouble();
        int column = model.record(0).value("column").toInt();
        int sum = model.record(0).value("sum").toInt();
        double discount = model.record(0).value("discount").toDouble();
        QString publishmentbrand =model.record(0).value("publishmentbrand").toString();
        QString ISBNmaterialcolumn =model.record(0).value("ISBNmaterialcolumn").toString();
        QString date =model.record(0).value("date").toString();
        QString pagenumbersizeweight =model.record(0).value("pagenumbersizeweight").toString();
        QString si = ui->sum->text();
        int suminput= si.toInt();
        int numflag1=1;
        for(int i=0;i<si.size();i++)
            if ((si[i]<'0')||(si[i]>'9'))
            {
                numflag1=0;
                break;
            }
        if(si.size()==0)
        {
            QMessageBox::critical(NULL, "错误","数量未填写！");
        }
        else if(numflag1==0)
        {
            QMessageBox::critical(NULL, "错误","数量填写格式错误！");

        }


        else if(suminput > sum )
        {
            QMessageBox::warning(NULL, tr("错误"), tr("输入商品数量大于库存！"));
        }
        else
        {
            confirm c(name, suminput);
            if(c.exec()==QDialog::Accepted)
            {

                if (addTrolley(num, name, description, primeprice, saleprice,column, suminput, discount, publishmentbrand, ISBNmaterialcolumn, date, pagenumbersizeweight))
                {
                    model.setData(model.index(0,6),sum-suminput);
                    model.submitAll();
                    QMessageBox::information(NULL, tr("成功"), tr("商品成功添加至购物车！"));
                    accept();
                }
            }

        }

    }else
    {
        QMessageBox::warning(NULL, tr("错误"), tr("未查询到商品！"));
    }
}