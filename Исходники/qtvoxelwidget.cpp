void Urho3DTemplate::AddOrRemoveObject()
{
    //Raycast and check if we hit a mushroom node. If yes, remove it, if no create a new one
    Vector3 hitPos;
    Drawable* hitDrawable;

    if (RayCast(250.0f, hitPos, hitDrawable))
    {
        Node* hitNode = hitDrawable->GetNode();
        if (hitNode->GetName() == "Mushroom")
        {
            hitNode->Remove();
        }
        else
        {
            CreateMushroom(hitPos);
        }
    }
}