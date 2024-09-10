void GraphicsWindow::MenuView(int id) {
    switch(id) {
        case MNU_ZOOM_IN:
            SS.GW.scale *= 1.2;
            SS.ScheduleShowTW();
            break;

        case MNU_ZOOM_OUT:
            SS.GW.scale /= 1.2;
            SS.ScheduleShowTW();
            break;

        case MNU_ZOOM_TO_FIT:
            SS.GW.ZoomToFit(/*includingInvisibles=*/false, /*useSelection=*/true);
            SS.ScheduleShowTW();
            break;

        case MNU_SHOW_GRID:
            SS.GW.showSnapGrid = !SS.GW.showSnapGrid;
            if(SS.GW.showSnapGrid && !SS.GW.LockedInWorkplane()) {
                Message("No workplane is active, so the grid will not "
                        "appear.");
            }
            SS.GW.EnsureValidActives();
            InvalidateGraphics();
            break;

        case MNU_PERSPECTIVE_PROJ:
            SS.usePerspectiveProj = !SS.usePerspectiveProj;
            if(SS.cameraTangent < 1e-6) {
                Error("The perspective factor is set to zero, so the view will "
                      "always be a parallel projection.\n\n"
                      "For a perspective projection, modify the perspective "
                      "factor in the configuration screen. A value around 0.3 "
                      "is typical.");
            }
            SS.GW.EnsureValidActives();
            InvalidateGraphics();
            break;

        case MNU_ONTO_WORKPLANE:
            if(SS.GW.LockedInWorkplane()) {
                SS.GW.AnimateOntoWorkplane();
                SS.GW.ClearSuper();
                SS.ScheduleShowTW();
                break;
            }  // if not in 2d mode fall through and use ORTHO logic
        case MNU_NEAREST_ORTHO:
        case MNU_NEAREST_ISO: {
            static const Vector ortho[3] = {
                Vector::From(1, 0, 0),
                Vector::From(0, 1, 0),
                Vector::From(0, 0, 1)
            };
            double sqrt2 = sqrt(2.0), sqrt6 = sqrt(6.0);
            Quaternion quat0 = Quaternion::From(SS.GW.projRight, SS.GW.projUp);
            Quaternion quatf = quat0;
            double dmin = 1e10;

            // There are 24 possible views; 3*2*2*2
            int i, j, negi, negj;
            for(i = 0; i < 3; i++) {
                for(j = 0; j < 3; j++) {
                    if(i == j) continue;
                    for(negi = 0; negi < 2; negi++) {
                        for(negj = 0; negj < 2; negj++) {
                            Vector ou = ortho[i], ov = ortho[j];
                            if(negi) ou = ou.ScaledBy(-1);
                            if(negj) ov = ov.ScaledBy(-1);
                            Vector on = ou.Cross(ov);

                            Vector u, v;
                            if(id == MNU_NEAREST_ORTHO || id == MNU_ONTO_WORKPLANE) {
                                u = ou;
                                v = ov;
                            } else {
                                u =
                                    ou.ScaledBy(1/sqrt2).Plus(
                                    on.ScaledBy(-1/sqrt2));
                                v =
                                    ou.ScaledBy(-1/sqrt6).Plus(
                                    ov.ScaledBy(2/sqrt6).Plus(
                                    on.ScaledBy(-1/sqrt6)));
                            }

                            Quaternion quatt = Quaternion::From(u, v);
                            double d = min(
                                (quatt.Minus(quat0)).Magnitude(),
                                (quatt.Plus(quat0)).Magnitude());
                            if(d < dmin) {
                                dmin = d;
                                quatf = quatt;
                            }
                        }
                    }
                }
            }

            SS.GW.AnimateOnto(quatf, SS.GW.offset);
            break;
        }

        case MNU_CENTER_VIEW:
            SS.GW.GroupSelection();
            if(SS.GW.gs.n == 1 && SS.GW.gs.points == 1) {
                Quaternion quat0;
                // Offset is the selected point, quaternion is same as before
                Vector pt = SK.GetEntity(SS.GW.gs.point[0])->PointGetNum();
                quat0 = Quaternion::From(SS.GW.projRight, SS.GW.projUp);
                SS.GW.AnimateOnto(quat0, pt.ScaledBy(-1));
                SS.GW.ClearSelection();
            } else {
                Error("Select a point; this point will become the center "
                      "of the view on screen.");
            }
            break;

        case MNU_SHOW_MENU_BAR:
            ToggleMenuBar();
            SS.GW.EnsureValidActives();
            InvalidateGraphics();
            break;

        case MNU_SHOW_TOOLBAR:
            SS.showToolbar = !SS.showToolbar;
            SS.GW.EnsureValidActives();
            InvalidateGraphics();
            break;

        case MNU_SHOW_TEXT_WND:
            SS.GW.showTextWindow = !SS.GW.showTextWindow;
            SS.GW.EnsureValidActives();
            break;

        case MNU_UNITS_INCHES:
            SS.viewUnits = SolveSpaceUI::UNIT_INCHES;
            SS.ScheduleShowTW();
            SS.GW.EnsureValidActives();
            break;

        case MNU_UNITS_MM:
            SS.viewUnits = SolveSpaceUI::UNIT_MM;
            SS.ScheduleShowTW();
            SS.GW.EnsureValidActives();
            break;

        case MNU_FULL_SCREEN:
            ToggleFullScreen();
            SS.GW.EnsureValidActives();
            break;

        default: oops();
    }
    InvalidateGraphics();
}