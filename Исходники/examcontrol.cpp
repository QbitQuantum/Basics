void ExamControl::updateStudentTable(QList<Student *> students)
{
    int numberLogin = 0;
    int numbersubmit = 0;
    tableWidget_student->setRowCount(students.count());
    for(int i = 0; i < students.count(); ++i){
        if(students.at(i)->getState() != QString("未登录"))
            numberLogin++;
        else if(students.at(i)->getState() == QString("已经交卷"))
            numbersubmit++;

        QTableWidgetItem *hostname = new QTableWidgetItem(students.at(i)->getHostname());
        QTableWidgetItem *id = new QTableWidgetItem(students.at(i)->getID());
        QTableWidgetItem *name = new QTableWidgetItem(students.at(i)->getName());
        QTableWidgetItem *grade = new QTableWidgetItem(QString::number(students.at(i)->getGrade()));
        QTableWidgetItem *_class = new QTableWidgetItem(QString::number(students.at(i)->getClass()));
        QTableWidgetItem *state = new QTableWidgetItem(students.at(i)->getState());

        if(state->text() == QString("未登录"))
        {
            state->setTextColor(QColor("red"));
        }

        tableWidget_student->setItem(i, 0, hostname);
        tableWidget_student->setItem(i, 1, id);
        tableWidget_student->setItem(i, 2, name);
        tableWidget_student->setItem(i, 3, grade);
        tableWidget_student->setItem(i, 4, _class);
        tableWidget_student->setItem(i, 5, state);
    }
    label_studentcount->setText(QString("共有%1名学生 已登录%2人 已交卷%3人").arg(students.count()).arg(numberLogin).arg(numbersubmit));
}