const PNAMELEN = 63;
const ANAMELEN = 40;
const STATELEN = 3;
const CODELEN = 4;
const NUMAIRPORTS = 1121;

typedef string placetype<PNAMELEN>;
typedef string airporttype<ANAMELEN>;
typedef string statetype<STATELEN>;
typedef string codetype<CODELEN>;
typedef struct Airport* airportlist;

struct Airport
{
	codetype code;
	airporttype name;
	statetype state;
	float latitude;
	float longitude;
	float distance;
	airportlist next;
};

typedef struct Airport Airport;

union readplaces_ret switch(int err)
{
	case 0:
	     airportlist list;
	case 1:
	     void;
};

struct Place
{
	placetype name;
	statetype state;
	float latitude;
	float longitude;	
};

typedef struct Place Place;

program AIRPORTPROG {
	version AIRPORTS_VERS {
		readplaces_ret READAIRPORT(Place) = 1;
	} = 1;
} = 0x3777777A;
