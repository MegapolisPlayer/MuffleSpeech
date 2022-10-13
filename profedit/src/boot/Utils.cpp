#include "Utils.h"

namespace ProfileEditor {
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
		} else if(aForeground <= 8) {
			lTemp.append(std::to_string(aForeground + 30));
		} else {
			lTemp.append(std::to_string(aForeground + 82));
		}
		lTemp += ';'; //why C++ stl??
		if(aBackground == COLOR_DEFAULT) {
			lTemp.append("49");
		} else if(aBackground <= 8) {
			lTemp.append(std::to_string(aBackground + 40));
		} else {
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
	
	double StringSameScoreC(const char* aCompareWhat, const char* aCompareTo) {
		uint64_t lString1Size = strlen(aCompareWhat);
		uint64_t lString2Size = strlen(aCompareTo);
		uint64_t lStringMaxLen;
		uint64_t lStringMinLen;
		
		if(lString1Size == lString2Size) {
			lStringMinLen = lString1Size;
			lStringMaxLen = lStringMinLen;
		} else {
			lStringMinLen = std::min(lString1Size, lString2Size);
			lStringMaxLen = std::max(lString1Size, lString2Size);
		}
		
		
		uint64_t lSameChars = 0;
		for(uint64_t lId = 0; lId < lStringMinLen; lId++) {
			if(aCompareWhat[lId] == aCompareTo[lId]) {
				lSameChars++;
			}
			if(aCompareWhat[lId] - 32 == aCompareTo[lId]) { //ascii lowercase offset, expects than aString1 is lowercase/user input
				lSameChars++;
			}
		}
		
		return double(lSameChars) / double(lStringMaxLen);
	}
	double StringSameScoreC(std::string aCompareWhat, std::string aCompareTo) {
		uint64_t lStringMinLen = std::min(aCompareWhat.size(), aCompareTo.size());
		uint64_t lStringMaxLen = std::max(aCompareWhat.size(), aCompareTo.size());
		
		uint64_t lSameChars = 0;
		for(uint64_t lId = 0; lId < lStringMinLen; lId++) {
			if(aCompareWhat[lId] == aCompareTo[lId]) {
				lSameChars++;
			}
			if(aCompareWhat[lId] - 32 == aCompareTo[lId]) { //ascii lowercase offset, expects that aString1 is lowercase/user input
				lSameChars++;
			}
		}
		
		return double(lSameChars) / double(lStringMaxLen);
	}
	
	uint64_t FindMostSimilarC(std::string aCompareTo, std::vector<std::string> aStrings) {
		uint64_t lTempBest = 0;
		double lTempBestScore = 0.0;
		for(uint64_t lId = 0; lId < aStrings.size(); lId++) {
			double lWorkingScore = StringSameScoreC(aCompareTo, aStrings[lId]);
			if(lWorkingScore > lTempBestScore) {
				lTempBest = lId;
				lTempBestScore = lWorkingScore;
			}
		}
		return lTempBest;
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
	
	void Exit(int aCode) {
		std::cout << "MFSP ProfileEditor exiting with code " << aCode << ".\n";
		char lBuffer;
		std::cout << "Press any key and ENTER to exit.\n";
		std::cin >> lBuffer;
		exit(aCode);
	}
}
