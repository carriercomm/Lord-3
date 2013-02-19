#include "CoreStd.h"
#include "PathUtil.h"
#include "StringUtil.h"

#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
#	include <dirent.h>
#	include <direct.h>
#	if (LORD_COMPILER == LORD_COMPILER_MSVC)
#		pragma warning(disable: 4996)
#	endif
#else
#	include <unistd.h>
#	include <sys/stat.h>
#	include <dirent.h>
#endif

LORD_NAMESPACE_BEGIN

const Dword PathUtil::MAX_PATHNAME = 260;
const Dword PathUtil::MAX_DIRNAME = 256;
const Dword PathUtil::MAX_FILENAME = 256;
const Dword PathUtil::MAX_EXTNAME = 256;

const tchar PathUtil::DOT = _T('.');
const tchar PathUtil::SEPERATOR = _T('/');
const tchar PathUtil::SLASH = _T('/');
const tchar PathUtil::BACKSLASH = _T('\\');

const String PathUtil::INVALID_PATH = _T("");

//////////////////////////////////////////////////////////////////////////

PathUtil::PathUtil()
{
}

PathUtil::~PathUtil()
{
}

void PathUtil::FormatPath(String &file, bool bLower)
{
	if(PathUtil::IsHttpFile(file))
	{
		file = StringUtil::Replace(file, BACKSLASH, SEPERATOR);
		while(StringUtil::ReplaceRet(file, _T("//"), _T("/")))
			continue;
		
		file = StringUtil::Replace(file, _T("http:/"), _T("http://"));
	}
	else 
	{
		bool bLan = false;
		bLan = IsLanFile(file);
		file = StringUtil::Replace(file, BACKSLASH, SEPERATOR);
		while(StringUtil::ReplaceRet(file, _T("//"), _T("/")))
			continue;
		
		if(bLan)
			file = SLASH + file;
	}
	
	if(bLower)
		StringUtil::LowerCase(file);
}

bool PathUtil::IsFileExist(const String &file)
{
	struct stat st;
	
	String tempFile = file;
	
	if(IsEndWithSeperator(tempFile))
		return false;
	
	std::string strDir = StringUtil::ConvMBS(tempFile).c_str();
	
	const char *filename = strDir.c_str();
	
	/* ignore hidden files */
	if(filename[0] == '.')
	{
		bool bRet = false;
		
		if(file.length() > 2)
		{
			if(filename[1] == '/' || filename[1] == '\\')
				bRet = true;
		}
		
		if(!bRet && file.length() > 3)
		{
			if(filename[1] == '.' && (filename[2] == '/' || filename[2] == '\\'))
				bRet = true;
		}
		
		if(!bRet)
			return false;
	}
	
	/* get dirent status */
	if(stat(filename, &st) == -1)
		return false;
	
	if(S_ISDIR(st.st_mode))
		return false;
	
	return true;
}

bool PathUtil::IsDirExist(const String &dir)
{
	if(IsDriveOrRoot(dir))
		return true;
	
	struct stat st;
	
	String tempPath = dir;
	if(IsEndWithSeperator(tempPath))
	{
		tempPath = tempPath.substr(0, tempPath.length() - 1);
	}
	
	std::string strDir;
	strDir = StringUtil::ConvMBS(tempPath).c_str();
	const char *filename = strDir.c_str();
	
	/* ignore hidden files */
	if(filename[0] == '.')
		return true;
	
	/* get dirent status */
	if(stat(filename, &st) == -1)
		return false;
	
	if(S_ISDIR(st.st_mode))
		return true;
	
	return false;
}

bool PathUtil::IsHttpFile(const String &file)
{
	String tempFile = file;
	StringUtil::LowerCase(tempFile);
	
	String key = _T("http:");
	size_t keyLen = key.length();
	
	if(tempFile.length() < keyLen)
		return false;
	
	if(tempFile.substr(0, keyLen) == key)
		return true;
	else
		return false;
}

