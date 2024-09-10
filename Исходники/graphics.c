Graphics::Graphics () {
    Picture* pict = InitPicture();
    View* view = new View(pict);
    Tray* interior = new Tray(view);
    Frame* pannerFrame = new Frame(new Panner(view));

    interior->Align(BottomRight, pannerFrame);
    interior->Propagate(false);  // keep pannerFrame from changing entire view
    Insert(interior);
}