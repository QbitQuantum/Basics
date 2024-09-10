    /**
    * Set the absolute detector position of a detector
    * @param instrument :: The instrument that contains the defined detector
    * @param detID :: Detector ID
    * @param pos :: new position of Dectector
    * @param sameParent :: true if detector has same parent as previous detector set here.
    */
    void ApplyCalibration::setDetectorPosition(const Geometry::Instrument_const_sptr & instrument, int detID, V3D pos, bool /*sameParent*/ )
    {
       Geometry::IDetector_const_sptr det = instrument->getDetector(detID);
       // Then find the corresponding relative position
       boost::shared_ptr<const Geometry::IComponent> parent = det->getParent();
       if (parent)
       {
         pos -= parent->getPos();
         Quat rot = parent->getRelativeRot();
         rot.inverse();
         rot.rotate(pos);
       }
       boost::shared_ptr<const Geometry::IComponent>grandparent = parent->getParent();
       if (grandparent)
       {
         Quat rot = grandparent->getRelativeRot();
         rot.inverse();
         rot.rotate(pos);
         boost::shared_ptr<const Geometry::IComponent>greatgrandparent = grandparent->getParent();
         if (greatgrandparent) {
           Quat rot2 = greatgrandparent->getRelativeRot();
            rot2.inverse();
            rot2.rotate(pos);
         }
       }

       // Add a parameter for the new position
       m_pmap->addV3D(det.get(), "pos", pos);
    }