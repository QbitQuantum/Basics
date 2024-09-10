void SceneView3D::HandlePostRenderUpdate(StringHash eventType, VariantMap& eventData)
{

    // Visualize the currently selected nodes
    if (selectedNode_.NotNull())
    {
        DrawNodeDebug(selectedNode_, debugRenderer_);

    }

    if (!MouseInView())
        return;

    Input* input = GetSubsystem<Input>();

    mouseLeftDown_ = false;

    if (input->GetMouseButtonPress(MOUSEB_LEFT))
    {
        SetFocus();

        if (!mouseMoved_ && !sceneEditor_->GetGizmo()->Selected())
        {
            Ray camRay  = GetCameraRay();
            PODVector<RayQueryResult> result;

            RayOctreeQuery query(result, camRay, RAY_TRIANGLE, camera_->GetFarClip(), DRAWABLE_GEOMETRY, 0x7fffffff);
            octree_->RaycastSingle(query);

            if (query.result_.Size())
            {
                const RayQueryResult& r = result[0];

                if (r.drawable_)
                {

                    VariantMap neventData;
                    Node* node = r.drawable_->GetNode();

                    // if temporary, this is a prefab
                    // TODO: if we use temporary for other stuff
                    // fix this to look for prefab
                    if (node->IsTemporary())
                        node = node->GetParent();

                    neventData[EditorActiveNodeChange::P_NODE] = node;
                    SendEvent(E_EDITORACTIVENODECHANGE, neventData);

                }
            }
        }

        mouseMoved_ = false;

    }
    else if (!input->GetMouseButtonDown(MOUSEB_LEFT))
    {

        Ray camRay  = GetCameraRay();
        PODVector<RayQueryResult> result;

        mouseMoved_ = false;

        /*
        Array<int> pickModeDrawableFlags = {
            DRAWABLE_GEOMETRY,
            DRAWABLE_LIGHT,
            DRAWABLE_ZONE
        };
        */

        RayOctreeQuery query(result, camRay, RAY_TRIANGLE, camera_->GetFarClip(), DRAWABLE_GEOMETRY, 0x7fffffff);
        octree_->RaycastSingle(query);

        if (query.result_.Size())
        {
            const RayQueryResult& r = result[0];

            if (r.drawable_)
            {
                debugRenderer_->AddNode(r.drawable_->GetNode(), 1.0, false);
                r.drawable_->DrawDebugGeometry(debugRenderer_, false);
            }
        }
    }
    else
    {
        mouseLeftDown_ = true;
        if (Abs(input->GetMouseMoveX() > 3 || input->GetMouseMoveY() >  3))
        {
            mouseMoved_ = true;
        }
    }

}