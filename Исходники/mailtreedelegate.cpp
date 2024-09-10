	QWidget* MailTreeDelegate::createEditor (QWidget *parent,
			const QStyleOptionViewItem& option, const QModelIndex& index) const
	{
		const auto& actionsVar = index.data (MailModel::MailRole::MessageActions);
		if (actionsVar.isNull ())
			return nullptr;

		const auto& actionInfos = actionsVar.value<QList<MessageListActionInfo>> ();
		if (actionInfos.isEmpty ())
			return nullptr;

		const auto& id = index.data (MailModel::MailRole::ID).toByteArray ();

		const auto container = new QToolBar { parent };
		auto style = new NullMarginsStyle;
		style->setParent (container);
		container->setStyle (style);
		for (const auto& actInfo : actionInfos)
			BuildAction (std::bind (Loader_, id), container, actInfo);

		Util::ExecuteLater ([=] { updateEditorGeometry (container, option, index); });

		return container;
	}