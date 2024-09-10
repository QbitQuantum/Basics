bool FaceUniter::process()
{
    if (workShell.IsNull())
        return false;
    modifiedShapes.clear();
    deletedShapes.clear();
    typeObjects.push_back(&getPlaneObject());
    typeObjects.push_back(&getCylinderObject());
    //add more face types.

    ModelRefine::FaceTypeSplitter splitter;
    splitter.addShell(workShell);
    std::vector<FaceTypedBase *>::iterator typeIt;
    for(typeIt = typeObjects.begin(); typeIt != typeObjects.end(); ++typeIt)
        splitter.registerType((*typeIt)->getType());
    splitter.split();

    ModelRefine::FaceVectorType facesToRemove;
    ModelRefine::FaceVectorType facesToSew;

    ModelRefine::FaceAdjacencySplitter adjacencySplitter(workShell);

    for(typeIt = typeObjects.begin(); typeIt != typeObjects.end(); ++typeIt)
    {
        ModelRefine::FaceVectorType typedFaces = splitter.getTypedFaceVector((*typeIt)->getType());
        ModelRefine::FaceEqualitySplitter equalitySplitter;
        equalitySplitter.split(typedFaces, *typeIt);
        for (std::size_t indexEquality(0); indexEquality < equalitySplitter.getGroupCount(); ++indexEquality)
        {
            adjacencySplitter.split(equalitySplitter.getGroup(indexEquality));
//            std::cout << "      adjacency group count: " << adjacencySplitter.getGroupCount() << std::endl;
            for (std::size_t adjacentIndex(0); adjacentIndex < adjacencySplitter.getGroupCount(); ++adjacentIndex)
            {
//                    std::cout << "         face count is: " << adjacencySplitter.getGroup(adjacentIndex).size() << std::endl;
                TopoDS_Face newFace = (*typeIt)->buildFace(adjacencySplitter.getGroup(adjacentIndex));
                if (!newFace.IsNull())
                {
                    facesToSew.push_back(newFace);
                    if (facesToRemove.capacity() <= facesToRemove.size() + adjacencySplitter.getGroup(adjacentIndex).size())
                        facesToRemove.reserve(facesToRemove.size() + adjacencySplitter.getGroup(adjacentIndex).size());
                    FaceVectorType temp = adjacencySplitter.getGroup(adjacentIndex);
                    facesToRemove.insert(facesToRemove.end(), temp.begin(), temp.end());
                    // the first shape will be marked as modified, i.e. replaced by newFace, all others are marked as deleted
                    // jrheinlaender: IMHO this is not correct because references to the deleted faces will be broken, whereas they should
                    // be replaced by references to the new face. To achieve this all shapes should be marked as
                    // modified, producing one single new face. This is the inverse behaviour to faces that are split e.g.
                    // by a boolean cut, where one old shape is marked as modified, producing multiple new shapes
                    if (!temp.empty())
                    {
                        for (FaceVectorType::iterator f = temp.begin(); f != temp.end(); ++f)
                              modifiedShapes.push_back(std::make_pair(*f, newFace));
                    }
                }
            }
        }
    }
    if (facesToSew.size() > 0)
    {
        modifiedSignal = true;
        workShell = ModelRefine::removeFaces(workShell, facesToRemove);
        TopExp_Explorer xp;
        bool emptyShell = true;
        for (xp.Init(workShell, TopAbs_FACE); xp.More(); xp.Next())
        {
            emptyShell = false;
            break;
        }

        if (!emptyShell || facesToSew.size() > 1)
        {
            BRepBuilderAPI_Sewing sew;
            sew.Add(workShell);
            FaceVectorType::iterator sewIt;
            for(sewIt = facesToSew.begin(); sewIt != facesToSew.end(); ++sewIt)
                sew.Add(*sewIt);
            sew.Perform();
            try {
                workShell = TopoDS::Shell(sew.SewedShape());
            } catch (Standard_Failure) {
                return false;
            }
            // update the list of modifications
            for (std::vector<ShapePairType>::iterator it = modifiedShapes.begin(); it != modifiedShapes.end(); ++it)
            {
                if (sew.IsModified(it->second))
                {
                    it->second = sew.Modified(it->second);
                    break;
                }
            }
        }
        else
        {
            // workShell has no more faces and we add exactly one face
            BRep_Builder builder;
            builder.MakeShell(workShell);
            FaceVectorType::iterator sewIt;
            for(sewIt = facesToSew.begin(); sewIt != facesToSew.end(); ++sewIt)
                builder.Add(workShell, *sewIt);
        }
        
        BRepLib_FuseEdges edgeFuse(workShell);
// TODO: change this version after occ fix. Freecad Mantis 1450
#if OCC_VERSION_HEX <= 0x070000
        TopTools_IndexedMapOfShape map;
        collectConicEdges(workShell, map);
        edgeFuse.AvoidEdges(map);
#endif
        TopTools_DataMapOfShapeShape affectedFaces;
        edgeFuse.Faces(affectedFaces);
        TopTools_DataMapIteratorOfDataMapOfShapeShape mapIt;
        for (mapIt.Initialize(affectedFaces); mapIt.More(); mapIt.Next())
        {
            ShapeFix_Face faceFixer(TopoDS::Face(mapIt.Value()));
            faceFixer.Perform();
        }
        workShell = TopoDS::Shell(edgeFuse.Shape());
        // update the list of modifications
        TopTools_DataMapOfShapeShape faceMap;
        edgeFuse.Faces(faceMap);
        for (mapIt.Initialize(faceMap); mapIt.More(); mapIt.Next())
        {
            bool isModifiedFace = false;
            for (std::vector<ShapePairType>::iterator it = modifiedShapes.begin(); it != modifiedShapes.end(); ++it)
            {
                if (mapIt.Key().IsSame(it->second)) {
                    // Note: IsEqual() for some reason does not work
                    it->second = mapIt.Value();
                    isModifiedFace = true;
                }
            }
            if (!isModifiedFace)
            {
                // Catch faces that were not united but whose boundary was changed (probably because
                // several adjacent faces were united)
                // See https://sourceforge.net/apps/mantisbt/free-cad/view.php?id=873
                modifiedShapes.push_back(std::make_pair(mapIt.Key(), mapIt.Value()));
            }
        }
        // Handle edges that were fused. See https://sourceforge.net/apps/mantisbt/free-cad/view.php?id=873
        TopTools_DataMapOfIntegerListOfShape oldEdges;
        TopTools_DataMapOfIntegerShape newEdges;
        edgeFuse.Edges(oldEdges);
        edgeFuse.ResultEdges(newEdges);
        TopTools_DataMapIteratorOfDataMapOfIntegerListOfShape edgeMapIt;
        for (edgeMapIt.Initialize(oldEdges); edgeMapIt.More(); edgeMapIt.Next())
        {
            const TopTools_ListOfShape& edges = edgeMapIt.Value();
            int idx = edgeMapIt.Key();
            TopTools_ListIteratorOfListOfShape edgeIt;
            for (edgeIt.Initialize(edges); edgeIt.More(); edgeIt.Next())
            {
                modifiedShapes.push_back(std::make_pair(edgeIt.Value(), newEdges(idx)));
            }
            // TODO: Handle vertices that have disappeared in the fusion of the edges
        }
    }
    return true;
}