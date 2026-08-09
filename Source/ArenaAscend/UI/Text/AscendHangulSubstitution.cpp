#include "AscendHangulSubstitution.h"

namespace
{
	constexpr TCHAR HangulSyllableBase = 0xAC00;
	constexpr TCHAR HangulSyllableLast = 0xD7A3;
	constexpr int32 MedialCount = 21;
	constexpr int32 FinalCount = 28;
	constexpr int32 SyllablesPerInitial = MedialCount * FinalCount;

	const TCHAR* InitialMappings[] =
	{
		TEXT("r"), TEXT("R"), TEXT("s"), TEXT("e"), TEXT("E"), TEXT("f"), TEXT("a"),
		TEXT("q"), TEXT("Q"), TEXT("t"), TEXT("T"), TEXT("d"), TEXT("w"), TEXT("W"),
		TEXT("c"), TEXT("z"), TEXT("x"), TEXT("v"), TEXT("g")
	};

	const TCHAR* MedialMappings[] =
	{
		TEXT("k"), TEXT("o"), TEXT("i"), TEXT("O"), TEXT("j"), TEXT("p"), TEXT("u"),
		TEXT("P"), TEXT("h"), TEXT("hk"), TEXT("ho"), TEXT("hl"), TEXT("y"), TEXT("n"),
		TEXT("nj"), TEXT("np"), TEXT("nl"), TEXT("b"), TEXT("m"), TEXT("ml"), TEXT("l")
	};

	const TCHAR* FinalMappings[] =
	{
		TEXT(""), TEXT("r"), TEXT("R"), TEXT("rt"), TEXT("s"), TEXT("sw"), TEXT("sg"),
		TEXT("e"), TEXT("f"), TEXT("fr"), TEXT("fa"), TEXT("fq"), TEXT("ft"), TEXT("fx"),
		TEXT("fv"), TEXT("fg"), TEXT("a"), TEXT("q"), TEXT("qt"), TEXT("t"), TEXT("T"),
		TEXT("d"), TEXT("w"), TEXT("c"), TEXT("z"), TEXT("x"), TEXT("v"), TEXT("g")
	};

	const TCHAR* GetCompatibilityJamoMapping(TCHAR Character)
	{
		switch (Character)
		{
		case 0x3131: return TEXT("r");
		case 0x3132: return TEXT("R");
		case 0x3133: return TEXT("rt");
		case 0x3134: return TEXT("s");
		case 0x3135: return TEXT("sw");
		case 0x3136: return TEXT("sg");
		case 0x3137: return TEXT("e");
		case 0x3138: return TEXT("E");
		case 0x3139: return TEXT("f");
		case 0x313A: return TEXT("fr");
		case 0x313B: return TEXT("fa");
		case 0x313C: return TEXT("fq");
		case 0x313D: return TEXT("ft");
		case 0x313E: return TEXT("fx");
		case 0x313F: return TEXT("fv");
		case 0x3140: return TEXT("fg");
		case 0x3141: return TEXT("a");
		case 0x3142: return TEXT("q");
		case 0x3143: return TEXT("Q");
		case 0x3144: return TEXT("qt");
		case 0x3145: return TEXT("t");
		case 0x3146: return TEXT("T");
		case 0x3147: return TEXT("d");
		case 0x3148: return TEXT("w");
		case 0x3149: return TEXT("W");
		case 0x314A: return TEXT("c");
		case 0x314B: return TEXT("z");
		case 0x314C: return TEXT("x");
		case 0x314D: return TEXT("v");
		case 0x314E: return TEXT("g");
		case 0x314F: return TEXT("k");
		case 0x3150: return TEXT("o");
		case 0x3151: return TEXT("i");
		case 0x3152: return TEXT("O");
		case 0x3153: return TEXT("j");
		case 0x3154: return TEXT("p");
		case 0x3155: return TEXT("u");
		case 0x3156: return TEXT("P");
		case 0x3157: return TEXT("h");
		case 0x3158: return TEXT("hk");
		case 0x3159: return TEXT("ho");
		case 0x315A: return TEXT("hl");
		case 0x315B: return TEXT("y");
		case 0x315C: return TEXT("n");
		case 0x315D: return TEXT("nj");
		case 0x315E: return TEXT("np");
		case 0x315F: return TEXT("nl");
		case 0x3160: return TEXT("b");
		case 0x3161: return TEXT("m");
		case 0x3162: return TEXT("ml");
		case 0x3163: return TEXT("l");
		default: return nullptr;
		}
	}
}

FString FAscendHangulSubstitution::SubstituteWithLatin(const FString& Source)
{
	FString Result;
	Result.Reserve(Source.Len() * 3);

	for (const TCHAR Character : Source)
	{
		if (Character >= HangulSyllableBase && Character <= HangulSyllableLast)
		{
			const int32 SyllableIndex = Character - HangulSyllableBase;
			const int32 InitialIndex = SyllableIndex / SyllablesPerInitial;
			const int32 MedialIndex = (SyllableIndex % SyllablesPerInitial) / FinalCount;
			const int32 FinalIndex = SyllableIndex % FinalCount;

			Result.Append(InitialMappings[InitialIndex]);
			Result.Append(MedialMappings[MedialIndex]);
			Result.Append(FinalMappings[FinalIndex]);
			continue;
		}

		if (const TCHAR* JamoMapping = GetCompatibilityJamoMapping(Character))
		{
			Result.Append(JamoMapping);
			continue;
		}

		Result.AppendChar(Character);
	}

	return Result;
}
