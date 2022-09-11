#ifndef MUFFLESPEECH_FILEMAP
#define MUFFLESPEECH_FILEMAP
#include "ArgumentHandler.h"

namespace MuffleSpeech {
	enum class FileMapEntryType {
		NONE = 0,
		ROOT,
		PATH
	};
	
	struct FileMapEntry {
		std::string FileName;
		uint64_t FileId;
		FileMapEntryType EntryType;
		FileMapEntry() : FileName(""), FileId(0), EntryType(FileMapEntryType::NONE) {}
		FileMapEntry(std::string aFileName, uint64_t aFileId, FileMapEntryType aEntryType) : FileName(aFileName), FileId(aFileId), EntryType(aEntryType) {}
	};
	struct FileMap {
		std::vector<FileMapEntry> Map;
	};
	
	void FindFiles(FileMap* aFileMap);
	void PrintFiles(const FileMap* aFileMap);
	uint64_t SelectFile(const FileMap* aFileMap);
}

#endif
