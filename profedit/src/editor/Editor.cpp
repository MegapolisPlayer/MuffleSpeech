#include "Editor.h"

//internal functions
namespace PEInternal {
	static void AllocateCharsToEntry(std::string aString, char(&aArray)[3]) {
		uint64_t lStringSize = aString.size();
		for(uint8_t lId = 0; lId < std::min<uint64_t>(lStringSize, 3); lId++) {
			aArray[lId] = aString[lId];
		}
		for(uint8_t lId = lStringSize; lId < 3; lId++) {
			aArray[lId] = '-';
		}
		
	}
	static int64_t Prompt() {
		std::string lTempId;
		std::cin >> lTempId;
		if(!ProfileEditor::IsNumber(lTempId)) {
			return -1; //change functions to return -1 on error
		}
		return std::stoi(lTempId);
	}
	static std::string PromptString() {
		std::string lTemp;
		std::cin >> lTemp;
		return lTemp;
	}
}

namespace ProfileEditor {
	const char* gHelpMenu = "--MFSP ProfileEditor Help-----\n"
	                        "ADD - adds new character map entry\n"
	                        "CHANGE - change character map entry\n"
	                        "REMOVE - removes character map entry\n"
	                        "SAVE - saves this profile\n"
	                        "LOAD - loads new profile (warning: this will delete unsaved work)\n"
	                        "CLEAR - clears profile\n"
	                        "CLEARFILE - clears profile and file\n"
	                        "LIST - prints the entiRe character map\n"
	                        "HELP - displays this help menu\n"
	                        "EXIT, QUIT - exits the program\n";
	
	std::string PromptFilename(std::string aExtension) {
		std::cout << "Please enter filename (without extension): ";
		return PEInternal::PromptString() + "." + aExtension;
	}
	std::string PromptFilename() {
		std::cout << "Please enter filename (with extension): ";
		return PEInternal::PromptString();
	}
	
	CharMapEntry PromptNew() {
		std::string lTemp;
		CharMapEntry lEntry;
		std::cout << "New entry input: ";
		std::cin >> lTemp;
		PEInternal::AllocateCharsToEntry(lTemp, lEntry.In);
		std::cout << "New entry output: ";
		std::cin >> lTemp;
		PEInternal::AllocateCharsToEntry(lTemp, lEntry.Out);
		return lEntry;
	}
	CharMapChange PromptChange(const uint64_t aId) {
		CharMapChange lChange;
		lChange.Id = aId;
		std::cout << "What do you want to change in ID " << aId << "?\n"
		          "(I) - Input\n"
		          "(O) - Output\n";
		char lBuffer;
		std::cin >> lBuffer;
		
		switch(lBuffer) {
			case('i'):
			case('I'):
				lChange.Destination = CharMapChangeDest::INPUT;
				break;
			case('o'):
			case('O'):
				lChange.Destination = CharMapChangeDest::OUTPUT;
				break;
			default:
				std::cout << "Invalid character " << lBuffer << "\n";
				return CharMapChange();
		}
		
		std::cout << "What to you want to replace the ";
		if(lBuffer == 'i' || lBuffer == 'I') {
			std::cout << "input ";
		}
		else {
			std::cout << "output ";
		}
		std::cout << "of id " << aId << " with?\nMax. 3 letters. If you write more than that, the letters will be discarded.\n";
		std::string lTemp;
		std::cin >> lTemp;
		PEInternal::AllocateCharsToEntry(lTemp, lChange.New);
		
		return lChange;
	}
	
	int64_t PromptRemove() {
		std::cout << "Please select ID of character map entry to be removed: ";
		return PEInternal::Prompt();
	}
	int64_t PromptFileSelect() {
		std::cout << "Please select ID of file to be loaded: ";
		return PEInternal::Prompt();
	}
}
