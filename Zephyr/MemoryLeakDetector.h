#ifndef MEMORY_LEAK_DETECTOR_H
#define MEMORY_LEAK_DETECTOR_H

#include <stdlib.h>
#include <Windows.h>
#include <list>
#include <iostream>
#include <sstream>
#include <new>


#ifdef _DEBUG

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

	typedef struct
	{
		DWORD address;
		DWORD size;
		char file[64];
		DWORD line;
	} ALLOC_INFO;

	typedef std::list<ALLOC_INFO*> AllocList;

	AllocList* allocList;

	void AddTrack(DWORD addr, DWORD asize, const char *fname, DWORD lnum)
	{
		ALLOC_INFO* info;

		if (!allocList)
		{
			allocList = new(AllocList);
		}

		info = new(ALLOC_INFO);
		info->address = addr;
		strncpy_s(info->file, fname, 63);
		info->line = lnum;
		info->size = asize;
		allocList->insert(allocList->begin(), info);
	};

	void RemoveTrack(DWORD addr)
	{
		AllocList::iterator i;

		if (!allocList)
		{
			return;
		}

		for (i = allocList->begin(); i != allocList->end(); i++)
		{
			if ((*i)->address == addr)
			{
				allocList->remove((*i));
				break;
			}
		}
	};

	void DumpUnfreed()
	{
		AllocList::iterator i;
		DWORD totalSize = 0;
		char buffer[1024];
		int leakCount = 0;

		if (!allocList)
		{
			return;
		}

		sprintf_s(buffer, "+------------------------------------------------------------+\n"); OutputDebugString(buffer);
		sprintf_s(buffer, "|                MEMORY LEAK DETECTOR OUTPUT                 |\n"); OutputDebugString(buffer);
		sprintf_s(buffer, "+------------------------------------------------------------+\n"); OutputDebugString(buffer);
		for (i = allocList->begin(); i != allocList->end(); i++)
		{
			sprintf_s(buffer, "%s : %d ADDRESS: %d - %d bytes unfreed\n", (*i)->file, (*i)->line, (*i)->address, (*i)->size);
			OutputDebugString(buffer);
			totalSize += (*i)->size;
			leakCount++;
		}

		if (leakCount > 0)
		{
			sprintf_s(buffer, "+------------------------------------------------------------+\n"); OutputDebugString(buffer);
			sprintf_s(buffer, "Total Unfreed: %d bytes\n", totalSize); OutputDebugString(buffer);
			sprintf_s(buffer, "+------------------------------------------------------------+\n"); OutputDebugString(buffer);
		}
		else
		{
			sprintf_s(buffer, "No memory leaks detected!\n"); OutputDebugString(buffer);
			sprintf_s(buffer, "+------------------------------------------------------------+\n"); OutputDebugString(buffer);
		}
	};

	std::string CurrentMemoryUsage()
	{
		std::ostringstream results;

		AllocList::iterator i;
		DWORD totalSize = 0;
		int leakCount = 0;

		if (!allocList)
		{
			return "";
		}

		results << "+------------------------------------------------------------+\n";
		results << "|                MEMORY LEAK DETECTOR OUTPUT                 |\n";
		results << "+------------------------------------------------------------+\n";
		for (i = allocList->begin(); i != allocList->end(); i++)
		{
			results << (*i)->file;
			results << " : ";
			results << (*i)->line;
			results << " ADDRESS: ";
			results << (*i)->address;
			results << " - ";
			results << (*i)->size;
			results << " bytes unfreed\n";
			totalSize += (*i)->size;
			leakCount++;
		}


		if (leakCount > 0)
		{
			results << "+------------------------------------------------------------+\n";
			results << "Total Unfreed: ";
			results << totalSize;
			results << " bytes\n";
			results << "+------------------------------------------------------------+\n";
		}
		else
		{
			results << "No memory leaks detected!\n";
			results << "+------------------------------------------------------------+\n";
		}

		return results.str();
	};

	void* __cdecl operator new(size_t size, const char* file, int line)
	{
		void* pointer = (void*)malloc(size);
		if (!pointer)
		{
			AddTrack((DWORD)pointer, size, file, line);
			return(pointer);
		}
		else
		{
			throw std::bad_alloc();
		}
	};

	void* __cdecl operator new[](size_t size, const char* file, int line)
	{
		void* pointer = (void*)malloc(size);
		if (pointer)
		{
			AddTrack((DWORD)pointer, size, file, line);
			return(pointer);
		}
		else
		{
			throw std::bad_alloc();
		}
	};

	void __cdecl operator delete(void* p)
	{
		RemoveTrack((DWORD)p);
		free(p);
	};

	void __cdecl operator delete[](void* p)
	{
		RemoveTrack((DWORD)p);
		free(p);
	};

#endif

#ifdef _DEBUG
#define DEBUG_NEW new(__FILENAME__, __LINE__)
#else
#define DEBUG_NEW new
#endif
#define new DEBUG_NEW


#endif