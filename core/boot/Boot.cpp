#include "Boot.h"

namespace Internal {
	static double StringSameScore(const char* aCompareWhat, const char* aCompareTo, uint64_t aMinSize, uint64_t aMaxSize) {
		using namespace MuffleSpeech;
		
		double lSameChars = 0;
		
		for(uint64_t lId = 0; lId < aMinSize; lId++) {
			if(IsBetween(65, aCompareWhat[lId], 90)) { //capital
				if(aCompareWhat[lId] + 32 == aCompareTo[lId]) { lSameChars++; loopover; }  //ascii capital offset, expects that aString1 is capital
				elif(lId < aMinSize - 1)                      { if(aCompareWhat[lId + 1] + 32 == aCompareTo[lId]) { lSameChars+=0.5; loopover; } } //+1 offset add 0.5 points
				elif(lId != 0)                                { if(aCompareWhat[lId - 1] + 32 == aCompareTo[lId]) { lSameChars+=0.5; loopover; } } //-1 offset add 0.5 points
			}
			elif(IsBetween(97, aCompareWhat[lId], 122)) { //lowercase
				if(aCompareWhat[lId] - 32 == aCompareTo[lId]) { lSameChars++; loopover; } //ascii lowercase offset, expects that aString1 is lowercase
				elif(lId < aMinSize - 1)                      { if(aCompareWhat[lId + 1] - 32 == aCompareTo[lId]) { lSameChars+=0.5; loopover; } } //+1 offset add 0.5 points
				elif(lId != 0)                                { if(aCompareWhat[lId - 1] - 32 == aCompareTo[lId]) { lSameChars+=0.5; loopover; } } //-1 offset add 0.5 points
			}
			if(aCompareWhat[lId] == aCompareTo[lId]) { lSameChars++; } //compares same
		}
		return double(lSameChars) / double(aMaxSize);
	}
}

namespace MuffleSpeech {
	MFSPInfo::MFSPInfo() {
		this->Component = "";
		this->Version = "";
		this->VersionName = "";
		this->VersionDate = "";
		this->Author = "";
		this->AdditionalHelp = "";
		this->Config = "";
	}
	MFSPInfo::MFSPInfo(RawStr&& aComponent, RawStr&& aVersion, RawStr&& aVersionName, RawStr&& aVersionDate, RawStr&& aAuthor, RawStr&& aAdditionalHelp) {
		this->Component = aComponent;
		this->Version = aVersion;
		this->VersionName = aVersionName;
		this->VersionDate = aVersionDate;
		this->Author = aAuthor;
		this->AdditionalHelp = aAdditionalHelp;
#ifdef _WIN32
		this->Config = "Windows";
#else
		this->Config = "Linux";
#endif
	}
	MFSPInfo::MFSPInfo(RawStr&& aComponent, RawStr&& aVersion, RawStr&& aVersionName, RawStr&& aVersionDate, RawStr&& aAuthor, RawStr&& aAdditionalHelp, RawStr&& aConfig) {
		this->Component = aComponent;
		this->Version = aVersion;
		this->VersionName = aVersionName;
		this->VersionDate = aVersionDate;
		this->Author = aAuthor;
		this->AdditionalHelp = aAdditionalHelp;
		this->Config = aConfig;
	}
	
	std::ostream& operator<< (std::ostream& aOstream, const MFSPInfo& aInfo) {
		aOstream << "MuffleSpeech/" << aInfo.Component << " (" << aInfo.Config << ") v. " << aInfo.Version << " \"" << aInfo.VersionName << "\"\nRelease date:" << aInfo.VersionDate << "\nby " << aInfo.Author << "\n";
		if(strlen("") != 0) {
			aOstream << aInfo.AdditionalHelp << "\n";
		}
		aOstream << "MuffleSpeech is licensed under CC BY 4.0.\nMore information here: creativecommons.org/licenses/by/4.0\n";
		return aOstream;
	}
	
	//Contributing? Add your name here!
	//MAKE SURE TO PLEASE SEPARATE YOUR NAMES BY MEWLINE
	const MFSPInfo MuffleSpeechInfo("Core", "2.0.0", "Commander-in-chief", __DATE__, "Martin/MegapolisPlayer",
	                                ""
	                                ""
	                                "" //here
	                               );
	                               
