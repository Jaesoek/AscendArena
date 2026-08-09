#include "ArenaAscend/UI/Text/AscendHangulSubstitution.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FAscendHangulSubstitutionTest,
	"ArenaAscend.UI.Text.HangulSubstitution",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FAscendHangulSubstitutionTest::RunTest(const FString& Parameters)
{
	TestEqual(
		TEXT("Precomposed Hangul syllables are substituted"),
		FAscendHangulSubstitution::SubstituteWithLatin(TEXT("각")),
		FString(TEXT("rkr")));

	TestEqual(
		TEXT("Initial and final consonants share the same mapping"),
		FAscendHangulSubstitution::SubstituteWithLatin(TEXT("ㄱㅏㄱ")),
		FString(TEXT("rkr")));

	TestEqual(
		TEXT("Non-Hangul characters are preserved"),
		FAscendHangulSubstitution::SubstituteWithLatin(TEXT("안녕 Arena 123!")),
		FString(TEXT("dkssud Arena 123!")));

	return true;
}

#endif
