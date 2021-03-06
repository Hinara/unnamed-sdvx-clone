#include <Shared/Shared.hpp>
#include <Shared/StringEncodingDetector.hpp>
#include <Shared/StringEncodingConverter.hpp>
#include <Tests/Tests.hpp>

#pragma region Test cases

struct EncodingTestCase
{
	const char* utf8;
	const char* cp932;
	const char* cp949;
};

const std::vector<EncodingTestCase> TEST_CASES = {
	{"", nullptr, nullptr},
	{"\r\n-- Test Data--\r\n@@\r\n", nullptr, nullptr},
	{"The quick brown fox jumps over the lazy dog", nullptr, nullptr},
	{"\xEF\xBB\xBF", nullptr, nullptr},

	/* Common Japanese Text */
	{
		// Japanese: 'Iroha' pangram
		"\xe3\x81\x84\xe3\x82\x8d\xe3\x81\xaf\xe3\x81\xab\xe3\x81\xbb\xe3\x81\xb8\xe3\x81\xa9\x20\x2f\x20\xe3\x81\xa1\xe3\x82\x8a\xe3\x81\xac\xe3\x82\x8b\xe3\x82\x92\x20\x2f\x20\xe3\x82\x8f\xe3\x81\x8c\xe3\x82\x88\xe3\x81\x9f\xe3\x82\x8c\xe3\x81\x9e\x20\x2f\x20\xe3\x81\xa4\xe3\x81\xad\xe3\x81\xaa\xe3\x82\x89\xe3\x82\x80\x20\x2f\x20\xe3\x81\x86\xe3\x82\x90\xe3\x81\xae\xe3\x81\x8a\xe3\x81\x8f\xe3\x82\x84\xe3\x81\xbe\x20\x2f\x20\xe3\x81\x91\xe3\x81\xb5\xe3\x81\x93\xe3\x81\x88\xe3\x81\xa6\x20\x2f\x20\xe3\x81\x82\xe3\x81\x95\xe3\x81\x8d\xe3\x82\x86\xe3\x82\x81\xe3\x81\xbf\xe3\x81\x98\x20\x2f\x20\xe3\x82\x91\xe3\x81\xb2\xe3\x82\x82\xe3\x81\x9b\xe3\x81\x9a",
		"\x82\xa2\x82\xeb\x82\xcd\x82\xc9\x82\xd9\x82\xd6\x82\xc7\x20\x2f\x20\x82\xbf\x82\xe8\x82\xca\x82\xe9\x82\xf0\x20\x2f\x20\x82\xed\x82\xaa\x82\xe6\x82\xbd\x82\xea\x82\xbc\x20\x2f\x20\x82\xc2\x82\xcb\x82\xc8\x82\xe7\x82\xde\x20\x2f\x20\x82\xa4\x82\xee\x82\xcc\x82\xa8\x82\xad\x82\xe2\x82\xdc\x20\x2f\x20\x82\xaf\x82\xd3\x82\xb1\x82\xa6\x82\xc4\x20\x2f\x20\x82\xa0\x82\xb3\x82\xab\x82\xe4\x82\xdf\x82\xdd\x82\xb6\x20\x2f\x20\x82\xef\x82\xd0\x82\xe0\x82\xb9\x82\xb8",
		"\xaa\xa4\xaa\xed\xaa\xcf\xaa\xcb\xaa\xdb\xaa\xd8\xaa\xc9\x20\x2f\x20\xaa\xc1\xaa\xea\xaa\xcc\xaa\xeb\xaa\xf2\x20\x2f\x20\xaa\xef\xaa\xac\xaa\xe8\xaa\xbf\xaa\xec\xaa\xbe\x20\x2f\x20\xaa\xc4\xaa\xcd\xaa\xca\xaa\xe9\xaa\xe0\x20\x2f\x20\xaa\xa6\xaa\xf0\xaa\xce\xaa\xaa\xaa\xaf\xaa\xe4\xaa\xde\x20\x2f\x20\xaa\xb1\xaa\xd5\xaa\xb3\xaa\xa8\xaa\xc6\x20\x2f\x20\xaa\xa2\xaa\xb5\xaa\xad\xaa\xe6\xaa\xe1\xaa\xdf\xaa\xb8\x20\x2f\x20\xaa\xf1\xaa\xd2\xaa\xe2\xaa\xbb\xaa\xba",
	},
	{
		// Japanese: "I'm eating dinner"
		"\xe6\x99\xa9\xe3\x81\x94\xe9\xa3\xaf\xe3\x82\x92\xe9\xa3\x9f\xe3\x81\xb9\xe3\x81\xbe\xe3\x81\x99",
		"\x94\xd3\x82\xb2\x94\xd1\x82\xf0\x90\x48\x82\xd7\x82\xdc\x82\xb7",
		"\xd8\xb9\xaa\xb4\xda\xf9\xaa\xf2\xe3\xdd\xaa\xd9\xaa\xde\xaa\xb9",
	},

	/* Common Korean Text */
	{
		// Korean: 'Innate requisite of kiss' pangram
		"\xed\x82\xa4\xec\x8a\xa4\xec\x9d\x98\x20\xea\xb3\xa0\xec\x9c\xa0\x20\xec\xa1\xb0\xea\xb1\xb4\xec\x9d\x80\x20\xec\x9e\x85\xec\x88\xa0\xeb\x81\xbc\xeb\xa6\xac\x20\xeb\xa7\x8c\xeb\x82\x98\xec\x95\xbc\x20\xed\x95\x98\xea\xb3\xa0\x20\xed\x8a\xb9\xeb\xb3\x84\xed\x95\x9c\x20\xea\xb8\xb0\xec\x88\xa0\xec\x9d\x80\x20\xed\x95\x84\xec\x9a\x94\xec\xb9\x98\x20\xec\x95\x8a\xeb\x8b\xa4\x2e",
		nullptr,
		"\xc5\xb0\xbd\xba\xc0\xc7\x20\xb0\xed\xc0\xaf\x20\xc1\xb6\xb0\xc7\xc0\xba\x20\xc0\xd4\xbc\xfa\xb3\xa2\xb8\xae\x20\xb8\xb8\xb3\xaa\xbe\xdf\x20\xc7\xcf\xb0\xed\x20\xc6\xaf\xba\xb0\xc7\xd1\x20\xb1\xe2\xbc\xfa\xc0\xba\x20\xc7\xca\xbf\xe4\xc4\xa1\x20\xbe\xca\xb4\xd9\x2e",
	},
	{
		// Korean: 'Jeep car' string, which can't be represented by EUC-KR
		"\xec\xb0\xa6\xec\xb0\xa8\xeb\xa5\xbc\x20\xed\x83\x80\xea\xb3\xa0\x20\xec\x98\xa8\x20\xed\x8e\xb2\xec\x8b\x9c\xeb\xa7\xa8\xea\xb3\xbc\x20\xec\x91\x9b\xeb\x8b\xa4\xeb\xa6\xac\x20\xeb\x98\xa0\xeb\xb0\xa9\xea\xb0\x81\xed\x95\x98",
		nullptr,
		"\xaa\x42\xc2\xf7\xb8\xa6\x20\xc5\xb8\xb0\xed\x20\xbf\xc2\x20\xbc\x84\xbd\xc3\xb8\xc7\xb0\xfa\x20\x9c\xba\xb4\xd9\xb8\xae\x20\x8c\x63\xb9\xe6\xb0\xa2\xc7\xcf",
	},

	/* Chart Examples from Nautica */
	{
		// Chart: c8232a20-8e7b-11ea-9d73-c3bee55888a3
		"\xe7\x85\x89\xe6\x83\x85\xe3\x83\x9f\xe3\x82\xb9\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x95\xe3\x82\xa3\xe3\x83\xaa\xe3\x82\xa2",
		"\x97\xf9\x8f\xee\x83\x7e\x83\x58\x83\x65\x83\x42\x83\x74\x83\x42\x83\x8a\x83\x41",
		"\xd6\xa1\xef\xd7\xab\xdf\xab\xb9\xab\xc6\xab\xa3\xab\xd5\xab\xa3\xab\xea\xab\xa2",
	},
	{
		"\xe7\x85\x89\xe6\x83\x85\xe3\x83\x9f\xe3\x82\xb9\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x95\xe3\x82\xa3\xe3\x83\xaa\xe3\x82\xa2/\xe7\x85\x89\xe6\x83\x85\xe3\x83\x9f\xe3\x82\xb9\xe3\x83\x86\xe3\x82\xa3\xe3\x83\x95\xe3\x82\xa3\xe3\x83\xaa\xe3\x82\xa2[EXH].ksh",
		"\x97\xf9\x8f\xee\x83\x7e\x83\x58\x83\x65\x83\x42\x83\x74\x83\x42\x83\x8a\x83\x41\x2f\x97\xf9\x8f\xee\x83\x7e\x83\x58\x83\x65\x83\x42\x83\x74\x83\x42\x83\x8a\x83\x41\x5b\x45\x58\x48\x5d\x2e\x6b\x73\x68",
		"\xd6\xa1\xef\xd7\xab\xdf\xab\xb9\xab\xc6\xab\xa3\xab\xd5\xab\xa3\xab\xea\xab\xa2/\xd6\xa1\xef\xd7\xab\xdf\xab\xb9\xab\xc6\xab\xa3\xab\xd5\xab\xa3\xab\xea\xab\xa2[EXH].ksh",
	},
	{
		// Chart: bf036180-8965-11ea-80b5-1921d08a2b47
		"AMAZING MIGHTYYYY!!!! [\xe6\x88\xbb]",
		"AMAZING MIGHTYYYY!!!! [\x96\xdf]",
		nullptr,
	},
	{
		// Chart: 0c655b40-9a8a-11ea-badc-21bdeef837da
		"\xe3\x83\x8a\xe3\x82\xa4\xe3\x83\x88\xe3\x83\xbb\xe3\x82\xaa\xe3\x83\x96\xe3\x83\xbb\xe3\x83\x8a\xe3\x82\xa4\xe3\x83\x84 (\xe3\x81\x8b\xe3\x82\x81\xe3\x82\x8a\xe3\x81\x82\xe2\x80\x99s\xe2\x80\x9c\xe3\x83\xaf\xe3\x83\xb3\xe3\x82\xb9\xe3\x83\xbb\xe3\x82\xa2\xe3\x83\x9d\xe3\x83\xb3\xe3\x83\xbb\xe3\x82\xa2\xe3\x83\xbb\xe3\x83\x8a\xe3\x82\xa4\xe3\x83\x88\xe2\x80\x9dRemix)",
		"\x83\x69\x83\x43\x83\x67\x81\x45\x83\x49\x83\x75\x81\x45\x83\x69\x83\x43\x83\x63\x20\x28\x82\xa9\x82\xdf\x82\xe8\x82\xa0\x81\x66\x73\x81\x67\x83\x8f\x83\x93\x83\x58\x81\x45\x83\x41\x83\x7c\x83\x93\x81\x45\x83\x41\x81\x45\x83\x69\x83\x43\x83\x67\x81\x68\x52\x65\x6d\x69\x78\x29",
		nullptr,
	},
	{
		// Chart: cb18a810-8eea-11ea-905a-5952da03319f
		"\xe3\x82\xa2\xe3\x83\xb3\xe3\x83\x93\xe3\x83\x90\xe3\x83\xac\xe3\x83\xb3\xe3\x83\x88",
		"\x83\x41\x83\x93\x83\x72\x83\x6f\x83\x8c\x83\x93\x83\x67",
		"\xab\xa2\xab\xf3\xab\xd3\xab\xd0\xab\xec\xab\xf3\xab\xc8",
	},
	{
		// Chart: fdb5eb20-5c41-11ea-a235-3f2db8c47d6e
		"\xe3\x83\xac\xe3\x82\xa4\xe3\x83\x89\xe3\x83\x9c\xe3\x82\xb9\x20\xe3\x82\xab\xe3\x82\xbf\xe3\x82\xb9\xe3\x83\x88\xe3\x83\xad\xe3\x83\x95\xe3\x82\xa3\xe3\x83\x83\xe3\x82\xaf\xe3\x83\xbb\xe3\x83\xa9\xe3\x83\xb4",
		"\x83\x8c\x83\x43\x83\x68\x83\x7b\x83\x58\x20\x83\x4a\x83\x5e\x83\x58\x83\x67\x83\x8d\x83\x74\x83\x42\x83\x62\x83\x4e\x81\x45\x83\x89\x83\x94",
		nullptr,
	},
	{
		// Chart: e780b180-9a0b-11e9-8686-b5e42a9923f2
		"\xe9\x9b\xaa\xe3\x81\xae\xe9\x9b\xab\x20\xe9\x9b\xa8\xe3\x81\xae\xe9\x9f\xb3",
		"\x90\xe1\x82\xcc\x8e\xb4\x20\x89\x4a\x82\xcc\x89\xb9",
		nullptr,
	},
	{
		"\xe9\x9b\xaa\xe3\x81\xae\xe9\x9b\xab",
		"\x90\xe1\x82\xcc\x8e\xb4",
		nullptr,
	},
	{
		"\xe9\x9b\xa8\xe3\x81\xae\xe9\x9f\xb3",
		"\x89\x4a\x82\xcc\x89\xb9",
		"\xe9\xeb\xaa\xce\xeb\xe5",
	},
	{
		"\xe5\xa4\xa9\xe6\xb8\xb8\x20\x66\x65\x61\x74\x2e\xe4\xb8\x9c\xe4\xba\xac\xe5\xa1\x94\xe5\xad\x90",
		nullptr,
		nullptr,
	},
	{
		"\xe9\x9b\xaa\xe3\x81\xae\xe9\x9b\xab\x20\xe9\x9b\xa8\xe3\x81\xae\xe9\x9f\xb3\x2e\x6d\x70\x33",
		"\x90\xe1\x82\xcc\x8e\xb4\x20\x89\x4a\x82\xcc\x89\xb9\x2e\x6d\x70\x33",
		nullptr,
	},
	{
		// Chart: 919220b0-977c-11ea-aed1-dd945ad1734d
		"\xe3\x83\x8e\xe3\x83\xbc\xe3\x83\x9d\xe3\x82\xa4\xe3\x83\x83\xef\xbc\x81",
		"\x83\x6d\x81\x5b\x83\x7c\x83\x43\x83\x62\x81\x49",
		nullptr,
	},
	{
		"\xe3\x83\x8f\xe3\x83\xad\xe3\x83\xbc\xe3\x80\x81\xe3\x83\x8f\xe3\x83\x83\xe3\x83\x94\xe3\x83\xbc\xe3\x83\xaf\xe3\x83\xbc\xe3\x83\xab\xe3\x83\x89\xef\xbc\x81",
		"\x83\x6e\x83\x8d\x81\x5b\x81\x41\x83\x6e\x83\x62\x83\x73\x81\x5b\x83\x8f\x81\x5b\x83\x8b\x83\x68\x81\x49",
		nullptr,
	},
	{
		"\xe2\x97\x88\x56\x54\x2e\x43\x6f\x4e\x75\x54\xe2\x82\x82\x20\x28\x45\x64\x69\x74\x65\x64\x20\x62\x79\x20\x54\x6f\x73\x68\x69\x79\x75\x6b\x69\x29",
		nullptr,
		"\xa2\xc2\x56\x54\x2e\x43\x6f\x4e\x75\x54\xa9\xfc\x20\x28\x45\x64\x69\x74\x65\x64\x20\x62\x79\x20\x54\x6f\x73\x68\x69\x79\x75\x6b\x69\x29",
	},
	{
		// Chart: 5d04f570-4975-11ea-9499-471063bac263
		"\xe3\x83\x80\xe3\x83\xb3\xe3\x82\xac\xe3\x83\xb3\xe3\x83\x8e\xe3\x83\xbc\xe3\x83\x84",
		"\x83_\x83\x93\x83K\x83\x93\x83m\x81[\x83\x63",
		nullptr,
	},
	{
		// What a naughty directory name
		"\xef\xbd\xa5\xef\xbe\x80\xef\xbd\xa5\xee\x8a\x98\xef\xbd\xac\xef\xbd\xa5\xee\x8a\x98\xef\xbe\x8e\xef\xbd\xa9`\xef\xbd\xa5\xef\xbe\x84/",
		"\xa5\xc0\xa5\xf3\xa5\xac\xa5\xf3\xa5\xce\xa9\x60\xa5\xc4\x2f",
		nullptr,
	},
	{
		// Chart: cadfef50-f52e-11e9-82bf-997489e7b8aa
		"parallel\xe2\x98\x86prism",
		"parallel\x81\x99prism",
		"parallel\xa1\xd9prism",
	},

	/* Chart Examples from Others (#314) */
	{
		// Chart: Toumeikan earial
		"\xe9\x80\x8f\xe6\x98\x8e\xe6\x84\x9f\xe3\x82\xa8\xe3\x82\xa2\xe3\x83\xaa\xe3\x82\xa2\xe3\x83\xab",
		"\x93\xa7\x96\xbe\x8a\xb4\x83\x47\x83\x41\x83\x8a\x83\x41\x83\x8b",
		"\xf7\xe2\xd9\xa5\xca\xef\xab\xa8\xab\xa2\xab\xea\xab\xa2\xab\xeb",
	},
	{
		"\xe3\x81\x9f\xe3\x81\x91\xe3\x81\x99\xe3\x81\xb4\xe3\x81\x8a\xe3\x82\x93",
		"\x82\xbd\x82\xaf\x82\xb7\x82\xd2\x82\xa8\x82\xf1",
		"\xaa\xbf\xaa\xb1\xaa\xb9\xaa\xd4\xaa\xaa\xaa\xf3",
	},
	{
		// Chart: ww
		"\x47\x61\x74\x69\x61\x20\x76\x73\x20\xe3\x81\xbf\xe3\x81\x9a\xe3\x81\x84\xe3\x82\x8d\xe3\x81\x8a\xe3\x81\x8a\xe3\x81\x8b\xe3\x81\xbf",
		"\x47\x61\x74\x69\x61\x20\x76\x73\x20\x82\xdd\x82\xb8\x82\xa2\x82\xeb\x82\xa8\x82\xa8\x82\xa9\x82\xdd",
		"\x47\x61\x74\x69\x61\x20\x76\x73\x20\xaa\xdf\xaa\xba\xaa\xa4\xaa\xed\xaa\xaa\xaa\xaa\xaa\xab\xaa\xdf",
	},
};

