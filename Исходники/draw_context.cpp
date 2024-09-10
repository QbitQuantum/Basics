void DrawContext::DrawDrawGroup(DrawGroup* dgroup) {
  cur_camera_ = dgroup->GetCamera();
  cur_camera_->SetViewportSize(viewport_width_, viewport_height_);

  Frustum frustum = cur_camera_;
  const QVector3D eye = cur_camera_->WorldTransform().map(QVector3D(0, 0, 0));

  // Figure out which nodes to draw and some data about them.
  std::vector<DrawNodeData> to_draw;
  const int num_draw_nodes = dgroup->DrawNodes().size();
  to_draw.reserve(num_draw_nodes);
  const bool do_frustum_culling = dgroup->GetFrustumCulling();

  for (DrawNode* draw_node : dgroup->DrawNodes()) {
    // If the node is not visible, then skip it.
    bool visible = true;
    for (SceneNode* node = draw_node; node; node = node->ParentNode()) {
      if (!node->Visible()) {
        visible = false;
        break;
      }
    }
    if (!visible) {
      continue;
    }

    // For each draw node, compute:
    //   - model matrix
    //   - world frame axis aligned bounding box
    //   - squared distance to camera
    //   - view frustum intersection
    DrawNodeData dndata;
    dndata.node = draw_node;

    // Cache the model mat matrix and world frame bounding box
    dndata.model_mat = draw_node->WorldTransform();

    // Compute the world frame axis-aligned bounding box
    dndata.world_bbox = draw_node->WorldBoundingBox();

    // View frustum culling
    if (do_frustum_culling &&
        dndata.world_bbox.Valid() &&
        !frustum.Intersects(dndata.world_bbox)) {
      continue;
    }

    dndata.squared_distance = squaredDistanceToAABB(eye,
        dndata.world_bbox);

    to_draw.push_back(dndata);
  }

  switch (dgroup->GetNodeOrdering()) {
    case NodeOrdering::kBackToFront:
      // Sort nodes to draw back to front
      std::sort(to_draw.begin(), to_draw.end(),
          [](const DrawNodeData& dndata_a, const DrawNodeData& dndata_b) {
          return dndata_a.squared_distance > dndata_b.squared_distance;
          });
      break;
    case NodeOrdering::kFrontToBack:
      // Sort nodes to draw front to back
      std::sort(to_draw.begin(), to_draw.end(),
          [](const DrawNodeData& dndata_a, const DrawNodeData& dndata_b) {
          return dndata_a.squared_distance < dndata_b.squared_distance;
          });
      break;
    case NodeOrdering::kNone:
    default:
      // Don't sort nodes
      break;
  }

  // Draw each draw node
  for (DrawNodeData& dndata : to_draw) {
    const QString name = dndata.node->Name();
    model_mat_ = dndata.model_mat;
    DrawDrawNode(dndata.node);

    if (draw_bounding_boxes_) {
      DrawBoundingBox(dndata.world_bbox);
    }
  }
}