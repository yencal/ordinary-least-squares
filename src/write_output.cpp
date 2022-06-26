#include <write_output.h>
#include <stdio.h>

void write_estOLS_to_file(int m, real_t *OLSest)
{
    // open file to write OLSest
    FILE *outputFile;
    outputFile = fopen ("OLSest.csv" , "w");

    // write column header
    fprintf(outputFile, "%s\n", "OLSest");

    // write OLSest data
    for (int i = 0; i < m; i++)
    {
        fprintf(outputFile, "%12.6E\n", OLSest[i]);
    }

    // close file
    fclose (outputFile);
}