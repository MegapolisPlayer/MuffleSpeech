#ifndef PROFILEEDITOR_EDITOR
#define PROFILEEDITOR_EDITOR
#include "CharMap.h"

namespace ProfileEditor {
	extern const char* gHelpMenu;
	                        
	void PrintCharArray(const char* aArray, const uint64_t aSize);
	
	std::string PromptFilename(std::string aExtension);
	std::string PromptFilename();
	
	CharMapEntry PromptNew();
	CharMapChange PromptChange(const uint64_t aId);
	int64_t PromptRemove();
	
	int64_t PromptFileSelect();
}

#endif
