#include "StdInclude.h"

struct ConsoleCommand {
	std::string LongName, ShortName;
	ConsoleCommand() : LongName(""), ShortName("") {}
	ConsoleCommand(std::string aLongName, std::string aShortName) : LongName(aLongName), ShortName(aShortName) {}
};

struct ConsoleCommands {
	std::vector<ConsoleCommand> Map;
};

namespace GlobalVariables {
	extern RawStr DeveloperName;
	extern RawStr DeveloperGroupName;
	extern RawStr ConfigName;
	extern RawStr Version;
	extern RawStr Year;
}

namespace MFShell {
	void About();
	void Help();
	void PauseExit(const uint8_t code);
}
