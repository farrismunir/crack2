#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN=20;        // Maximum any password will be
const int HASH_LEN=33;        // Length of MD5 hash strings

// Given a hash and a plaintext guess, return 1 if
// the hash of the guess matches the given hash.
// That is, return 1 if the guess is correct.
int tryguess(char *hash, char *guess)
{
    // Hash the guess using MD5
    char *h = md5(guess, strlen(guess));
    char *c = malloc(strlen(h));
    // Compare the two hashes
    if (h != hash)
    {
    return 0;
    }
    else
    return 1;
    // Free any malloc'd memory
    free(c);
}
// Read in the dictionary file and return the array of strings
// and store the length of the array in size.
// This function is responsible for opening the dictionary file,
// reading from it, building the data structure, and closing the
// file.
char **read_dictionary(char *filename, int *size)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Can't open %s for reading\n", filename);
        exit(1);
    }
    *size = 0;
    char line [40];
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '\n') size++;
    }
    // Reading in the file
    while(fgets(line, 40, f) != NULL)
    {
        // Return pointer to array of strings
        char *l = malloc(line);
        return l;
        // Store length of the array in size
        char *s = malloc(strlen(line));
        free(s);
    }
    // Close the file
    fclose(f);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Read the dictionary file into an array of strings.
    char hash[40];
    char word[40];
    int dlen;
    char **dict = read_dictionary("password.txt", &dlen);
    // Open the hash file for reading.
    FILE *h = fopen("hashes.txt", "r");
    if (!h)
    {
        printf("Can't open hashes.txt for reading\n");
        exit(1);
    }
    while (fgets(hash, 40, h) != NULL)
    {
        hash[strlen(hash)-1] = '\0';
        
    }
    
    while(fgets(word, 40, dict) != NULL)
    {
        char *wordhash = md5(word, strlen(word));
        word[strlen(word)-1] = '\0';
        if (strcmp(wordhash, hash) == 0)
        {
        printf("%s %s\n", hash, word);
        }
    }
    fclose(h);
    // For each hash, try every entry in the dictionary.
    // Print the matching dictionary entry.
    // Need two nested loops.
}
