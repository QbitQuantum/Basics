QString CQuazaaSysInfo::osVersionToString()
{
	QString operatingSystemString = "";

#if defined(Q_OS_WIN)
	QString sVersion;
	QString sEdition;
	QString sServicePack;
	QString sMachine;

	switch(GetWindowsVersion())
	{
	case WindowsVersion::Windows:
		sVersion = "Windows";
		break;
	case WindowsVersion::Windows32s:
		sVersion = "Windows 32s";
		break;
	case WindowsVersion::Windows95:
		sVersion = "Windows 95";
		break;
	case WindowsVersion::Windows95OSR2:
		sVersion = "Windows 95 SR2";
		break;
	case WindowsVersion::Windows98:
		sVersion = "Windows 98";
		break;
	case WindowsVersion::Windows98SE:
		sVersion = "Windows 98 SE";
		break;
	case WindowsVersion::WindowsMillennium:
		sVersion = "Windows Me";
		break;
	case WindowsVersion::WindowsNT351:
		sVersion = "Windows NT 3.51";
		break;
	case WindowsVersion::WindowsNT40:
		sVersion = "Windows NT 4.0";
		break;
	case WindowsVersion::WindowsNT40Server:
		sVersion = "Windows NT 4.0 Server";
		break;
	case WindowsVersion::Windows2000:
		sVersion = "Windows 2000";
		break;
	case WindowsVersion::WindowsXP:
		sVersion = "Windows XP";
		break;
	case WindowsVersion::WindowsXPProfessionalx64:
		sVersion = "Windows XP Professional x64";
		break;
	case WindowsVersion::WindowsHomeServer:
		sVersion = "Windows Home Server";
		break;
	case WindowsVersion::WindowsServer2003:
		sVersion = "Windows Server 2003";
		break;
	case WindowsVersion::WindowsServer2003R2:
		sVersion = "Windows Server 2003 R2";
		break;
	case WindowsVersion::WindowsVista:
		sVersion = "Windows Vista";
		break;
	case WindowsVersion::WindowsServer2008:
		sVersion = "Windows Server 2008";
		break;
	case WindowsVersion::WindowsServer2008R2:
		sVersion = "Windows Server 2008 R2";
		break;
	case WindowsVersion::Windows7:
		sVersion = "Windows 7";
		break;
	case WindowsVersion::WindowsServer2012:
		sVersion = "Windows Server 2012";
		break;
	case WindowsVersion::Windows8:
		sVersion = "Windows 8";
		break;
	default:
		sVersion = "Unknown Windows Version";
		break;
	}

	switch(GetWindowsEdition())
	{
	case WindowsEdition::EditionUnknown:
		sEdition = "Unknown Edition";
		break;
	case WindowsEdition::Workstation:
		sEdition = "Workstation";
		break;
	case WindowsEdition::Server:
		sEdition = "Server";
		break;
	case WindowsEdition::AdvancedServer:
		sEdition = "Advanced Server";
		break;
	case WindowsEdition::Home:
		sEdition = "Home";
		break;
	case WindowsEdition::Ultimate:
		sEdition = "Ultimate";
		break;
	case WindowsEdition::HomeBasic:
		sEdition = "Home Basic";
		break;
	case WindowsEdition::HomePremium:
		sEdition = "Home Premium";
		break;
	case WindowsEdition::Enterprise:
		sEdition = "Enterprise";
		break;
	case WindowsEdition::HomeBasicN:
		sEdition = "Home Basic N";
		break;
	case WindowsEdition::Business:
		sEdition = "Business";
		break;
	case WindowsEdition::StandardServer:
		sEdition = "Server Standard";
		break;
	case WindowsEdition::DatacenterServer:
		sEdition = "Server Datacenter (full installation)";
		break;
	case WindowsEdition::SmallBusinessServer:
		sEdition = "Small Business Server";
		break;
	case WindowsEdition::EnterpriseServer:
		sEdition = "Server Enterprise (full installation)";
		break;
	case WindowsEdition::Starter:
		sEdition = "Starter";
		break;
	case WindowsEdition::DatacenterServerCore:
		sEdition = "Server Datacenter (core installation)";
		break;
	case WindowsEdition::StandardServerCore:
		sEdition = "Server Standard (core installation)";
		break;
	case WindowsEdition::EnterpriseServerCore:
		sEdition = "Server Enterprise (core installation)";
		break;
	case WindowsEdition::EnterpriseServerIA64:
		sEdition = "Server Enterprise for Itanium-based Systems";
		break;
	case WindowsEdition::BusinessN:
		sEdition = "Business N";
		break;
	case WindowsEdition::WebServer:
		sEdition = "Web Server (full installation)";
		break;
	case WindowsEdition::ClusterServer:
		sEdition = "High Performance Computing Edition";
		break;
	case WindowsEdition::HomeServer:
		sEdition = "Storage Server 2008 R2 Essentials";
		break;
	case WindowsEdition::StorageExpressServer:
		sEdition = "Storage Server Express";
		break;
	case WindowsEdition::StorageStandardServer:
		sEdition = "Storage Server Standard";
		break;
	case WindowsEdition::StorageWorkgroupServer:
		sEdition = "Storage Server Workgroup";
		break;
	case WindowsEdition::StorageEnterpriseServer:
		sEdition = "Storage Server Enterprise";
		break;
	case WindowsEdition::ServerForSmallBusiness:
		sEdition = "for Windows Essential Server Solutions";
		break;
	case WindowsEdition::SmallBusinessServerPremium:
		sEdition = "Small Business Server Premium";
		break;
	case WindowsEdition::HomePremiumN:
		sEdition = "Home Premium N";
		break;
	case WindowsEdition::EnterpriseN:
		sEdition = "Enterprise N";
		break;
	case WindowsEdition::UltimateN:
		sEdition = "Ultimate N";
		break;
	case WindowsEdition::WebServerCore:
		sEdition = "Web Server (core installation)";
		break;
	case WindowsEdition::MediumBusinessServerManagement:
		sEdition = "Essential Business Server Management Server";
		break;
	case WindowsEdition::MediumBusinessServerSecurity:
		sEdition = "Essential Business Server Security Server";
		break;
	case WindowsEdition::MediumBusinessServerMessaging:
		sEdition = "Essential Business Server Messaging Server";
		break;
	case WindowsEdition::ServerFoundation:
		sEdition = "Server Foundation";
		break;
	case WindowsEdition::HomePremiumServer:
		sEdition = "Home Server 2011";
		break;
	case WindowsEdition::ServerForSmallBusinessV:
		sEdition = "without Hyper-V for Windows Essential Server Solutions";
		break;
	case WindowsEdition::StandardServerV:
		sEdition = "Server Standard without Hyper-V";
		break;
	case WindowsEdition::DatacenterServerV:
		sEdition = "Server Datacenter without Hyper-V (full installation)";
		break;
	case WindowsEdition::EnterpriseServerV:
		sEdition = "Server Enterprise without Hyper-V (full installation)";
		break;
	case WindowsEdition::DatacenterServerCoreV:
		sEdition = "Server Datacenter without Hyper-V (core installation)";
		break;
	case WindowsEdition::StandardServerCoreV:
		sEdition = "Server Standard without Hyper-V (core installation)";
		break;
	case WindowsEdition::EnterpriseServerCoreV:
		sEdition = "Server Enterprise without Hyper-V (core installation) ";
		break;
	case WindowsEdition::HyperV:
		sEdition = "Hyper-V Server";
		break;
	case WindowsEdition::StorageExpressServerCore:
		sEdition = "Storage Express Server Core";
		break;
	case WindowsEdition::StorageStandardServerCore:
		sEdition = "Storage Standard Server Core";
		break;
	case WindowsEdition::StorageWorkgroupServerCore:
		sEdition = "Storage Workgroup Server Core";
		break;
	case WindowsEdition::StorageEnterpriseServerCore:
		sEdition = "Storage Enterprise Server Core";
		break;
	case WindowsEdition::StarterN:
		sEdition = "Starter N";
		break;
	case WindowsEdition::Professional:
		sEdition = "Professional";
		break;
	case WindowsEdition::ProfessionalN:
		sEdition = "Professional N";
		break;
	case WindowsEdition::SBSolutionServer:
		sEdition = "Windows Small Business Server 2011 Essentials";
		break;
	case WindowsEdition::ServerForSBSolutions:
		sEdition = "Server For Small Business Solutions";
		break;
	case WindowsEdition::StandardServerSolutions:
		sEdition = "Server Solutions Premium";
		break;
	case WindowsEdition::StandardServerSolutionsCore:
		sEdition = "Server Solutions Premium (core installation)";
		break;
	case WindowsEdition::SBSolutionServerEM:
		sEdition = "Server For Small Business Solutions EM";
		break;
	case WindowsEdition::ServerForSBSolutionsEM:
		sEdition = "Server For Small Business Solutions EM";
		break;
	case WindowsEdition::SolutionEmbeddedServer:
		sEdition = "MultiPoint Server";
		break;
	case WindowsEdition::SolutionEmbeddedServerCore:
		sEdition = "MultiPoint Server (core installation)";
		break;
	case WindowsEdition::EssentialBusinessServerMGMT:
		sEdition = "Essential Server Solution Management";
		break;
	case WindowsEdition::EssentialBusinessServerADDL:
		sEdition = "Essential Server Solution Additional";
		break;
	case WindowsEdition::EssentialBusinessServerMGMTSVC:
		sEdition = "Essential Server Solution Management Service";
		break;
	case WindowsEdition::EssentialBusinessServerADDLSVC:
		sEdition = "Essential Server Solution Additional Service";
		break;
	case WindowsEdition::SmallBusinessServerPremiumCore:
		sEdition = "Small Business Server Premium (core installation)";
		break;
	case WindowsEdition::ClusterServerV:
		sEdition = "Server Hyper Core V";
		break;
	case WindowsEdition::Embedded:
		sEdition = "Embedded Standard";
		break;
	case WindowsEdition::StarterE:
		sEdition = "Starter E";
		break;
	case WindowsEdition::HomeBasicE:
		sEdition = "Home Basic E";
		break;
	case WindowsEdition::HomePremiumE:
		sEdition = "Home Premium E";
		break;
	case WindowsEdition::ProfessionalE:
		sEdition = "Professional E";
		break;
	case WindowsEdition::EnterpriseE:
		sEdition = "Enterprise E";
		break;
	case WindowsEdition::UltimateE:
		sEdition = "Ultimate E";
		break;
	case WindowsEdition::EnterpriseEvaluation:
		sEdition = "Server Enterprise (evaluation installation)";
		break;
	case WindowsEdition::MultipointStandardServer:
		sEdition = "MultiPoint Server Standard (full installation)";
		break;
	case WindowsEdition::MultipointPremiumServer:
		sEdition = "MultiPoint Server Premium (full installation)";
		break;
	case WindowsEdition::StandardEvaluationServer:
		sEdition = "Server Standard (evaluation installation)";
		break;
	case WindowsEdition::DatacenterEvaluationServer:
		sEdition = "Server Datacenter (evaluation installation)";
		break;
	case WindowsEdition::EnterpriseNEvaluation:
		sEdition = "Enterprise N (evaluation installation)";
		break;
	case WindowsEdition::StorageWorkgroupEvaluationServer:
		sEdition = "Storage Server Workgroup (evaluation installation)";
		break;
	case WindowsEdition::StorageStandardEvaluationServer:
		sEdition = "Storage Server Standard (evaluation installation)";
		break;
	case WindowsEdition::CoreN:
		sEdition = "Core N";
		break;
	case WindowsEdition::CoreCountrySpecific:
		sEdition = "Core China";
		break;
	case WindowsEdition::CoreSingleLanguage:
		sEdition = "Core Single Language";
		break;
	case WindowsEdition::Core:
		sEdition = "Core";
		break;
	case WindowsEdition::ProfessionalWindowsMediaCenter:
		sEdition = "Professional Windows Media Center";
		break;
	default:
		sEdition = "Unknown Edition";
	}

	sServicePack = GetServicePackInfo();

	if(Is64bitPlatform())
		sMachine = "64-bit";
	else
		sMachine = "32-bit";

	operatingSystemString = QString(sVersion + " ");
	if(!sEdition.isEmpty())
		operatingSystemString.append(sEdition + " ");
	if(!sServicePack.isEmpty())
		operatingSystemString.append(tr("with %1 ").arg(sServicePack));
	operatingSystemString.append(sMachine);

#elif defined(Q_OS_MAC)
	switch ( QSysInfo::MacintoshVersion ) {
		case QSysInfo::MV_9 :
			operatingSystemString = "Mac OS 9 (unsupported)";
			break;
		case QSysInfo::MV_10_0 :
			operatingSystemString = "Mac OS X 10.0 Cheetah (unsupported)";
			break;
		case QSysInfo::MV_10_1 :
			operatingSystemString = "Mac OS X 10.1 Puma (unsupported)";
			break;
		case QSysInfo::MV_10_2 :
			operatingSystemString = "Mac OS X 10.2 Jaguar (unsupported)";
			break;
		case QSysInfo::MV_10_3 :
			operatingSystemString = "Mac OS X 10.3 Panther";
			break;
		case QSysInfo::MV_10_4 :
			operatingSystemString = "Mac OS X 10.4 Tiger";
			break;
		case QSysInfo::MV_10_5 :
			operatingSystemString = "Mac OS X 10.5 Leopard";
			break;
		case QSysInfo::MV_10_6 :
			operatingSystemString = "Mac OS X 10.6 Snow Leopard";
			break;
		case QSysInfo::MV_10_7 :
			operatingSystemString = "Mac OS X 10.7 Lion";
			break;
		case QSysInfo::MV_10_8 :
			operatingSystemString = "Mac OS X 10.8 Mountain Lion";
			break;
		case QSysInfo::MV_10_9 :
			operatingSystemString = "Mac OS X 10.9 Mavericks";
			break;
		case QSysInfo::MV_Unknown :
			operatingSystemString = "An unknown and currently unsupported Mac platform";
			break;
		default :
			operatingSystemString = "Unknown Mac operating system.";
			break;
	}
#else
	//TODO: Detect Unix, Linux etc. distro as described on http://www.novell.com/coolsolutions/feature/11251.html
	operatingSystemString = "Linux";
	QProcess process;
	process.start("uname -s");
	bool result = process.waitForFinished(1000);
	QString os = process.readAllStandardOutput().trimmed();

	process.start("uname -r");
	result = process.waitForFinished(1000);
	QString rev = process.readAllStandardOutput().trimmed();

	process.start("uname -m");
	result = process.waitForFinished(1000);
	QString mach = process.readAllStandardOutput().trimmed();

	if ( os == "SunOS" ) {
		os = "Solaris";

		process.start("uname -p");
		result = process.waitForFinished(1000);
		QString arch = process.readAllStandardOutput().trimmed();

		process.start("uname -v");
		result = process.waitForFinished(1000);
		QString timestamp = process.readAllStandardOutput().trimmed();

		operatingSystemString = os + " " + rev + " (" + arch + " " + timestamp + ")";
	}
	else if ( os == "AIX" ) {
		process.start("oslevel -r");
		result = process.waitForFinished(1000);
		QString oslevel = process.readAllStandardOutput().trimmed();

		operatingSystemString = os + "oslevel " + oslevel;
	}
	else if ( os == "Linux" ) {
		QString dist;
		QString pseudoname;
		QString kernel = rev;

		if ( QFile::exists("/etc/SUSE-release") ) {
			process.start("sh -c \"cat /etc/SUSE-release | tr '\\n' ' '| sed s/VERSION.*//\"");
			result = process.waitForFinished(1000);
			dist = process.readAllStandardOutput().trimmed();

			process.start("sh -c \"cat /etc/SUSE-release | tr '\\n' ' ' | sed s/.*=\\ //\"");
			result = process.waitForFinished(1000);
			rev = process.readAllStandardOutput().trimmed();
		}
		else if ( QFile::exists("/etc/mandrake-release") ) {
			dist = "Mandrake";

			process.start("sh -c \"cat /etc/mandrake-release | sed s/.*\\(// | sed s/\\)//\"");
			result = process.waitForFinished(1000);
			pseudoname = process.readAllStandardOutput().trimmed();

			process.start("sh -c \"cat /etc/mandrake-release | sed s/.*release\\ // | sed s/\\ .*//\"");
			result = process.waitForFinished(1000);
			rev = process.readAllStandardOutput().trimmed();
		}
		else if ( QFile::exists("/etc/lsb-release") ) {
			dist = "Ubuntu";

			QString processCall = "sh -c \"cat /etc/lsb-release | grep --max-count=1 DISTRIB_RELEASE=\"";
			process.start( processCall );
			result = process.waitForFinished(1000);
			rev = process.readAllStandardOutput().trimmed();
			qDebug() << "revision:" << rev;
			if(!rev.isEmpty())
			{
				rev.remove("DISTRIB_RELEASE=");
				rev.remove("\"");
			}
			QString errorStr = process.readAllStandardError();

			process.start("sh -c \"cat /etc/lsb-release | grep --max-count=1 DISTRIB_CODENAME=\"");
			result = process.waitForFinished(1000);
			pseudoname = process.readAllStandardOutput().trimmed();
			qDebug() << "pseudoname:" << pseudoname;
			if(!pseudoname.isEmpty())
			{
				pseudoname.remove("DISTRIB_CODENAME=");
				pseudoname.remove("\"");
			}
	   }
			else if ( QFile::exists("/etc/debian_version") ) {
			dist = "Debian";

			process.start("cat /etc/debian_version");
			result = process.waitForFinished(1000);
			dist += process.readAllStandardOutput().trimmed();

			rev = "";
		}

		if ( QFile::exists("/etc/UnitedLinux-release") ) {
			process.start("sh -c \"cat /etc/UnitedLinux-release | grep --max-count=1 \"VERSION = \"\"");
			result = process.waitForFinished(1000);
			dist += process.readAllStandardOutput().trimmed();
			if(!dist.isEmpty())
			{
				dist.remove("VERSION = ");
				dist.remove("\"");
			}
		}


		if ( QFile::exists("/etc/os-release") ) { //This file makes distribution identification much easier.
			process.start("sh -c \"cat /etc/os-release | grep --max-count=1 PRETTY_NAME=\"");
			result = process.waitForFinished(1000);
			QString distname = process.readAllStandardOutput().trimmed();
			if(!distname.isEmpty())
			{
				distname.remove("PRETTY_NAME=");
				distname.remove("\"");

				dist = distname;
				pseudoname = "";
			}
		}

		operatingSystemString = os;
		if(!dist.isEmpty())
			operatingSystemString.append(" " + dist);
		if(!rev.isEmpty())
			operatingSystemString.append(" " + rev);
		operatingSystemString.append(" (");
		if(!pseudoname.isEmpty())
			operatingSystemString.append(pseudoname + " ");
		if(!kernel.isEmpty())
			operatingSystemString.append(kernel + " ");
		operatingSystemString.append(mach + ")");
	}
#endif

	return operatingSystemString;
}