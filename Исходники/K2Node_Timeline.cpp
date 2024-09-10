void UK2Node_Timeline::DestroyNode()
{
	UBlueprint* Blueprint = GetBlueprint();
	check(Blueprint);
	UTimelineTemplate* Timeline = Blueprint->FindTimelineTemplateByVariableName(TimelineName);
	if(Timeline)
	{
		FBlueprintEditorUtils::RemoveTimeline(Blueprint, Timeline, true);

		// Move template object out of the way so that we can potentially create a timeline with the same name either through a paste or a new timeline action
		Timeline->Rename(NULL, GetTransientPackage(), (Blueprint->bIsRegeneratingOnLoad ? REN_ForceNoResetLoaders : REN_None));
	}

	Super::DestroyNode();
}