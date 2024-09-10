void ListEntityDialog::createEntity()
{
    CreateEntityDialog dialog(m_container, QString(), this);

    if (dialog.exec() == CreateEntityDialog::Accepted)
    {
        if (m_container->transaction())
        {
            Entity entity(m_container->createEntity(dialog.type(), dialog.name(), dialog.title()));

            if (entity.isValid())
                if (entity.type() == Entity::Composite)
                {
                    bool ok = true;

                    for (CreateEntityDialog::size_type i = 0, size = dialog.size(); i < size; ++i)
                        if (!m_container->addProperty(entity, dialog.property(i), dialog.propertyName(i)))
                        {
                            ok = false;
                            QMessageBox::critical(this, tr("Error"), toUnicode(m_container->lastError()));
                            break;
                        }

                    if (ok)
                        if (m_container->commit())
                            m_model.add(entity);
                        else
                        {
                            m_container->rollback();
                            QMessageBox::critical(this, tr("Error"), toUnicode(m_container->lastError()));
                        }
                }
                else
                    if (m_container->commit())
                        m_model.add(entity);
                    else
                    {
                        m_container->rollback();
                        QMessageBox::critical(this, tr("Error"), toUnicode(m_container->lastError()));
                    }
            else
            {
                m_container->rollback();
                QMessageBox::critical(this, tr("Error"), toUnicode(m_container->lastError()));
            }
        }
        else
            QMessageBox::critical(this, tr("Error"), toUnicode(m_container->lastError()));
    }
}