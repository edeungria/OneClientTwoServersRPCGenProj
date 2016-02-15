/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "place_airport.h"

extern Place place_array[NUMPLACES];

// case sensitive
Place* searchPlaces(placetype city, statetype state)
{
	int i=0;
	while(i<NUMPLACES)
	{
		if(strncmp(city, place_array[i].name, strlen(city)) == 0)
		{
			if(strncmp(state, place_array[i].state, strlen(state)) == 0)
			{
				return &place_array[i];
			}
		}
		i++;
	}
	return NULL;
}

readplaces_ret *
readplace_1_svc(Place *argp, struct svc_req *rqstp)
{
    airportlist air;
    airportlist* air_list;
	static readplaces_ret  result;
	Place* place_to_search;
	/*
	  Call airport server methods instead of this dummy code
	 */
	place_to_search = searchPlaces(argp->name, argp->state);
	
	if(place_to_search)
	{
		// dummy code
		air_list = &result.readplaces_ret_u.list;

		*air_list = (Airport*) malloc(sizeof(Airport));
		air = *air_list;
		strcpy(air->code, "ABC");
		strcpy(air->name,"Bloop");
		strcpy(air->state,"WA");
		air->latitude = 0.123;
		air->longitude = 0.123;
		air->distance = 0.0;
		air->next = NULL;
	}
	
	result.err = 0;
	return &result;
}
