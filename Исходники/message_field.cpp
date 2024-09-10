InlineBotQuery ParseInlineBotQuery(not_null<const Ui::InputField*> field) {
	auto result = InlineBotQuery();

	const auto &text = field->getTextWithTags().text;
	const auto textLength = text.size();

	auto inlineUsernameStart = 1;
	auto inlineUsernameLength = 0;
	if (textLength > 2 && text[0] == '@' && text[1].isLetter()) {
		inlineUsernameLength = 1;
		for (auto i = inlineUsernameStart + 1; i != textLength; ++i) {
			const auto ch = text[i];
			if (ch.isLetterOrNumber() || ch.unicode() == '_') {
				++inlineUsernameLength;
				continue;
			} else if (!ch.isSpace()) {
				inlineUsernameLength = 0;
			}
			break;
		}
		auto inlineUsernameEnd = inlineUsernameStart + inlineUsernameLength;
		auto inlineUsernameEqualsText = (inlineUsernameEnd == textLength);
		auto validInlineUsername = false;
		if (inlineUsernameEqualsText) {
			validInlineUsername = text.endsWith(qstr("bot"));
		} else if (inlineUsernameEnd < textLength && inlineUsernameLength) {
			validInlineUsername = text[inlineUsernameEnd].isSpace();
		}
		if (validInlineUsername) {
			auto username = text.midRef(inlineUsernameStart, inlineUsernameLength);
			if (username != result.username) {
				result.username = username.toString();
				if (const auto peer = App::peerByName(result.username)) {
					if (const auto user = peer->asUser()) {
						result.bot = peer->asUser();
					} else {
						result.bot = nullptr;
					}
					result.lookingUpBot = false;
				} else {
					result.bot = nullptr;
					result.lookingUpBot = true;
				}
			}
			if (result.lookingUpBot) {
				result.query = QString();
				return result;
			} else if (result.bot && (!result.bot->botInfo
				|| result.bot->botInfo->inlinePlaceholder.isEmpty())) {
				result.bot = nullptr;
			} else {
				result.query = inlineUsernameEqualsText
					? QString()
					: text.mid(inlineUsernameEnd + 1);
				return result;
			}
		} else {
			inlineUsernameLength = 0;
		}
	}
	if (inlineUsernameLength < 3) {
		result.bot = nullptr;
		result.username = QString();
	}
	result.query = QString();
	return result;
}