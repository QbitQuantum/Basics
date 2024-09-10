void BLOCK::compress(                  // squash it up
                     const ICOORD vec  // and move
                    ) {
  box.move (vec);
  compress();
}