void UBlinkyChaseBehaviorComponent::FindPath()
{
	auto Owner = static_cast<AGhost*>(GetOwner());
	auto PathFollower = Owner->GetPathFollowingComponent();

	TActorIterator<APacmanPlayer> PlayerIt(GetWorld());

	GNavigationSystem->FindPathToLocation(Owner->GetActorLocation(), PlayerIt->GetActorLocation(), Owner->GetActorForwardVector(), PathFollower->GetPath());
	PathFollower->StartPathFollowing();
}