inline void psEntityLabels::UpdateTarget()
{
    GEMClientObject* lastUnderTarget = underTarget;

    // Find out the object
    underTarget = psengine->GetCharManager()->GetTarget();

    // Is this a new object?
    if (underTarget != lastUnderTarget)
    {
        // Hide old
        if (lastUnderTarget != NULL && MatchVisibility(lastUnderTarget->GetObjectType(), LABEL_ONTARGET))
            ShowLabelOfObject(lastUnderTarget,false);
        
        if (underTarget != NULL && !MatchVisibility(underTarget->GetObjectType(), LABEL_ONTARGET))
            return;

        // Show new
        if (underTarget != NULL)
        {
            // Don't show other player names unless introduced.
            if (underTarget->GetObjectType() == GEM_ACTOR && !(underTarget->Flags() & psPersistActor::NAMEKNOWN))
                return;

            csRef<iMeshWrapper> mesh = underTarget->GetMesh();
            if (mesh)
            {
                // Only show labels within range
                csVector3 here = celClient->GetMainPlayer()->Pos();
                csVector3 there = mesh->GetMovable()->GetPosition();
                int range = (underTarget->GetObjectType() == GEM_ITEM) ? RANGE_TO_SEE_ITEM_LABELS : RANGE_TO_SEE_ACTOR_LABELS ;
                bool show = ((here-there).Norm() < range);

                ShowLabelOfObject(underTarget, show);
            }
        }
    }
}