/**
 * @file Main.c
 * @author HERVE NGUYEN & GABRIEL RADONIAINA
 * @brief Main "module", entry door for the program. Deals with arguments and launches the game or do other behaviors accordingly.
 * @version 0.1
 * @date 2023-01-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/Main.h"

void printHelp(){
    printf("You can either launch the game with the `-l`/`--leaderboard` option to see the leaderboard only or without any options to play the game\n\n");
    printf("To play the game here are the controls :\n");
    printf("- Press and maintain Z,Q,S,D to respectively move UP,DOWN,LEFT,RIGHT (you can also use the corresponding arrow keys)\n");
    printf("- Press and maintant SHIFT to use your mana and have a faster top speed and acceleration\n");
    printf("- Press and maintant SPACE to use your mana and hide from the golems by being invisible\n");
    printf("You need to collect all (magenta) relics in the map while not being detected by patroling golems\n");
    printf("Your performance depends on how fast you have achieved the objectif and how much mana you have used\n");
}

int main(int argc, char * argv[]){

    int opt;
    char optLead[] = "--leaderboard";
    char optHelp[] = "--help";
    int skip;

    skip = 0;

  	while (1) {
      	static struct option long_options[] =
        {
          {"leaderboard",    no_argument,     0, 'l'},
          {"help",    no_argument,     0, 'h'},
          {0, 0, 0, 0}
        };
      
      	int option_index = 0;

      	opt = getopt_long (argc, argv, "lh",
                       	   long_options, &option_index);
        
      	if (opt == -1){
            break;
        }
        
		switch (opt) {
			case 'l':
                {
				skip = 1;
                printf("pekora\n");
				break;
                }
			case 'h':
                {
                printHelp();
                return 0;
                }
			case '?':
                printf("to show help, run the program with the option `-h or `--help`\n");
				return 2;
		}
    }

    for(; optind < argc; optind++){
        if (!strcmp(argv[optind], optLead)){
            skip = 1;
            continue;
        }
        if (!strcmp(argv[optind], optHelp)){
            {
            printHelp();
            return 0;
            }
        }
        else{
            printf("%s: unrecognized argument `%s`\n", argv[0], argv[optind]);
            printf("to show help, run the program with the option `-h or `--help`\n");
            return 2;
        }
    }
    game(skip);
    return 0;
}