#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "No output file specified\n");
        return 1;
    }

    if (argc < 3) {
        fprintf(stderr, "No options specified\n");
        return 1;
    }

    FILE *output = fopen(argv[1], "w");
    if (output == NULL) {
        perror("Failed to open output file\n");
        return 1;
    }

    argv += 2;
    argc -= 2;

    int maxlen = 0;
    for (int i = 0; i < argc; i++) {
        size_t len = strlen(argv[i]);
        maxlen = len > maxlen ? len : maxlen;
    }

    char *item = malloc(maxlen + 2);
    if (item == NULL) {
        fprintf(stderr, "Failed to allocate for items\n");
        fclose(output);
        return 1;
    }

    initscr(); // initialize Ncurses
    
    WINDOW *w = newwin(argc + 2, maxlen + 4, 1, 1); // create a new window
    box(w, 0, 0); // sets default borders for the window
    
    // now print all the menu items and highlight the first one
    for(int i = 0; i < argc; i++) {
        if (i == 0) 
            wattron(w, A_STANDOUT); // highlights the first item.
        else
            wattroff(w, A_STANDOUT);

        sprintf(item, "%-*s", maxlen + 1, argv[i]);
        mvwprintw(w, i + 1, 2, "%s", item);
    }
    
    wrefresh(w); // update the terminal screen
    
    noecho(); // disable echoing of characters on the screen
    keypad(w, TRUE); // enable keyboard input for the window.
    curs_set(0); // hide the default screen cursor.
    
    int i = 0;
    int ch = 0;

    // get the input
    while((ch = wgetch(w)) != '\n') { 
        // right pad with spaces to make the items appear with even width.
        sprintf(item, "%-*s", maxlen + 1, argv[i]); 
        mvwprintw(w, i + 1, 2, "%s", item); 
        // use a variable to increment or decrement the value based on the input.
        switch( ch ) {
            case KEY_UP:
                i--;
                i = (i < 0) ? argc - 1 : i;
                break;
            case KEY_DOWN:
                i++;
                i = (i == argc) ? 0 : i;
                break;
        }
        // now highlight the next item in the list.
        wattron(w, A_STANDOUT);
        sprintf(item, "%-*s", maxlen + 1, argv[i]);
        mvwprintw(w, i + 1, 2, "%s", item);
        wattroff(w, A_STANDOUT);
    }
    delwin(w);
    endwin();

    fputs(argv[i], output);
    fclose(output);

    return 0;
}
