#include <fstream>
#include <iostream>
#include <iomanip>
#include "..\\catch_amalgamated.hpp"
#pragma once

using namespace std;

/* find max value function          */
/* numValue: number of data values  */
/* ptr: contains memory address     */
float* findMaximum(int numValue, float* ptr);
/* find min value function          */
/* numValue: number of data values  */
/* ptr: contains memory address     */
float* findMinimum(int numValue, float* ptr);

int main(int argc, char** argv) 
{
    fstream fin;        /* file input */
    ofstream fout;      /* file output */
    float* ptr;         /* contains memory address */
    int numValues;      /* size of data */
    int actualValue;    /* true number of values */
    float place;        /* place holder */
    int i;              /* loop variable */

    /* check command line arguments */
    if (argc != 3)
    {
        cout << "Usage: m0020.exe inputfile outputfile" << endl;
        return 0;
    }

    fin.open(argv[1]); /* open input file */

    if (!fin.is_open())
    {
        cout << "Unable to open input file: " << argv[1] << endl;
        return 0;
    }

    fout.open(argv[2]); /* open output file */

    if (!fout.is_open())
    {
        cout << "Unable to open output file: " << argv[2] << endl;
        return 0;
    }

    /* reading input file */
    if (fin >> numValues) 
    {
        ptr = new (nothrow) float[numValues]; /* allocate memory */
        
        if (ptr == nullptr) 
        {
            cout << "Unable to allocate memory" << endl;
            return 0;
        }

        actualValue = 0;
        while (fin >> place && actualValue <= numValues - 1)
        {
            ptr[actualValue] = place;
            actualValue++;
        }

        /* writing output file */
        fout << actualValue << endl; /* first line, number of data values */
        fout << fixed << setprecision(3) << *findMinimum(actualValue, ptr) << " - " << *findMaximum(actualValue, ptr) << endl; /* min - max */

        for (i = 0; i < actualValue; ++i)
        {
            fout << setw(15) << ptr[i]; /* write values */
            if ((i + 1) % 5 == 0 && i > 0) /* endl after 5 data values */
            {
                fout << endl;
            }
        }
        if (i % 5 != 0) /* accounting endl for last line */
        {
            fout << endl;
        }

        delete[] ptr; /* deallocate ptr */
    }

    fin.close();
    fout.close();
    
    return 0;
}

float* findMaximum(int numValue, float* ptr)
{
    int place = 0;  /* place holder to step through data */
    int i;          /* loop variable */
    float* maximum; /* maximum value */

    /* steps through data to find max value */
    for (i = 1; i < numValue; ++i)
    {
        if (ptr[place] < ptr[i])
        {
            place = i;
        }
    }

    maximum = ptr + place;

    return maximum;
}

float* findMinimum(int numValue, float* ptr)
{
    int place = 0;  /* placeholder to step through data */
    int i;          /* loop variable */
    float* minimum; /* minimum value */

    /* steps through data to find min value */
    for (i = 1; i < numValue; ++i)
    {
        if (ptr[place] > ptr[i])
        {
            place = i;
        }
    }

    minimum = ptr + place;

    return minimum;
}