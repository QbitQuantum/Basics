int main(int argc, char *argv[])
{
    AutoData *Data;
    doublereal u[3] = {0., 0., 0.};
    integer ipar[3] = {0, 1, 2};
    doublereal par[3] = {0., 14., 2.};
    
    Data = (AutoData *)MALLOC(sizeof(AutoData));

    BlankData(Data);
    DefaultData(Data);
    
    // Equilibrium points
    CreateSpecialPoint(Data,3,1,u,3,ipar,par,NULL,NULL,NULL,NULL);     // 9 = Beginning point, 1 = branch label
    Data->iap.irs = 1;      // Start from this point
    
    Data->print_input = 0;
    Data->print_output = 0;
    printf("\nEquilibrium points...\n");
    AUTO(Data);
    
    system("touch d.ab");
    system("cat fort.9 >> d.ab");
    system("rm fort.9");
    
    // Periodic orbits
    CleanupSolution(Data);
    DefaultData(Data);
    
    Data->iap.ips = 2;      // BVP
    Data->iap.irs = 4;      // Label of Hopf point
    Data->iap.ilp = 0;      // No detection of folds
    Data->iap.nicp = 2;     // Number of free parameters
    Data->iap.nmx = 150;    // Number of points on branch
    Data->iap.npr = 30;     // Output point and cycle after every npr steps
    Data->rap.dsmax = 0.5;  // Maximum arclength stepsize

    Data->icp = (integer *)REALLOC(Data->icp,Data->iap.nicp*sizeof(integer));
    Data->icp[1] = 10;      // Adds period to free parameters
    
    printf("\nPeriodic orbits...\n");
    AUTO(Data);
    
    system("touch d.ab");
    system("cat fort.9 >> d.ab");
    system("rm fort.9");
    
    // Fold points
    CleanupSolution(Data);
    DefaultData(Data);
    
    Data->iap.irs = 2;        // Label of limit point
    Data->iap.nicp = 2;       // Number of free parameters
    Data->iap.isp = 1;        // Turn on detection of branch points
    Data->iap.isw = 2;        // Controls branch switching (?)
    Data->rap.dsmax = 0.5;    // Maximum arclength stepsize
    Data->icp[1] = 2;         // 3rd parameter is free
    
    printf("\nFold points...\n");
    AUTO(Data);
    
    system("touch d.ab");
    system("cat fort.9 >> d.ab");
    system("rm fort.9");

    // Fold points (reverse)
    CleanupSolution(Data);
    DefaultData(Data);
    
    Data->iap.irs = 2;       // Label of limit point
    Data->iap.nicp = 2;      // Number of free parameters
    Data->iap.isp = 1;       // Turn on detection of branch points
    Data->iap.isw = 2;       // Controls branch switching (?)
    Data->rap.dsmax = 0.5;   // Maximum arclength stepsize
    Data->icp[1] = 2;        // 3rd parameter is free
    Data->rap.ds = -0.01;    // Stepsize (reverse)
    
    printf("\nFold points (reverse)...\n");
    AUTO(Data);
    
    system("touch d.ab");
    system("cat fort.9 >> d.ab");
    system("rm fort.9");

    // Hopf points (reverse)
    CleanupSolution(Data);
    DefaultData(Data);
    
    Data->iap.irs = 4;       // Label of hopf point
    Data->iap.nicp = 2;      // Number of free parameters
    Data->iap.isw = 2;       // Controls branch switching (?)
    Data->rap.dsmax = 0.5;   // Maximum arclength stepsize
    Data->icp[1] = 2;        // 3rd parameter is free
    Data->rap.ds = -0.01;    // Stepsize (reverse)
    
    printf("\nHopf points (reverse)...\n");
    AUTO(Data);
    
    system("touch d.ab");
    system("cat fort.9 >> d.ab");
    system("rm fort.9");
    
    CleanupAll(Data);
    
    return 0;
}