void generateMap(AABB workspace) {
    Vector2 min = Vector2(workspace.min()[0], workspace.min()[1]);
    Vector2 max = Vector2(workspace.max()[0], workspace.max()[1]);
    auto sampler = std::make_shared<SamplerRandom<2>>(std::make_pair(min, max));

    cad::MapGenerator<2> mapGenerator(workspace, sampler);
    auto meshes = mapGenerator.generateMap(80, Vector2(10, 10), Vector2(80, 80));
    cad::exportCad(cad::ExportFormat::OBJ, "obstacle", cad::mergeMeshes(meshes));
}