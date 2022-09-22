#include "pch.h"
#include "CppUnitTest.h"
#include "../DemoCpp1/MyClass.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			//std::string name = "Hao";
			MyClass mc(11);

			//Assert::AreEqual(name, mc.getName());
			Assert::AreEqual(11, mc.getAge());
		}
	};
}
