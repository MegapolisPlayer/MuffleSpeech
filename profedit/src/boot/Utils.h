#ifndef PROFILEEDITOR_UTILS
#define PROFILEEDITOR_UTILS
#include "StdInclude.h"

#define elif     else if
#define loopover continue;

namespace ProfileEditor {
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
	//True ids of linux color, not used currently
	//holds only foreground colors
	enum struct ColorTrue {
		PE_COLOR_TRUE_BLACK = 30,
		PE_COLOR_TRUE_RED,
		PE_COLOR_TRUE_GREEN,
		PE_COLOR_TRUE_BROWN,
		PE_COLOR_TRUE_BLUE,
		PE_COLOR_TRUE_PURPLE,
		PE_COLOR_TRUE_CYAN,
		PE_COLOR_TRUE_LIGHT_GREY,
		PE_COLOR_TRUE_DEFAULT = 39,
		PE_COLOR_TRUE_DARK_GREY = 90,
		PE_COLOR_TRUE_LIGHT_RED,
		PE_COLOR_TRUE_LIGHT_GREEN,
		PE_COLOR_TRUE_YELLOW,
		PE_COLOR_TRUE_LIGHT_BLUE,
		PE_COLOR_TRUE_PINK,
		PE_COLOR_TRUE_LIGHT_CYAN,
		PE_COLOR_TRUE_WHITE
	};
#endif
	
	void SetColor(Color aForeground, Color aBackground = COLOR_DEFAULT);
	void ResetColor();
	
	class ScopedColor {
	public:
		ScopedColor(Color aForeground, Color aBackground = COLOR_DEFAULT);
		~ScopedColor();
	};
	
	//for future: add proper capital/lowercase comparisons
	//new version:
	//
	//list if in offset +1 -1
	
	//for grammar checking - highest score is the closest (0 to 1)
	//string MUST be null-terminated, capital only variation
	double StringSameScoreC(const char* aCompareWhat, const char* aCompareTo);
	//for grammar checking - highest score is the closest (0 to 1), capital only variation
	double StringSameScoreC(std::string aCompareWhat, std::string aCompareTo);
	
	//returns id of most similar string in array, capital only variation
	uint64_t FindMostSimilarC(std::string aCompareTo, std::vector<std::string> aStrings);
	
	bool IsNumber(const char* aString);
	bool IsNumber(std::string aString);
	
	void Exit(int aCode);
}

#endif