bool PathUtil::IsLanFile(const String &file)
{
	String tempFile = StringUtil::Replace(file, BACKSLASH, SEPERATOR);
	
	String key = _T("//");
	size_t keyLen = key.length();
	
	if(tempFile.length() < keyLen)
		return false;
	
	if(tempFile.substr(0, keyLen) == key)
		return true;
	else
		return false;
}

String PathUtil::GetHttpSafeFilePath(const String &httpfile)
{
	String ret = httpfile;
	FormatPath(ret);
	StringUtil::Trim(ret);
	ret = StringUtil::Replace(ret, _T(" "), _T("%20"));
	return ret;
}

String PathUtil::GetHttpFileInPath(const String &httpfile)
{
	String ret = httpfile;
	FormatPath(ret);
	
	size_t pos = ret.find_last_of(SEPERATOR);
	if(pos == String::npos)
		return INVALID_PATH;
	
	return ret.substr(0, pos + 1);
}

bool PathUtil::IsEndWithSlash(const String &path)
{
	if(!path.length())
		return false;
	
	return path[path.length() - 1] == SLASH;
}

bool PathUtil::IsEndWithBackSlash(const String &path)
{
	if(!path.length())
		return false;
	
	return path[path.length() - 1] == BACKSLASH;
}

bool PathUtil::IsEndWithSeperator(const String &path)
{
	if(!path.length())
		return false;
	
	size_t pos = path.length() - 1;
	return path[pos] == SLASH || path[pos] == BACKSLASH;
}

bool PathUtil::IsRelativePath(const String &path)
{
	if(!path.length())
		return false;
	
	// »Áπ˚ «“‘ . ø™Õ∑µƒ£¨ƒ«√¥æÕ≈–∂œÀ¸ «¥øŒƒº˛√˚£¨≤ª «æ¯∂‘¬∑æ∂
	if(path[0] == DOT)
		return true;
	
	return false;
}

bool PathUtil::IsAbsolutePath(const String &path)
{
	return !IsRelativePath(path);
}

bool PathUtil::IsDir(const String &path)
{
	if(path.length() == 0)
		return false;
	
	return IsEndWithSeperator(path);
}

bool PathUtil::IsDriveOrRoot(const String &path)
{
	String tempPath = path;
	FormatPath(tempPath);
	if(	path[0] == SEPERATOR ||		// unix/linux mount point
	   ((path.length() == 2 || path.length() ==3) && path[1] == _T(':'))	// windows drive, like c:/
	   )
		return true;
	
	return false;
}

bool PathUtil::IsFileType(const String &filename, const String &extWithDot)
{
	size_t fileLen = filename.length();
	size_t extLen = extWithDot.length();
	
	if(fileLen < extLen)
		return false;
	
	String fileExt = filename.substr(fileLen - extLen);
	
	if(fileExt == extWithDot)
		return true;
	
	return false;
}

bool PathUtil::IsSameFile(const String &file1, const String &file2)
{
	if(!IsFileExist(file1) || !IsFileExist(file2))
		return false;
	
	const char *szFile1 = StringUtil::ConvMBS(file1).c_str();
	const char *szFile2 = StringUtil::ConvMBS(file2).c_str();
	
	struct stat st1;
	struct stat st2;
	
	/* get dirent status */
	if(stat(szFile1, &st1) == -1 || stat(szFile2, &st2) == -1)
		return false;
	
	/* if dirent is a directory */
	if(S_ISDIR(st1.st_mode) || S_ISDIR(st2.st_mode))
		return false;
	
	//  [10/19/2011 Jerry]
	// ◊¢“‚£∫øº¬«µΩøÁ∆ΩÃ®–‘£¨≤ª“™±»ΩœŒƒº˛ Ù–‘£¨win∫Õunix/linuxµƒŒƒº˛ Ù–‘≤ª“ª÷¬
	if(	st1.st_mtime == st2.st_mtime &&			// –ﬁ∏ƒ ±º‰
	   st1.st_size == st2.st_size				// ¥Û–°
	   )
		return true;
	else
		return false;
}

