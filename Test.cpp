#include "FitsObject.h"
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include <stdexcept>

using namespace std;

struct DefaultFixture
{
    DefaultFixture()
    {
        f = new Fits("test.fits");
    }

    ~DefaultFixture()
    {
        delete f;
    }

    Fits *f;
};

struct TableFixture : public DefaultFixture
{
    TableFixture() : 
        DefaultFixture()
    {
        f->moveHDU(2);
    }
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

TEST_FIXTURE(TableFixture, HDUName)
{
    CHECK_EQUAL("TABLE", f->hduname());
}

TEST_FIXTURE(DefaultFixture, BadHDURows)
{
    f->moveHDU(1);
    CHECK_THROW(f->nrows(), runtime_error);
}

TEST_FIXTURE(TableFixture, NRowsTest)
{
    CHECK_EQUAL(3, f->nrows());
}

TEST_FIXTURE(TableFixture, ColnumTest)
{
    CHECK_EQUAL(1, f->columnNumber("target"));
    CHECK_EQUAL(2, f->columnNumber("V_mag"));
}

TEST_FIXTURE(TableFixture, StringColumnRetrievalTest)
{
    vector<string> data = f->columnData<string>("target");
    CHECK_EQUAL("NGC1001", data[0]);
    CHECK_EQUAL("NGC1002", data[1]);
    CHECK_EQUAL("NGC1003", data[2]);
}

TEST_FIXTURE(TableFixture, DoubleColumnRetrievalTest)
{
    vector<double> data = f->columnData<double>("V_mag");
    CHECK_CLOSE(11.1, data[0], 0.05);
    CHECK_CLOSE(12.3, data[1], 0.05);
    CHECK_CLOSE(15.2, data[2], 0.05);
}

int main(int argc, const char *argv[])
{
    return UnitTest::RunAllTests();
}
