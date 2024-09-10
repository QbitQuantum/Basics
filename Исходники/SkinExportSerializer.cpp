	void SkinExportSerializer::fillRegionData(DataPtr _data, pugi::xml_node _node)
	{
		pugi::xpath_node_set regions = _node.select_nodes("BasisSkin[@type=\"SubSkin\"or@type=\"TileRect\"]");
		for (pugi::xpath_node_set::const_iterator region = regions.begin(); region != regions.end(); region ++)
		{
			DataPtr regionData = NULL;

			MyGUI::Align align = MyGUI::Align::parse((*region).node().attribute("align").value());

			if (align.isLeft() && align.isTop())
				regionData = getChildData(_data, "Region", "Left Top");
			else if (align.isLeft() && align.isVStretch())
				regionData = getChildData(_data, "Region", "Left");
			else if (align.isLeft() && align.isBottom())
				regionData = getChildData(_data, "Region", "Left Bottom");

			else if (align.isHStretch() && align.isTop())
				regionData = getChildData(_data, "Region", "Top");
			else if (align.isHStretch() && align.isVStretch())
				regionData = getChildData(_data, "Region", "Center");
			else if (align.isHStretch() && align.isBottom())
				regionData = getChildData(_data, "Region", "Bottom");

			else if (align.isRight() && align.isTop())
				regionData = getChildData(_data, "Region", "Right Top");
			else if (align.isRight() && align.isVStretch())
				regionData = getChildData(_data, "Region", "Right");
			else if (align.isRight() && align.isBottom())
				regionData = getChildData(_data, "Region", "Right Bottom");

			if (regionData == nullptr)
				continue;

			regionData->setPropertyValue("Visible", "True");

			std::string type = (*region).node().attribute("type").value();
			if (type == "TileRect")
			{
				bool vert = MyGUI::utility::parseValue<bool>((*region).node().select_single_node("State/Property[@key=\"TileV\"]/@value").attribute().value());
				bool horz = MyGUI::utility::parseValue<bool>((*region).node().select_single_node("State/Property[@key=\"TileH\"]/@value").attribute().value());

				if (vert && !horz)
					type = "TileRect Vert";
				else if (!vert && horz)
					type = "TileRect Horz";
			}

			regionData->setPropertyValue("Type", type);
		}

		pugi::xpath_node regionText = _node.select_single_node("BasisSkin[@type=\"SimpleText\"or@type=\"EditText\"]");
		if (!regionText.node().empty())
		{
			DataPtr regionData = getChildData(_data, "RegionText", "Text");

			if (regionData != nullptr)
			{
				regionData->setPropertyValue("Visible", "True");

				std::string type = regionText.node().attribute("type").value();
				regionData->setPropertyValue("Type", type);

				MyGUI::IntCoord offset = MyGUI::IntCoord::parse(regionText.node().attribute("offset").value());
				regionData->setPropertyValue("Coord", offset);

				MyGUI::Align align = MyGUI::Align::parse(regionText.node().attribute("align").value());
				regionData->setPropertyValue("Align", align);
			}
		}
	}