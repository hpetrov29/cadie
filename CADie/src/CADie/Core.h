#pragma once

#ifdef CADIE_PLATFORM_WINDOWS
	#ifdef CADIE_BUILD_DLL
		#define CADIE_API _declspec(dllexport)
	#else
		#define CADIE_API _declspec(dllimport)
	#endif
#else
	#error Cadie is supported only on Windows
#endif


#define BIT(x) (1 << x)