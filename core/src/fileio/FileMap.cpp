#include "FileMap.h"

namespace MuffleSpeech {
	FileMapEntry::FileMapEntry() {
		this->Name = "";
	}
	FileMapEntry::FileMapEntry(std::string aName) {
		this->Name = aName;
	}
	
	void FileMap::Print() const {
		for(uint64_t lId = 0; lId < this->Map.size(); lId++) {
			std::cout << '(' << lId << ')' << this->Map[lId].Name << "\n";
		}
	}
	void FileMap::PrintExtensive() const {
		std::cout << "--Detected Files:-------------\n";
		for(uint64_t lId = 0; lId < this->Map.size(); lId++) {
			std::cout << '(' << lId << ')' << this->Map[lId].Name << "\n";
		}
	}
	uint64_t FileMap::Select() const {
		this->PrintExtensive();
		std::string lTemp;
		std::cout << "Please select ID of file to load: ";
		std::cin >> lTemp;
		if(!IsNumber(lTemp)) {
			return -1;
		}
		return std::stoi(lTemp);
	}
	
	void FileMap::Detect(std::string aDirectory) {
		for(const auto & entry : std::filesystem::directory_iterator(aDirectory)) {
			if(entry.is_directory()) {
				this->Detect(entry.path().string()); //recursive call, should be fine because directories will eventualy run out
			}
			elif(entry.path().extension() == ".mfsp2") {
				this->Map.push_back(FileMapEntry(entry.path().string()));
			}
		}
	}
}
