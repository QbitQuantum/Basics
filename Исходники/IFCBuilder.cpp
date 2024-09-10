IFCBuilder::IFCBuilder() {
	model = 0; 
	saveIfx = false;
	aggrRelatedElements = NULL;
	aggrRepresentations = NULL;

	ifcApplicationInstance = 0,
	ifcBuildingInstance = 0,
	ifcBuildingInstancePlacement = 0,
	ifcBuildingStoreyInstance = 0,
	ifcBuildingStoreyInstancePlacement = 0,
	ifcBuildOwnerHistoryInstance = 0,
	ifcConversionBasedUnitInstance = 0,
	ifcDimensionalExponentsInstance = 0,
	ifcGeometricRepresentationContextInstance = 0,
	ifcOrganizationInstance = 0,
	ifcPersonAndOrganizationInstance = 0,
	ifcPersonInstance = 0,
	ifcProjectInstance = 0,
	ifcSiteInstance = 0,
	ifcSiteInstancePlacement = 0,
	ifcUnitAssignmentInstance = 0;

	char ifcSchemaName[30] = "../IFC2X3_Final.exp";

	if ( !PathFileExists(ifcSchemaName) ) {
		std::cerr << "IFC schema file is not accessible" << std::endl;
	}
	model = sdaiCreateModelBN(1, NULL, ifcSchemaName);

	if	(!model) {
		std::cerr << ("IFC Model could not be instantiated, probably it cannot find the schema file.");
		getch();
		exit(-1);
		return;
	}

	identityMatrix(&matrix);

	ifcApplicationInstance = 0;
	ifcBuildOwnerHistoryInstance = 0;
	ifcConversionBasedUnitInstance = 0;
	ifcDimensionalExponentsInstance = 0;
	ifcGeometricRepresentationContextInstance = 0;
	ifcOrganizationInstance = 0;
	ifcPersonAndOrganizationInstance = 0;
	ifcPersonInstance = 0;
	ifcUnitAssignmentInstance = 0;

	//
	//	Build standard IFC structures
	//

	ifcProjectInstance = getProjectInstance();
	ifcSiteInstance = buildSiteInstance(&matrix, NULL, &ifcSiteInstancePlacement);
	buildRelAggregatesInstance("ProjectContainer", "ProjectContainer for Sites", ifcProjectInstance, ifcSiteInstance);

	//  CDP: now own function: addBuilding(CDP_Building building) --Andreas
	//ifcBuildingInstance = buildBuildingInstance(&matrix, ifcSiteInstancePlacement, &ifcBuildingInstancePlacement);
	//buildRelAggregatesInstance("SiteContainer", "SiteContainer For Buildings", ifcSiteInstance, ifcBuildingInstance);

	// we don't modell the individual floors --Andreas
	//ifcBuildingStoreyInstance = buildBuildingStoreyInstance(&matrix, ifcBuildingInstancePlacement, &ifcBuildingStoreyInstancePlacement);
	//buildRelAggregatesInstance("BuildingContainer", "BuildingContainer for BuildigStories", ifcBuildingInstance, ifcBuildingStoreyInstance);

	/*
	if  (objectsWillBeAdded) {
		buildRelContainedInSpatialStructureInstance("BuildingStoreyContainer", "BuildingStoreyContainer for Building Elements", ifcBuildingStoreyInstance, &aggrRelatedElements);
	}
	*/

}