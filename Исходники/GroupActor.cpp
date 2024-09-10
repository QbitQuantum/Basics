void AGroupActor::RemoveSubGroupsFromArray(TArray<AGroupActor*>& GroupArray)
{
	for(int32 GroupIndex=0; GroupIndex<GroupArray.Num(); ++GroupIndex)
	{
		AGroupActor* GroupToCheck = GroupArray[GroupIndex];
		if(GroupHasParentInArray(GroupToCheck, GroupArray))
		{
			GroupArray.Remove(GroupToCheck);
			--GroupIndex;
		}
	}
}