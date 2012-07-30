#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define DEFAULT_CHANNEL_SPACING 25000
#define DEFAULT_RECEIVE_OFFSET 21400000
#define MAXIMUM_CHANNEL_SPACE 10000000

int main(int argc, char const *argv[])
{
	int R,N,O,target_frequency,channel_spacing,receive_offset;
	if(argc<2 || argc>3)
	{	
		printf("usage:\n\trncalc target_frequency_kHz [receive_offset_kHz] [channel_spacing_kHz]\n");
		return -0;
	}

	target_frequency=strtol(argv[1], argv[1]+strlen(argv[1]), 10)*1000;  
	if ((errno == ERANGE && (target_frequency == LONG_MAX || target_frequency == LONG_MIN)) || (errno != 0 && target_frequency == 0))
	{
		perror("Faulty target_frequency");
		exit(EXIT_FAILURE);
	}

	if(argc==3)
	{
		receive_offset=strtol(argv[2], argv[2]+strlen(argv[2]), 10)*1000;  
		if ((errno == ERANGE && (receive_offset == LONG_MAX || receive_offset == LONG_MIN)) || (errno != 0 && receive_offset == 0))
		{
			perror("Faulty receive_offset");
			exit(EXIT_FAILURE);
		}
	}
	else
		receive_offset=DEFAULT_RECEIVE_OFFSET;

	if(argc==4)
	{
		channel_spacing=strtol(argv[3], argv[3]+strlen(argv[3]), 10)*1000;
		if ((errno == ERANGE && (channel_spacing == LONG_MAX || channel_spacing == LONG_MIN)) || (errno != 0 && channel_spacing == 0))
		{
			perror("Faulty channel_spacing");
			exit(EXIT_FAILURE);
		}
	}
	else
		channel_spacing=DEFAULT_CHANNEL_SPACING;

	R = MAXIMUM_CHANNEL_SPACE/channel_spacing;
	if(MAXIMUM_CHANNEL_SPACE%channel_spacing != 0)
	{
		channel_spacing = MAXIMUM_CHANNEL_SPACE/R;
		printf("Channel spacing is rounded to %d\n", channel_spacing);
	}
	else
	{
		printf("Channel spacing is set to %d\n", channel_spacing);
	}

	N = target_frequency/channel_spacing;
	if(target_frequency%channel_spacing != 0)
	{
		target_frequency = N*channel_spacing;
		printf("Target frequency is rounded to %d\n", target_frequency);
	}
	else
	{
		printf("Target frequency is set to %d\n", target_frequency);
	}

	O = receive_offset/channel_spacing;
	if(receive_offset%channel_spacing != 0)
	{
		receive_offset = O*channel_spacing;
		printf("Receive offset is rounded to %d\n", receive_offset);
	}
	else
	{
		printf("Receive offset is set to %d\n", receive_offset);
	}


	printf("N=%d\n", N);
	printf("R=%d\n", R);
	printf("O=%d\n", O);

	return 0;
}
