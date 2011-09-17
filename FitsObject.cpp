#include "FitsObject.h"
#include <stdexcept>

using namespace std;

    Fits::Fits(const string &filename)
: m_status(0), m_filename(filename)
{
    fits_open_file(&*this->fptr(), this->m_filename.c_str(), READWRITE, &this->status());
    this->check();
}

Fits::Fits() {}

Fits::~Fits()
{
    fits_close_file(*this->fptr(), &this->status());
    this->check();
}

void Fits::check()
{
    char errbuf[FLEN_ERRMSG];
    while (fits_read_errmsg(errbuf))
    {
        fprintf(stderr, "Fits error (on stack): %s\n", errbuf);
    }

    if (this->status())
    {

        char buf[FLEN_STATUS];


        fits_get_errstatus(this->status(), buf);

         //Have to set the status back to 0 otherwise
         //when the destructor is called and the file is closed
         //then another exception will be thrown 
        this->status() = 0;
        // Ensure the marks are not visible 
        fits_clear_errmsg();
        throw runtime_error(buf);


    }
}

void Fits::moveHDU(const string &hduname)
{
    fits_movnam_hdu(*this->fptr(), ANY_HDU, const_cast<char*>(hduname.c_str()), 0, &this->status());
    this->check();
}

void Fits::moveHDU(int hdunum)
{
    int hdutype;
    fits_movabs_hdu(*this->fptr(), hdunum, &hdutype, &this->status());
    this->check();
}

void Fits::checkForTable()
{
    /* Checks for a table extension */
    int hdutype;
    fits_get_hdu_type(*this->fptr(), &hdutype, &this->status());
    this->check();

    if ((hdutype != ASCII_TBL) && (hdutype != BINARY_TBL))
    {
        throw runtime_error("Non-table hdu found");
    }
}


int Fits::columnNumber(const std::string &colname)
{
    this->checkForTable();

    int colnum;
    fits_get_colnum(*this->fptr(), CASEINSEN, const_cast<char*>(colname.c_str()), &colnum, &this->status());
    this->check();

    return colnum;

}

long Fits::nrows()
{
    // Ensure the current hdu is a (binary) table 
    this->checkForTable();

    int hdutype;
    fits_get_hdu_type(*this->fptr(), &hdutype, &this->status());
    this->check();

    if ((hdutype != ASCII_TBL) && (hdutype != BINARY_TBL))
    {
        throw runtime_error("Non-table hdu found");
    }

    long nrows;
    fits_get_num_rows(*this->fptr(), &nrows, &this->status());
    this->check();

    return nrows;


}

fitsfile **Fits::fptr() { return &this->m_fptr; }
int &Fits::status() { return this->m_status; }

void Fits::check(int status)
{
    if (status)
    {
        char buf[FLEN_STATUS];
        fits_get_errstatus(status, buf);
        throw runtime_error(buf);
    }
}

const string Fits::hduname()
{
    char buf[FLEN_VALUE];
    fits_read_key(*this->fptr(), TSTRING, "EXTNAME", buf, NULL, &this->status());
    this->check();
    return string(buf);
}

NewFits::NewFits(const string &filename)
{
    this->m_filename = filename;
    this->status() = 0;

    fits_create_file(&*this->fptr(), filename.c_str(), &this->status());
    this->check();

    /* Ensure the basic keywords are there */
    long naxes[] = {0, 0};
    fits_create_img(*this->fptr(), BYTE_IMG, 0, naxes, &this->status());
    this->check();
}

