/** Returns the i-th window in the Previously Loaded Stream */
Window* CHUImporter::GetWindow(unsigned int wid)
{
    ieWord WindowID, XPos, YPos, Width, Height, BackGround;
    ieWord ControlsCount, FirstControl;
    ieResRef MosFile;
    unsigned int i;

    bool found = false;
    for (unsigned int c = 0; c < WindowCount; c++) {
        str->Seek( WEOffset + ( 0x1c * c ), GEM_STREAM_START );
        str->ReadWord( &WindowID );
        if (WindowID == wid) {
            found = true;
            break;
        }
    }
    if (!found) {
        return NULL;
    }
    str->Seek( 2, GEM_CURRENT_POS );
    str->ReadWord( &XPos );
    str->ReadWord( &YPos );
    str->ReadWord( &Width );
    str->ReadWord( &Height );
    str->ReadWord( &BackGround );
    str->ReadWord( &ControlsCount );
    str->ReadResRef( MosFile );
    str->ReadWord( &FirstControl );

    Window* win = new Window( WindowID, XPos, YPos, Width, Height );
    if (BackGround == 1) {
        ResourceHolder<ImageMgr> mos(MosFile);
        if (mos != NULL) {
            win->SetBackGround( mos->GetSprite2D(), true );
        } else
            printMessage( "CHUImporter","Cannot Load BackGround, skipping\n",YELLOW );
    }
    if (!core->IsAvailable( IE_BAM_CLASS_ID )) {
        printMessage( "CHUImporter","No BAM Importer Available, skipping controls\n",LIGHT_RED );
        return win;
    }
    for (i = 0; i < ControlsCount; i++) {
        str->Seek( CTOffset + ( ( FirstControl + i ) * 8 ), GEM_STREAM_START );
        ieDword COffset, CLength, ControlID;
        ieWord XPos, YPos, Width, Height;
        ieByte ControlType, temp;
        str->ReadDword( &COffset );
        str->ReadDword( &CLength );
        str->Seek( COffset, GEM_STREAM_START );
        str->ReadDword( &ControlID );
        str->ReadWord( &XPos );
        str->ReadWord( &YPos );
        str->ReadWord( &Width );
        str->ReadWord( &Height );
        str->Read( &ControlType, 1 );
        str->Read( &temp, 1 );
        switch (ControlType) {
        case IE_GUI_BUTTON:
        {
            //Button
            Button* btn = new Button( );
            btn->ControlID = ControlID;
            btn->XPos = XPos;
            btn->YPos = YPos;
            btn->Width = Width;
            btn->Height = Height;
            btn->ControlType = ControlType;
            ieResRef BAMFile;
            ieWord Cycle, UnpressedIndex, PressedIndex,
                   SelectedIndex, DisabledIndex;
            str->ReadResRef( BAMFile );
            str->ReadWord( &Cycle );
            str->ReadWord( &UnpressedIndex );
            str->ReadWord( &PressedIndex );
            str->ReadWord( &SelectedIndex );
            str->ReadWord( &DisabledIndex );
            btn->Owner = win;
            /** Justification comes from the .chu, other bits are set by script */
            if (!Width) {
                btn->SetFlags(IE_GUI_BUTTON_NO_IMAGE, BM_OR);
            }
            if (core->HasFeature(GF_UPPER_BUTTON_TEXT)) {
                btn->SetFlags(IE_GUI_BUTTON_CAPS, BM_OR);
            }

            btn->SetFlags( Cycle&0xff00, BM_OR );
            if (strnicmp( BAMFile, "guictrl\0", 8 ) == 0) {
                if (UnpressedIndex == 0) {
                    printMessage("CHUImporter", "Special Button Control, Skipping Image Loading\n",GREEN );
                    win->AddControl( btn );
                    break;
                }
            }
            AnimationFactory* bam = ( AnimationFactory* )
                                    gamedata->GetFactoryResource( BAMFile,
                                            IE_BAM_CLASS_ID, IE_NORMAL );
            if (!bam ) {
                printMessage( "CHUImporter","Cannot Load Button Images, skipping control\n",LIGHT_RED );
                /* IceWind Dale 2 has fake BAM ResRefs for some Buttons,
                   this will handle bad ResRefs */
                win->AddControl( btn );
                break;
            }
            /** Cycle is only a byte for buttons */
            Sprite2D* tspr = bam->GetFrame( UnpressedIndex, (unsigned char) Cycle );
            btn->SetImage( IE_GUI_BUTTON_UNPRESSED, tspr );
            tspr = bam->GetFrame( PressedIndex, (unsigned char) Cycle );
            btn->SetImage( IE_GUI_BUTTON_PRESSED, tspr );
            //ignorebuttonframes is a terrible hack
            if (core->HasFeature( GF_IGNORE_BUTTON_FRAMES) ) {
                if (bam->GetCycleSize( (unsigned char) Cycle) == 4 )
                    SelectedIndex=2;
            }
            tspr = bam->GetFrame( SelectedIndex, (unsigned char) Cycle );
            btn->SetImage( IE_GUI_BUTTON_SELECTED, tspr );
            if (core->HasFeature( GF_IGNORE_BUTTON_FRAMES) ) {
                if (bam->GetCycleSize( (unsigned char) Cycle) == 4 )
                    DisabledIndex=3;
            }
            tspr = bam->GetFrame( DisabledIndex, (unsigned char) Cycle );
            btn->SetImage( IE_GUI_BUTTON_DISABLED, tspr );
            win->AddControl( btn );
        }
        break;

        case IE_GUI_PROGRESSBAR:
        {
            //GemRB specific, progressbar
            ieResRef MOSFile, MOSFile2;
            ieResRef BAMFile;
            ieWord KnobXPos, KnobYPos;
            ieWord CapXPos, CapYPos;
            ieWord KnobStepsCount;
            ieWord Cycle;

            str->ReadResRef( MOSFile );
            str->ReadResRef( MOSFile2 );
            str->ReadResRef( BAMFile );
            str->ReadWord( &KnobStepsCount );
            str->ReadWord( &Cycle );
            str->ReadWord( &KnobXPos );
            str->ReadWord( &KnobYPos );
            str->ReadWord( &CapXPos );
            str->ReadWord( &CapYPos );
            Progressbar* pbar = new Progressbar(KnobStepsCount, true );
            pbar->ControlID = ControlID;
            pbar->XPos = XPos;
            pbar->YPos = YPos;
            pbar->ControlType = ControlType;
            pbar->Width = Width;
            pbar->Height = Height;
            pbar->SetSliderPos( KnobXPos, KnobYPos, CapXPos, CapYPos );

            Sprite2D* img = NULL;
            Sprite2D* img2 = NULL;
            if ( MOSFile[0] ) {
                ResourceHolder<ImageMgr> mos(MOSFile);
                img = mos->GetSprite2D();
            }
            if ( MOSFile2[0] ) {
                ResourceHolder<ImageMgr> mos(MOSFile2);
                img2 = mos->GetSprite2D();
            }

            pbar->SetImage( img, img2 );
            if( KnobStepsCount ) {
                /* getting the bam */
                AnimationFactory *af = (AnimationFactory *)
                                       gamedata->GetFactoryResource(BAMFile, IE_BAM_CLASS_ID );
                /* Getting the Cycle of the bam */
                pbar->SetAnimation(af->GetCycle( Cycle & 0xff ) );
            }
            else {
                ResourceHolder<ImageMgr> mos(BAMFile);
                Sprite2D* img3 = mos->GetSprite2D();
                pbar->SetBarCap( img3 );
            }
            win->AddControl( pbar );
        }
        break;
        case IE_GUI_SLIDER:
        {
            //Slider
            ieResRef MOSFile, BAMFile;
            ieWord Cycle, Knob, GrabbedKnob;
            ieWord KnobXPos, KnobYPos, KnobStep, KnobStepsCount;
            str->ReadResRef( MOSFile );
            str->ReadResRef( BAMFile );
            str->ReadWord( &Cycle );
            str->ReadWord( &Knob );
            str->ReadWord( &GrabbedKnob );
            str->ReadWord( &KnobXPos );
            str->ReadWord( &KnobYPos );
            str->ReadWord( &KnobStep );
            str->ReadWord( &KnobStepsCount );
            Slider* sldr = new Slider( KnobXPos, KnobYPos, KnobStep, KnobStepsCount, true );
            sldr->ControlID = ControlID;
            sldr->XPos = XPos;
            sldr->YPos = YPos;
            sldr->ControlType = ControlType;
            sldr->Width = Width;
            sldr->Height = Height;
            ResourceHolder<ImageMgr> mos(MOSFile);
            Sprite2D* img = mos->GetSprite2D();
            sldr->SetImage( IE_GUI_SLIDER_BACKGROUND, img);

            AnimationFactory* bam = ( AnimationFactory* )
                                    gamedata->GetFactoryResource( BAMFile,
                                            IE_BAM_CLASS_ID, IE_NORMAL );
            if( bam ) {
                img = bam->GetFrame( Knob, 0 );
                sldr->SetImage( IE_GUI_SLIDER_KNOB, img );
                img = bam->GetFrame( GrabbedKnob, 0 );
                sldr->SetImage( IE_GUI_SLIDER_GRABBEDKNOB, img );
            }
            else {
                sldr->SetState(IE_GUI_SLIDER_BACKGROUND);
            }
            win->AddControl( sldr );
        }
        break;

        case IE_GUI_EDIT:
        {
            //Text Edit
            ieResRef BGMos;
            ieResRef FontResRef, CursorResRef;
            ieWord maxInput;
            ieWord CurCycle, CurFrame;
            ieWord PosX, PosY;

            str->ReadResRef( BGMos );
            str->Seek( 16, GEM_CURRENT_POS );
            str->ReadResRef( CursorResRef );
            str->ReadWord( &CurCycle );
            str->ReadWord( &CurFrame );
            str->ReadWord( &PosX );
            str->ReadWord( &PosY );
            str->Seek( 4, GEM_CURRENT_POS );
            str->ReadResRef( FontResRef );
            str->Seek( 34, GEM_CURRENT_POS );
            str->ReadWord( &maxInput );
            Font* fnt = core->GetFont( FontResRef );

            AnimationFactory* bam = ( AnimationFactory* )
                                    gamedata->GetFactoryResource( CursorResRef,
                                            IE_BAM_CLASS_ID,
                                            IE_NORMAL );
            Sprite2D *cursor = NULL;
            if (bam) {
                cursor = bam->GetFrame( CurCycle, CurFrame );
            }

            ResourceHolder<ImageMgr> mos(BGMos);
            Sprite2D *img = NULL;
            if(mos) {
                img = mos->GetSprite2D();
            }

            TextEdit* te = new TextEdit( maxInput, PosX, PosY );
            te->ControlID = ControlID;
            te->XPos = XPos;
            te->YPos = YPos;
            te->Width = Width;
            te->Height = Height;
            te->ControlType = ControlType;
            te->SetFont( fnt );
            te->SetCursor( cursor );
            te->SetBackGround( img );
            win->AddControl( te );
        }
        break;

        case IE_GUI_TEXTAREA:
        {
            //Text Area
            ieResRef FontResRef, InitResRef;
            Color fore, init, back;
            ieWord SBID;
            str->ReadResRef( FontResRef );
            str->ReadResRef( InitResRef );
            Font* fnt = core->GetFont( FontResRef );
            Font* ini = core->GetFont( InitResRef );
            str->Read( &fore, 4 );
            str->Read( &init, 4 );
            str->Read( &back, 4 );
            str->ReadWord( &SBID );
            TextArea* ta = new TextArea( fore, init, back );
            ta->ControlID = ControlID;
            ta->XPos = XPos;
            ta->YPos = YPos;
            ta->Width = Width;
            ta->Height = Height;
            ta->ControlType = ControlType;
            ta->SetFonts( ini, fnt );
            win->AddControl( ta );
            if (SBID != 0xffff)
                win->Link( SBID, ( unsigned short ) ControlID );
        }
        break;

        case IE_GUI_LABEL:
        {
            //Label
            ieResRef FontResRef;
            ieStrRef StrRef;
            RevColor fore, back;
            ieWord alignment;
            str->ReadDword( &StrRef );
            str->ReadResRef( FontResRef );
            Font* fnt = core->GetFont( FontResRef );
            str->Read( &fore, 4 );
            str->Read( &back, 4 );
            str->ReadWord( &alignment );
            Label* lab = new Label( fnt );
            lab->ControlID = ControlID;
            lab->XPos = XPos;
            lab->YPos = YPos;
            lab->Width = Width;
            lab->Height = Height;
            lab->ControlType = ControlType;
            char* str = core->GetString( StrRef );
            lab->SetText( str );
            core->FreeString( str );
            if (alignment & 1) {
                lab->useRGB = true;
                Color f, b;
                f.r = fore.b;
                f.g = fore.g;
                f.b = fore.r;
                f.a = 0;
                b.r = back.b;
                b.g = back.g;
                b.b = back.r;
                b.a = 0;
                lab->SetColor( f, b );
            }
            int align = IE_FONT_ALIGN_CENTER;
            if (( alignment & 0x10 ) != 0) {
                align = IE_FONT_ALIGN_RIGHT;
                goto endvertical;
            }
            if (( alignment & 0x04 ) != 0) {
                goto endvertical;
            }
            if (( alignment & 0x08 ) != 0) {
                align = IE_FONT_ALIGN_LEFT;
                goto endvertical;
            }
endvertical:
            if (( alignment & 0x20 ) != 0) {
                align |= IE_FONT_ALIGN_TOP;
                goto endalign;
            }
            if (( alignment & 0x80 ) != 0) {
                align |= IE_FONT_ALIGN_BOTTOM;
            } else {
                align |= IE_FONT_ALIGN_MIDDLE;
            }
endalign:
            lab->SetAlignment( align );
            win->AddControl( lab );
        }
        break;

        case IE_GUI_SCROLLBAR:
        {
            //ScrollBar
            ieResRef BAMResRef;
            ieWord Cycle, Trough, Slider, TAID;
            ieWord UpUnPressed, UpPressed;
            ieWord DownUnPressed, DownPressed;

            str->ReadResRef( BAMResRef );
            str->ReadWord( &Cycle );
            str->ReadWord( &UpUnPressed );
            str->ReadWord( &UpPressed );
            str->ReadWord( &DownUnPressed );
            str->ReadWord( &DownPressed );
            str->ReadWord( &Trough );
            str->ReadWord( &Slider );
            str->ReadWord( &TAID );
            ScrollBar* sbar = new ScrollBar();
            sbar->ControlID = ControlID;
            sbar->XPos = XPos;
            sbar->YPos = YPos;
            sbar->Width = Width;
            sbar->Height = Height;
            sbar->ControlType = ControlType;

            AnimationFactory* bam = ( AnimationFactory* )
                                    gamedata->GetFactoryResource( BAMResRef,
                                            IE_BAM_CLASS_ID, IE_NORMAL );
            if (bam) {
                sbar->SetImage( IE_GUI_SCROLLBAR_UP_UNPRESSED,
                                bam->GetFrame( UpUnPressed, Cycle ) );
                sbar->SetImage( IE_GUI_SCROLLBAR_UP_PRESSED,
                                bam->GetFrame( UpPressed, Cycle ) );
                sbar->SetImage( IE_GUI_SCROLLBAR_DOWN_UNPRESSED,
                                bam->GetFrame( DownUnPressed, Cycle ) );
                sbar->SetImage( IE_GUI_SCROLLBAR_DOWN_PRESSED,
                                bam->GetFrame( DownPressed, Cycle ) );
                sbar->SetImage( IE_GUI_SCROLLBAR_TROUGH,
                                bam->GetFrame( Trough, Cycle ) );
                sbar->SetImage( IE_GUI_SCROLLBAR_SLIDER,
                                bam->GetFrame( Slider, Cycle ) );
            }
            win->AddControl( sbar );
            if (TAID != 0xffff)
                win->Link( ( unsigned short ) ControlID, TAID );
        }
        break;

        default:
            printMessage( "CHUImporter","Control Not Supported\n",LIGHT_RED );
        }
    }
    return win;
}