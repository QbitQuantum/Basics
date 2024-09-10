int GModel::writeMESH(const std::string &name, int elementTagType,
                      bool saveAll, double scalingFactor)
{
  FILE *fp = Fopen(name.c_str(), "w");
  if(!fp){
    Msg::Error("Unable to open file '%s'", name.c_str());
    return 0;
  }

  if(noPhysicalGroups()) saveAll = true;

  int numVertices = indexMeshVertices(saveAll);

  fprintf(fp, " MeshVersionFormatted 2\n");
  fprintf(fp, " Dimension\n");
  fprintf(fp, " 3\n");

  fprintf(fp, " Vertices\n");
  fprintf(fp, " %d\n", numVertices);
  std::vector<GEntity*> entities;
  getEntities(entities);
  for(unsigned int i = 0; i < entities.size(); i++)
    for(unsigned int j = 0; j < entities[i]->mesh_vertices.size(); j++)
      entities[i]->mesh_vertices[j]->writeMESH(fp, scalingFactor);

  int numEdges = 0, numTriangles = 0, numQuadrangles = 0;
  int numTetrahedra = 0, numHexahedra = 0;
  for(eiter it = firstEdge(); it != lastEdge(); ++it){
    if(saveAll || (*it)->physicals.size()){
      numEdges += (*it)->lines.size();
    }
  }
  for(fiter it = firstFace(); it != lastFace(); ++it){
    if(saveAll || (*it)->physicals.size()){
      numTriangles += (*it)->triangles.size();
      numQuadrangles += (*it)->quadrangles.size();
    }
  }
  for(riter it = firstRegion(); it != lastRegion(); ++it){
    if(saveAll || (*it)->physicals.size()){
      numTetrahedra += (*it)->tetrahedra.size();
      numHexahedra += (*it)->hexahedra.size();
    }
  }

  if(numEdges){
    if(CTX::instance()->mesh.order == 2) // FIXME (check getPolynomialOrder())
      fprintf(fp, " EdgesP2\n");
    else
      fprintf(fp, " Edges\n");
    fprintf(fp, " %d\n", numEdges);
    for(eiter it = firstEdge(); it != lastEdge(); ++it){
      int numPhys = (*it)->physicals.size();
      if(saveAll || numPhys){
        for(unsigned int i = 0; i < (*it)->lines.size(); i++)
          (*it)->lines[i]->writeMESH(fp, elementTagType, (*it)->tag(),
                                     numPhys ? (*it)->physicals[0] : 0);
      }
    }
  }
  if(numTriangles){
    if(CTX::instance()->mesh.order == 2) // FIXME (check getPolynomialOrder())
      fprintf(fp, " TrianglesP2\n");
    else
      fprintf(fp, " Triangles\n");
    fprintf(fp, " %d\n", numTriangles);
    for(fiter it = firstFace(); it != lastFace(); ++it){
      int numPhys = (*it)->physicals.size();
      if(saveAll || numPhys){
        for(unsigned int i = 0; i < (*it)->triangles.size(); i++)
          (*it)->triangles[i]->writeMESH(fp, elementTagType, (*it)->tag(),
                                         numPhys ? (*it)->physicals[0] : 0);
      }
    }
  }
  if(numQuadrangles){
    fprintf(fp, " Quadrilaterals\n");
    fprintf(fp, " %d\n", numQuadrangles);
    for(fiter it = firstFace(); it != lastFace(); ++it){
      int numPhys = (*it)->physicals.size();
      if(saveAll || numPhys){
        for(unsigned int i = 0; i < (*it)->quadrangles.size(); i++)
          (*it)->quadrangles[i]->writeMESH(fp, elementTagType, (*it)->tag(),
                                           numPhys ? (*it)->physicals[0] : 0);
      }
    }
  }
  if(numTetrahedra){
    if(CTX::instance()->mesh.order == 2)
      fprintf(fp, " TetrahedraP2\n"); // FIXME (check getPolynomialOrder())
    else
      fprintf(fp, " Tetrahedra\n");
    fprintf(fp, " %d\n", numTetrahedra);
    for(riter it = firstRegion(); it != lastRegion(); ++it){
      int numPhys = (*it)->physicals.size();
      if(saveAll || numPhys){
        for(unsigned int i = 0; i < (*it)->tetrahedra.size(); i++)
          (*it)->tetrahedra[i]->writeMESH(fp, elementTagType, (*it)->tag(),
                                          numPhys ? (*it)->physicals[0] : 0);
      }
    }
  }
  if(numHexahedra){
    fprintf(fp, " Hexahedra\n");
    fprintf(fp, " %d\n", numHexahedra);
    for(riter it = firstRegion(); it != lastRegion(); ++it){
      int numPhys = (*it)->physicals.size();
      if(saveAll || numPhys){
        for(unsigned int i = 0; i < (*it)->hexahedra.size(); i++)
          (*it)->hexahedra[i]->writeMESH(fp, elementTagType, (*it)->tag(),
                                         numPhys ? (*it)->physicals[0] : 0);
      }
    }
  }

  fprintf(fp, " End\n");

  fclose(fp);
  return 1;
}