#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

GLuint _textureId; //The id of the textur
GLuint _textureId1;
GLuint _textureId2;
GLuint _textureMoon;
GLuint _textureEarth;
GLuint _textureCannabis;
GLuint _textureLsd;
GLuint _texturePorco;
GLuint _textureMoto;
GLuint texture[19];

GLUquadric *moon;
GLUquadric *cannabis;
GLUquadric *earth;
GLUquadric *lsdSelo;

GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;

struct objetos{
	int type;
	bool flag;
	int rotate;
	float x,y,z;
};

#define lsd 0
#define bob 1
#define barreiro 2
#define like 3

#define glicose 4
#define regime 5
#define sedativo 6
#define larica 7
#define jesus 8

#define PNG_SIG_BYTES 8

float eyex = 0.0, eyey = 0.0, eyez = 2.0, upx = 0.0, upy = 1.0, upz = 0.0, rotateJ = 0.0, posPorcoX = 25.0, posPorcoY = 6.0, JoaoX = 0.0, rotate, score = 0;
int porcoFlag = 0, MoonFlag = 0, BarreiroFlag = 0, LikeFlag = 0, level = 1, maxLevel = 10, LsdFlag = 0, BobFlag = 0, start = 0, help = 0, playing = 1, pauseGame = 0, winner = 0, numObjects;
objetos *teste;
GLUquadric* qobj;