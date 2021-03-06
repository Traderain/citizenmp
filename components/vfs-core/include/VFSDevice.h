/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

#pragma once

#ifdef COMPILING_VFS_CORE
#define VFS_CORE_EXPORT DLL_EXPORT
#else
#define VFS_CORE_EXPORT DLL_IMPORT
#endif

namespace vfs
{
struct FindData
{
	std::string name;
	uint32_t attributes;
	size_t length;
};

#define INVALID_DEVICE_HANDLE (vfs::Device::InvalidHandle)

class VFS_CORE_EXPORT Device : public fwRefCountable
{
public:
	typedef uintptr_t THandle;

	static const THandle InvalidHandle = -1;

public:
	virtual THandle Open(const std::string& fileName, bool readOnly) = 0;

	virtual THandle OpenBulk(const std::string& fileName, uint64_t* ptr);

	virtual size_t Read(THandle handle, void* outBuffer, size_t size) = 0;

	virtual size_t ReadBulk(THandle handle, uint64_t ptr, void* outBuffer, size_t size);

	virtual size_t Seek(THandle handle, intptr_t offset, int seekType) = 0;

	virtual bool Close(THandle handle) = 0;

	virtual bool CloseBulk(THandle handle);

	virtual size_t GetLength(THandle handle);

	virtual size_t GetLength(const std::string& fileName);

	virtual THandle FindFirst(const std::string& folder, FindData* findData) = 0;

	virtual bool FindNext(THandle handle, FindData* findData) = 0;

	virtual void FindClose(THandle handle) = 0;

	virtual void SetPathPrefix(const std::string& pathPrefix);
};
}