//----------------------------------------------------------------
// Function: TopoDS_Shape level function to update the core Surface
//           for any movement  or Boolean operation of the body.
// Author: Jane Hu
//----------------------------------------------------------------
CubitStatus OCCSurface::update_OCC_entity(TopoDS_Face& old_surface,
                                          TopoDS_Shape& new_surface,
                                          BRepBuilderAPI_MakeShape *op,
                                          TopoDS_Vertex* removed_vertex,
                                          LocOpe_SplitShape* sp) 
{
  //set the Wires
  TopTools_IndexedMapOfShape M, M2;
  TopoDS_Shape shape, shape2, shape_edge, shape_vertex;
  TopExp::MapShapes(old_surface, TopAbs_WIRE, M);

  TopTools_ListOfShape shapes;  
  BRepFilletAPI_MakeFillet2d* test_op = NULL;

  for (int ii=1; ii<=M.Extent(); ii++) 
  {
     TopoDS_Wire wire = TopoDS::Wire(M(ii));
     TopTools_ListOfShape shapes;
     if(op)
     {
       test_op = dynamic_cast<BRepFilletAPI_MakeFillet2d*>(op);
       if(!test_op)
         shapes.Assign(op->Modified(wire));
       if(shapes.Extent() == 0)
         shapes.Assign(op->Generated(wire));
       if(!new_surface.IsNull())
         TopExp::MapShapes(new_surface,TopAbs_WIRE, M2);
     }
     else if(sp)
       shapes.Assign(sp->DescendantShapes(wire));

     if (shapes.Extent() == 1)
     {
       shape = shapes.First();
       if(M2.Extent() == 1)
       {
         shape2 = TopoDS::Wire(M2(1));
         if(!shape.IsSame(shape2))
           shape = shape2;
       }
       else if(M2.Extent() > 1)
         shape.Nullify();
     }
     else if(shapes.Extent() > 1)
       shape.Nullify();
     else if(op->IsDeleted(wire) || shapes.Extent() == 0)
     {
       TopTools_IndexedMapOfShape M_new;
       TopExp::MapShapes(new_surface, TopAbs_WIRE, M_new);
       if (M_new.Extent()== 1)
         shape = M_new(1);
       else
         shape.Nullify();
     }
     else
     {
       shape = wire;
       continue;
     }

     //set curves
     BRepTools_WireExplorer Ex;
      
     for(Ex.Init(wire); Ex.More();Ex.Next())
     {
       TopoDS_Edge edge = Ex.Current();
       if(op && !test_op)
       {
         shapes.Assign(op->Modified(edge));
         if(shapes.Extent() == 0)
           shapes.Assign(op->Generated(edge));
       }
         
       else if(sp)
         shapes.Assign(sp->DescendantShapes(edge));

       if (shapes.Extent() == 1)
       {
        //in fillet creating mothod, one edge could generated a face, so check
        //it here.
         TopAbs_ShapeEnum type = shapes.First().TShape()->ShapeType(); 
         if(type != TopAbs_EDGE)
           shape_edge.Nullify();
         else
           shape_edge = shapes.First();
       }
       else if (shapes.Extent() > 1)
       {
         //update all attributes first.
         TopTools_ListIteratorOfListOfShape it;
         it.Initialize(shapes);
         for(; it.More(); it.Next())
         {
           shape_edge = it.Value();
           OCCQueryEngine::instance()->copy_attributes(edge, shape_edge);
         }
         shape_edge.Nullify();
       }
       else if (op->IsDeleted(edge))
         shape_edge.Nullify(); 
       else if (test_op)
       {
         if(!test_op->IsModified(edge))
           shape_edge = edge;
         else
           shape_edge = (test_op->Modified(edge)).First();
       } 
       else
         shape_edge = edge;

       //update vertex
       TopoDS_Vertex vertex = Ex.CurrentVertex();
       shapes.Clear();
       if(test_op)
         assert(removed_vertex != NULL);

       if(op && ! test_op )
         shapes.Assign(op->Modified(vertex));
       else if(sp)
         shapes.Assign(sp->DescendantShapes(vertex));

       if (shapes.Extent() == 1)
         shape_vertex = shapes.First();

       else if(shapes.Extent() > 1)
       {
         //update all attributes first.
         TopTools_ListIteratorOfListOfShape it;
         it.Initialize(shapes);
         for(; it.More(); it.Next())
         {
           shape_vertex = it.Value();
           OCCQueryEngine::instance()->copy_attributes(vertex, shape_vertex);
         }
         shape_vertex.Nullify() ;
       }
       else if(op->IsDeleted(vertex) || (test_op && vertex.IsSame( *removed_vertex)))
         shape_vertex.Nullify() ;
         
       else
         shape_vertex = vertex;
      
       if(!vertex.IsSame(shape_vertex) )
         OCCQueryEngine::instance()->update_OCC_map(vertex, shape_vertex);

       if (!edge.IsSame(shape_edge))
         OCCQueryEngine::instance()->update_OCC_map(edge, shape_edge);
     }
     if (!wire.IsSame(shape))
       OCCQueryEngine::instance()->update_OCC_map(wire, shape);
  }
  double dTOL = OCCQueryEngine::instance()->get_sme_resabs_tolerance();
  if (!old_surface.IsSame(new_surface))
  {
    TopAbs_ShapeEnum shapetype =  TopAbs_SHAPE;
    if(!new_surface.IsNull())
      shapetype = new_surface.TShape()->ShapeType();  
    if(shapetype == TopAbs_FACE || new_surface.IsNull())
      OCCQueryEngine::instance()->update_OCC_map(old_surface, new_surface);
    else 
    {
      TopTools_IndexedMapOfShape M;
      TopExp::MapShapes(new_surface, TopAbs_FACE, M);   
      TopoDS_Shape new_shape;
      if(M.Extent() == 1)
        new_shape = M(1);
      else if(M.Extent() > 1)
      {
        for(int i = 1; i <= M.Extent(); i++)
        {
          GProp_GProps myProps;
          BRepGProp::SurfaceProperties(old_surface, myProps);
          double orig_mass = myProps.Mass();
          gp_Pnt orig_pnt = myProps.CentreOfMass();
          BRepGProp::SurfaceProperties(M(i), myProps);
          double after_mass = myProps.Mass();
          gp_Pnt after_pnt = myProps.CentreOfMass();
          if(fabs(-after_mass + orig_mass) <= dTOL && 
             orig_pnt.IsEqual(after_pnt, dTOL))
          {
            new_shape = M(i);
            break;
          }
        }
      }
      OCCQueryEngine::instance()->update_OCC_map(old_surface, new_shape);
    }
  }
  return CUBIT_SUCCESS;
}