bool LogChangeWidget::populateLog(const QString &repository, const QString &commit, LogFlags flags)
{
    const QString currentCommit = this->commit();
    int selected = currentCommit.isEmpty() ? 0 : -1;
    if (const int rowCount = m_model->rowCount())
        m_model->removeRows(0, rowCount);

    // Retrieve log using a custom format "Sha1:Subject [(refs)]"
    GitClient *client = GitPlugin::instance()->gitClient();
    QStringList arguments;
    arguments << QLatin1String("--max-count=1000") << QLatin1String("--format=%h:%s %d");
    arguments << (commit.isEmpty() ? QLatin1String("HEAD") : commit);
    if (!(flags & IncludeRemotes))
        arguments << QLatin1String("--not") << QLatin1String("--remotes");
    QString output;
    if (!client->synchronousLog(repository, arguments, &output, 0, VcsBasePlugin::NoOutput))
        return false;
    foreach (const QString &line, output.split(QLatin1Char('\n'))) {
        const int colonPos = line.indexOf(QLatin1Char(':'));
        if (colonPos != -1) {
            QList<QStandardItem *> row;
            for (int c = 0; c < ColumnCount; ++c) {
                QStandardItem *item = new QStandardItem;
                item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                if (line.endsWith(QLatin1Char(')'))) {
                    QFont font = item->font();
                    font.setBold(true);
                    item->setFont(font);
                }
                row.push_back(item);
            }
            const QString sha1 = line.left(colonPos);
            row[Sha1Column]->setText(sha1);
            row[SubjectColumn]->setText(line.right(line.size() - colonPos - 1));
            m_model->appendRow(row);
            if (selected == -1 && currentCommit == sha1)
                selected = m_model->rowCount() - 1;
        }
    }
    setCurrentIndex(m_model->index(selected, 0));
    return true;
}