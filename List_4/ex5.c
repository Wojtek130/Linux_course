
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

#define COLOR 2
#define WORLD 4

#define ESC "\x1b["
#define ESC_CYAN ESC "36m"
#define ESC_RESET ESC "0m"

void help()
{
    printf(
        "Implementation of hwb\n"
        "A program to print 'hello, name'\n"
        "\n"
        "Options:\n"
        "  -c, -capitalize             capitalize name\n"
        "  -color=[never|auto|always]  colour name "
        "  -g text, -greeting=text     replace 'Hello' with the given text\n"
        "  -h, -help                   show the manual\n"
        "  -v, -version                name, version and copyright\n"
        "  -w, -world                  prints an additional row 'Hello, wordl'\n\n");
}

void capitalize(char **names, int number_of_names)
{
    for (int i = 0; i < number_of_names; i++)
    {
        names[i][0] = toupper(names[i][0]);
    }
}

void print_line(char *greeting, char *name, int options)
{
    bool color = ((options & 2) >> 1);

    printf("%s, ", greeting);
    if (color)
        printf(ESC_CYAN);
    printf("%s", name);
    if (color)
        printf(ESC_RESET);
    printf("!\n");
}

void print_hello(char *greeting, char **names, int number_of_names,
                 int options)
{
    if (((options & WORLD) >> 2))
    {
        print_line(greeting, "world", options);
    }

    for (int i = 0; i < number_of_names; i++)
    {
        print_line(greeting, names[i], options);
    }
}

struct option long_options[] = {
    {"capitalize", no_argument, 0, 'c'},
    {"color", required_argument, 0, 0},
    {"greeting", required_argument, 0, 'g'},
    {"help", no_argument, 0, 'h'},
    {"version", no_argument, 0, 'v'},
    {"world", no_argument, 0, 'w'},
    {NULL, 0, 0, 0}};

void color_options(int long_option_index, int *options)
{
    switch (long_option_index)
    {
    case 1:
        if (strcmp(optarg, "always") == 0)
        {
            *options = *options | 2;
        }
        else if (strcmp(optarg, "never") == 0)
        {
            *options = *options & ~2;
        }
        else if (strcmp(optarg, "auto") != 0)
        {
            help();
            exit(EXIT_FAILURE);
        }
        break;

    default:
        help();
        exit(EXIT_FAILURE);
        break;
    }
}

int main(int argc, char **argv)
{
    char *greeting = malloc(sizeof(char) * (strlen("Hello") + 1));
    strcpy(greeting, "Hello");
    int options = 0;

    while (true)
    {
        int short_option;
        int long_option_index = 0;
        short_option = getopt_long(argc, argv, "cg:hvw", long_options, &long_option_index);
        if (short_option == -1)
            break;

        switch (short_option)
        {
        case 0:
            color_options(long_option_index, &options);
            break;
        case 'c':
            options |= 1;
            break;
        case 'g':
            greeting = realloc(greeting, sizeof(char) * (strlen(optarg) + 1));
            strcpy(greeting, optarg);
            break;
        case 'h':
            help();
            exit(EXIT_SUCCESS);
            break;
        case 'v':
            printf("hwb ex5, version 1.0.0, Copyright\n");
            exit(EXIT_SUCCESS);
            break;
        case 'w':
            options |= WORLD;
            break;
        case '?':
        default:
            help();
            exit(EXIT_FAILURE);
            break;
        }
    }
    char **names = argv + optind;
    int number_of_names = argc - optind;
    if ((options & 1))
        capitalize(names, number_of_names);
    print_hello(greeting, names, number_of_names, options);
    free(greeting);
    return 0;
}