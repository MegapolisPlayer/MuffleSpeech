#include "ShellHandler.h"

namespace MuffleSpeech {
	namespace Shell {
		//Contributing on the shell? Add your name here!
		//MAKE SURE TO PLEASE SEPARATE YOUR NAMES BY MEWLINE
		const MFSPInfo gShInfo("Shell", "2.0.1", "Commander-in-chief", __DATE__, "Martin/MegapolisPlayer",
		                       ""
		                       ""
		                       "" //here
		                      );
		                      
		const char* gConsoleCommands[] = {
			"APPLY",
			"STRBUF",
			"ECHOBUF",
			"COPYBUF",
			"CLEARBUF",
			"SAVEBUF",
			"RELOAD",
			"PRINT",
			"LIST",
			"ABOUT",
			"HELP",
			"EXIT",
			"QUIT"
		};
		uint64_t gConsoleCommandsAmount = 13;
		static const char* sConsoleCommandDesc[] = {
			"Applies the character map to STRBUF and saves the result in FINBUF.",
			"Appends STRBUF.",
			"Appends ECHOBUF.",
			"Copies contents of other buffers the ECHOBUF.",
			"Clears selected buffer.",
			"Saves selected buffer to file.",
			"Reloads the character map.",
			"Prints the contents of ECHOBUF.",
			"Prints the current loaded profile.",
			"Prints the about menu.",
			"Loads the main help prompt.",
			"Exits the application.",
			"Same as EXIT."
		};
		static constexpr uint64_t sConsoleCommandDescAmount = 13;
		
		std::string PromptFilename() {
			std::cout << "Please enter filename (with extension): ";
			std::string lTemp;
			std::cin >> lTemp;
			return lTemp;
		}
		std::string PromptAppend(std::string aBuffer) {
			std::cout << "Append to " << aBuffer << ": ";
			std::string lTemp;
			std::getline(std::cin >> std::ws, lTemp);
			return lTemp;
		}
		char PromptBufferSelectLite() {
			std::cout << "Which buffer to copy to ECHOBUF?\n(S) - STRBUF\n(F) - FINBUF\n";
			std::string lTemp;
			std::cin >> lTemp;
			return lTemp[0]; //done this way to not have issues
		}
		char PromptBufferSelect() {
			std::cout << "Which buffer to copy to ECHOBUF?\n(S) - STRBUF\n(F) - FINBUF\n(E) - ECHOBUF\n";
			std::string lTemp;
			std::cin >> lTemp;
			return lTemp[0];
		}
		
		void DetectLoadFile(CharMap* aCm, File* aFile) {
			MuffleSpeech::FileMap lFm;
			lFm.Detect();
			
			if(lFm.Map.size() == 0) {
				MuffleSpeech::ScopedColor lSC(MuffleSpeech::COLOR_RED);
				std::cout << "Error: No MFSP2 files detected.\nIf you have older files, please try running then through the Profile Editor under the load legacy profile option.\n";
				MuffleSpeech::Exit(EXIT_FAILURE);
			}
			int64_t lId = lFm.Select(); //also prints
			if(lId == -1) {
				MuffleSpeech::ScopedColor lSC(MuffleSpeech::COLOR_RED);
				std::cout << "Error: Input not numeric.\n";
				MuffleSpeech::Exit(EXIT_FAILURE);
			}
			if(lId > lFm.Map.size()) {
				MuffleSpeech::ScopedColor lSC(MuffleSpeech::COLOR_RED);
				std::cout << "Error: Input out or range.\n";
				MuffleSpeech::Exit(EXIT_FAILURE);
			}
			
			aFile->Open(lFm.Map[lId].Name);
			aCm->Map.clear();
			aCm->Load(aFile);
			
			if(aCm->Map.empty()) {
				MuffleSpeech::ScopedColor lSC(MuffleSpeech::COLOR_RED);
				std::cout << "File loaded was empty.\n";
				MuffleSpeech::Exit(EXIT_FAILURE);
			}
			
			aFile->Close();
			
			aCm->Print();
		}
		
		void About(Arguments* aArgs) {
		
			if(!aArgs->DisableAsciiArt) {
#ifdef _WIN32
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, 23);
#endif
				std::cout <<
#ifdef __linux
				          "\x1b[0;37;44m"
#endif
				          " ______________________________________________________________________ \n"
				          "|                                                                      |\n"
				          "|  #   #         ##   ## #        ##                         #     ##  |\n"
				          "|  ## ##  # #   #    #   #   #   #      ##    #    #     ##  #    #  # |\n"
				          "|  # # #  # #  ###  ###  #  # #   ##   #  #  # #  # #   #    ##     #  |\n"
				          "|  #   #  # #   #    #   #  ##      #  #  #  ##   ##    #    # #   #   |\n"
				          "|  #   #   #    #    #   #   ###  ##   ###    ###  ###   ##  # #  #### |\n"
				          "|                                      #                               |\n"
				          "|                                      #                               |\n"
				          "|                                      #                               |\n"
				          "|______________________________________________________________________|"
#ifdef __linux
				          "\x1b[0;39;49m"
#endif
				          "\n";
#ifdef _WIN32
				SetConsoleTextAttribute(h, 7);
#endif
			}
			std::cout << MuffleSpeechInfo << gShInfo;
		}
		
		static void CommandList() {
			if(gConsoleCommandsAmount != sConsoleCommandDescAmount) {
				ScopedColor lSC(COLOR_RED);
				std::cout << "Error: mismatch between declared command amount and declared help menu prompts (file: " << __FILE__ << ")\n";
				Exit(EXIT_FAILURE);
			}
			
			std::cout << "--Command list:---------------\n";
			for(uint64_t lId = 0; lId < gConsoleCommandsAmount; lId++) {
				std::cout << gConsoleCommands[lId] << " - " << sConsoleCommandDesc[lId] << "\n";
			}
			std::cout << "------------------------------\n";
		}
		static void Changelog() {
			std::cout <<
			          "--MFSP Changelog:-------------\n"
			          "----Overall improvements:-----\n"
			          "-profile editor\n"
			          "-statistics and statistics viewer\n"
			          "(statsviewer) saving snapshots as custom format and as CSV\n"
			          "-improved help menu\n"
			          "-time output, performance measuring\n"
			          "-grammar correction\n"
			          "-new file format, mfsp2\n"
			          "-ability to change up to 3 characters\n"
			          "----New arguments:------------\n"
			          "(shell) `-disable_art` - disable ascii art (changed from last release)\n"
			          "(lib) `-nostat` - disable statistics\n"
			          "------------------------------\n"
			          "All arguments only apply to current session.\n"
			          "------------------------------\n";
		}
		void Help() {
			while(true) {
				std::cout << "--MuffleSpeech Help:----------\n"
				          "Please select an option:\n"
				          "(L) - List all commands\n"
				          "(C) - List changelog\n"
				          "Press any other key to return to shell.\n";
				char lBuffer;
				std::cin >> lBuffer;
				switch(lBuffer) {
					case('L'): case('l'):
						CommandList();
						break;
					case('C'): case('c'):
						Changelog();
						break;
					default: return;
					
				}
			}
		}
		void ExitSuccess() { Exit(EXIT_SUCCESS); }
		void ExitFailure() { Exit(EXIT_FAILURE); }
	}
}
