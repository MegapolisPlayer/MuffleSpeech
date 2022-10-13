#ifndef MUFFLESPEECH_SHELLHANDLER
#define MUFFLESPEECH_SHELLHANDLER
#include <MS/MFSP.h>

namespace MuffleSpeech {
	namespace Shell {
		extern const MFSPInfo gShInfo;
		
		extern const char* gConsoleCommands[];
		extern uint64_t gConsoleCommandsAmount;
		
		std::string PromptFilename();
		std::string PromptAppend(std::string aBuffer);
		char PromptBufferSelectLite();
		char PromptBufferSelect();
		
		void DetectLoadFile(CharMap* aCm, File* aFile);
		
		void About(Arguments* aArgs);
		void Help();
		void ExitSuccess();
		void ExitFailure();
	}
}

#endif
