#include "binaryninjaapi.h"

/* function we must export by convention, see binaryninjacore.h */
extern "C"  BINARYNINJAPLUGIN bool CorePluginInit()
{
	/* from binaryninjaapi.h, along with LogWarn(), LogError(), etc. */
	BinaryNinja::LogInfo("Hello, world!\n");

	return true;
}
