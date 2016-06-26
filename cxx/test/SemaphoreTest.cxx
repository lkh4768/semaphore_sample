#include <limits.h>
#include <stdexcept>
#include "gtest/gtest.h"
#include "../src/Semaphore.hxx"

#include <cstdlib>

class SemaphoreTest : public ::testing::Test
{
	public:
		static Semaphore semaphore;
	protected:
		static void SetUpTestCase() {}
		static void TearDownTestCase(){}
		virtual void SetUp(){}
		virtual void TearDown(){}
};

Semaphore SemaphoreTest::semaphore(0x200, 0666);

TEST_F(SemaphoreTest, init_test)
{
	ASSERT_GT(semaphore.get_id(), -1); 
};
