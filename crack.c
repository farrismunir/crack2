#include <stdio.h>
#include <stdlib.h>
#include "md5.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

const int PASS_LEN=20;        // Maximum any password will be
const int HASH_LEN=33;        // Length of MD5 hash strings

int file_length(char *filename)
{
    struct stat info;
    if (stat(filename, &info) == -1) 
    return -1;
    else 
    return info.st_size;
}

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    // Hash the guess using MD5
    char *hashguess = md5(guess, strlen(guess));
    // Compare the two hashes
    if (strcmp(hash, hashguess) == 0)
    {
    return 1;
    }
    else
    {
    return 0;
    }
    // Free any malloc'd memory
    free(hashguess);
}

// Read in the dictionary file and return the array of strings
// and store the length of the array in size.
// This function is responsible for opening the dictionary file,
// reading from it, building the data structure, and closing the
// file.
char **read_dictionary(char *filename, int *size)
{
    *size = file_length(filename);
    char *p = malloc(*size);
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        printf("Can't open %s for reading\n", filename);
        exit(1);
    }
    fread(p, 1, *size, f);
    fclose(f);
    int numpass = 0;
    for (int i = 0; i < *size; i++)
    {
        if (p[i] == '\n')
        {
            numpass++;
            p[i] = '\0';
        }
    }
    char **pws = malloc(numpass * sizeof(char *));
    pws[0] = p;
    int j = 1;
    for (int i = 0; i < *size-1; i++)
    {
        
        if (p[i] == '\0')
        {
            pws[j] = &p[i+1];
            j++;
        }
    } 
    *size = numpass;
    return pws;
    free(pws);
    free(p);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }
    char hash[33];
    int dlen; 
    char **dict = read_dictionary(argv[2], &dlen);
    FILE *h = fopen(argv[1], "r");
    if (!h)
    {
        printf("Can't open %s for reading\n", argv[1]);
        exit(1);
    }
    while (fgets(hash, 33, h) != NULL)
    {
        for (int i = 0; i < dlen; i++)
        {
            if (tryguess(hash, dict[i]) == 1)
            {
                printf("%s %s\n", hash, dict[i]);
            }
        }
        
    }
    fclose(h);
}
// Read the dictionary file into an array of strings.
// Open the hash file for reading.
// For each hash, try every entry in the dictionary.
// Print the matching dictionary entry.
// Need two nested loops.

