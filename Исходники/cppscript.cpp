void CPPScript::mf_fillFile_h(_QSTR& class_name)
{
    qDebug()<<"mf_fillFile_h class_name: "<<class_name<<endl;
    string file_class_name = getDirFolder()+STR_OBJECT+class_name.toStdString()+".h";
    fstream file(file_class_name.c_str());

    string str_class_name_upper = class_name.toUpper().toStdString();
    string str_class_name = class_name.toStdString();

    file<<"#ifndef OBJECT_"<<str_class_name_upper<<"_H"<<endl;
    file<<"#define OBJECT_"<<str_class_name_upper<<"_H"<<endl;
    file<<endl;
    file<<"#include \"share_include.h\""<<endl;
    file<<endl;
    file<<"#define TABLE_NAME_"<<class_name.toUpper().toStdString()<<" \""<<class_name.toStdString()<<"\""<<endl;
    file<<"class object_"<<str_class_name<<":public object_general"<<endl;
    file<<"{"<<endl;
    file<<endl;

    file<<"private:"<<endl;

    for(unsigned int i = 0; i < md_o_v_column_names.size(); i++)
    {
        string temp = md_o_v_column_names[i].toStdString();
        file<<"\t_QSTR md_o_"<<temp<<";"<<endl;
    }
    file<<endl;
    file<<"public:"<<endl;
    file<<"\tobject_"<<str_class_name<<"();"<<endl;

    string temp_1 = md_o_v_column_names[0].toStdString();
    file<<"\tobject_"<<str_class_name<<"(_QSTR "<<temp_1;
    for(unsigned int i = 1; i < md_o_v_column_names.size(); i++)
    {
        string temp = md_o_v_column_names[i].toStdString();
        file<<", _QSTR "<<temp;
    }
    file<<");"<<endl;

    if(md_o_v_column_names.size() > 1)
    {
        string temp_2 = md_o_v_column_names[1].toStdString();
        file<<"\tobject_"<<str_class_name<<"(_QSTR "<<temp_2;
        for(unsigned int i = 2; i < md_o_v_column_names.size(); i++)
        {
            string temp = md_o_v_column_names[i].toStdString();
            file<<", _QSTR "<<temp;
        }
        file<<");"<<endl;
        file<<endl;
    }
    for(unsigned int i = 0; i < md_o_v_column_names.size(); i++)
    {
        string temp = md_o_v_column_names[i].toStdString();
        file<<"\tvoid mf_set_"<<temp<<"(_QSTR "<<temp<<");"<<endl;
    }

    file<<endl;
    for(unsigned int i = 0; i < md_o_v_column_names.size(); i++)
    {
        string temp = md_o_v_column_names[i].toStdString();
        file<<"\t_QSTR mf_get_"<<temp<<"();"<<endl;
    }
    file<<endl;


    file<<"\tbool mf_load(_QSTR pk);"<<endl;
    file<<"\tbool mf_add();"<<endl;
    file<<"\tbool mf_update();"<<endl;
    file<<"\tbool mf_remove();"<<endl;
    //file<<"\tQSqlQueryModel* mf_get();"<<endl;
    file<<endl;
    file<<"\t~object_"<<str_class_name<<"();"<<endl;
    file<<"};";
    file<<endl;
    file<<"#endif // OBJECT_"+str_class_name_upper+"_H";

    file<<endl;
    file<<"\t/*"<<endl;

    file<<"\tobject_"<<str_class_name<<" obj_"<<str_class_name<<";"<<endl;
    for(unsigned int i = 0; i < md_o_v_column_names.size(); i++)
    {
        string temp = md_o_v_column_names[i].toStdString();
        file<<"\t"<<"obj_"<<str_class_name<<"."<<"mf_set_"<<temp<<"();"<<endl;
    }

    file<<endl;
    for(unsigned int i = 0; i < md_o_v_column_names.size(); i++)
    {
        string temp = md_o_v_column_names[i].toStdString();
        file<<"\t"<<"obj_"<<str_class_name<<"."<<"mf_get_"<<temp<<"();"<<endl;
    }
    file<<"\t*/"<<endl;

}