EntityCreatorCreationInstance::EntityCreatorCreationInstance(World& world, Eris::TypeService& typeService, Authoring::EntityRecipe& recipe, bool randomizeOrientation, sigc::slot<void>& adapterValueChangedSlot) :
		mWorld(world), mTypeService(typeService), mRecipe(recipe), mEntity(0), mEntityNode(0), mModelMount(0), mModel(0), mMovement(0), mAxisMarker(0)
{
	mConnection = mRecipe.EventValueChanged.connect(adapterValueChangedSlot);

	mInitialOrientation.identity();
	if (randomizeOrientation) {
		WFMath::MTRand rng;
		mInitialOrientation.rotation(2, rng.rand() * 360.0f);
	}

}