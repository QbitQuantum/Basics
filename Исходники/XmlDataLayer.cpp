InvoiceData XmlDataLayer::invoiceSelectData(QString name, int type) {
	qDebug() << __FILE__ << __LINE__ << __FUNCTION__;

	InvoiceData o_invData;

	QDomDocument doc(sett().getInoiveDocName());
	QDomElement root;
	QDomElement nabywca;
	QDomElement product;
	QString fName = name;

	QFile file(sett().getInvoicesDir() + fName);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("file doesn't exist");
		return o_invData;
	} else {
		QTextStream stream(&file);
		if (!doc.setContent(stream.readAll())) {
			file.close();
			return o_invData;
		}
	}

	root = doc.documentElement();
	o_invData.frNr = root.attribute("no");
	o_invData.sellingDate = QDate::fromString(root.attribute("sellingDate"), sett().getDateFormat());
	o_invData.productDate = QDate::fromString(root.attribute("issueDate"),	sett().getDateFormat());

	QDomNode tmp;
	tmp = root.firstChild();
	tmp = tmp.toElement().nextSibling(); // nabywca
	nabywca = tmp.toElement();
	o_invData.customer = nabywca.attribute("name") + "," + nabywca.attribute(
			"city") + "," + nabywca.attribute("street") + "," + QObject::trUtf8("NIP: ")
			+ nabywca.attribute("tic");
			/* not required
			+ ", " + nabywca.attribute("account")
			+ ", " + nabywca.attribute("phone") + ", " + nabywca.attribute(
			"email") + ", " + nabywca.attribute("www")) */
	// kontrName->setCursorPosition(1);

	tmp = tmp.toElement().nextSibling(); // product
	product = tmp.toElement();

	o_invData.discount = product.attribute("discount").toInt();



	tmp = tmp.toElement().nextSibling();
	QDomElement additional = tmp.toElement();
	o_invData.additText = additional.attribute("text");
	int curPayment = sett().value("payments").toString().split("|").indexOf(additional.attribute("paymentType"));

	if (curPayment == sett().value("payments").toString().split("|").count() - 1) {
	    // disconnect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));

		// platCombo->setCurrentIndex(curPayment);

		// ; //  = new CustomPaymData();
		o_invData.custPaym.payment1 = additional.attribute("payment1");
		o_invData.custPaym.amount1  = additional.attribute("amount1").toDouble();
		o_invData.custPaym.date1    = QDate::fromString(additional.attribute("liabDate1"), sett().getDateFormat());
		o_invData.custPaym.payment2 = additional.attribute("payment2");
		o_invData.custPaym.amount2  = additional.attribute("amount2").toDouble();
		o_invData.custPaym.date2    = QDate::fromString(additional.attribute("liabDate2"), sett().getDateFormat());

		// connect(platCombo, SIGNAL(currentIndexChanged (QString)), this, SLOT(payTextChanged(QString)));
	} else {
		// platCombo->setCurrentIndex(curPayment);
	}

	o_invData.liabDate = QDate::fromString(additional.attribute("liabDate"), sett().getDateFormat());
	int curCurrency = sett().value("waluty").toString().split("|").indexOf(additional.attribute("currency"));
	o_invData.currencyTypeId = curCurrency;


    QFile db(sett().getInvoicesDir() + name);

    if (!db.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug("file doesn't exist");
         return o_invData;
    }

    QXmlQuery query;
    QString res;

    query.setFocus(&db);
    query.setQuery("//product");
    if ( ! query.isValid())
        return o_invData;

    query.evaluateTo(&res);
    db.close();

    QDomDocument productsDOMDocument;
    productsDOMDocument.setContent("" + res + "");
    QDomNodeList products = productsDOMDocument.elementsByTagName("product");

    for (int i = 0; i < products.count(); i++) {
        QDomElement product = products.at(i).toElement();
        o_invData.products[i] =
                ProductData(product.attribute("id").toInt(),
                            product.attribute("name"),
                            product.attribute("code"),
                            product.attribute("PKWiU"),
                            product.attribute("quantity").toDouble(),
                            product.attribute("quantityType"),
                            product.attribute("discount").toDouble(),
                            product.attribute("price").toDouble(),
                            product.attribute("nett").toDouble(),
                            product.attribute("vatBucket").toInt(),
                            product.attribute("gross").toDouble(),
                            additional.attribute("currency"));
    }
    return o_invData;
}