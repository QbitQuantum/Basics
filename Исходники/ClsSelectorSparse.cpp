int iqrfe::ClsSelectorSparse::validateCell(int iR, int iC, bool bAllowEmpty) {
    int iReturn = -1;

//ZZZ    QString qstr = qtablePoints->text( iR, iC ).stripWhiteSpace();
    QTableWidgetItem *qtwi = qtablePoints->itemAt ( iR, iC);
    if(qtwi!=NULL){
	QString qstr = qtwi->text().trimmed();
	if(!qstr.length()<=0){
	    for(unsigned int jj=0; jj<qstr.length(); jj++) {
		QChar qc = qstr[jj];
		if(!qc.isDigit()){
//ZZZ		qtablePoints->setText(iR, iC, "invalid entry");
		    QTableWidgetItem *newItem= new QTableWidgetItem("invalid entry");
		    qtablePoints->setItem(iR, iC, newItem);
		    return iReturn;
		}
	    }
	    try{
		iReturn = iqrUtils::string2int(qstr.toStdString());
	    }
	    catch(...){
//ZZZ	    qtablePoints->setText(iR, iC, "invalid entry");
		QTableWidgetItem *newItem= new QTableWidgetItem("invalid entry");
		qtablePoints->setItem(iR, iC, newItem);
	    }
	} else {
	    if(!bAllowEmpty){
//ZZZ	    qtablePoints->setText(iR, iC, "invalid entry");
		QTableWidgetItem *newItem= new QTableWidgetItem("invalid entry");
		qtablePoints->setItem(iR, iC, newItem);
	    }
	}
	return iReturn;
    }
}