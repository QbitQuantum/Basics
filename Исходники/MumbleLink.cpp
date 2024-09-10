	bool MumbleLink::init() {
		assert(mumbleLinkedMemory == nullptr);
#ifdef WIN32
		priv->obj = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
		if (priv->obj == nullptr)
			return false;

		mumbleLinkedMemory = static_cast<MumbleLinkedMemory *>(MapViewOfFile(
			priv->obj, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(*mumbleLinkedMemory)));

		if (mumbleLinkedMemory == nullptr) {
			CloseHandle(priv->obj);
			priv->obj = nullptr;
			return false;
		}
#else
		std::string name = "/MumbleLink." + std::to_string(getuid());

		priv->fd = shm_open(name.c_str(), O_RDWR, S_IRUSR | S_IWUSR);

		if (priv->fd < 0) {
			return false;
		}

		mumbleLinkedMemory = static_cast<MumbleLinkedMemory *>(
			(mmap(nullptr, sizeof(*mumbleLinkedMemory), PROT_READ | PROT_WRITE,
				MAP_SHARED, priv->fd, 0)));

		if (mumbleLinkedMemory == MAP_FAILED) {
			mumbleLinkedMemory = nullptr;
			return false;
		}
#endif
		return true;
	}