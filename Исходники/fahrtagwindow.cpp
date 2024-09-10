void FahrtagWindow::itemChanged(QListWidgetItem *item , AActivity::Category kat, bool isExtern)
{
    /* item: Das Item das Verändert wurde */
    /* kat: Die Kategorie, auf die gebucht wird */
    /* is Extern: Gibt an ob die Person extern ist */
    // Laden der Informationen zur geänderten Person
    QString text = item->text();
    QStringList liste = text.split(QRegExp("\\s*;\\s*"));
    QString name = liste.at(0);
    QString bem = "";
    QTime start = QTime(0,0);
    QTime ende = QTime(0,0);
    QString aufgabe = AActivity::getStringFromCategory(kat);
    if (liste.length() > 1) {
        bem = liste.at(1);
    }
    if (bem.toUpper().contains("EXTERN")) isExtern = true;

    Person *person;

    if (isExtern) {
        person = new Person(name);
        person->setAusbildungTf(true);
        person->setAusbildungZf(true);
        person->setAusbildungRangierer(true);
        person->addActivity(fahrtag, kat);
        fahrtag->addPerson(person, bem, start, ende, aufgabe);

        if (listeMitNamen->contains(item)) {
            fahrtag->removePerson(listeMitNamen->value(item));
            listeMitNamen->remove(item);
            ui->tablePersonen->removeRow(ui->tablePersonen->row(listToTable->value(item)));
            namen->remove(name);
        }
        return;
    } else if (!fahrtag->getPersonal()->personExists(name)) {
        QMessageBox::information(this, "Person nicht gefunden", "Die eingegebene Person konnte nicht gefunden werden!");
        return;
    }

    person = fahrtag->getPersonal()->getPerson(name);

    // Die Person ist in Ordnung und kann jetzt übernommen werden
    name = person->getName();

    if (listeMitNamen->contains(item)) {
        if (listeMitNamen->value(item) == name) {
            // Der Name hat sich nicht verändert, lediglich die Bemerkungen updaten
            fahrtag->updatePersonBemerkung(person, bem);
            return;
        } else {
            // Der Name wurde verändert -> alte Person löschen und dann verfahren, als ob person nicht vorhanden wäre
            QString nameAlt = listeMitNamen->value(item);
            AActivity::Infos *info = fahrtag->getIndividual(person);
            start = info->beginn;
            ende = info->ende;
            aufgabe = info->aufgabe;
            fahrtag->removePerson(nameAlt); // Alte Person von Fahrtag lösen

            listeMitNamen->remove(item);
            ui->tablePersonen->removeRow(ui->tablePersonen->row(listToTable->value(item)));
            listToTable->remove(item);
        }
    }

    if (fahrtag->addPerson(person, bem, start, ende, aufgabe) == ManagerPersonal::FalscheQualifikation) {
        QMessageBox::warning(this, "Fehlene Qualifikation", "Die Aufgabe kann/darf nicht von der angegebenen Person übernommen werden, da dies eine Aufgabe ist, welche eine Ausbildung voraussetzt.");
        return;
    }
    person->addActivity(fahrtag, kat);

    listeMitNamen->insert(item, name);
    // Zeile für die Person in die Tabelle einfügen
    ui->tablePersonen->insertRow(0);
    QTableWidgetItem *zelleName = new QTableWidgetItem(name);
    zelleName->setFlags(Qt::NoItemFlags);
    ui->tablePersonen->setItem(0,0,zelleName);

    if (start != QTime(0, 0)) {
        ui->tablePersonen->setItem(0, 1, new QTableWidgetItem(start.toString("hh:mm")));
    }
    if (ende != QTime(0,0)) {
        ui->tablePersonen->setItem(0, 2, new QTableWidgetItem(ende.toString("hh:mm")));
    }

    QTableWidgetItem *zelleAufgabe = new QTableWidgetItem(AActivity::getStringFromCategory(kat));
    zelleAufgabe->setFlags(Qt::NoItemFlags);
    ui->tablePersonen->setItem(0,3,zelleAufgabe);
    listToTable->insert(item, zelleName);
    namen->insert(name);
}