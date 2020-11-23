#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab7.3(Iter)/Lab7.3(Iter).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest73Iter
{
	TEST_CLASS(UnitTest73Iter)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int i = 2;
			const int j = 3;
			int k;

			int** a = new int* [i];
			for (int p = 0; p < i; p++) {
				a[p] = new int[j];
			}

			a[0][0] = { 0 }; a[1][0] = { 0 }; a[0][1] = { 1 }; a[1][1] = { 1 }; a[0][2] = { 2 }; a[1][2] = { 2 };

			k = MultiplicationResult(a, i, j);
			Assert::AreEqual(k, 0);

			for (int p = 0; p < i; p++) {
				delete[] a[p];
			}
			delete[] a;

		}
	};
}
