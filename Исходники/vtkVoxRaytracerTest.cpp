int main()
{
    BEGIN_TESTING(vtk VoxRaytracer);


    // muon scatter //
    MuonScatter muon;
    muon.LineIn().origin() << -6, 12, -6, 1;
    muon.LineIn().direction() << 1 , -1 , 1 , 0;
    muon.LineOut().origin() << 6 , -4 , 6 , 1;
    muon.LineOut().direction() << 1 , -1 , 1 , 0;

    Vtk::vtkMuonScatter v_muon(muon);


    // structured grid //
    ImageData grid(Vector3i(12,10,12));
    grid.SetSpacing(Vector3f(1,1,1));
    grid.SetPosition(Vector3f(0,0,0));


    Vtk::vtkStructuredGrid v_grid(grid);


    // voxraytracer //
    VoxRaytracer rt(grid);
    Vector4f pt;
    rt.GetEntryPoint(muon.LineIn(),pt);
    std::cout << pt.transpose() << "\n";

    Vtk::vtkVoxRaytracerRepresentation v_rt(rt);
    v_rt.SetMuon(muon);
    v_rt.SetRayColor(Vector4f(1,0,0,1));

    //    // renderer //
    Vtk::Viewer viewer;

    // widget //
    vtkBoxWidget *widget = v_grid.GetWidget();


    vtkWidgetCallback *cbk = vtkWidgetCallback::New();
    cbk->SetTracer(&v_rt);
    cbk->SetMuon(&muon);
    cbk->SetAnnotation(viewer.GetAnnotation());
    widget->AddObserver(vtkCommand::InteractionEvent, cbk);
    widget->SetInteractor(viewer.GetInteractor());
    widget->PlaceWidget();
    widget->On();

    viewer.AddPuppet(v_grid);
    viewer.AddPuppet(v_rt);
    viewer.AddPuppet(v_muon);
    viewer.Start();


    END_TESTING;
}