#pragma endregion

Test("StringEncodingDetector.UTF8")
{
	for (auto& testCase : TEST_CASES)
	{
		TestEnsure(!StringEncodingConverter::NeedsConversion(StringEncodingDetector::Detect(testCase.utf8)));
	}
}

Test("StringEncodingDetector.CP932")
{
	for (auto& testCase : TEST_CASES)
	{
		if(testCase.cp932)
			TestEnsure(StringEncodingDetector::Detect(testCase.cp932) == StringEncoding::CP932);
	}
}

/* Not enabled by default
Test("StringEncodingDetector.CP949")
{
	for (auto& testCase : TEST_CASES)
	{
		if (testCase.cp949)
			TestEnsure(StringEncodingDetector::Detect(testCase.cp949) == StringEncoding::CP949);
	}
}
*/

Test("StringEncodingConverter.CP932")
{
	for (auto& testCase : TEST_CASES)
	{
		if (testCase.utf8 && testCase.cp932)
		{
			TestEnsure(StringEncodingConverter::ToUTF8(StringEncoding::CP932, testCase.cp932) == testCase.utf8);
		}
	}
}

Test("StringEncodingConverter.CP949")
{
	for (auto& testCase : TEST_CASES)
	{
		if (testCase.utf8 && testCase.cp949)
		{
			TestEnsure(StringEncodingConverter::ToUTF8(StringEncoding::CP949, testCase.cp949) == testCase.utf8);
		}
	}
}