int main(int argc, char **argv)
{
    EffectRunner r;
    ParticleTrailEffect e;
    r.setEffect(&e);
    r.setMaxFrameRate(30);
    r.setLayout("../layouts/grid32x16z.json");
    return r.main(argc, argv);
}