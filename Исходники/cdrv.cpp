int drv_button(int drvid, void *a0, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9)
{
    handle_head* head = (handle_head*)a0;
    QPushButton *self = (QPushButton*)head->native;
    switch (drvid) {
    case BUTTON_INIT: {
        drvNewObj(a0,new QPushButton);
        break;
    }
    case BUTTON_SETFLAT: {
        self->setFlat(drvGetBool(a1));
        break;
    }
    case BUTTON_ISFLAT: {
        drvSetBool(a1,self->isFlat());
        break;
    }
    case BUTTON_SETDEFAULT: {
        self->setDefault(drvGetBool(a1));
        break;
    }
    case BUTTON_ISDEFAULT: {
        drvSetBool(a1,self->isDefault());
        break;
    }
    case BUTTON_SETMENU: {
        self->setMenu(drvGetMenu(a1));
        break;
    }
    case BUTTON_MENU: {
        drvSetHandle(a1,self->menu());
        break;
    }
    case BUTTON_ONCLICKED: {
        QObject::connect(self,SIGNAL(clicked()),drvNewSignal(self,a1,a2),SLOT(call()));
        break;
    }
    default:
        return 0;
    }
    return 1;
}