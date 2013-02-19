//
//  main.cpp
//  Lord
//
//  Created by jerry on 13-1-27.
//  Copyright (c) 2013年 Lord. All rights reserved.
//
//#define _UNICODE
#include "../Core/Core.h"
#include <iostream>

//#include "MathLib.h"

USING_LORD_NAMESPACE

#if defined(_LIBCPP_VERSION)
#	define _TEST 1
#else
#	define _TEST 0
#endif

int main(int argc, const char * argv[])
{
	setlocale(LC_ALL, "zh_CN.UTF-8");
	String str = StringUtil::ConvStr("");
	
	//test();
	
	Guid guid;
	guid.regen();
	str = guid.toString();
	
	printf("%s\n", str.c_str());
	
	Byte *bytes = LordNewArrayT(Byte, 256);
	//LordDeleteArrayT(bytes, Byte, 256);
	
	printf("LORD_COMPILER: %d\n", LORD_COMPILER);
	printf("LORD_COMPILER_VERSION: %d\n", LORD_COMPILER_VERSION);
	printf("LORD_ARCHITECTURE: %d\n", LORD_ARCHITECTURE);
	
	printf("_TEST: %d\n", _TEST);
	
	return 0;
}