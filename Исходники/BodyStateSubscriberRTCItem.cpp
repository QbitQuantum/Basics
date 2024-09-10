void PointCloudInput::read1()
{
    if(port1.isNew()){
        do {
            port1.read();
        } while(port1.isNew());
    
        bool rgb = false;
        for(size_t i=0; i < pointCloud1.fields.length(); ++i){
            string name = string(pointCloud1.fields[i].name);
            pointCloudField[name].offset = pointCloud1.fields[i].offset;
            pointCloudField[name].type = pointCloud1.fields[i].data_type;
            pointCloudField[name].count = pointCloud1.fields[i].count;
            if(i==5){
                rgb = true;
            }
        }

        int n = pointCloud1.height * pointCloud1.width;
        int m = pointCloud1.data.length() / pointCloud1.point_step;
        int numPoints = std::min(n, m);
        unsigned char* src = (unsigned char*)pointCloud1.data.get_buffer();
        auto tmpPoints = std::make_shared<vector<Vector3f>>();
        std::shared_ptr<Image> tmpImage;
        unsigned char* pixels = nullptr;
        if(rgb){
            tmpImage = std::make_shared<Image>();
            tmpImage->setSize(pointCloud1.width, pointCloud1.height, 3);
            pixels = tmpImage->pixels();
        }
        
        tmpPoints->clear();
        tmpPoints->reserve(numPoints);
        
        PointCloudField& fex = pointCloudField["x"];
        PointCloudField& fey = pointCloudField["y"];
        PointCloudField& fez = pointCloudField["z"];
        PointCloudField& fer = pointCloudField["r"];
        PointCloudField& feg = pointCloudField["g"];
        PointCloudField& feb = pointCloudField["b"];
        
        for(int i=0; i < numPoints; ++i, src+=pointCloud1.point_step){
            Vector3f point;
            point.x() = readFloatPointCloudData(&src[fex.offset], fex, pointCloud1.is_bigendian );
            point.y() = readFloatPointCloudData(&src[fey.offset], fey, pointCloud1.is_bigendian );
            point.z() = readFloatPointCloudData(&src[fez.offset], fez, pointCloud1.is_bigendian );
            tmpPoints->push_back(point);
            
            if(rgb && pixels){
                pixels[0] = src[fer.offset];
                pixels[1] = src[feg.offset];
                pixels[2] = src[feb.offset];
                pixels += 3;
            }
        }
        
        if(!rgb || !pixels){
            tmpImage.reset();
        }

        RangeCameraPtr tmpRangeCamera = rangeCamera;
        callLater([tmpRangeCamera, tmpPoints, tmpImage]() mutable {
                tmpRangeCamera->setPoints(tmpPoints);
                if(tmpImage){
                    tmpRangeCamera->setImage(tmpImage);
                }
                tmpRangeCamera->notifyStateChange();
            });
    }
}