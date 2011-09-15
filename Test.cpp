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

int main(int argc, const char *argv[])
{
    
    return UnitTest::RunAllTests();
}
