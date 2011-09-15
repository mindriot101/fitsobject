#include "FitsObject.h"
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include <stdexcept>

using namespace std;

struct DefaultFixture
{
    DefaultFixture()
    {
        f = new Fits("../test.fits");
    }

    ~DefaultFixture()
    {
        delete f;
    }

    Fits *f;
};

/* Check for a bad filename */
TEST(BadFilename)
{
    CHECK_THROW(Fits test("badfilename"), runtime_error);
}

TEST_FIXTURE(DefaultFixture, BadMoveCheck)
{
    CHECK_THROW(f->moveHDU(-100), runtime_error);

}

TEST_FIXTURE(DefaultFixture, PastFileMoveCheck)
{
    CHECK_THROW(f->moveHDU(100), runtime_error);

}

TEST_FIXTURE(DefaultFixture, BadHDUName)
{
    CHECK_THROW(f->moveHDU("BADHDUNAME"), runtime_error);
}

int main(int argc, const char *argv[])
{
    return UnitTest::RunAllTests();
}
