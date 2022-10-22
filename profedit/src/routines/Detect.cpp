#include "Detect.h"

namespace ProfileEditor {
	FileMapEntry::FileMapEntry() {
		this->Name = "";
		this->Type = FileMapEntryType::UNINIT;
	}
	FileMapEntry::FileMapEntry(std::string aName, FileMapEntryType aType) {
		this->Name = aName;
		this->Type = aType;
	}
	void FileMap::Print() const {
		std::cout << "--Detected Files:-------------\n";
		for(uint64_t lId = 0; lId < this->Map.size(); lId++) {
			switch(this->Map[lId].Type) {
				case(FileMapEntryType::MFSP1):
					SetColor(COLOR_LIGHT_RED);
					std::cout << '(' << lId << ")[LEGACY]";
					break;
				case(FileMapEntryType::MFSP2):
					SetColor(COLOR_LIGHT_BLUE);
					std::cout << '(' << lId << ')';
					break;
				default:
					std::cout << "\nSomething went wrong, file of id " << lId << "has value FileMapEntryType::UNINIT.\n";
					Exit(EXIT_FAILURE);
			}
			std::cout << this->Map[lId].Name << "\n";
			ResetColor();
		}
	}
	
	void FileMap::Detect(std::string aDirectory) {
		for(const auto & entry : std::filesystem::directory_iterator(aDirectory)) {
			if(entry.is_directory()) {
				this->Detect(entry.path().string()); //recursive call, should be fine because directories will eventualy run out
			}
			elif(entry.path().extension() == ".mfsp") {
				this->Map.push_back(FileMapEntry(entry.path().string(), FileMapEntryType::MFSP1));
			}
			elif(entry.path().extension() == ".mfsp2") {
				this->Map.push_back(FileMapEntry(entry.path().string(), FileMapEntryType::MFSP2));
			}
		}
	}
};
