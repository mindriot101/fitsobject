#include "FitsObject.h"
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



int main(int argc, const char *argv[])
{
    
    return UnitTest::RunAllTests();
}
