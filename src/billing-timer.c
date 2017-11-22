#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

typedef struct {
	int time_diff;
	int hours;
	int minutes;
	int seconds;
	int paused;
} billing_time;

void render_screen( billing_time * et, int * running );

int main()
{
	time_t start_time, current_time, pause_time;
	float pause_time_diff;
	float precise_time_difference;

	//Setup the billing timer struct
	billing_time timer;
	timer.paused = 0;

	//Setup status
	int running = 0;

	//Setup ncurses to read key input
	initscr();
	noecho();
	curs_set(0);
	timeout(50);
	printf("Starting billing timer...\n\n");
	running = 1;

	//Set start time.
	time(&start_time);

	while (1) 
	{
		//Read input for ncurses non-blocking input
		int c = getch();

		//Check for pause
		if ( c == 112 && running == 1 ) {
			time(&pause_time);
			running = 0;
		} else if ( c == 114 && running == 0 ) {
			//Check for resume
			timer.paused = timer.paused + pause_time_diff;
			pause_time_diff = 0;
			running = 1;
		} else if ( c == 113 ) {
			endwin();
			return 0;
		}

		//Always fetch the current time.
		time(&current_time);

		//If the timer is running
		if ( running == 1 ) {
			precise_time_difference = difftime(current_time, start_time);

			//Ensure we subtract paused time
			timer.time_diff = ( (int) precise_time_difference - (int) timer.paused );
		} else {
			//If the timer has been paused
			pause_time_diff = difftime(current_time, pause_time);
		}

		erase();
		render_screen( &timer, &running );

		//Sleep for 100ms
		usleep(10000);

	}

	endwin();
	return 0;
}

void render_screen( billing_time * et, int * running )
{
	char plural[10];
	et->hours = (et->time_diff / 3600);
	et->minutes = (et->time_diff % 3600) / 60;
	et->seconds = (et->time_diff % 60 ) % 60;

	printf("\rRunning for: ");
	if ( et->hours > 0 ) {
		strcpy(plural, ( et->hours > 1 ? "hours" : "hour" )); 	
		printf("%d %s, ", et->hours, plural);
	}
	if ( et->minutes > 0 ) {
		strcpy(plural, ( et->minutes > 1 ? "minutes" : "minute" )); 	
		printf("%d %s, ", et->minutes, plural);
	}
	strcpy(plural, ( et->seconds > 1 ? "seconds" : "second" )); 	
	printf("%d %s", et->seconds, plural);

	//Ensure we have nulled out the line
	if ( *running == 1 ) {
		printf(" - [P]ause    [Q]uit   ");
	} else {
		printf(" - [R]esume    [Q]uit   ");
	}

	fflush(stdout);
}
