void BillboardSet::UpdateVertexBuffer(const FrameInfo& frame)
{
    // If using animation LOD, accumulate time and see if it is time to update
    if (animationLodBias_ > 0.0f && lodDistance_ > 0.0f)
    {
        animationLodTimer_ += animationLodBias_ * frame.timeStep_ * ANIMATION_LOD_BASESCALE;
        if (animationLodTimer_ >= lodDistance_)
            animationLodTimer_ = fmodf(animationLodTimer_, lodDistance_);
        else
        {
            // No LOD if immediate update forced
            if (!forceUpdate_)
                return;
        }
    }

    unsigned numBillboards = billboards_.Size();
    unsigned enabledBillboards = 0;
    const Matrix3x4& worldTransform = node_->GetWorldTransform();
    Matrix3x4 billboardTransform = relative_ ? worldTransform : Matrix3x4::IDENTITY;
    Vector3 billboardScale = scaled_ ? worldTransform.Scale() : Vector3::ONE;

    // First check number of enabled billboards
    for (unsigned i = 0; i < numBillboards; ++i)
    {
        if (billboards_[i].enabled_)
            ++enabledBillboards;
    }

    sortedBillboards_.Resize(enabledBillboards);
    unsigned index = 0;

    // Then set initial sort order and distances
    for (unsigned i = 0; i < numBillboards; ++i)
    {
        Billboard& billboard = billboards_[i];
        if (billboard.enabled_)
        {
            sortedBillboards_[index++] = &billboard;
            if (sorted_)
                billboard.sortDistance_ = frame.camera_->GetDistanceSquared(billboardTransform * billboards_[i].position_);
        }
    }

    batches_[0].geometry_->SetDrawRange(TRIANGLE_LIST, 0, enabledBillboards * 6, false);

    bufferDirty_ = false;
    forceUpdate_ = false;
    if (!enabledBillboards)
        return;

    if (sorted_)
        Sort(sortedBillboards_.Begin(), sortedBillboards_.End(), CompareBillboards);

    float* dest = (float*)vertexBuffer_->Lock(0, enabledBillboards * 4, true);
    if (!dest)
        return;

    for (unsigned i = 0; i < enabledBillboards; ++i)
    {
        Billboard& billboard = *sortedBillboards_[i];

        Vector2 size(billboard.size_.x_ * billboardScale.x_, billboard.size_.y_ * billboardScale.y_);
        unsigned color = billboard.color_.ToUInt();

        float rotationMatrix[2][2];
        rotationMatrix[0][0] = Cos(billboard.rotation_);
        rotationMatrix[0][1] = Sin(billboard.rotation_);
        rotationMatrix[1][0] = -rotationMatrix[0][1];
        rotationMatrix[1][1] = rotationMatrix[0][0];

        dest[0] = billboard.position_.x_; dest[1] = billboard.position_.y_; dest[2] = billboard.position_.z_;
        ((unsigned&)dest[3]) = color;
        dest[4] = billboard.uv_.min_.x_; dest[5] = billboard.uv_.min_.y_;
        dest[6] = -size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
        dest[7] = -size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];

        dest[8] = billboard.position_.x_; dest[9] = billboard.position_.y_; dest[10] = billboard.position_.z_;
        ((unsigned&)dest[11]) = color;
        dest[12] = billboard.uv_.max_.x_; dest[13] = billboard.uv_.min_.y_;
        dest[14] = size.x_ * rotationMatrix[0][0] + size.y_ * rotationMatrix[0][1];
        dest[15] = size.x_ * rotationMatrix[1][0] + size.y_ * rotationMatrix[1][1];

        dest[16] = billboard.position_.x_; dest[17] = billboard.position_.y_; dest[18] = billboard.position_.z_;
        ((unsigned&)dest[19]) = color;
        dest[20] = billboard.uv_.max_.x_; dest[21] = billboard.uv_.max_.y_;
        dest[22] = size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
        dest[23] = size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];

        dest[24] = billboard.position_.x_; dest[25] = billboard.position_.y_; dest[26] = billboard.position_.z_;
        ((unsigned&)dest[27]) = color;
        dest[28] = billboard.uv_.min_.x_; dest[29] = billboard.uv_.max_.y_;
        dest[30] = -size.x_ * rotationMatrix[0][0] - size.y_ * rotationMatrix[0][1];
        dest[31] = -size.x_ * rotationMatrix[1][0] - size.y_ * rotationMatrix[1][1];

        dest += 32;
    }

    vertexBuffer_->Unlock();
    vertexBuffer_->ClearDataLost();
}