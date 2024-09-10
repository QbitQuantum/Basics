int CUnitHandler::TestUnitBuildSquare(
	const BuildInfo& buildInfo,
	CFeature*& feature,
	int allyteam,
	std::vector<float3>* canbuildpos,
	std::vector<float3>* featurepos,
	std::vector<float3>* nobuildpos,
	const std::vector<Command>* commands)
{
	feature = NULL;

	const int xsize = buildInfo.GetXSize();
	const int zsize = buildInfo.GetZSize();
	const float3 pos = buildInfo.pos;

	const int x1 = (int) (pos.x - (xsize * 0.5f * SQUARE_SIZE));
	const int x2 = x1 + xsize * SQUARE_SIZE;
	const int z1 = (int) (pos.z - (zsize * 0.5f * SQUARE_SIZE));
	const int z2 = z1 + zsize * SQUARE_SIZE;
	const float h = GetBuildHeight(pos, buildInfo.def);

	int canBuild = 2;

	if (buildInfo.def->needGeo) {
		canBuild = 0;
		std::vector<CFeature*> features = qf->GetFeaturesExact(pos, max(xsize, zsize) * 6);

		for (std::vector<CFeature*>::iterator fi = features.begin(); fi != features.end(); ++fi) {
			if ((*fi)->def->geoThermal
				&& fabs((*fi)->pos.x - pos.x) < (xsize * 4 - 4)
				&& fabs((*fi)->pos.z - pos.z) < (zsize * 4 - 4)) {
				canBuild = 2;
				break;
			}
		}
	}

	if (commands != NULL) {
		//! unsynced code
		for (int x = x1; x < x2; x += SQUARE_SIZE) {
			for (int z = z1; z < z2; z += SQUARE_SIZE) {
				int tbs = TestBuildSquare(float3(x, pos.y, z), buildInfo.def, feature, gu->myAllyTeam);

				if (tbs) {
					std::vector<Command>::const_iterator ci = commands->begin();

					for (; ci != commands->end() && tbs; ci++) {
						BuildInfo bc(*ci);

						if (std::max(bc.pos.x - x - SQUARE_SIZE, x - bc.pos.x) * 2 < bc.GetXSize() * SQUARE_SIZE &&
							std::max(bc.pos.z - z - SQUARE_SIZE, z - bc.pos.z) * 2 < bc.GetZSize() * SQUARE_SIZE) {
							tbs = 0;
						}
					}

					if (!tbs) {
						nobuildpos->push_back(float3(x, h, z));
						canBuild = 0;
					} else if (feature || tbs == 1) {
						featurepos->push_back(float3(x, h, z));
					} else {
						canbuildpos->push_back(float3(x, h, z));
					}

					canBuild = min(canBuild, tbs);
				} else {
					nobuildpos->push_back(float3(x, h, z));
					canBuild = 0;
				}
			}
		}
	} else {
		for (int x = x1; x < x2; x += SQUARE_SIZE) {
			for (int z = z1; z < z2; z += SQUARE_SIZE) {
				canBuild = min(canBuild, TestBuildSquare(float3(x, h, z), buildInfo.def, feature, allyteam));

				if (canBuild == 0) {
					return 0;
				}
			}
		}
	}

	return canBuild;
}