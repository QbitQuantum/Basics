void TextDataSourceDialog::loadFile(const QString &fileName)
{
    mFileName = fileName;
    QFile inputFile(mFileName);

    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;  //TODO: Add normal treatment

    ui->groupBox->setTitle(fileName + " contents");

    QTextStream in(&inputFile);
    int nLines = 0;

    QMap<QChar, int> symbolsCount;
    QStringList fileContents;
    while (!in.atEnd() && nLines < 10) {
        QString line = in.readLine();
        fileContents << line;
        ui->textBrowser->append("<font color=\"blue\"><b><i>" + QString::number(++nLines)
                                + ":</i></b></font>&nbsp;&nbsp;&nbsp;" + line);
        for (auto ch : line) {
            if (symbolsCount.find(ch) == symbolsCount.end()) {
                symbolsCount[ch] = 0;
            }
            symbolsCount[ch]++;
        }
    }
    if (!in.atEnd()) {
        ui->textBrowser->append("<font color=\"blue\"><b><i> ...</i></b></font> " );
    }
    //TODO: the stuff below is to move scrollBar to the top (doesn't seem to work), need to be fixed
    ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->minimum());

    //determine separator
    auto isValidSeparator = [] (QChar ch) {
      return !ch.isLetterOrNumber() && !ch.isSpace() && (ch != sDecimalMark)
              && (ch != '-') && (ch != '+');
    };
    int separatorCounter = 0;
    for (const auto& sym : symbolsCount.keys()) {
        if (isValidSeparator(sym)) {
            if (symbolsCount[sym] > separatorCounter) {
                separatorCounter = symbolsCount[sym];
                mFieldSeparator = sym.toLatin1();
            }
        }
    }
    ui->fieldSeparatorLineEdit->setText(QString(mFieldSeparator));

    auto countPercentageOfLetters = [separator = this->mFieldSeparator] (const QString& str) {
        int totalNumber = 0;
        int numberLetters = 0;
        for (auto i = str.begin(); i != str.end(); ++i) {
            if (*i != separator && ! i->isSpace()) {
                totalNumber++;
                if (i->isLetter()) {
                    numberLetters++;
                }
            }
        }
        return totalNumber ? (double)numberLetters / totalNumber : 0;
    };


    if (fileContents.size() > 0 && countPercentageOfLetters(fileContents[0]) > 0.5) {
        ui->namesLineComboBox->setCurrentValue(0);
        if (fileContents.size() > 1 && countPercentageOfLetters(fileContents[1]) > 0.5) {
            ui->descriptionLineComboBox->setCurrentValue(1);
            if (fileContents.size() > 2 && countPercentageOfLetters(fileContents[2]) > 0.5) {
                ui->unitsLineComboBox->setCurrentValue(2);
            }
        }
    }


}