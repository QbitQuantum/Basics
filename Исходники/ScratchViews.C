void fill_pre_req_data(
  ElemDataRequests& dataNeeded,
  const stk::mesh::BulkData& bulkData,
  stk::topology topo,
  stk::mesh::Entity elem,
  const stk::mesh::FieldBase* coordField,
  ScratchViews& prereqData)
{
  int nodesPerElem = topo.num_nodes();

  MasterElement *meSCS = dataNeeded.get_cvfem_surface_me();
  MasterElement *meSCV = dataNeeded.get_cvfem_volume_me();
  prereqData.elemNodes = bulkData.begin_nodes(elem);

  const FieldSet& neededFields = dataNeeded.get_fields();
  for(const FieldInfo& fieldInfo : neededFields) {
    stk::mesh::EntityRank fieldEntityRank = fieldInfo.field->entity_rank();
    unsigned scalarsDim1 = fieldInfo.scalarsDim1;
    bool isTensorField = fieldInfo.scalarsDim2 > 1;

    if (fieldEntityRank==stk::topology::ELEM_RANK) {
      if (isTensorField) {
        SharedMemView<double**>& shmemView = prereqData.get_scratch_view_2D(*fieldInfo.field);
        gather_elem_tensor_field(*fieldInfo.field, elem, scalarsDim1, fieldInfo.scalarsDim2, shmemView);
      }
      else {
        SharedMemView<double*>& shmemView = prereqData.get_scratch_view_1D(*fieldInfo.field);
        unsigned len = shmemView.dimension(0);
        double* fieldDataPtr = static_cast<double*>(stk::mesh::field_data(*fieldInfo.field, elem));
        for(unsigned i=0; i<len; ++i) {
          shmemView(i) = fieldDataPtr[i];
        }
      }
    }
    else if (fieldEntityRank == stk::topology::NODE_RANK) {
      if (isTensorField) {
        SharedMemView<double***>& shmemView3D = prereqData.get_scratch_view_3D(*fieldInfo.field);
        gather_elem_node_tensor_field(*fieldInfo.field, nodesPerElem, scalarsDim1, fieldInfo.scalarsDim2, bulkData.begin_nodes(elem), shmemView3D);
      }
      else {
        if (scalarsDim1 == 1) {
          SharedMemView<double*>& shmemView1D = prereqData.get_scratch_view_1D(*fieldInfo.field);
          gather_elem_node_field(*fieldInfo.field, nodesPerElem, prereqData.elemNodes, shmemView1D);
        }
        else {
          SharedMemView<double**>& shmemView2D = prereqData.get_scratch_view_2D(*fieldInfo.field);
          if (scalarsDim1 == 3) {
            gather_elem_node_field_3D(*fieldInfo.field, nodesPerElem, prereqData.elemNodes, shmemView2D);
          }
          else {
            gather_elem_node_field(*fieldInfo.field, nodesPerElem, scalarsDim1, prereqData.elemNodes, shmemView2D);
          }
        }
      }
    }
    else {
      ThrowRequireMsg(false, "Only node and element fields supported currently.");
    }
  } 
      
  SharedMemView<double**>* coordsView = nullptr;
  if (coordField != nullptr) {
    coordsView = &prereqData.get_scratch_view_2D(*coordField);
  }

  const std::set<ELEM_DATA_NEEDED>& dataEnums = dataNeeded.get_data_enums();
  double error = 0;
  for(ELEM_DATA_NEEDED data : dataEnums) {
    switch(data)
    {
      case SCS_AREAV:
         ThrowRequireMsg(meSCS != nullptr, "ERROR, meSCS needs to be non-null if SCS_AREAV is requested.");
         ThrowRequireMsg(coordsView != nullptr, "ERROR, coords null but SCS_AREAV requested.");
         meSCS->determinant(1, &((*coordsView)(0,0)), &prereqData.scs_areav(0,0), &error);
         break;
      case SCS_GRAD_OP:
         ThrowRequireMsg(meSCS != nullptr, "ERROR, meSCS needs to be non-null if SCS_GRAD_OP is requested.");
         ThrowRequireMsg(coordsView != nullptr, "ERROR, coords null but SCS_GRAD_OP requested.");
         meSCS->grad_op(1, &((*coordsView)(0,0)), &prereqData.dndx(0,0,0), &prereqData.deriv(0), &prereqData.det_j(0), &error);
         break;
      case SCS_SHIFTED_GRAD_OP:
        ThrowRequireMsg(meSCS != nullptr, "ERROR, meSCS needs to be non-null if SCS_GRAD_OP is requested.");
        ThrowRequireMsg(coordsView != nullptr, "ERROR, coords null but SCS_GRAD_OP requested.");
        meSCS->shifted_grad_op(1, &((*coordsView)(0,0)), &prereqData.dndx_shifted(0,0,0), &prereqData.deriv(0), &prereqData.det_j(0), &error);
        break;
      case SCS_GIJ:
         ThrowRequireMsg(meSCS != nullptr, "ERROR, meSCS needs to be non-null if SCS_GIJ is requested.");
         ThrowRequireMsg(coordsView != nullptr, "ERROR, coords null but SCS_GIJ requested.");
         meSCS->gij(&((*coordsView)(0,0)), &prereqData.gijUpper(0,0,0), &prereqData.gijLower(0,0,0), &prereqData.deriv(0));
         break;
      case SCV_VOLUME:
         ThrowRequireMsg(meSCV != nullptr, "ERROR, meSCV needs to be non-null if SCV_VOLUME is requested.");
         ThrowRequireMsg(coordsView != nullptr, "ERROR, coords null but SCV_VOLUME requested.");
         meSCV->determinant(1, &((*coordsView)(0,0)), &prereqData.scv_volume(0), &error);
         break;
      default: break;
    }
  }
}