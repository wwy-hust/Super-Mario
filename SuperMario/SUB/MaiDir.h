#ifndef MaiDir_h
#define MaiDir_h

#include "SUB/Mai_All.h"
#include "SUB/Heap_Alloc0.h"
#include "SUB/MaiString.h"
#include "SUB/Unicode.h"

#ifdef MAI_WIN
class MaiDir
{
private:
	HANDLE  dirp;
	//struct dirent* direntp;
	WIN32_FIND_DATA wfd0;
	Mai_I32 counter;

protected:
	Mai_WChar *src;
	Mai_I8 *asrc;
	Heap_Alloc0 heap0;
public:
	MaiDir(Mai_I8 *src);
	MaiDir(Mai_WChar *src);
	~MaiDir();
	Mai_Bool is_exist();
	Mai_Status make();
	Mai_Bool is_dir();
	Mai_WChar *UgetPathPtr();
	Mai_I8 *getPathPtr();
	Mai_Status open();
	Mai_Status getNextFile(Mai_WChar *filename, Mai_I8 *type, Mai_I64 *size);
	Mai_Status getNextFile(Mai_I8 *filename, Mai_I8 *type, Mai_I64 *size);
	Mai_Status close();
	Mai_Status remove();
private:
	Mai_Status init(Mai_WChar *src);
};
#else


#include <dirent.h>
#include <sys/stat.h>

class MaiDir
{
private:
	DIR* dirp;
	struct dirent* direntp;

protected:
	Mai_WChar *usrc;
	Mai_I8 *src;
	Heap_Alloc0 heap0;
public:
	MaiDir(Mai_I8 *src);
	MaiDir(Mai_WChar *src);
	~MaiDir();
	Mai_Bool is_exist();
	Mai_Status make();
	Mai_Bool is_dir();
	Mai_WChar *UgetPathPtr();
	Mai_I8 *getPathPtr();
	Mai_Status open();
	Mai_Status getNextFile(Mai_WChar *filename, Mai_I8 *type, Mai_I64 *size);
	Mai_Status getNextFile(Mai_I8 *filename, Mai_I8 *type, Mai_I64 *size);
	Mai_Status close();
	Mai_Status remove();
private:
	Mai_Status init(Mai_I8 *src);
};
#endif

#endif
