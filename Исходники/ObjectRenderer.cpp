void    ObjectRenderer::RenderShadow(int pass, const Vector3& light, const Vector3& observer){
    if(pass<0) return;

    glPushMatrix();

    Vector3 objLight;
    Vector3 objObserver;


    Vector3 obsObj = mObject->GetReferenceFrame().GetOrigin();
    obsObj -= observer;

    Vector3 ligObj = mObject->GetReferenceFrame().GetOrigin();
    ligObj -= light;

    glMultMatrixf(mObject->GetReferenceFrame().GetHMatrix().RowOrderForceFloat());

    mObject->GetReferenceFrame().GetInverse().GetHMatrix().Transform(light,     objLight);
    mObject->GetReferenceFrame().GetInverse().GetHMatrix().Transform(observer,  objObserver);

    for(int i=0;i<int(mShapes.size());i++){
        if(mShapes[i]->shape){
            GL3DObject::RenderShadowInitPass(pass +(obsObj.Dot(ligObj)>0?0:2));
            mShapes[i]->shape->RenderShadowPass(pass, objLight);
        }
    }

    glPopMatrix();

    AbstractRenderer::RenderShadow(pass,light,observer);
}