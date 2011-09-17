#ifndef FITSOBJECT_H

#define FITSOBJECT_H

#include <vector>
#include <string>
#include <exception>
#include <fitsio.h>


class Fits
{
    public:
    Fits(const std::string &filename);
    virtual ~Fits();
    void check();
    void moveHDU(const std::string &hduname);
    void moveHDU(int hdunum);
    fitsfile **fptr();
    int &status();
    static void check(int status);
    const std::string hduname();

    long nrows();
    int columnNumber(const std::string &colname);
    std::vector<std::string> stringColumn(const std::string &columnname);


    protected:
    fitsfile *m_fptr;
    int m_status;
    std::string m_filename;
    void checkForTable();


    /* Default constructor - does nothing */
    Fits();
};


class NewFits : public Fits
{
    public:
    NewFits(const std::string &filename);
};

class FitsException : public std::exception
{
    char msg[FLEN_STATUS];
    public:
    FitsException(const int status)
    {
        fits_get_errstatus(status, msg);
    }
    const char *what() const throw()
    {
        return msg;
    }

};


#endif /* end of include guard: FITSOBJECT_H */
