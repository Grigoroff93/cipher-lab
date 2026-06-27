#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool digit_checker(string s);
void rotate(string s, int key);
char rotate_upper(char a, int key);
char rotate_lower(char a, int key);
void print_intro(void);
void print_menu(void);
void print_help(void);
int get_valid_key(void);
int get_mode(void);
int count_letters(string s);
int count_unchanged(string s);

int main(void)
{
    print_intro();

    while (true)
    {
        print_menu();

        int mode = get_mode();

        if (mode == 4)
        {
            printf("Goodbye!\n");
            return 0;
        }

        if (mode == 3)
        {
            print_help();
        }
        else
        {
            int key = get_valid_key();
            int effective_key = key % 26;

            string text = get_string("Enter text: ");

            int total_characters = strlen(text);
            int letters = count_letters(text);
            int unchanged = count_unchanged(text);

            if (mode == 1)
            {
                rotate(text, effective_key);
                printf("\nEncrypted text: %s\n", text);
            }
            else if (mode == 2)
            {
                int decrypt_key = 26 - effective_key;
                rotate(text, decrypt_key);
                printf("\nDecrypted text: %s\n", text);
            }

            printf("\nSummary:\n");
            printf("Total characters: %i\n", total_characters);
            printf("Letters changed: %i\n", letters);
            printf("Characters left unchanged: %i\n", unchanged);
            printf("Original key: %i\n", key);
            printf("Effective key: %i\n\n", effective_key);
        }
    }
}

void print_intro(void)
{
    printf("\n");
    printf("=====================================\n");
    printf("        SIMPLE CAESAR CIPHER TOOL     \n");
    printf("=====================================\n");
    printf("This is an educational encryption tool.\n");
    printf("It is not real secure encryption.\n");
    printf("It is meant for practicing C basics.\n");
    printf("\n");
}

void print_menu(void)
{
    printf("Choose an option:\n");
    printf("1. Encrypt text\n");
    printf("2. Decrypt text\n");
    printf("3. How it works\n");
    printf("4. Exit\n");
}

void print_help(void)
{
    printf("\n");
    printf("How the Caesar cipher works:\n");
    printf("Each letter is shifted by a number of positions in the alphabet.\n");
    printf("For example, with key 3:\n");
    printf("A becomes D, B becomes E, C becomes F.\n");
    printf("The program keeps spaces, numbers, and punctuation unchanged.\n");
    printf("A key like 29 works the same as key 3, because the alphabet has 26 letters.\n");
    printf("\n");
}

int get_mode(void)
{
    int mode = get_int("Option: ");

    while (mode < 1 || mode > 4)
    {
        printf("Please choose 1, 2, 3, or 4.\n");
        mode = get_int("Option: ");
    }

    return mode;
}

int get_valid_key(void)
{
    string key_text = get_string("Enter key: ");

    while (!digit_checker(key_text))
    {
        printf("Key must contain only numbers.\n");
        key_text = get_string("Enter key: ");
    }

    int key = atoi(key_text);

    return key;
}

bool digit_checker(string s)
{
    int length = strlen(s);

    if (length == 0)
    {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        char c = s[i];

        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;
}

void rotate(string s, int key)
{
    int length = strlen(s);

    for (int i = 0; i < length; i++)
    {
        if (isupper(s[i]))
        {
            s[i] = rotate_upper(s[i], key);
        }
        else if (islower(s[i]))
        {
            s[i] = rotate_lower(s[i], key);
        }
    }
}

char rotate_upper(char a, int key)
{
    return (char)((a - 'A' + key) % 26 + 'A');
}

char rotate_lower(char a, int key)
{
    return (char)((a - 'a' + key) % 26 + 'a');
}

int count_letters(string s)
{
    int letters = 0;
    int length = strlen(s);

    for (int i = 0; i < length; i++)
    {
        if (isalpha(s[i]))
        {
            letters++;
        }
    }

    return letters;
}

int count_unchanged(string s)
{
    int unchanged = 0;
    int length = strlen(s);

    for (int i = 0; i < length; i++)
    {
        if (!isalpha(s[i]))
        {
            unchanged++;
        }
    }

    return unchanged;
}
