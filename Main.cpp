#include "CharMap.h"

int main(int argc, char* argv[]) {
#ifdef _WIN32
	SetConsoleTitle(_T("MuffleSpeech 1.1.0 (build 5)"));
#endif
	
	std::string lInput;
	std::string lSavedFile;
	MuffleSpeech::Arguments lArgs;
	MuffleSpeech::CharMap lCm;
	MuffleSpeech::FileMap lFm;
	
	MuffleSpeech::ProcessArgs(argc, argv, &lArgs);
	
	MuffleSpeech::Shell::About(&lArgs);
	
	MuffleSpeech::LoadCharMaps(&lFm, &lCm);
	std::cout << "MuffleSpeech profile loaded, please input a string.\nInput _EXIT to exit the program.\nInput _HELP for function documentation.\n";
	
	while(true) {
		std::cout << "mfsp>";
		std::getline(std::cin >> std::ws, lInput);
		
		if(lInput[0] == '_') {
			if(lInput.size() == 2) {
				switch(lInput[1]) {
					default:
						std::cout << lInput << ": No such shortcut.\n";
					case('H'):
						MuffleSpeech::Shell::Help();
						break;
					case('A'):
						MuffleSpeech::Shell::About(&lArgs);
						break;
					case('R'):
						MuffleSpeech::LoadCharMaps(&lFm, &lCm);
						break;
					case('E'):
						std::cout << "Exiting MuffleSpeech...\n";
						MuffleSpeech::Shell::PauseExit(0);
					case('Q'):
						std::cout << "Quitting MuffleSpeech...\n";
						MuffleSpeech::Shell::PauseExit(0);
				}
			}
			//LONG VERSIONS
			else {
				if(lInput == "_EXIT") {
					std::cout << "Exiting MuffleSpeech...\n";
					MuffleSpeech::Shell::PauseExit(0);
				} else if(lInput == "_QUIT") {
					std::cout << "Quitting MuffleSpeech...\n";
					MuffleSpeech::Shell::PauseExit(0);
				} else if(lInput == "_HELP") {
					MuffleSpeech::Shell::Help();
				} else if(lInput == "_ABOUT") {
					MuffleSpeech::Shell::About(&lArgs);
				} else if(lInput == "_RELOAD") {
					MuffleSpeech::LoadCharMaps(&lFm, &lCm);
				} else {
					std::cout << lInput << ": No such command.\n";
				}
			}
		}
		//APPLYING CHARMAP
		else {
			char lBuffer;
			std::cout << "Do you want to enable logging?\nThis will result in a slowdown, but is useful for debugging. (Y/N)\n";
			std::cin >> lBuffer;
			
			std::cout << "\nInput: " << lInput << "\n";
			
			if(lBuffer == 'Y' or lBuffer == 'y') {
				MuffleSpeech::ApplyCharMap(lInput, &lCm, true);
			} else {
				MuffleSpeech::ApplyCharMap(lInput, &lCm, false);
			}
			
			std::cout << "Output: " << lInput << "\n"
			          "Do you want to save the output? (Y/N)\n";
			std::cin >> lBuffer;
			if(lBuffer == 'Y' or lBuffer == 'y') {
				std::ofstream lOfstream;
				if(lSavedFile.empty()) {
					std::cout << "Please enter filename: ";
					std::cin >> lSavedFile;
				} else {
					std::cout << "Do you want to use the file opened previously? (Y/N)\n";
					std::cin >> lBuffer;
					if(lBuffer != 'Y' and lBuffer != 'y') {
						std::cout << "Please enter filename: ";
						std::cin >> lSavedFile;
					}
				}
				lOfstream.open(lSavedFile, std::ios::app);
				lOfstream << lInput << "\n";
				lOfstream.close();
				std::cout << "Output saved to " << lSavedFile << "\n";
			}
		}
		
		lInput.clear();
	}
	MuffleSpeech::Shell::PauseExit(0);
}