bool PathUtil::CanWriteToFile(const String &file, bool bCreateNoExist)
{
	if(!file.length())
		return false;
	
	if(bCreateNoExist)
	{
		String dirPath = GetFileDirPath(file);
		
		if(!EnsureDir(dirPath))
			return false;
	}
	
	std::string filename = StringUtil::ConvMBS(file);
	FILE *pFile = fopen(filename.c_str(), "wbS");
	if(!pFile)
		return false;
	
	fclose(pFile);
	return true;
}

String PathUtil::GetCurrentDir()
{
	char buff[MAX_PATHNAME];
	std::string str = getcwd(buff, MAX_PATHNAME);
	return StringUtil::ConvStr(str);
}

String PathUtil::GetFileDirPath(const String &filename)
{
	String path = filename;
	FormatPath(path);
	size_t pos = path.find_last_of(SEPERATOR);
	if(pos == String::npos)
	{
		return INVALID_PATH;
	}
	path = path.substr(0, pos + 1);
	
	return path;
}

String PathUtil::GetPureFilename(const String &filename, bool bNeedExt)
{
	String pureFilename = filename;
	pureFilename = StringUtil::Replace(pureFilename, BACKSLASH, SEPERATOR);
	
	size_t pos = pureFilename.find_last_of(SEPERATOR);
	if(pos != String::npos)
	{
		pureFilename = pureFilename.substr(pos + 1);
		
		if(!bNeedExt)
		{
			size_t dotPos = pureFilename.find_last_of(DOT);
			pureFilename = pureFilename.substr(0, dotPos);
		}
	}
	
	return pureFilename;
}

String PathUtil::GetPureDirname(const String &dirname)
{
	if(!IsDir(dirname))
		return INVALID_PATH;
	
	String pureDirname = dirname;
	pureDirname = pureDirname.substr(0, pureDirname.length() - 1);
	pureDirname = StringUtil::Replace(pureDirname, BACKSLASH, SLASH);
	
	size_t pos = pureDirname.find_last_of(SEPERATOR);
	if(pos != String::npos)
	{
		pureDirname = pureDirname.substr(pos + 1);
	}
	
	pureDirname += SEPERATOR;
	
	return pureDirname;
}

String PathUtil::GetFileExt(const String &filename, bool bNeedDot)
{
	size_t pos = filename.find_last_of(DOT);
	if(pos == String::npos)
	{
		return INVALID_PATH;
	}
	
	if(!bNeedDot)
		++pos;
	
	return filename.substr(pos);
}

String PathUtil::GetRenameExtFile(const String &filename, const String &extWithDot)
{
	String newFilename = filename;
	newFilename = StringUtil::Replace(newFilename, BACKSLASH, SLASH);
	
	size_t dotPos = newFilename.find_last_of(DOT);
	newFilename = newFilename.substr(0, dotPos) + extWithDot;
	
	FormatPath(newFilename);
	
	return newFilename;
}

String PathUtil::GetRelativePath(const String &path, const String &rootPath)
{
	String lowerFileOrPath = path;
	String lowerRootPath = rootPath;
	
	FormatPath(lowerFileOrPath, true);
	FormatPath(lowerRootPath, true);
	
	if(!IsEndWithSeperator(lowerRootPath))
	{
		lowerRootPath += SEPERATOR;
	}
	
	size_t ret = lowerFileOrPath.find(lowerRootPath);
	if(ret == 0)
	{
		String result = path.substr(lowerRootPath.length());
		return result;
	}
	else
	{
		return INVALID_PATH;
	}
	
	return INVALID_PATH;
}

String PathUtil::GetParentPath(const String &fileOrPath)
{
	String tempFile = fileOrPath;
	FormatPath(tempFile);
	if(IsDir(tempFile))
	{
		tempFile = tempFile.substr(0, tempFile.length() - 1);
	}
	tempFile = GetFileDirPath(tempFile);
	
	return tempFile;
}

String PathUtil::GetLastDirName(const String &path)
{
	String tempPath = path;
	if(!IsDir(tempPath))
		return INVALID_PATH;
	
	tempPath = tempPath.substr(0, tempPath.length() - 1);
	
	return GetPureFilename(tempPath, true);
}

