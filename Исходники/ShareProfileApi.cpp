	void ShareProfileApi::parseProfile(ShareProfilePtr& aProfile, const json& j) {
		auto name = JsonUtil::getField<string>("name", j, false);

		auto token = ShareManager::getInstance()->getProfileByName(name);
		if (token && token != aProfile->getToken()) {
			JsonUtil::throwError("name", JsonUtil::ERROR_EXISTS, "Profile with the same name exists");
		}

		aProfile->setPlainName(name);
	}