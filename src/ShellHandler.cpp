#include "ShellHandler.h"

namespace GlobalVariables {
	RawStr DeveloperName = "Martin";
	RawStr DeveloperGroupName = "MegapolisPlayer";
#ifdef _WIN32
	RawStr ConfigName = "Windows x64";
#else
	RawStr ConfigName = "Linux x64";
#endif
	RawStr Version = "1.0 (b4)";
	RawStr Year = "2022";
}

namespace MFShell {
	void About() {
		std::cout <<
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
		          "|________________________________________________________________|\n"
		          << "MuffleSpeech " << GlobalVariables::Version << " (" << GlobalVariables::ConfigName
		          << ")\nby " << GlobalVariables::DeveloperGroupName << "/" << GlobalVariables::DeveloperName << ", " << GlobalVariables::Year
		          << "\nMuffleSpeech (c) 2022 by MegapolisPlayer is licensed under CC BY 4.0.\n";
	}
	void Help() {
		std::cout << "MuffleSpeech HELP:\n"
		          "(_E, _Q) _EXIT or _QUIT - Exit application\n"
		          "(_H) _HELP - display this menu\n"
		          "(_R) _RELOAD - reload character map\n"
		          "(_A) _ABOUT - about the application\n"
		          "Any other string not beginning with \'_\' will be muffled according to the current loaded profile.\n"
				  "The command in brackets is the shortened form.\n";
	}
	void PauseExit(const uint8_t code) {
		std::cout << "\nPress any key and enter to exit...\n";
		char lBuffer;
		std::cin >> lBuffer;
		exit(code);
	}
}
