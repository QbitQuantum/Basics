void primordialSoup() {
    for (int x = 0; x < xDim; x++) {
        for (int y = 0; y < yDim; y++) {
            for (int z = 0; z < zDim; z++) {
                float r = twister.rand();
                if (r > 0.85) values[z](x,y) = 1.0;
                else values[z](x,y) = 0.0;
            }
        }
    }
}