String PathUtil::GetLastPathName(const String &filename)
{
	String tempFile = filename;
	bool bIsFolder = IsDir(tempFile);
	if(bIsFolder)
	{
		tempFile = tempFile.substr(0, tempFile.length() - 1);
	}
	
	String ret = GetPureFilename(tempFile, true);
	
	if(bIsFolder)
		return ret + SEPERATOR;
	else
		return ret;
}

String PathUtil::GetDrive(const String &path)
{
	String tempPath = path;
	FormatPath(tempPath);
	size_t pos = tempPath.find(_T(":/"));
	if(!pos)
		return INVALID_PATH;
	
	return tempPath.substr(0, pos + 2);
}

String PathUtil::GetDriveOrRoot(const String &path)
{
	String tempPath = path;
	FormatPath(tempPath);
	size_t pos = tempPath.find(_T(":/"));
	if(pos)
	{
		tempPath = tempPath.substr(0, pos + 2);
	}
	else
	{
		if(tempPath[0] == SEPERATOR)
			tempPath = SEPERATOR;
		else
			tempPath = INVALID_PATH;
	}
	
	return tempPath;
}

i64 PathUtil::GetFileSize(const String& file)
{
	std::string filename = StringUtil::ConvMBS(file);
	struct stat st;
	
	/* get dirent status */
	if(stat(filename.c_str(), &st) == -1)
		return false;
	
	/* if dirent is a directory */
	if(S_ISDIR(st.st_mode))
		return false;
	
	return st.st_size;
}

bool PathUtil::CreateDir(const String &dir)
{
	std::vector<std::string> paths;
	char seps[] = _T("/\\");
	char pathBuf[MAX_PATHNAME];
	char *token = NULL;
	
	memset(pathBuf, 0, MAX_PATHNAME);
	memcpy(pathBuf, dir.c_str(), dir.length() * sizeof(tchar));
	
	token = strtok(pathBuf, seps);
	
	std::string tempDir;
	while( token != NULL )
	{
		tempDir = token;
		if(!IsDriveOrRoot(tempDir))
		{
			paths.push_back(tempDir);
		}
		
		token = strtok(NULL, seps);
	}

	tempDir = StringUtil::ConvMBS(GetDriveOrRoot(dir));
	
	for(size_t i=0; i < paths.size(); ++i)
	{
		tempDir += paths[i];
		tempDir += SEPERATOR;
		
		if(!IsDirExist(tempDir))
		{
#if (LORD_PLATFORM == LORD_PLATFORM_WINDOWS)
			if(mkdir(tempDir.c_str()) != 0)
#else
			if(mkdir(tempDir.c_str(), S_IRWXU|S_IRWXG|S_IRWXO) != 0)
#endif
				return false;
		}
	}
	
	return true;
}

bool PathUtil::EnsureDir(const String &dir)
{
	if(!IsDir(dir))
		return false;
	
	if(!IsDirExist(dir))
	{
		if(!CreateDir(dir))
			return false;
	}
	
	return true;
}

bool PathUtil::RenameFile(const String &src, const String &dest)
{
	std::string srcFile = StringUtil::ConvMBS(src);
	std::string destFile = StringUtil::ConvMBS(dest);
	if(!rename(srcFile.c_str(), destFile.c_str()))
		return true;
	else
		return false;
}

bool PathUtil::RenameDir(const String &src, const String &dest)
{
	std::string srcFile = StringUtil::ConvMBS(src);
	std::string destFile = StringUtil::ConvMBS(dest);
	if(!rename(srcFile.c_str(), destFile.c_str()))
		return true;
	else
		return false;
}

