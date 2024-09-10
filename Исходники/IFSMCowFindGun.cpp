void IFSMCowFindGun::Calculate(MovingEntity* entity, Instance* instance){

	Gun* target = instance->GetGun();
	if (entity->GetPosition().DistanceBetween(target->GetPosition()) <= CATCH_DISTANCE)
	{
		//switch states
		printf("[Cow] found the Gun!\n");
		entity->SetState(new IFSMCowHide());
		instance->ResetEntities(false, false, false, true);
		return;
	}

	Vector2D newHeading = (target->GetPosition() - entity->GetPosition());
	newHeading.Normalize();

	entity->SetHeading(newHeading);
	entity->Move(0.0f);

}