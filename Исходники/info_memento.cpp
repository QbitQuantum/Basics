std::unique_ptr<ContentMemento> Memento::DefaultContent(
		not_null<Data::Feed*> feed,
		Section section) {
	switch (section.type()) {
	case Section::Type::Profile:
		return std::make_unique<FeedProfile::Memento>(feed);
	case Section::Type::Channels:
		return std::make_unique<Channels::Memento>(feed);
	}
	Unexpected("Wrong feed section in Info::Memento::DefaultContent()");
}