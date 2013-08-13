#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include "Types.hpp"
#include <stdio.h>
#include <stdlib.h>

#include <android_native_app_glue.h>
//#include <fstream>

namespace gm_serv {

struct ResourceDescriptor {
	int32_t mDescriptor;
	off_t mStart;
	off_t mLength;
};

class Resource {
public:
	Resource(android_app* pApplication, const char* pPath);

	const char* getPath();

	status open();
	void close();
	status read(void* pBuffer, size_t pCount);
	status read_spc(void* pBuffer, size_t pCount);

	off_t getLength();
	const void* bufferize();

	ResourceDescriptor descript();

private:
	const char* mPath;
	//std::ifstream mInputStream;
	//char* mBuffer;
	AAssetManager* mAssetManager;
	AAsset* mAsset;

};
}
#endif