void PathUtil::EnumFilesInDir(	StringArray &ret,
							  const String &rootPath,
							  bool bIncDir,
							  bool bIncSubDirs)
{
	DIR *pDir;
	struct dirent *pDirInfo;
	struct stat st;
	
	String tempRootDir = rootPath;
	FormatPath(tempRootDir);
	if(IsEndWithSeperator(tempRootDir))
		tempRootDir = tempRootDir.substr(0, tempRootDir.length() -1);
	
	std::string strDir = StringUtil::ConvMBS(tempRootDir).c_str();
	const char *szDir = strDir.c_str();
	
	// open dirent directory
	if((pDir = opendir(szDir)) == NULL)
		return ;
	
	// read all files in this dir
	while((pDirInfo = readdir(pDir)) != NULL)
	{
		char fullname[255];
		memset(fullname, 0, sizeof(fullname));
		
		/* ignore hidden files */
		if(pDirInfo->d_name[0] == '.')
			continue;
		
		strncpy(fullname, szDir, sizeof(fullname));
		strncat(fullname, "/", sizeof(fullname));
		strncat(fullname, pDirInfo->d_name, sizeof(fullname));
		
		/* get dirent status */
		if(stat(fullname, &st) == -1)
			return ;
		
		/* if dirent is a directory, call itself */
		if(S_ISDIR(st.st_mode))
		{
			if(bIncDir)
			{
				String dirEntry = StringUtil::ConvStr(fullname) + SEPERATOR;
				ret.push_back(dirEntry);
			}
			
			if(bIncSubDirs)
			{
				String subFolder = StringUtil::ConvStr(fullname);
				EnumFilesInDir(ret, subFolder, bIncDir, bIncSubDirs);
			}
		}
		else
		{
			String fileEntry = StringUtil::ConvStr(fullname);
			ret.push_back(fileEntry);
		}
	}
}

void PathUtil::EnumSubDirs(	StringArray &ret,
							const String &rootPath,
							bool bIncSubDirs)
{
	DIR *pDir;
	struct dirent *pDirInfo;
	struct stat st;
	
	String tempRootDir = rootPath;
	FormatPath(tempRootDir);
	if(IsEndWithSeperator(tempRootDir))
		tempRootDir = tempRootDir.substr(0, tempRootDir.length() -1);
	
	std::string strDir = StringUtil::ConvMBS(tempRootDir);
	
	const char *szDir = strDir.c_str();
	
	// open dirent directory
	if((pDir = opendir(szDir)) == NULL)
		return ;
	
	// read all files in this dir
	while((pDirInfo = readdir(pDir)) != NULL)
	{
		char fullname[255];
		memset(fullname, 0, sizeof(fullname));
		
		/* ignore hidden files */
		if(pDirInfo->d_name[0] == '.')
			continue;
		
		strncpy(fullname, szDir, sizeof(fullname));
		strncat(fullname, "/", sizeof(fullname));
		strncat(fullname, pDirInfo->d_name, sizeof(fullname));
		
		/* get dirent status */
		if(stat(fullname, &st) == -1)
			return ;
		
		/* if dirent is a directory, call itself */
		if(S_ISDIR(st.st_mode))
		{
			if(bIncSubDirs)
			{
				String subFolder = StringUtil::ConvStr(fullname);
				ret.push_back(subFolder);
				
				EnumSubDirs(ret, subFolder, bIncSubDirs);
			}
		}
	} // while
}

bool PathUtil::CopyFilePath(const String &src, const String &dest, bool bOverWrite)
{
	String destDir = GetFileDirPath(dest);
	if(!EnsureDir(destDir))
		return false;
	
	IFStream fin(src.c_str());
	OFStream fout(dest.c_str());
	
	tchar buf[4096];
	fin.read(buf, 4096);
	i64 rdCount = fin.gcount();
	while(rdCount != 0)
	{
		fout.write(buf, fin.gcount());
		fin.read(buf, 4096);
		rdCount = fin.gcount();
	}
	
	fin.close();
	fout.close();
	
	if(GetFileSize(src) == GetFileSize(dest))
		return true;
	else
		return false;
}

