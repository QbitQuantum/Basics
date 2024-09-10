    //constructeur
    Fl_Progress_Window()  : Fl_Window(238,105,"Progression...")
    {
        // Progress 1 Label
        Fl_Box *label = new Fl_Box(10,10,215,15,"Pourcentage Général:");
        label->labelsize(12);
        label->labelfont(1);
        label->labelcolor((Fl_Color)136);
        label->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

        //Progress1
        progress1 = new Fl_Progress(10,28,215,20,"0%");
        progress1->selection_color((Fl_Color)175);
        progress1->maximum(100);
        progress1->minimum(0);
        progress1->labelsize(12);

        // Progress filename (label progress 2)
        progress_filename = new Fl_Box(10,52,215,15, "Fichier:");
        progress_filename->labelsize(12);
        progress_filename->labelfont(1);
        progress_filename->labelcolor((Fl_Color)136);
        progress_filename->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

        // Progress 2
        progress2 = new Fl_Progress(10,70,215,20,"0%");
        progress2->maximum(100);
        progress2->minimum(0);
        progress2->labelsize(12);
        progress2->selection_color((Fl_Color)175);

        //fin du window...
        this->set_modal();
        this->end();
    }