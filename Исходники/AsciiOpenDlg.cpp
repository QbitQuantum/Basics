void AsciiOpenDlg::updateTable(const QString &separator)
{
	tableWidget->setEnabled(false);
	extractSFNamesFrom1stLineCheckBox->setEnabled(false);
	m_headerLine.clear();

	if (m_filename.isEmpty())
	{
		tableWidget->clear();
        return;
	}

    if (separator.length()<1)
    {
        asciiCodeLabel->setText("Enter a valid character!");
        buttonBox->setEnabled(false);
		tableWidget->clear();
		m_invalidColumns = true;
        return;
    }

	//we open the file in ASCII mode
	FILE* pFile = fopen(qPrintable(m_filename),"rt");
	if (!pFile)
	{
		tableWidget->clear();
		m_invalidColumns = true;
        return;
	}

    //buffer
	char line[MAX_ASCII_FILE_LINE_LENGTH];      //last read line

    //we skip first lines (if needed)
	unsigned i;
    for (i=0;i<m_skippedLines;++i)
	{
        if (fgets(line, MAX_ASCII_FILE_LINE_LENGTH, pFile))
		{
			//we keep track of the first line
			if (i==0)
				m_headerLine = QString(line);
		}
		else
		{
			fclose(pFile);
			tableWidget->clear();
			m_invalidColumns = true;
            return;
		}
	}

    //new separator
    m_separator = separator[0];
    asciiCodeLabel->setText(QString("(ASCII code: %1)").arg(m_separator.unicode()));
	//if the old setup has less than 3 columns, we forget it
	if (m_columnsCount<3)
	{
		tableWidget->clear();
		m_columnsCount=0;
	}
    tableWidget->setRowCount(DISPLAYED_LINES+1);    //+1 for first line shifting

	unsigned lineCount = 0;			//number of lines read
	unsigned totalChars = 0;        //total read characters (for stats)
	unsigned columnsCount = 0;		//max columns count per line

	std::vector<bool> valueIsNumber;	//identifies columns with numbers only [mandatory]
	std::vector<bool> valueIsBelowOne;	//identifies columns with values between -1 and 1 only
	std::vector<bool> valueIsInteger;	//identifies columns with integer values only
	std::vector<bool> valueIsBelow255;	//identifies columns with integer values between 0 and 255 only

	while ((lineCount<LINES_READ_FOR_STATS) && fgets(line, MAX_ASCII_FILE_LINE_LENGTH, pFile))
	{
        //we convert char buffer to a QString object
		QString str(line);

        //we recognize "//" as comment
		if (line[0]!='/' || line[1]!='/')
		{
			QStringList parts = str.trimmed().split(m_separator,QString::SkipEmptyParts);
            unsigned partsCount = (unsigned)parts.size();
            if (partsCount>MAX_COLUMNS)
                partsCount=MAX_COLUMNS;

            if (lineCount<DISPLAYED_LINES)
            {
                //do we need to add one or several new columns?
                if (partsCount>columnsCount)
                {
					//we also extend vectors
					for (i=columnsCount;i<partsCount;++i)
					{
						valueIsNumber.push_back(true);
						valueIsBelowOne.push_back(true);
						valueIsBelow255.push_back(true);
						valueIsInteger.push_back(true);
					}

					tableWidget->setColumnCount(partsCount);
                    columnsCount=partsCount;
                }

                //we fill row with extracted parts
                for (i=0;i<partsCount;++i)
                {
                    QTableWidgetItem *newItem = new QTableWidgetItem(parts[i]);

					//test values
					bool isANumber = false;
					double value = parts[i].toDouble(&isANumber);
					if (!isANumber)
					{
						valueIsNumber[i]	= false;
						valueIsBelowOne[i]	= false;
						valueIsInteger[i]	= false;
						valueIsBelow255[i]	= false;
						newItem->setBackground(QBrush(QColor(255,160,160)));
					}
					else
					{
						double intPart, fracPart;
						fracPart = modf(value,&intPart);

						valueIsBelowOne[i]	= valueIsBelowOne[i] && (fabs(value)<=1.0);
						valueIsInteger[i]	= valueIsInteger[i] && (fracPart == 0.0);
						valueIsBelow255[i]	= valueIsBelow255[i] && (valueIsInteger[i] && (intPart >= 0.0 && value<=255.0));
					}

					tableWidget->setItem(lineCount+1, i, newItem); //+1 for first line shifting
                }
            }

            totalChars += (str.size()+1); //+1 for return char at eol

            ++lineCount;
		}
	}

	fclose(pFile);
	pFile=0;

	if (lineCount==0 || columnsCount==0)
	{
		m_averageLineSize = -1.0;
		tableWidget->clear();
		m_invalidColumns = true;
        return;
	}

	//average line size
	m_averageLineSize = double(totalChars)/double(lineCount);

    //we add a type selector for each column
	QStringList propsText;
	for (i=0; i<ASCII_OPEN_DLG_TYPES_NUMBER; i++)
        propsText << QString(ASCII_OPEN_DLG_TYPES_NAMES[i]);

	//remove unnecessary columns
	while (columnsCount<m_columnsCount)
		tableWidget->removeColumn(--m_columnsCount);
	for (i=lineCount+1;i<=DISPLAYED_LINES;++i)
		tableWidget->removeRow(i);

    int columnWidth = (tableWidget->width()*9) / (columnsCount*10);
    columnWidth = std::max(columnWidth,80);

	//Icons
	const QIcon xIcon(QString::fromUtf8(":/CC/Types/images/types/x_coordinate.png"));
	const QIcon yIcon(QString::fromUtf8(":/CC/Types/images/types/y_coordinate.png"));
	const QIcon zIcon(QString::fromUtf8(":/CC/Types/images/types/z_coordinate.png"));
	const QIcon NormIcon(QString::fromUtf8(":/CC/Types/images/types/normal.png"));
	const QIcon RGBIcon(QString::fromUtf8(":/CC/Types/images/types/rgb_color.png"));
	const QIcon GreyIcon(QString::fromUtf8(":/CC/Types/images/types/gray_color.png"));
	const QIcon ScalarIcon(QString::fromUtf8(":/CC/Types/images/types/scalar_field.png"));
	const QIcon PositiveScalarIcon(QString::fromUtf8(":/CC/Types/images/types/positive_scalar_field.png"));

	unsigned assignedXYZ = 0;
	unsigned assignedNorm = 0;
	unsigned assignedRGB = 0;
	for (i=0;i<columnsCount;i++)
	{
		QComboBox* columnHeader = static_cast<QComboBox*>(tableWidget->cellWidget(0,i));
		QComboBox* _columnHeader = columnHeader;
		if (!columnHeader)
		{
			columnHeader = new QComboBox();
			columnHeader->addItems(propsText);
			columnHeader->setMaxVisibleItems(ASCII_OPEN_DLG_TYPES_NUMBER);
			columnHeader->setCurrentIndex(0);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_X,xIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_Y,yIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_Z,zIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_NX,NormIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_NY,NormIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_NZ,NormIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_R,RGBIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_G,RGBIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_B,RGBIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_Grey,GreyIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_Scalar,ScalarIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_Positive_Scalar,PositiveScalarIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_RGB32i,RGBIcon);
			columnHeader->setItemIcon(ASCII_OPEN_DLG_RGB32f,RGBIcon);

			connect(columnHeader, SIGNAL(currentIndexChanged(int)), this, SLOT(columnsTypeHasChanged(int)));
		}

		if (valueIsNumber[i])
		{
			//first time? let's try to assign each column a type
			if ((m_invalidColumns || m_columnsCount==0) && columnsCount>1)
			{
				columnHeader->blockSignals(true);
				//by default, we assume that the first columns are always X,Y and Z
				if (assignedXYZ<3)
				{
					//in rare cases, the first column is an index
					if (assignedXYZ==0 && valueIsInteger[i] && (i+1<columnsCount) && !valueIsInteger[i+1])
					{
						//we skip it
					}
					else
					{
						++assignedXYZ;
						columnHeader->setCurrentIndex(assignedXYZ);
					}
				}
				else
				{
					//looks like RGB?
					if (valueIsBelow255[i] && assignedRGB<3 && (i+2-assignedRGB < columnsCount)
						&& (assignedRGB > 0 || (valueIsBelow255[i+1] && valueIsBelow255[i+2]))) //make sure that next values are also ok!
					{
						columnHeader->setCurrentIndex(ASCII_OPEN_DLG_R+assignedRGB);
						++assignedRGB;
					}
					else if (valueIsBelowOne[i] && assignedNorm<3 && (i+2-assignedNorm < columnsCount)
						&& (assignedNorm > 0 || (valueIsBelowOne[i+1] && valueIsBelowOne[i+2]))) //make sure that next values are also ok!
					{
						columnHeader->setCurrentIndex(ASCII_OPEN_DLG_NX+assignedNorm);
						++assignedNorm;
					}
					else
					{
						//maybe it's a scalar?
						columnHeader->setCurrentIndex(ASCII_OPEN_DLG_Scalar);
					}
				}
				columnHeader->blockSignals(false);
			}
		}

		if (!_columnHeader)
			tableWidget->setCellWidget(0,i,columnHeader);
		tableWidget->setColumnWidth(i,columnWidth);
	}