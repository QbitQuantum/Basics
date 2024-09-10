void CppCodeGenerator::GenConstruction(PObjectBase obj, bool is_widget)
{
  ObjectType type = obj->GetObjectType();
  
  switch (type)
  {
    case T_WIDGET:
    {
      // comprobamos si no se ha declarado como atributo de clase
      // en cuyo caso lo declaramos en el constructor
      string perm_str = obj->GetProperty("permission")->GetValue();
      if (perm_str == "none")
        m_source->WriteLn(GetCode(obj,"declaration"));
      
      m_source->WriteLn(GetCode(obj,"construction"));
      GenSettings(obj->GetObjectInfo(), obj);
      
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        GenConstruction(obj->GetChild(i),true);
    }
    break;

    case T_SIZER:
    {
      m_source->WriteLn(GetCode(obj,"declaration"));
      m_source->WriteLn(GetCode(obj,"construction"));
      GenSettings(obj->GetObjectInfo(), obj);
      
      for (unsigned int i=0; i<obj->GetChildCount() ; i++)
        GenConstruction(obj->GetChild(i),false);
        
      if (is_widget)
      {
        // hay que hacer un SetSizer, pero
        // no hay una plantilla para esta operación :-(
        // No conviene empotrar plantillas en la aplicación, ya que
        // para hacer cambios hay que recompilar el código (sin que
        // sirva de precedente, vamos a hacerlo aquí)
        string _template = "#wxparent $name->SetSizer($name);\n"
                           "#wxparent $name->SetAutoLayout(true);\n"
                           "#wxparent $name->Layout();";
        CppTemplateParser parser(obj,_template);
        m_source->WriteLn(parser.ParseTemplate());
      } 
      
    }
    break;

    case T_SPACER:
      // nada que hacer
      break;
    
    case T_SIZERITEM:
    {
      // El hijo, hay que añadirlo al sizer teniendo en cuenta el tipo
      // del objeto hijo (hay 3 rutinas diferentes)
      GenConstruction(obj->GetChild(0),false);
      
      ObjectType child_type = obj->GetChild(0)->GetObjectType();
      string temp_name;
      switch (child_type)
      {
        case T_WIDGET:
          temp_name = "window_add";
          break;

        case T_SIZER:
          temp_name = "sizer_add";
          break;

        case T_SPACER:
          temp_name = "spacer_add";
          break;

        default:
          assert(false);
          break;
      }
      m_source->WriteLn(GetCode(obj,temp_name));
    }
    break;
    
    default:
    break;
  }
}