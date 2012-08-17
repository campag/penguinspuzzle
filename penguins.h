/*
 Copyright (c) 2012 Peter de Rivaz

 WebGL version at http://penguinspuzzle.appspot.com

 Constants and structures used to define the game logic
*/

/* Different allowed values for the object type */
typedef enum {PENG=0,
	TREE=1,
	CHEST=2,
	NONE=3,  
	FRAGMENT=4,
	FISHPAIL=5,
	ROBOT=6,
	OGUN=7,
	BULLET=8,
	BOMB=9,
	DETONATOR=10,
	FIRE=11,
	SPOTLIGHT=12,
	WSNOWBALL=13,
	ROCKET=14,
	EXPLOSION=15,
	BARREL=16,
	CAMERA=17,
	SOUTHPOLE=18,
	SMHAT=19,
	OLASER=20,
	OMIRROR=21,
	OSHIELD=22,
	OROCKET=23,
	OSHIELDBLOCK=24,
	BABYPENG=25,
	OLAST=26} OBJECT_T;

/* Different allowed values for the object state */
enum { BOPPING=0,WALKING=1,STILL=2,FEEDING=3,CONTROLLED=4,FED=5,
	   PUZZLER=6,FFRAGMENT=7,FSMOKE=8,FFLASH=9,FEXPLOSION=10,FDEBRIS=11,FLASER=12};

#define MAXBACKUPS 64
#define MAXPENGS 100
#define MAXSQUARES (64*64)
	   
/* Different block types */
typedef enum { BICE=0,
	    BCRACKED=1,
	    BSEA=2,
	    BSNOW=3,
	    BEXIT=4,
	    BDOOR=5,
	    BFISHINGROD=6,
	    BSKIS=7,
	    BTILE=8,
	    BPOLE=9,
	    BBUTTON=10,
	    BFRAGILE=11} BLOCKTYPE_T;
		
typedef struct penguin_s
{
	struct penguin_s *contents;
	struct penguin_s *standingon;
	int type;
	int state;
	int thetaf;
	int square;
	int bounce;
	int numfish;
	int size;
	int speed;
	int steps;
	float vturn;
	float x;
	float y;
	float d;
	float dx,dy,vx,vy;
	float potential;
} PENGUIN_T;

typedef struct square_s
{
	BLOCKTYPE_T block; 
	PENGUIN_T *contents;
	float h;
	float dx;
	float dy;
} SQUARE_T;

typedef struct backup_s
{
	int numpengs;
	PENGUIN_T P[MAXPENGS];
	SQUARE_T L[MAXSQUARES];
} BACKUP_T;
		

typedef struct level_s
{
	int t;
	int mode;
	int delay;
	int grid;
    float sz;
	int levnum;
	int w,h;
	int numpengs;
	PENGUIN_T P[MAXPENGS];
	SQUARE_T *L;
	int numbackups;
	int backup;
	BACKUP_T snapshots[MAXBACKUPS];
	BUFFER_T *buf;
	VIEW_T *view;
} LEVEL_T;

extern LEVEL_T *level_new(int t);
extern void level_make_model(LEVEL_T *l);
extern void level_draw_tiles(LEVEL_T *l, SHADER_T *s);
extern void level_draw_objects(LEVEL_T *l, SHADER_T *s, int transparent);
extern void level_draw_fragments(LEVEL_T *l, SHADER_T *s, MODEL_T *expl);
extern void level_load(LEVEL_T *l);
extern void level_update(LEVEL_T *l);
extern void level_update_view(LEVEL_T *l);

	   