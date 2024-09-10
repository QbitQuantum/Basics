void CDialogSkinAuto::LoadSkel()
{
	const string skel = QFileDialog::getOpenFileName(this, tr("Charger un squelette"),
		"Model/", tr("Fichier squelette (*.chr)"));

	if (!skel.isEmpty())
	{
		QFileInfo fileInfo(skel);
		ModelMng->SetModelPath(fileInfo.path() % '/');
		CSkeleton* skl = ModelMng->GetSkeleton(fileInfo.fileName());

		if (skl)
		{
			Delete(m_mesh->m_skeleton);
			m_mesh->m_skeleton = skl;
			DeleteArray(m_mesh->m_bones);
			ui.bonesList->clear();
			m_items.clear();

			ui.skelName->setText(fileInfo.fileName());

			m_mesh->m_bones = new D3DXMATRIX[skl->GetBoneCount() * 2];
			m_mesh->m_invBones = m_mesh->m_bones + skl->GetBoneCount();
			skl->ResetBones(m_mesh->m_bones, m_mesh->m_invBones);

			QList<QTreeWidgetItem*> items;

			QTreeWidgetItem* item;
			Bone* bone;
			for (int i = 0; i < skl->GetBoneCount(); i++)
			{
				bone = &skl->m_bones[i];
				item = new QTreeWidgetItem(QStringList(bone->name));
				item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
				item->setCheckState(0, Qt::Unchecked);
				item->setData(0, Qt::UserRole + 1, QVariant(i));
				m_items[i] = item;

				if (bone->parentID == -1)
					items.append(item);
				else
					m_items[bone->parentID]->addChild(item);
			}

			ui.bonesList->insertTopLevelItems(0, items);
			ui.bonesList->expandAll();

			ui.okSkel->setEnabled(true);
		}
	}
}