   sd->val = from;
   pd->intvl_to = to;

   if (pd->intvl_from < sd->val_min) {
        pd->intvl_from = sd->val_min;
        sd->val = sd->val_min;
   }
   if (pd->intvl_to > sd->val_max) pd->intvl_to = sd->val_max;

   efl_ui_slider_val_set(obj);
}

EOLIAN static void
_efl_ui_slider_interval_interval_value_get(const Eo *obj EINA_UNUSED, Efl_Ui_Slider_Interval_Data *pd, double *from, double *to)
{
   if (from) *from = fmin(pd->intvl_from, pd->intvl_to);
   if (to) *to = fmax(pd->intvl_from, pd->intvl_to);
}

EOLIAN static Efl_Object *
_efl_ui_slider_interval_efl_object_constructor(Eo *obj, Efl_Ui_Slider_Interval_Data *pd EINA_UNUSED)
{
   ELM_WIDGET_DATA_GET_OR_RETURN(obj, wd, NULL);

   if (!elm_widget_theme_klass_get(obj))
     elm_widget_theme_klass_set(obj, "slider_interval");
   obj = efl_constructor(efl_super(obj, MY_CLASS));

   return obj;
}
