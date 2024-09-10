 virtual void draw() {
     // Draw Wrapped Window first as it is in the background
     WindowDecorator::draw();
     // Now draw the actual menu bar
     drawMenuBar();
 }