bool PathUtil::CopyDir(const String &srcDir, const String &destDir, bool bOverWrite)
{
	DIR *pDir;
	struct dirent *pDirInfo;
	struct stat st;
	
	String tempSrcDir = srcDir;
	String tempDestDir = destDir;
	FormatPath(tempSrcDir);
	FormatPath(tempDestDir);
	
	std::string strDir = StringUtil::ConvMBS(tempSrcDir);
	
	const char *dirname = strDir.c_str();
	
	// open dirent directory
	if((pDir = opendir(dirname)) == NULL)
		return false;
	
	// read all files in this dir
	while((pDirInfo = readdir(pDir)) != NULL)
	{
		char fullname[255];
		memset(fullname, 0, sizeof(fullname));
		
		/* ignore hidden files */
		if(pDirInfo->d_name[0] == '.')
			continue;
		
		strncpy(fullname, dirname, sizeof(fullname));
		strncat(fullname, pDirInfo->d_name, sizeof(fullname));
		
		/* get dirent status */
		if(stat(fullname, &st) == -1)
			return false;
		
		/* if dirent is a directory, call itself */
		if(S_ISDIR(st.st_mode))
		{
			String subDir = StringUtil::ConvStr(fullname) + SEPERATOR;
			String subDestDir = tempDestDir + GetPureDirname(subDir);
			
			if(!IsEndWithSeperator(subDestDir))
				subDestDir += SEPERATOR;
			
			PathUtil::CopyDir(subDir, subDestDir, bOverWrite);
		}
		else
		{
			String tempEntry = StringUtil::ConvStr(pDirInfo->d_name);
			String subSrcDir = StringUtil::ConvStr(dirname);
			String destFile = tempDestDir + tempEntry;
			PathUtil::CopyFilePath(subSrcDir, destFile, bOverWrite);
		}
	} // while
	
	return true;
}

bool PathUtil::DelFilesInDir(const String &dir)
{
	DIR *pDir;
	struct dirent *pDirInfo;
	struct stat st;
	
	String tempDir = dir;
	FormatPath(tempDir);
	if(IsEndWithSeperator(tempDir))
		tempDir = tempDir.substr(0, tempDir.length() -1);
	
	std::string strDir  = StringUtil::ConvMBS(tempDir);
	const char *dirname = strDir.c_str();
	
	// open dirent directory
	if((pDir = opendir(dirname)) == NULL)
		return false;
	
	// read all files in this dir
	while((pDirInfo = readdir(pDir)) != NULL)
	{
		char fullname[255];
		memset(fullname, 0, sizeof(fullname));
		
		/* ignore hidden files */
		if(pDirInfo->d_name[0] == '.')
			continue;
		
		strncpy(fullname, dirname, sizeof(fullname));
		strncat(fullname, "/", sizeof(fullname));
		strncat(fullname, pDirInfo->d_name, sizeof(fullname));
		
		/* get dirent status */
		if(stat(fullname, &st) == -1)
			return false;
		
		/* if dirent is a directory, call itself */
		if(S_ISDIR(st.st_mode))
		{
			String subDir = StringUtil::ConvStr(fullname);
			if(DelFilesInDir(subDir))
			{
				if(rmdir(fullname) != 0)
					return false;
			}
			else
				return false;
		}
		else
		{
			// delete file
			if(remove(fullname) != 0)
				return false;
		}
	}
	
	return true;
}

bool PathUtil::DelPath(const String &path)
{
	struct stat st;
	
	String tempPath = path;
	FormatPath(tempPath);
	if(IsEndWithSeperator(tempPath))
		tempPath = tempPath.substr(0, tempPath.length() -1);
	
	std::string strPath  = StringUtil::ConvMBS(tempPath);
	const char *szPath = strPath.c_str();
	
	/* get dirent status */
	if(stat(szPath, &st) == -1)
		return false;
	
	bool flag = false;
	
	/* if dirent is a directory, call itself */
	if(S_ISDIR(st.st_mode))
	{
		if(DelFilesInDir(tempPath))
		{
			if(rmdir(szPath) == 0)
				flag = true;
		}
	}
	else
	{
		// delete file
		if(remove(szPath) == 0)
			flag = true;
	}
	
	return flag;
}

LORD_NAMESPACE_END