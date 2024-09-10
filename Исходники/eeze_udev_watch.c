EAPI Eeze_Udev_Watch *
eeze_udev_watch_add(Eeze_Udev_Type     type,
                    int                event,
                    Eeze_Udev_Watch_Cb cb,
                    void              *user_data)
{
   _udev_monitor *mon = NULL;
   int fd;
   Ecore_Fd_Handler *handler;
   Eeze_Udev_Watch *watch = NULL;
   struct _store_data *store = NULL;

   if (!(store = calloc(1, sizeof(struct _store_data))))
     return NULL;

   if (!(watch = malloc(sizeof(Eeze_Udev_Watch))))
     goto error;

   if (!(mon = udev_monitor_new_from_netlink(udev, "udev")))
     goto error;

#ifndef OLD_UDEV_RRRRRRRRRRRRRR

   switch (type)
     {
      case EEZE_UDEV_TYPE_KEYBOARD:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "input", NULL);
        break;

      case EEZE_UDEV_TYPE_MOUSE:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "input", NULL);
        break;

      case EEZE_UDEV_TYPE_TOUCHPAD:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "input", NULL);
        break;

      case EEZE_UDEV_TYPE_DRIVE_MOUNTABLE:
      case EEZE_UDEV_TYPE_DRIVE_INTERNAL:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "block", NULL);
        break;

      case EEZE_UDEV_TYPE_DRIVE_REMOVABLE:
      case EEZE_UDEV_TYPE_DRIVE_CDROM:
        break;

      case EEZE_UDEV_TYPE_POWER_AC:
      case EEZE_UDEV_TYPE_POWER_BAT:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "power_supply",
                                                        NULL);
        break;

      case EEZE_UDEV_TYPE_NET:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "net", NULL);
        break;

      case EEZE_UDEV_TYPE_IS_IT_HOT_OR_IS_IT_COLD_SENSOR:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "hwmon", NULL);
        break;

      /*
              case EEZE_UDEV_TYPE_ANDROID:
                udev_monitor_filter_add_match_subsystem_devtype(mon, "input", "usb_interface");
                break;
       */

      case EEZE_UDEV_TYPE_V4L:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "video4linux",
                                                        NULL);
        break;

      case EEZE_UDEV_TYPE_BLUETOOTH:
        udev_monitor_filter_add_match_subsystem_devtype(mon, "bluetooth",
                                                        NULL);
        break;

      default:
        break;
     }

#endif

   if (udev_monitor_enable_receiving(mon))
     goto error;

   fd = udev_monitor_get_fd(mon);
   store->func = cb;
   store->data = user_data;
   store->mon = mon;
   store->type = type;
   store->watch = watch;
   store->event = event;

   if (!(handler = ecore_main_fd_handler_add(fd, ECORE_FD_READ,
                                             _get_syspath_from_watch, store, NULL, NULL)))
     goto error;

   watch->mon = mon;
   watch->handler = handler;
   return watch;
error:
   if (store)
     free(store);
   if (watch)
     free(watch);
   if (mon)
     udev_monitor_unref(mon);
   ERR("Could not create watch!");
   return NULL;
}