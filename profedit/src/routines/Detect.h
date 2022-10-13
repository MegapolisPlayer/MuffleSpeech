#ifndef PROFILEEDITOR_ROUTINE_DETECT
#define PROFILEEDITOR_ROUTINE_DETECT
#include "../boot/Boot.h"

namespace ProfileEditor {
	enum struct FileMapEntryType {
		UNINIT = -1,
		MFSP1,
		MFSP2
	};
	struct FileMapEntry {
		std::string Name;
		FileMapEntryType Type;
		
		FileMapEntry();
		FileMapEntry(std::string aName, FileMapEntryType aType);
	};
	struct FileMap {
		std::vector<FileMapEntry> Map;
		
		void Print() const;
		
		void Detect(std::string aDirectory = ".");
	};
};

#endif
