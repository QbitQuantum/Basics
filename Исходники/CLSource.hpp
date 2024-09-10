		/**
		* ソースコードを管理するためのクラス
		* \param[in] filename ファイル名
		* \param[in] kernelName カーネル名
		* \param[in] type ソースコードの種類
		*/
		CLSource(const std::string& filename, const std::string& kernelName, const SourceType type)
			: fileName(filename), kernelName(kernelName), type(type)
		{
			OpenFile();
		}