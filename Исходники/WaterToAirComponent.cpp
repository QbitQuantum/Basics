bool WaterToAirComponent_Impl::removeFromAirLoopHVAC()
{
    Model _model = model();
    ModelObject thisObject = getObject<ModelObject>();

    if( boost::optional<AirLoopHVAC> airLoop = airLoopHVAC() )
    {
        if( airOutletModelObject().get() == airLoop->supplyOutletNodes().front() &&
                airInletModelObject().get() == airLoop->supplyInletNode() )
        {
            ModelObject sourceModelObject = airInletModelObject().get();
            unsigned sourcePort = connectedObjectPort( airInletPort() ).get();
            ModelObject targetModelObject = airOutletModelObject().get();
            unsigned targetPort = connectedObjectPort( airOutletPort() ).get();

            model().disconnect(thisObject,airOutletPort());
            model().disconnect(thisObject,airInletPort());

            _model.connect( sourceModelObject, sourcePort,
                            targetModelObject, targetPort );
            return true;
        }
        else if( airOutletModelObject().get() == airLoop->supplyOutletNodes().front() )
        {
            Node sourceModelObject = airInletModelObject()->optionalCast<Node>().get();
            ModelObject targetModelObject = airOutletModelObject().get();
            unsigned targetPort = connectedObjectPort( airOutletPort() ).get();
            ModelObject source2ModelObject = sourceModelObject.inletModelObject().get();
            unsigned source2Port = sourceModelObject.connectedObjectPort( sourceModelObject.inletPort() ).get();

            model().disconnect(thisObject,airOutletPort());
            model().disconnect(thisObject,airInletPort());

            _model.connect( source2ModelObject, source2Port,
                            targetModelObject, targetPort );

            sourceModelObject.remove();

            return true;
        }
        else
        {
            ModelObject sourceModelObject = airInletModelObject().get();
            unsigned sourcePort = connectedObjectPort( airInletPort() ).get();
            Node targetModelObject = airOutletModelObject()->optionalCast<Node>().get();
            ModelObject target2ModelObject = targetModelObject.outletModelObject().get();
            unsigned target2Port = targetModelObject.connectedObjectPort( targetModelObject.outletPort() ).get();

            model().disconnect(thisObject,airOutletPort());
            model().disconnect(thisObject,airInletPort());


            _model.connect( sourceModelObject, sourcePort,
                            target2ModelObject, target2Port );

            targetModelObject.remove();

            return true;
        }
    }

    return false;
}