// on_create_result_1
int TextHandler::build_tmx_result_file(const TextID & tid, string & result_file_name)
{
    int ret = SUCCESS;

    //从数据库读取翻译结果
    vector<boost::tuple<string, string, string> > result_vec;
    string tgt_language;

    ret = DBOperation::GetTransResultPair(tid, result_vec, tgt_language);

    if(SUCCESS != ret)
    {
        return ERR_GET_TGT_VEC_FROM_DB;
    }

    //生成TMX 格式数据
    string tmx_data;

//<?xml version="1.0" encoding=UTF-8" ?>
//
//<tmx version="1.4">
//	<header creationdate=""			    <!--创建日期-->
//			creationtool="" 			<!--创建工具-->
//			creationtoolversion=""      <!--创建工具的版本-->
//			datatype="unknown"          <!--数据类型：有很多种，一般使用默认-->
//			o-tmf="unknown"				<!--源存储格式-->
//			segtype="block"				<!--段值：block,paragraph,sentence,phrase-->
//			srclang="*all*"				<!--源语言:常使用*all*-->
//			adminlang="en"/>            <!--Administrative language-->
//
//	<body>
//		<tu changedate="">              <!--修改日期-->
//			<tuv xml:lang="en"><seg>introduction</seg></tuv>
//			<tuv xml:lang="zh-cn"><seg>简介</seg></tuv>
//		</tu>
//		<tu changedate="">
//			<tuv xml:lang="en"><seg>conclusion</seg></tuv>
//			<tuv xml:lang="zh-cn"><seg>总结</seg></tuv>
//		</tu>
//	</body>
//</tmx>

    TiXmlDocument * xmlDocs = new TiXmlDocument();

    try
    {
        //声明
        TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "UTF-8", "");
        xmlDocs->LinkEndChild(dec);

        //tmx 节点
        TiXmlElement * tmxElem = new TiXmlElement("tmx");
        xmlDocs->LinkEndChild(tmxElem);

        //header节点
        TiXmlElement * headerElem = new TiXmlElement("header");
        headerElem->SetAttribute("creationdate", "");
        headerElem->SetAttribute("creationtool", "ict_trans");
        headerElem->SetAttribute("creationtoolversion", "1.0");
        headerElem->SetAttribute("datatype", "unknown");
        headerElem->SetAttribute("o-tmf", "unknown");
        headerElem->SetAttribute("segtype", "sentence");
        headerElem->SetAttribute("srclang", "en");
        headerElem->SetAttribute("srclang", "zh-cn");
        tmxElem->LinkEndChild(headerElem);

        //body节点
        TiXmlElement * bodyElem = new TiXmlElement("body");
        tmxElem->LinkEndChild(bodyElem);

        //loop tu 节点
        for(size_t i=0; i<result_vec.size(); ++i)
        {
            //tu节点
            TiXmlElement * tuElem = new TiXmlElement("tu");
            bodyElem->LinkEndChild(tuElem);

            //tuv 节点对
            string * p_english = NULL;
            string * p_chinese = NULL;

            if(LANGUAGE_CHINESE == tgt_language)
            {
                p_english = &result_vec[i].get<0>();

                if(result_vec[i].get<2>().size() > 0)
                {
                    CLanguage::En2ChPost(result_vec[i].get<2>());
                    p_chinese = &result_vec[i].get<2>();
                }else
                {
                    p_chinese = &result_vec[i].get<1>();
                }

            }else
            {
                p_chinese = &result_vec[i].get<0>();

                if(result_vec[i].get<2>().size() > 0)
                {
                    CLanguage::Ch2EnPost(result_vec[i].get<2>());
                    p_english = &result_vec[i].get<2>();
                }else
                {
                    p_english = &result_vec[i].get<1>();
                }
            }

            //tuv-en
            TiXmlElement * tuvenElem = new TiXmlElement("tuv");
            TiXmlText * tuvenText = new TiXmlText(p_english->c_str());
            tuvenElem->SetAttribute("xml:lang", "en");
            tuvenElem->LinkEndChild(tuvenText);
            tuElem->LinkEndChild(tuvenElem);

            //tuv-ch
            TiXmlElement * tuvchElem = new TiXmlElement("tuv");
            TiXmlText * tuvchText = new TiXmlText(p_chinese->c_str());
            tuvenElem->SetAttribute("xml:lang", "zh-ch");
            tuvchElem->LinkEndChild(tuvchText);
            tuElem->LinkEndChild(tuvchElem);

        }

        //输出到xmldata
        TiXmlPrinter print;
        xmlDocs->Accept(&print);
        tmx_data = print.CStr();

    }catch (...)
    {
        lerr << "Create xml-tmx failed." << endl;
        delete xmlDocs;

        return ERR_USR_XML_PARSER;
    }

    delete xmlDocs;

    //写入到文件
    string build_id = GenerateUUID();
    result_file_name = tid + "." + build_id + ".tmx";
    string tmx_filepath = m_default_file_path + result_file_name;

    if(false == write_file(tmx_filepath, tmx_data.c_str(), tmx_data.size()))
    {
        return ERR_OPEN_RESULT_FILE_FAILED;
    }

    return SUCCESS;
}