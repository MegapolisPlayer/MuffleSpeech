#ifndef MUFFLESPEECH_SHELLHANDLER
#define MUFFLESPEECH_SHELLHANDLER
#include "ArgumentHandler.h"

namespace MuffleSpeech {
	struct AppInfo {
		RawStr DeveloperName;
		RawStr DeveloperGroupName;
		RawStr ConfigName;
		RawStr Version;
		RawStr Year;
		
		AppInfo();
		AppInfo(RawStr aDeveloperName, RawStr aDeveloperGroupName, RawStr aConfigName, RawStr aVersion, RawStr aYear);
	};
	
	const extern AppInfo MuffleSpeechInfo;
	
	namespace Shell {	
		struct ConsoleCommand {
			std::string LongName, ShortName;
			ConsoleCommand() : LongName(""), ShortName("") {}
			ConsoleCommand(std::string aLongName, std::string aShortName) : LongName(aLongName), ShortName(aShortName) {}
		};
		
		struct ConsoleCommands {
			std::vector<ConsoleCommand> Map;
		};
		
		void MultiLineInput(std::string& aInput);
		
		void About(Arguments* aArgs);
		void Help();
		void PauseExit [[noreturn]] (const uint8_t code);
	}
}

#endif
