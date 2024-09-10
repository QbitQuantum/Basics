Vector2D Unit::AvoidUnitCollision()
{
    if (DetectUnitCollision()){
        std::cout << "\n" << " found";
        RenderableObject* closesestUnit = objects[0];
        for(std::vector<RenderableObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            RenderableObject* currentObject = *it;
            Vector2D length = GetPosition() - currentObject->GetPosition();
//            std::cout << "\n current : " << length.Length();
//            std::cout << "\n current test : " << (GetPosition() - closesestUnit->GetPosition()).Length();
            if ((GetPosition() - closesestUnit->GetPosition()).Length() == 0){
                closesestUnit = currentObject;
            }
            if (length.Length() <= (GetPosition() - closesestUnit->GetPosition()).Length() && length.Length() > 0){

                closesestUnit = currentObject;
            }
        }
        Vector2D colPosition = closesestUnit->GetPosition();
        Vector2D currentToPosition = (GetPosition() + velocity) - colPosition;
        return currentToPosition.Normalized();
    }
    else{
        return Vector2D(0,0);
    }
}