	Arguments ProcessArguments(int argc, char** argv) {
		Arguments lArgs;
		//on linux: first argument command
		//on windows: first argument directory of exe
		for(int lId = 1; lId < argc; lId++) {
			if(strcmp(argv[lId], "-disable_art") == 0)
				lArgs.DisableAsciiArt = true;
			elif(strcmp(argv[lId], "-nostat") == 0)
			lArgs.DisableStats = true;
			else
				std::cout << "WARNING: no argument " << argv[lId] << "\n";
		}
		return lArgs;
	}
	
	void SetColor(Color aForeground, Color aBackground) {
#ifdef WIN32
		HANDLE lHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(lHandle, (aBackground * 16) + aForeground);
#endif
#ifdef __linux
		std::string lTemp;
		lTemp.append("\x1b[0;");
		if(aForeground == COLOR_DEFAULT) {
			lTemp.append("39");
		}
		else if(aForeground <= 8) {
			lTemp.append(std::to_string(aForeground + 30));
		}
		else {
			lTemp.append(std::to_string(aForeground + 82));
		}
		lTemp += ';'; //why C++ stl??
		if(aBackground == COLOR_DEFAULT) {
			lTemp.append("49");
		}
		else if(aBackground <= 8) {
			lTemp.append(std::to_string(aBackground + 40));
		}
		else {
			lTemp.append(std::to_string(aBackground + 92));
		}
		lTemp += 'm';
		std::cout << lTemp;
#endif
	}
	void ResetColor() {
#ifdef WIN32
		HANDLE lHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(lHandle, 7);
#endif
#ifdef __linux
		std::cout << "\x1b[0;39;49m";
#endif
	}
	
	ScopedColor::ScopedColor(Color aForeground, Color aBackground) {
		SetColor(aForeground, aBackground);
	}
	ScopedColor::~ScopedColor() {
		ResetColor();
	}
	
	bool IsNumber(const char* aString) {
		for(uint64_t lId = 0; lId < strlen(aString); lId++) {
			if((aString[lId] < 48) || (aString[lId] > 57)) {
				return false;
			}
		}
		return true;
	}
	bool IsNumber(std::string aString) {
		for(uint64_t lId = 0; lId < aString.size(); lId++) {
			if((aString[lId] < 48) || (aString[lId] > 57)) {
				return false;
			}
		}
		return true;
	}
	
	bool IsBetween(uint8_t aLower, char aChar, uint8_t aHigher) {
		return (aChar >= aLower && aChar <= aHigher);
	}
	
	void PrintCharArray(const char* aArray, const uint64_t aSize) {
		for(uint64_t lId = 0; lId < aSize; lId++) {
			std::putchar(aArray[lId]);
		}
	}
	void EmptyCharArray(char* aArray, const uint64_t aSize) {
		for(uint64_t lId = 0; lId < aSize; lId++) {
			aArray[lId] = 0;
		}
	}
	
	double StringSameScore(const char* aCompareWhat, uint64_t aWhatSize, const char* aCompareTo, uint64_t aToSize) {
		return Internal::StringSameScore(
		           aCompareWhat,
		           aCompareTo,
		           std::min(aWhatSize, aToSize),
		           std::max(aWhatSize, aToSize)
		       );
	}
	double StringSameScore(const char* aCompareWhat, const char* aCompareTo) {
		uint64_t lString1Size = strlen(aCompareWhat); uint64_t lString2Size = strlen(aCompareTo);
		return Internal::StringSameScore(
		           aCompareWhat,
		           aCompareTo,
		           std::min(lString1Size, lString2Size),
		           std::max(lString1Size, lString2Size)
		       );
	}
	double StringSameScore(std::string aCompareWhat, std::string aCompareTo) {
		return Internal::StringSameScore(
		           aCompareWhat.c_str(),
		           aCompareWhat.c_str(),
		           std::min(aCompareWhat.size(), aCompareTo.size()),
		           std::max(aCompareWhat.size(), aCompareTo.size())
		       );
	}
	
	uint64_t Min64(uint64_t aNum1, uint64_t aNum2) {
		if(aNum1 < aNum2) { return aNum1; }
		else { return aNum2; }
	}
	
	void Exit(int aCode) {
		std::cout << "MFSP ProfileEditor exiting with code " << aCode << ".\n";
		char lBuffer;
		std::cout << "Press any key and ENTER to exit.\n";
		std::cin >> lBuffer;
		exit(aCode);
	}
}
