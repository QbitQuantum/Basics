void Dialog_editPersInfo::inserSkillIntoList(QString skillName, int skillId)
{
    QLabel* skillVal  = new QLabel(skillName);

    QPushButton* delButton  = new QPushButton(QString("Видалити"));
    delButton->setCursor(Qt::PointingHandCursor);

    int rowNumber = ui->layout_persSkills->rowCount();
    ui->layout_persSkills->addWidget(skillVal, rowNumber, 0);
    //ui->layout_persSkills->addWidget(delButton, rowNumber, 1);

    skills.append(skillId);
    connect(delButton, SIGNAL(clicked()), this, SLOT( removeSkill() ));
}