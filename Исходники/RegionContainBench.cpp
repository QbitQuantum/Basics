    RegionContainBench(void* param, Proc proc, const char name[]) : INHERITED(param) {
        fProc = proc;
        fName.printf("region_contains_%s", name);

        SkRandom rand;
        for (int i = 0; i < COUNT; i++) {
            fA.op(randrect(rand, i), SkRegion::kXOR_Op);
        }

        fB.setRect(0, 0, H, W);

        fIsRendering = false;
    }