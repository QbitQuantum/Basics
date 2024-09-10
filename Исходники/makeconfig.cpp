void MakeConfig::onDataAvailable()
{
    QMutexLocker mtxlock(mtx);
    QByteArray data =  port->readAll();
    if(data[0]==13 || data[0]==10) return;

    buf.append(data);
qDebug()<<"state"<<state<<"buf="<<buf;
    if (state == stNone) return;
    if (state == stReadCurState) {
        ui->statusBar->showMessage(QString::fromLocal8Bit("Получение текущего состояния..."));
        if (!buf.contains(";")) return;
        ui->statusBar->showMessage(QString::fromLocal8Bit("Дешифровка текущего состояния..."));
        QString s = QString(buf);
        QStringList devs = s.split(QString(","));
        if (devs.count() < 2) {
            state = stNone;
            qDebug()<<"no sensor devices found";
            buf.clear();
            return;
        }
        QString cmd;
        for (int i=0; i< devs.count()-1; ++i ) {
            cmd.append(QString("iic %1,*;").arg(devs[i]));
        }
        qDebug()<<"iic cmd: "<<cmd;
        buf.clear();
        port->write(cmd.toLocal8Bit());
        state = stReadCurState2;
        return;
    } else if (state == stReadCurState2) {
        if (!buf.contains(";")) {
            return;
        }
        qDebug()<<"got iic data:"<<buf;
        QString data(buf.trimmed());
        data.chop(1);
        QStringList parts = data.split(",");
        if (parts.length() < 3) {
            qDebug()<<"bad data:"<<data;
            buf.clear();
            return;
        }
        int r=0;
        while (r < this->ui->tblConfig->rowCount()) {
            if (! (ui->tblConfig->item(r, 2) && ui->tblConfig->item(r, 3))) {
                ++r;
                continue;
            }
            if ( (ui->tblConfig->item(r, 3)->text() == parts[1]) && (ui->tblConfig->item(r, 2)->text() == parts[0]) ) {

                QTableWidgetItem *item= new QTableWidgetItem(parts[2]);
                ui->tblConfig->setItem(r, 10, item);
                break;
            }
            ++r;
        }//while
        buf = buf.remove(0, buf.indexOf(";") + 1);
    } else if (state == stSendConfigLines) {
        //qDebug()<<buf.contains("OK");
        if (buf.contains("OK")) {
            buf.clear();
            ui->statusBar->showMessage(QString::fromLocal8Bit("Отправляем строку конфигурации №%1").arg(lsi+1));
            this->sendConfigLine(++lsi);
        } else if (buf.contains("setup()")) {
            buf.clear();
            this->sendConfigLine(lsi);
        }
        return;
    }else if (stSendSensorsCount == state) {
        //qDebug()<<buf.contains("SET");
        if (buf.contains(("SET"))) {
            state = stSendPlantNames;
            this->lsi  = 0;
            ui->statusBar->showMessage(QString::fromLocal8Bit("Начинаем отправку названий растений..."));
            this->port->write("\7");
            this->port->flush();
            sleep(1);
            this->sendPlantName(lsi);
        }
        return;
    } else if (state == stSendPlantNames) {
        //qDebug()<<buf.contains("OK");
        if (buf.contains("OK")) {
            buf.clear();
            ui->statusBar->showMessage(QString::fromLocal8Bit("Отправка названия из строки %1").arg(lsi+1));
            this->sendPlantName(++lsi);
        }
        return;
    } else if (state == stGetW2Dsizes) {
        if (buf.contains(";")) {
            QRegExp re("^.*(\\d+)\\s*\\,\\s*(\\d+).*$");
            if (re.indexIn(buf) > -1) {
                qDebug()<<re.cap(1)<< re.cap(1).toInt()<<re.cap(2)<< re.cap(2).toInt();
                ui->spinX->setMaximum(re.cap(1).toInt());
                ui->spinY->setMaximum(re.cap(2).toInt());
            } else {
                qDebug()<<"not matched";
            }
            state = stNone;
        }
    } else if (state == stReadConfig) {
        if (buf.contains(";")) {
            if (last_index == -1) {
                qDebug()<<"got pot cnt";
                buf = buf.trimmed();
                buf.chop(1);
                pots_total = buf.toInt();
                last_index = 0;
                buf.clear();
                this->port->write(QString("pot get %1;\r\n").arg(last_index).toLocal8Bit());
                this->ui->tblConfig->setRowCount(0);
                this->ui->tblConfig->setRowCount(pots_total);
            } else if (buf.length() > 10 && buf.contains(",")) {
                buf = buf.trimmed();
                buf.chop(1);
                QStringList parts = buf.split(",");
                if (parts.length() >=14) {
                    QTableWidgetItem*item;
                    SETITEM(last_index, 0, parts[1]);//флаги
                    SETITEM(last_index, 1, parts[2]);//растение
                    SETITEM(last_index, 2, parts[3]);//чип
                    SETITEM(last_index, 3, parts[4]);//пин
                    SETITEM(last_index, 4, parts[5]);// Х
                    SETITEM(last_index, 5, parts[6]);// У
                    SETITEM(last_index, 6, parts[7]);// доза
                    SETITEM(last_index, 7, parts[8]);// программа
                    SETITEM(last_index, 8, parts[9]);// мин
                    SETITEM(last_index, 9, parts[10]);// макс
                    SETITEM(last_index, 10, QString("?"));// тек.знач-ие
                    SETITEM(last_index, 11, parts[13]);// вкл/выкл
                    SETITEM(last_index, 12, (parts[12]=="1"?QString::fromLocal8Bit("сушим"):QString::fromLocal8Bit("льём")));// состояние(полив/подсушка)
                    SETITEM(last_index, 13, parts[14]);// вылито
                    ++last_index;
                    PlantData pd;
                    pd.index = parts[0].toInt();
                    pd.flags = parts[1].toInt();
                    pd.name = parts[2];
                    pd.chip = parts[3].toInt();
                    pd.pin = parts[4].toInt();
                    pd.X = parts[5].toInt();
                    pd.Y = parts[6].toInt();
                    pd.portion = parts[7].toInt();
                    pd.pgm = parts[8].toInt();
                    pd.min = parts[9].toInt();
                    pd.max = parts[10].toInt();
                    pd.en = parts[13].toInt();
                    this->pots_data.push_back(pd);
                } else {
                    qDebug()<<"re-query pot "<<last_index;
                }
                buf.clear();
                if (last_index < pots_total) {
                    qDebug()<<"query pot "<<last_index;
                    this->port->write(QString("pot get %1;\r\n").arg(last_index).toLocal8Bit());
                    //this->port->flush();
                } else {
                    state = stGetW2Dsizes;
                    this->port->write("WSZ;\r\n");
                }
            } else {
                this->port->write(QString("pot get %1;\r\n").arg(last_index).toLocal8Bit());
                buf.clear();
            }
            return;
        } else {
            return;
        }
        if (!buf.contains(";;")) return;
        buf = buf.trimmed();
        qDebug()<<"READ CONFIG"<<"\n----\n"<<buf<<"\n-----";
        QRegExp re("\\{(\\d+)\\};");
        re.indexIn(buf);
        int n_rows = re.cap(1).toInt();
        this->ui->tblConfig->setRowCount(0);
        this->ui->tblConfig->setRowCount(n_rows);

        buf= buf.replace(re, "").trimmed();
        QStringList list = buf.split(";");
        qDebug()<<list;
        QRegExp il("^(.*)\\[(.*)\\]$");
        int r = 0;
        for (int i = 0; i < list.length(); ++i) {
            //qDebug()<<list[i];
            if (il.indexIn(list[i].trimmed()) > -1) {
                QString nums = il.cap(1), name = il.cap(2);
                nums = nums.replace(QRegExp("\\s+"), "");
                //qDebug()<<"nums:"<<nums;
                QStringList numz = nums.split(",");
                QTableWidgetItem*item;
                SETITEM(r, 0, name);
                SETITEM(r, 1, numz[0]);
                SETITEM(r, 2, numz[1]);
                SETITEM(r, 3, numz[2]);
                SETITEM(r, 4, numz[3]);
                SETITEM(r, 5, numz[4]);
                SETITEM(r, 6, numz[5]);
                SETITEM(r, 7, numz[6]);
                SETITEM(r, 8, numz[7]);
                ++r;
             //   qDebug()<<numz;
            }
        }
        buf.clear();
        state = stNone;
        return;
    }
    //QStringList lines = buf.split("\n");
    //first line -- cmd echo
    //qDebug()<<data<<data.contains(';');
    if (buf.contains(';')) {
        buf = buf.trimmed();
        //qDebug()<<buf;
        if (state == stDetectPinStep1) {
            //test1.resize(0);
        } else if(state == stDetectPinStep2) {
            //test2.resize(0);
        } else {
            ui->statusBar->showMessage(QString::fromLocal8Bit("Неправильный код состояния. Возможно, идёт отсылка/приём данных..."));
            data.clear();
            return;
        }
            QString str = QString(buf);
            QTextStream st(&str,  QIODevice::ReadOnly);
            int n;
            st>>n;
            //qDebug() << "n="<<n;
            for (int i = 0; i < n; ++i) {
                int val;
                st>>val;
                if (state == stDetectPinStep1) {
                    //test1.push_back(val);
                } else if (state ==stDetectPinStep2) {
                    //test2.push_back(val);
                }
            }
            if (state == stDetectPinStep1) {
                ui->statusBar->showMessage(QString::fromLocal8Bit("Готов к шагу 2"));
            } else if (state == stDetectPinStep2) {
                qDebug()<<"state"<<state<<"buf="<<buf;
              /*  if (test1.size()!=test2.size()) {
                    ui->statusBar->showMessage(QString::fromLocal8Bit("Ошибка: не совпадает размер данных"));
                    buf.clear();
                    //qDebug()<<"state=0, ln 216";
                    state = stNone;
                    return;
                }
                int max_df = 0, max_index=-1, _cdf;
                for (int i=0;i<test1.size(); ++i) {
                    _cdf = abs(test1.at(i)-test2.at(i));
                    if (_cdf > max_df) {
                        qDebug()<<"delta: "<<_cdf;
                        max_index = i;
                        max_df = _cdf;
                    }
                }
                if (max_index >=0 ) {
                    qDebug()<<"max_index "<<max_index;
                    int pins = ui->cbChipType->itemData((ui->cbChipType->currentIndex())).toInt();
                    qDebug()<<"max_index "<<max_index;
                    ui->statusBar->showMessage(QString::fromLocal8Bit("Чип %1 пин %2").arg(max_index/pins).arg(max_index%pins));
                    this->last_found = max_index;
                }
                state = stNone;
                //qDebug()<<"state=0, ln234";
                */
            }
    }