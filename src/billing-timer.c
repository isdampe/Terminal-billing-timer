#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void render_screen();

typedef struct {
	int time_diff;
	int hours;
	int minutes;
	int seconds;
} billing_time;

int main()
{
	time_t start_time, current_time;
	double precise_time_difference;
	billing_time timer;

	printf("Starting billing timer...\n");
	time(&start_time);

	while (1) 
	{
		sleep(1);
		time(&current_time);
		precise_time_difference = difftime(current_time, start_time);
		timer.time_diff = (int) precise_time_difference;
		render_screen( &timer );
	}

	return 0;
}

void render_screen( billing_time * et )
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
	printf("              ");

	fflush(stdout);
}
