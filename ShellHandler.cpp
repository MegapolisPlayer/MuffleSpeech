#include "ShellHandler.h"

namespace MuffleSpeech {
	AppInfo::AppInfo() {
		this->DeveloperName = "";
		this->DeveloperGroupName = "";
		this->ConfigName = "";
		this->Version = "";
		this->Year = "";
	}
	AppInfo::AppInfo(RawStr aDeveloperName, RawStr aDeveloperGroupName, RawStr aConfigName, RawStr aVersion, RawStr aYear) {
		this->DeveloperName = aDeveloperName;
		this->DeveloperGroupName = aDeveloperGroupName;
		this->ConfigName = aConfigName;
		this->Version = aVersion;
		this->Year = aYear;
	}
	
	//Contributing? Add you name here!
#ifdef _WIN32
	const AppInfo MuffleSpeechInfo("Martin", "MegapolisPlayer", "Windows x64", "1.1.0 (b5)", "2022");
#else
	const AppInfo MuffleSpeechInfo("Martin", "MegapolisPlayer", "Linux x64", "1.1.0 (b5)", "2022");
#endif
	
	namespace Shell {
		void About(Arguments* aArgs) {
		
			if(!aArgs->DisabledAsciiArt) {
#ifdef _WIN32
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, 23);
#endif
				std::cout <<
#ifdef __linux
				          "\x1b[0;37;44m"
#endif
				          " ________________________________________________________________ \n"
				          "|                                                                |\n"
				          "|  #   #         ##   ## #        ##                         #   |\n"
				          "|  ## ##  # #   #    #   #   #   #      ##    #    #     ##  #   |\n"
				          "|  # # #  # #  ###  ###  #  # #   ##   #  #  # #  # #   #    ##  |\n"
				          "|  #   #  # #   #    #   #  ##      #  #  #  ##   ##    #    # # |\n"
				          "|  #   #   #    #    #   #   ###  ##   ###    ###  ###   ##  # # |\n"
				          "|                                      #                         |\n"
				          "|                                      #                         |\n"
				          "|                                      #                         |\n"
				          "|________________________________________________________________|"
#ifdef __linux
				          "\x1b[0;39;49m"
#endif
				          "\n";
#ifdef _WIN32
				SetConsoleTextAttribute(h, 7);
#endif
			}
			
			std::cout << "MuffleSpeech " << MuffleSpeechInfo.Version << " (" << MuffleSpeechInfo.ConfigName
			          << ")\nby " << MuffleSpeechInfo.DeveloperGroupName << "/" << MuffleSpeechInfo.DeveloperName << ", " << MuffleSpeechInfo.Year
			          << "\nMuffleSpeech (c) 2022 by MegapolisPlayer is licensed under CC BY 4.0.\n";
		}
		void Help() {
			std::cout << "MuffleSpeech HELP:\n"
			          "(_H) _HELP - display this menu\n"
			          "(_R) _RELOAD - reload character map\n"
			          "(_A) _ABOUT - about the application\n"
			          "(_E, _Q) _EXIT or _QUIT - Exit application\n"
			          "Any other string not beginning with \'_\' will be muffled according to the current loaded profile.\n"
			          "The commands in brackets are the shortened variation.\n";
		}
		void PauseExit [[noreturn]](const uint8_t code) {
			std::cout << "\nPress any key and enter to exit...\n";
			char lBuffer;
			std::cin >> lBuffer;
			exit(code);
		}
	}
}
