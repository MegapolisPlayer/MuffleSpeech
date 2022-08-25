#include "CharMap.h"
#include "ShellHandler.h"

int main() {
	MFShell::About();
	std::string lTemporary;
	CharMap lCm;
	FileMap lFm;
	
	MuffleSpeech::FindFiles(&lFm);
	if(lFm.Map.size() == 0) { MFShell::PauseExit(1); }
	MuffleSpeech::PrintFiles(&lFm);
	uint64_t lSelection = MuffleSpeech::SelectFile(&lFm);
	if(lSelection == 0) { MFShell::PauseExit(0); }
	if(!MuffleSpeech::LoadCharMap(&lFm.Map[lSelection - 1], &lCm)) { MFShell::PauseExit(1); }
	std::cout << "Character changes detected: " << lCm.Map.size() << "\nGenerating capital letter variants:\n";
	MuffleSpeech::GenerateCapitals(&lCm);
	MuffleSpeech::PrintCharMap(&lCm);
	std::cout << "MuffleSpeech profile loaded, please input a string.\nInput _EXIT to exit the program.\nInput _HELP for function documentation.\n";
	while(true) {
		std::cout << "mfsp>";
		std::getline(std::cin >> std::ws, lTemporary);
		
		if(lTemporary[0] == '_') {
			if(lTemporary.size() == 2) {
				switch(lTemporary[1]) {
					default:
						std::cout << lTemporary << ": No such shortcut.\n";
					case('E'):
						std::cout << "Exiting MuffleSpeech...\n";
						MFShell::PauseExit(0);
					case('Q'):
						std::cout << "Quitting MuffleSpeech...\n";
						MFShell::PauseExit(0);
					case('H'):
						MFShell::Help();
						break;
					case('A'):
						MFShell::About();
						break;
					case('R'):
						lFm.Map.clear();
						lCm.Map.clear();
						MuffleSpeech::FindFiles(&lFm);
						if(lFm.Map.size() == 0) { MFShell::PauseExit(1); }
						MuffleSpeech::PrintFiles(&lFm);
						uint64_t lSelection = MuffleSpeech::SelectFile(&lFm);
						if(lSelection == 0) { MFShell::PauseExit(0); }
						if(!MuffleSpeech::LoadCharMap(&lFm.Map[lSelection - 1], &lCm)) { MFShell::PauseExit(1);	}
						std::cout << "Character changes detected: " << lCm.Map.size() << "\nGenerating capital letter variants:\n";
						MuffleSpeech::GenerateCapitals(&lCm);
						MuffleSpeech::PrintCharMap(&lCm);
						break;
				}
			} else {
				if(lTemporary == "_EXIT") {
					std::cout << "Exiting MuffleSpeech...\n";
					MFShell::PauseExit(0);
				} else if(lTemporary == "_QUIT") {
					std::cout << "Quitting MuffleSpeech...\n";
					MFShell::PauseExit(0);
				} else if(lTemporary == "_HELP") {
					MFShell::Help();
				} else if(lTemporary == "_ABOUT") {
					MFShell::About();
				} else if(lTemporary == "_RELOAD") {
					lFm.Map.clear();
					lCm.Map.clear();
					MuffleSpeech::FindFiles(&lFm);
					if(lFm.Map.size() == 0) { MFShell::PauseExit(1); }
					MuffleSpeech::PrintFiles(&lFm);
					uint64_t lSelection = MuffleSpeech::SelectFile(&lFm);
					if(lSelection == 0) { MFShell::PauseExit(0); }
					if(!MuffleSpeech::LoadCharMap(&lFm.Map[lSelection - 1], &lCm)) { MFShell::PauseExit(1);	}
					std::cout << "Character changes detected: " << lCm.Map.size() << "\nGenerating capital letter variants:\n";
					MuffleSpeech::GenerateCapitals(&lCm);
					MuffleSpeech::PrintCharMap(&lCm);
				} else {
					std::cout << lTemporary << ": No such command.\n";
				}
			}
		} else {
			char lBuffer;
			std::cout << "Do you want to enable logging?\nThis will result in a slowdown, but is useful for debugging. (Y/N)\n";
			std::cin >> lBuffer;
			std::cout << "\nInput: " << lTemporary << "\n";
			if(lBuffer == 'Y' or lBuffer == 'y') {
				MuffleSpeech::ApplyCharMap(lTemporary, &lCm, true);
			} else {
				MuffleSpeech::ApplyCharMap(lTemporary, &lCm, false);
			}
			std::cout << "Output: " << lTemporary << "\n"
			          "Do you want to save the output? (Y/N)\n";
			std::cin >> lBuffer;
			if(lBuffer == 'Y' or lBuffer == 'y') {
				std::ofstream lOfstream;
				std::string lFilename;
				std::cout << "Please enter filename: ";
				std::cin >> lFilename;
				lOfstream.open(lFilename, std::ios::app);
				lOfstream << lTemporary;
				lOfstream.close();
				std::cout << "Output saved to " << lFilename << "\n";
			}
		}
		
		lTemporary.clear();
	}
	MFShell::PauseExit(0);
}
