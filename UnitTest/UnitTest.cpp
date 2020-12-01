#include "pch.h"
#include "CppUnitTest.h"
#include "../Program/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(met_get_sidlovi_tochki)
		{
			const int size[2] = { 2, 2 };
			int** matrix = new int* [] {
				new int[] {0, 0},
				new int[] {3, 2},
			}, ** out_tochki = nullptr, size_2[2] = {0, 2};
			get_sidlovi_tochki(matrix, size, out_tochki, size_2);
			Assert::AreEqual(size_2[0], 1);
		}
	};
}
