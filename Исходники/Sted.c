void Sted::InsertDialog (Interactor* dialog) {
    World* world = GetWorld();

    Coord x, y;
    Align(Center, 0, 0, x, y);
    GetRelative(x, y, world);

    world->InsertTransient(dialog, this, x, y, Center);
}