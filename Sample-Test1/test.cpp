#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../Project_DeviceDriver/DeviceDriver.cpp"


using namespace std;
using namespace testing;
class MockFlashMemoryDevice:public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), ());
	MOCK_METHOD(void, write, (long address, unsigned char data), ());
};

TEST(TestCaseName, TestName_Read5) {
	MockFlashMemoryDevice FlashMemoryDevice{};

	EXPECT_CALL(FlashMemoryDevice, read(0x40000000)).
	Times(5);
	DeviceDriver driver(&FlashMemoryDevice);
	driver.read(0x40000000);
}

TEST(TestCaseName, TestName_Exception) {
	MockFlashMemoryDevice FlashMemoryDevice{};


	EXPECT_CALL(FlashMemoryDevice, read(0x40000000))
		.WillOnce(Return(5))
		.WillOnce(Return(5))
		.WillOnce(Return(5))
		.WillOnce(Return(5))
		.WillOnce(Return(6));

	DeviceDriver driver(&FlashMemoryDevice);
	EXPECT_THROW(driver.read(0x40000000), std::exception);
}