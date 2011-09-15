#include "FitsObject.h"
#include <UnitTest++/UnitTest++.h>

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
}

int main(int argc, const char *argv[])
{
    
    return UnitTest::RunAllTests();
}
