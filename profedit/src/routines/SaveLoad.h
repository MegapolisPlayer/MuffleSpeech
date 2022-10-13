#ifndef PROFILEEDITOR_ROUTINE_LOAD
#define PROFILEEDITOR_ROUTINE_LOAD
#include "../editor/Editor.h"

namespace ProfileEditor {
	//returns -1 if fails
	int16_t LoadFileLegacy(std::fstream& aFstream, CharMap* aCharMap); //for .mfsp files
	int16_t LoadFile(std::fstream& aFstream, CharMap* aCharMap); //for .mfsp2 files
	void SaveFile(std::fstream& aFstream, CharMap* aCharMap); //will save .mfsp2 files
	
	void OverwriteFile(std::fstream& aFstream, std::string aFileName);
}

#endif