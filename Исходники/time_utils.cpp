            QDate fromYYYYMMDD (const QString& yyyymmdd) {
                if (yyyymmdd.length() != YYYYMMDD_FORMAT.length())
                    throw "Invalid input. Provide date as yyyyMMdd (e.g. June 2, 2016 = '20160602')";

                for (QString::const_iterator chr (yyyymmdd.begin()); chr != yyyymmdd.end(); chr++) {
                    if (!chr->isDigit())
                        throw "Non digit character in input string.";
                }

                const QDate result = QDate::fromString(yyyymmdd, YYYYMMDD_FORMAT);

                if (!result.isValid())
                    throw "Invalid date input";

                return result;
            }