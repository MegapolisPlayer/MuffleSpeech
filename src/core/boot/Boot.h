#ifndef MUFFLESPEECH_BOOT
#define MUFFLESPEECH_BOOT
#include "StdInclude.h"

namespace MuffleSpeech {
#ifdef _WIN32
#ifdef MFSPDLL
#define MFFN __declspec(dllexport)
#else
#define MFFN __declspec(dllimport)
#endif
#else
#define MFFN
#endif

	typedef const char* RawStr;
	
	struct MFFN MFSPInfo {
		RawStr Component;
		RawStr Version;
		RawStr VersionName;
		RawStr VersionDate;
		RawStr Author;
		RawStr AdditionalHelp;
		RawStr Config;
		
		MFSPInfo();
		MFSPInfo(RawStr&& aComponent, RawStr&& aVersion, RawStr&& aVersionName, RawStr&& aVersionDate, RawStr&& aAuthor, RawStr&& aAdditionalHelp);
		MFSPInfo(RawStr&& aComponent, RawStr&& aVersion, RawStr&& aVersionName, RawStr&& aVersionDate, RawStr&& aAuthor, RawStr&& aAdditionalHelp, RawStr&& aConfig);
	};
	
	MFFN std::ostream& operator<< (std::ostream& aOstream, const MFSPInfo& aInfo);
	
	MFFN const extern MFSPInfo MuffleSpeechInfo;
	
	struct MFFN Arguments {
		bool DisableAsciiArt = false; //-disable_art
		bool DisableStats = false; //-nostat
	};
	
	MFFN Arguments ProcessArguments(int argc, char** argv);
	
#ifdef _WIN32
	enum Color {
		COLOR_BLACK = 0,
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_CYAN,
		COLOR_RED,
		COLOR_PURPLE,
		COLOR_BROWN,
		COLOR_LIGHT_GREY,
		COLOR_GREY,
		COLOR_LIGHT_BLUE,
		COLOR_LIGHT_GREEN,
		COLOR_LIGHT_CYAN,
		COLOR_LIGHT_RED,
		COLOR_PINK,
		COLOR_YELLOW,
		COLOR_WHITE,
		COLOR_DEFAULT
	};
#endif
#ifdef __linux
	enum Color {
		COLOR_BLACK = 0,
		COLOR_RED,
		COLOR_GREEN,
		COLOR_BROWN,
		COLOR_BLUE,
		COLOR_PURPLE,
		COLOR_CYAN,
		COLOR_LIGHT_GREY,
		COLOR_DARK_GREY = 8,
		COLOR_LIGHT_RED,
		COLOR_LIGHT_GREEN,
		COLOR_YELLOW,
		COLOR_LIGHT_BLUE,
		COLOR_PINK,
		COLOR_LIGHT_CYAN,
		COLOR_WHITE,
		COLOR_DEFAULT = 39
	};
#endif
	
	MFFN void SetColor(Color aForeground, Color aBackground = COLOR_DEFAULT);
	MFFN void ResetColor();
	
	class MFFN ScopedColor {
	public:
		ScopedColor(Color aForeground, Color aBackground = COLOR_DEFAULT);
		~ScopedColor();
	};
	
	MFFN bool IsNumber(const char* aString);
	MFFN bool IsNumber(std::string aString);
	
	MFFN bool IsBetween(uint8_t aLower, char aChar, uint8_t aHigher);
	
	MFFN void PrintCharArray(const char* aArray, const uint64_t aSize);
	MFFN void EmptyCharArray(char* aArray, const uint64_t aSize);
	
	//highest string is the closest
	//size without null terminator
	MFFN double StringSameScore(const char* aCompareWhat, uint64_t aWhatSize, const char* aCompareTo, uint64_t aToSize);
	//highest score is the closest (0 to 1)
	//string MUST be null-terminated
	MFFN double StringSameScore(const char* aCompareWhat, const char* aCompareTo);
	//highest score is the closest (0 to 1)
	MFFN double StringSameScore(std::string aCompareWhat, std::string aCompareTo);
	
	MFFN uint64_t Min64(uint64_t aNum1, uint64_t aNum2);
	
	MFFN void Exit(int aCode);
}

#endif
