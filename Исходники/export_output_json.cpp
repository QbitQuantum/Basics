			|| file.skipReason != SkipReason::None);

		push(label, [&]() -> QByteArray {
			const auto pre = name.isEmpty() ? QByteArray() : name + ' ';
			switch (file.skipReason) {
			case SkipReason::Unavailable:
				return pre + "(File unavailable, please try again later)";
			case SkipReason::FileSize:
				return pre + "(File exceeds maximum size. "
					"Change data exporting settings to download.)";
			case SkipReason::FileType:
				return pre + "(File not included. "
					"Change data exporting settings to download.)";
			case SkipReason::None: return FormatFilePath(file);
			}
			Unexpected("Skip reason while writing file path.");
		}());
	};
	const auto pushPhoto = [&](const Image &image) {
		pushPath(image.file, "photo");
		if (image.width && image.height) {
			push("width", image.width);
			push("height", image.height);
		}
	};

	message.action.content.match([&](const ActionChatCreate &data) {
		pushActor();
		pushAction("create_group");
		push("title", data.title);
		pushUserNames(data.userIds);