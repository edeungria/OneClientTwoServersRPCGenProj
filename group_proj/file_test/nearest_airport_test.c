#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define pi 3.14159265358979323846

const static char* file_mode = "r";
const static char* place_file = "places2k.txt";
const static char* airport_file = "airport-locations.txt"; 

const int TOTAL_NUMBER_OF_AIRPORTS = 1122;
const int TOTAL_NUMBER_OF_PLACES = 25375;
const int NEAREST_NUMBER_OF_AIRPORTS = 5;

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*:: This function converts decimal degrees to radians :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg) {
 return (deg * pi / 180);
}
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*:: This function converts radians to decimal degrees :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad) {
 return (rad * 180 / pi);
}

double distance(double lat1, double lon1, double lat2, double lon2)
{
 double theta, dist;
 theta = lon1 - lon2;
 dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) *
 cos(deg2rad(lat2)) * cos(deg2rad(theta));
 dist = acos(dist);
 dist = rad2deg(dist);
 dist = dist * 60 * 1.1515;
 return (dist);
}

struct Place
{
  char state[3]; // state[2] = '\0'
  char name[63];
  float latitude;
  float longitude;
};

struct Airport
{
  char code[4]; // state[3] = '\0'
  char name[40];
  char state[3]; // state[2] = '\0'
  float latitude;
  float longitude;
};

typedef struct Place Place;
typedef struct Airport Airport;

Place* place_array;
Airport* airport_array;

void printPlace(const Place* place)
{
  printf("\nState: %s\n", place->state);
  printf("Name:  %s\n", place->name);
  printf("Lat:   %f\n", place->latitude);
  printf("Long:  %f\n\n", place->longitude);
}

void printAirport(const Airport* airport)
{
  printf("Code:   %s\n", airport->code);
  printf("Name:   %s\n", airport->name);
  printf("State:  %s\n", airport->state);
  printf("Lat:    %f\n", airport->latitude);
  printf("Long:   %f\n", airport->longitude);
}

void parsePlaceLine(const char line[200], Place* place)
{
  memcpy(place->state, &line[0], sizeof(char) * 2);
  place->state[2] = '\0';
  memcpy(place->name, &line[9], sizeof(char) * 63);
  char lat[11], lon[12];
  memcpy(lat, &line[143], sizeof(char) * 11);
  memcpy(lon, &line[153], sizeof(char) * 12);
  lat[10] = '\0';
  lon[11] = '\0';
  place->latitude = (float)atof(lat);
  place->longitude = (float)atof(lon);
}

void readPlaces()
{
  FILE* places;
  place_array = malloc(TOTAL_NUMBER_OF_PLACES * sizeof(Place));
  int place_count = 0;
  
  places = fopen(place_file, file_mode);
  if(places == NULL)
  {
	printf("Opening places failed\n");
	return;
  }
  printf("Opening places successful\n");
  printf("Reading file now...\n");
  char line[200];
  while(place_count < TOTAL_NUMBER_OF_PLACES && fgets(line, 200, places))
  {
	parsePlaceLine(line, &place_array[place_count]);
	place_count++;

	memset(line, 0, sizeof(line));
  }
  //free(place_array);
  printf("Done with places\n");
}

void getNearestAirports(float latitude, float longitude)
{	
	double smallest[5] = {999999,999999,999999,999999,999999};
	Airport* closest_airports = malloc(5 * sizeof(Place));
	int i=0;
	while(i<TOTAL_NUMBER_OF_AIRPORTS)
	{
		double currentDistance = distance((float)latitude, (float)longitude, (float)airport_array[i].latitude, (float)airport_array[i].longitude);
		int pos = NEAREST_NUMBER_OF_AIRPORTS;
		while(currentDistance<smallest[pos-1]&& pos>0)
			pos--;
		
		if(pos!=NEAREST_NUMBER_OF_AIRPORTS)
		{
			int j = 0;	
			for(j = 4; j > pos; j--)
			{
				closest_airports[j]=closest_airports[j-1];
				smallest[j]=smallest[j-1];
			}
			closest_airports[pos] = airport_array[i];
			smallest[pos]=currentDistance;
		}
		i++;
	}
	for(i = 0; i < 5; i++)
		printAirport(&closest_airports[i]);
}

void searchPlaces(char * city, char * state)
{
	int i=0;
	while(i<TOTAL_NUMBER_OF_PLACES)
	{
		if(strncmp(city, place_array[i].name, strlen(city)) == 0)
		{
			if(strncmp(state, place_array[i].state, strlen(state)) == 0)
			{
				getNearestAirports(place_array[i].latitude, place_array[i].longitude);
				return;
			}
		}
		i++;
	}
	printf("Place not found");
}

void parseAirportLine(char line[100], Airport* airport)
{

  char* token = strtok(line, " \t");
  memcpy(airport->code, &token[1], sizeof(char) * 3);
  airport->code[3] = '\0';

  token = strtok(NULL, " \t");
  airport->latitude = (float)atof(token);

  token = strtok(NULL, " \t");
  airport->longitude = (float)atof(token);

  // get name and state
  token = strtok(NULL, "\t");

  // Split name and state
  char* t2 = strtok(token, ",");
  memcpy(airport->name, t2, sizeof(char) * 40);

  t2 = strtok(NULL, ",");
  memcpy(airport->state, t2, sizeof(char) * 2);
  airport->state[3] = '\0';

}

void readAirports()
{
  FILE* airports;
  airport_array = malloc(TOTAL_NUMBER_OF_AIRPORTS * sizeof(Airport));
  Airport* new_array;
  int airport_count = 0;

  airports = fopen(airport_file, file_mode);
  if(airports == NULL)
  {
	printf("Opening airports failed.\n");
	return;
  }
  printf("Opening airports successful.\n");
  printf("Reading file now...\n");
  char line[100];
  fgets(line, 100, airports); // skip the first line of the file
  memset(line, 0, sizeof(line));
  while(airport_count < TOTAL_NUMBER_OF_AIRPORTS && fgets(line, 100, airports))
  {	  
	if(strlen(line) > 1)
	{
	  parseAirportLine(line, &airport_array[airport_count]);	  
	  airport_count++;
	}
	memset(line, 0, sizeof(line));
  }
  free(airport_array);
  printf("Done with airports\n");
}

int main(int argc, char *argv[])
{
  if(argc < 4) {
	exit (1);
  }
  char *host = argv[1];
  char *city = argv[2];
  char *state = argv[3];

  printf(city, state);
	
  readPlaces();
  readAirports();
  searchPlaces(city, state);
  
  return 0;
}