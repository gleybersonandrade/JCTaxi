#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>       
#include <inttypes.h>
#include <assert.h>
#include "header.h"
#include "homer.cpp"
#include "png.h"
#include "texture.cpp"

using namespace std;

void inicializarObjetos(){
	int randPos,rotate;
	srand (time(NULL));
	numObjects = level * 10 * 0.2;
	for (int i = 0; i < level*10; i++){
		randPos = rand() % 24;
		if (i < numObjects){
			teste[i].type = rand() % 5 + 4 ;
		} else {
			teste[i].type = rand() % 4;
		}		
		teste[i].x = randPos - 12;
		teste[i].rotate = rand() % 315;
		teste[i].z = -9;
		if ((randPos - 12 > 6) || (randPos - 12 <  -6))
			teste[i].y = 28 ;
		else
			teste[i].y = 29;
	}
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
 			if (!pauseGame) {
	 			if (BobFlag == 0){
					if (JoaoX >= -12)
						JoaoX = JoaoX - 0.3 + LikeFlag * 0.2;
	 			} else {
					if (JoaoX <= 12)
						JoaoX = JoaoX + 0.3 - LikeFlag * 0.2;
	 			}
	 		}
			glutPostRedisplay();
			break;
      	case 'd':
			if (!pauseGame) {
	 			if (BobFlag == 0){
					if (JoaoX <= 12)
						JoaoX = JoaoX + 0.3 - LikeFlag * 0.2;
				} else {
					if (JoaoX >= -12)
						JoaoX = JoaoX - 0.3 + LikeFlag * 0.2;
				}
			}
			glutPostRedisplay();
 			break;
		case 'q':
			if ((JoaoX >= -12) && (!pauseGame))
				JoaoX = JoaoX - 0.1;
			glutPostRedisplay();
			break;		
      	case 'e':
			if ((JoaoX <= 12) && (!pauseGame))
				JoaoX = JoaoX + 0.1;
			glutPostRedisplay();
 			break; 		
 		case 'p':
			if (!pauseGame)
				pauseGame = 1;
			else
				pauseGame = 0;
			glutPostRedisplay();
			break;
 		case 'h':
 			help = 1;
 			glutPostRedisplay();
 			break;
 		case 32:
 			if ((BarreiroFlag && LikeFlag && LsdFlag && BobFlag) || (winner)) {
 				exit(0);
 			}
			start = 1;
			help = 0;
			glutPostRedisplay();
 			break; 		
	}
}

void scoredisplay (int posx, int posy, int posz, int space_char, int scorevar) {
	int j = 0, p = scorevar, k = 0;
	glDisable(GL_LIGHTING);
    glColor3f(1.0,1.0,1.0);
    while(p > 9) {
        k = p % 10;
        glRasterPos3f ((posx-(j*space_char)),posy, posz);    
        glutBitmapCharacter(font_style1,48+k);
        j++;
        p /= 10;
    }
    glRasterPos3f ((posx-(j*space_char)), posy, posz);    
    glutBitmapCharacter(font_style1,48+p);
    glEnable(GL_LIGHTING);
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	moon = gluNewQuadric();
	earth = gluNewQuadric();
	cannabis = gluNewQuadric();

	texture[0] = png_texture("img/moon.png");
	texture[1] = png_texture("img/earth.png");
	texture[2] = png_texture("img/lsd.png");
	texture[3] = png_texture("img/cat.png");
	texture[4] = png_texture("img/bob.png");
	texture[5] = png_texture("img/reggae1.png");
	texture[6] = png_texture("img/shineray.png");
	texture[7] = png_texture("img/barreiro.png");
	texture[8] = png_texture("img/principal1.png");
	texture[9] = png_texture("img/placar.png");
	texture[10] = png_texture("img/Hofmann_Bicycle_Day.png");
	texture[11] = png_texture("img/porco.png");
	texture[12] = png_texture("img/samuel.png");
	texture[13] = png_texture("img/jesus.png");
	texture[14] = png_texture("img/coca.png");
	texture[15] = png_texture("img/gameover.png");
	texture[16] = png_texture("img/fundo.png");
	texture[17] = png_texture("img/vencedor.png");
	texture[18] = png_texture("img/help.png");
	
	_textureMoon = texture[0];
	_textureEarth = texture[1];
	initHomer();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
    gluLookAt(eyex,eyey, eyez, 0.0, 0.0,0.0, upx, upy,upz);
	glMatrixMode(GL_MODELVIEW);
}

void animateVelhoBarreiro() {
	if (upx <= -3) {
		MoonFlag = 1;
	} else if (upx >= 3) {
		MoonFlag = 0;
	}
	if (MoonFlag == 1) {
		upx = upx + 0.5;
	} else {
		upx = upx - 0.5;
	}
	glutPostRedisplay();
}

void animateV(int value) {
    if (BarreiroFlag){
		animateVelhoBarreiro();
	} else {
		if (upx > 0)
			upx = upx - 0.5;
		else if(upx < 0)
			upx = upx + 0.5;
	}
	glutTimerFunc(70, animateV, 1);
	glutPostRedisplay();
}

void callEffects(int obj_id){
	switch (teste[obj_id].type) {
		case barreiro:
			BarreiroFlag = 1;
			break;
		case glicose:
			numObjects--;
			BarreiroFlag = 0;
			break;
		case like:
			LikeFlag = 1;
			break;
		case regime:
			numObjects--;
			LikeFlag = 0;
			break;
		case bob:
			_textureEarth = texture[4];
			_textureMoon  = texture[5];
			BobFlag = 1;
			break;
		case larica:
			numObjects--;
			if (LsdFlag) {
				_textureMoon  = texture[2];
				_textureEarth = texture[3];
			} else {
				_textureMoon = texture[0];
				_textureEarth = texture[1];
			}
			BobFlag = 0;
			break;
		case lsd:
			LsdFlag = 1;
			_textureMoon  = texture[2];
			_textureEarth = texture[3];
			break;
		case sedativo:
			numObjects--;
			LsdFlag = 0;
			if (BobFlag) {
				_textureMoon  = texture[4];
				_textureEarth = texture[5];
			} else {
				_textureMoon = texture[0];
				_textureEarth = texture[1];
			}
			break;
		case jesus:
			numObjects--;
			_textureMoon = texture[0];
			_textureEarth = texture[1];
			BarreiroFlag = 0;
			LikeFlag = 0;	
			LsdFlag = 0;
			BobFlag = 0;
			break;
	}
}

void drawObj(int obj_id){
	glPushMatrix();
		glRotatef(teste[obj_id].rotate,1.0f,0.0f,0.0f);
		if ((JoaoX < teste[obj_id].x + 1) && (JoaoX > teste[obj_id].x - 1) && (rotate >= (315 - teste[obj_id].rotate)) && (rotate <= (324 - teste[obj_id].rotate))) {
			glColor3f(0,1,1);
			teste[obj_id].flag = true;
			callEffects(obj_id);
		} else {
			if (((rotate + teste[obj_id].rotate) >= 50) && (100 <= (rotate + teste[obj_id].rotate))){
				switch (teste[obj_id].type) {
					case barreiro:
						GLUquadric *pinga;
						pinga = gluNewQuadric();
						glTranslatef(teste[obj_id].x, teste[obj_id].y+1, teste[obj_id].z);
						glPushMatrix();
							glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
							glBindTexture(GL_TEXTURE_2D, texture[7]);
							glEnable(GL_TEXTURE_2D);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
							glRotatef(90,1.0f,0.0f,0.0f);
							gluQuadricTexture(pinga,1);
							gluCylinder(pinga,0.4,0.4,2.5,10,10);
							gluSphere(pinga,0.35,30,30);
							glDisable(GL_TEXTURE_2D);
							glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
							glColor3f(1,1,1);
							glTranslated(0.0,0.0,-1);
							gluCylinder(pinga,0.09,0.09,1,10,10);
							glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
						glPopMatrix();
						break;
					case lsd:
						glBindTexture(GL_TEXTURE_2D,texture[10]);
						glEnable (GL_TEXTURE_2D);
						glPushMatrix();					
							glTranslatef(teste[obj_id].x, teste[obj_id].y, teste[obj_id].z);
							glBegin(GL_QUADS);						
							glTexCoord2f(1, 1);
							glVertex3f( 0.75f, 0.75f, 0.0f);
							glTexCoord2f(0, 1);
							glVertex3f(-0.75f, 0.75f, 0.0f);
							glTexCoord2f(0, 0);
							glVertex3f(-0.75f,-0.75f, 0.0f);
							glTexCoord2f(1, 0);
							glVertex3f( 0.75f,-0.75f, 0.0f);
							glEnd();
						glPopMatrix();
						glDisable(GL_TEXTURE_2D);
						glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
						break;
					case like:				
						glTranslatef(teste[obj_id].x, teste[obj_id].y, teste[obj_id].z);					
						glRotatef(90, 1.0f, 0.0f, 0.0f);
						glScalef(0.7, 0.7, 0.55);
						glColor3f(0.823, 0.529, 0.172);
						glutSolidSphere(0.75, 10, 10);
						glColor3f(0.482, 0.168, 0.062);					
						glutSolidTorus(0.32, 0.5, 10, 10);
						glTranslatef(0.0, 0.0, 0.3);
						glColor3f(0.0, 0.268, 0.0);
						glutSolidTorus(0.32, 0.5, 10, 10);
						glColor3f(1.0, 0.0, 0.0);
						glTranslatef(1.0, 0,-1);		
						glutSolidCone(0.35,1.4,10,10);	
						glColor3f(1, 1, 1);
						GLUquadric *coca;
						coca = gluNewQuadric();
						glColor4f(0.1f, 0.1f, 0.1f, 0.1f);
						glBindTexture(GL_TEXTURE_2D, texture[12]);
						glEnable(GL_TEXTURE_2D);
						gluQuadricTexture(coca,1);
						gluCylinder(coca,0.3,0.3,1.4,10,10);	
						glDisable(GL_TEXTURE_2D);
						break;
					case bob:
						glPushMatrix();
							glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
							glTranslatef(teste[obj_id].x, teste[obj_id].y+1, teste[obj_id].z);
							glRotatef(90, 1.0f, 0.0f, 0.0f);
							glRotatef(180, 0.0f, 0.0f, 1.0f);
							GLUquadric *cannabis_at;
							cannabis_at = gluNewQuadric();
							glBindTexture(GL_TEXTURE_2D, texture[4]);
							glEnable(GL_TEXTURE_2D);
							gluQuadricTexture(cannabis_at,1);
							gluCylinder(cannabis_at,0.2,0.2,1.4,10,10);	
							glBindTexture(GL_TEXTURE_2D, texture[5]);
							glTranslatef(0,0,1.2);
							gluSphere(cannabis_at,0.3,10,10);
							glDisable(GL_TEXTURE_2D);
							glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
						glPopMatrix();
						break;
					case glicose:
						glTranslatef(teste[obj_id].x, teste[obj_id].y + 1.4, teste[obj_id].z );
						glRotatef(90,1,0,0);
						glPushMatrix();
							glColor3f(0,1,0);
							GLUquadric *sedativo_quad;
							sedativo_quad = gluNewQuadric();
							glColor4f(0.1f, 0.1f, 0.1f, 0.1f);
							glColor3f(1, 1,1);					
							gluQuadricTexture(sedativo_quad,1);
							gluCylinder(sedativo_quad,0.3,0.3,1.4,10,10);
							glColor3f(1, 0,0);					
							glTranslatef(0,0,-0.5);
							gluCylinder(sedativo_quad,0.15,0.15,1.4,10,10);	
							glColor3f(1, 1,1);		
							glTranslatef(0,0,-0.1);			
							gluCylinder(sedativo_quad,0.3,0.3,0.2,10,10);	
							glColor3f(1, 1,1);	
							glTranslatef(0,0,2);
							glutSolidCone(0.3,0.4,10,10);			
							glTranslatef(0,0,0.2);			
							gluCylinder(sedativo_quad,0.001,0.001,0.4,10,10);	
						glPopMatrix();	
						break;
					case regime:
						glPushMatrix();
							GLUquadric *peso;
							peso = gluNewQuadric();
							glColor4f(0.4f, 0.4f, 0.4f, 0.0f);
							glTranslatef(teste[obj_id].x, teste[obj_id].y, teste[obj_id].z);
							glRotatef(90,0.0f,1.0f,0.0f);
							gluQuadricTexture(peso,1);
							gluCylinder(peso, 0.3, 0.3, 1, 10, 10);
							glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
							glPushMatrix();
								glTranslatef(0.0, 0.0, 0.6);
								gluQuadricTexture(peso,1);
								gluCylinder(peso,0.8,0.8,0.6,10,10);
							glPopMatrix();
							glPushMatrix();
								glTranslatef(0.0, 0.0, -0.6);
								gluQuadricTexture(peso,1);
								gluCylinder(peso,0.8,0.8,0.6,10,10);
							glPopMatrix();
						glPopMatrix();
						glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
						break;
					case larica:
						glTranslatef(teste[obj_id].x, teste[obj_id].y, teste[obj_id].z);
						glColor3f(1.0, 0.407, 0.850);
						glRotatef(90, 1.0f, 0.0f, 0.0f);
						glScalef(1, 1, 1);
						glutSolidTorus(0.25, 0.5, 20,20);
						break;
					case sedativo:
						glPushMatrix();
							GLUquadric *glic;
							glic = gluNewQuadric();
							glTranslatef(teste[obj_id].x, teste[obj_id].y, teste[obj_id].z);
							glRotatef(90,0.0f,1.0f,0.0f);
							gluQuadricTexture(glic,1);
							glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
							glPushMatrix();
								gluCylinder(glic, 0.3, 0.3, 0.5, 10, 10);
								gluSphere(glic,0.25,10,10);
							glPopMatrix();
							glTranslatef(0.0f,0.0f,0.5f);
							glColor4f(0.0f, 0.0f, 0.4f, 0.0f);
							glPushMatrix();
								gluCylinder(glic, 0.3, 0.3, 0.5, 10, 10);
								glTranslatef(0.0f,0.0f,0.5f);
								gluSphere(glic,0.25,10,10);
							glPopMatrix();
							glTranslatef(1, 1, 0);
							glRotatef(90,1.0f,0.0f,0.0f);
							glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
							glPushMatrix();
								gluCylinder(glic, 0.3, 0.3, 0.5, 10, 10);
								gluSphere(glic,0.25,10,10);
							glPopMatrix();
							glTranslatef(0.0f,0.0f,0.5f);
							glColor4f(0.0f, 0.0f, 0.4f, 0.0f);
							glPushMatrix();
								gluCylinder(glic, 0.3, 0.3, 0.5, 10, 10);
								glTranslatef(0.0f,0.0f,0.5f);
								gluSphere(glic,0.25,10,10);
							glPopMatrix();
							glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
						glPopMatrix();
						glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
						break;				
					case jesus:
						glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
						glBindTexture(GL_TEXTURE_2D,texture[13]);
						glEnable (GL_TEXTURE_2D);
						glPushMatrix();					
							glTranslatef(teste[obj_id].x, teste[obj_id].y, teste[obj_id].z);
							glBegin(GL_QUADS);						
							glTexCoord2f(1, 1);
							glVertex3f( 1.0f, 1.0f, 0.0f);
							glTexCoord2f(0, 1);
							glVertex3f(-1.0f, 1.0f, 0.0f);
							glTexCoord2f(0, 0);
							glVertex3f(-1.0f,-1.0f, 0.0f);
							glTexCoord2f(1, 0);
							glVertex3f( 1.0f,-1.0f, 0.0f);
							glEnd();
						glPopMatrix();
						glDisable(GL_TEXTURE_2D);
						break;
				}
			}
		}
	glPopMatrix();
}

void drawMotorcycle(){
	playing = 0;
	if ((JoaoX < 1) && (JoaoX > -1) && (rotate >= 328) && (rotate <= 330)){
		winner = 1;
	}
	glBindTexture(GL_TEXTURE_2D,texture[6]);
	glEnable (GL_TEXTURE_2D);
	glPushMatrix();					
		glTranslatef(0, 29, -12);
		glBegin(GL_QUADS);
		glTexCoord2f(1, 1);
		glVertex3f( 1.5f, 1.5f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-1.5f, 1.5f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-1.5f,-1.5f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f( 1.5f,-1.5f, 0.0f);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
}

void drawMoon(){
	glPushMatrix();
		glTranslatef(0.0f, -30.0f, -40.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureMoon);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glRotatef(90,1.0f,0.0f,0.0f);
		glRotatef(rotate,1.0f,0,0.0f);
		gluQuadricTexture(moon,1);
	    gluSphere(moon,30,100,100);
		glDisable(GL_TEXTURE_2D);
		if ( level <= maxLevel ) {
			bool flag = false;
			for (int i = 0; i < level*10; i++) {
				if (!teste[i].flag) {
					drawObj(i);
					if (teste[i].type >= 4 && teste[i].type <= 8)
						flag = true;
				}
			}
			if ( !flag && (level <= maxLevel) ) {
				_textureMoon = texture[0];
				_textureEarth = texture[1];
				LsdFlag = BobFlag = BarreiroFlag = LikeFlag = 0;
				level++;
				free(teste);
				teste = (objetos *) calloc (level*10, sizeof(objetos));
				inicializarObjetos();
			}
		} else {
			drawMotorcycle();
		}
  	glPopMatrix();
}

void drawRecpFlag(){
	glBegin(GL_QUADS);						
		glTexCoord2f(1, 1);
		glVertex3f( 0.5f, 0.5f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(-0.5f, 0.5f, 0.0f);
		glTexCoord2f(0, 0);
		glVertex3f(-0.5f,-0.5f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f( 0.5f,-0.5f, 0.0f);
	glEnd();
}

void drawFlags(){
	if (LsdFlag){		
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
				glLoadIdentity();
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
				glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
				glBindTexture(GL_TEXTURE_2D, texture[10]);
		        glTranslated(10, 0.9, -17.5);
				drawRecpFlag();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	if (BarreiroFlag){
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
				glLoadIdentity();
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
				glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
				glBindTexture(GL_TEXTURE_2D, texture[7]);
		        glTranslated(10, 2.0, -17.5);
				drawRecpFlag();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	if (LikeFlag){
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
				glLoadIdentity();
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
				glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
				glBindTexture(GL_TEXTURE_2D, texture[14]);
		        glTranslated(10, 3.1, -17.5);
				drawRecpFlag();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	if (BobFlag){
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glLoadIdentity();
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
			glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
			glBindTexture(GL_TEXTURE_2D, texture[5]);
		    glTranslated(10, 4.2, -17.5);
			drawRecpFlag();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
}

void drawEarth(){	
	glPushMatrix();
		glTranslatef(-9.0f, 2.8f, -25.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, _textureEarth);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glRotatef(90,1.0f,0.0f,0.0f);
		glRotatef(rotate,0.0f,0.0f,1.0f);
		gluQuadricTexture(earth,1);
		gluSphere(earth,2,100,100);
		glDisable(GL_TEXTURE_2D);
  	glPopMatrix();
}

void drawScreen(GLuint texture1, GLuint texture2, GLuint texture3){
	glTranslatef(0.0f, 0.0f, -0.40f);
	glPushMatrix();
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex3f(1,1,0);
			glTexCoord2f(0,0);
			glVertex3f(1,-1,0);
			glTexCoord2f(1,0);
			glVertex3f(3,-1,0);
			glTexCoord2f(1,1);
			glVertex3f(3,1,0);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();	
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex3f(-2,1,0);
			glTexCoord2f(0,0);
			glVertex3f(-2,-1,0);
			glTexCoord2f(1,0);
			glVertex3f(0,-1,0);
			glTexCoord2f(1,1);
			glVertex3f(0,1,0);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture3);
		glBegin(GL_QUADS);
			glTexCoord2f(0,1);
			glVertex3f(-1,1,0);
			glTexCoord2f(0,0);
			glVertex3f(-1,-1,0);
			glTexCoord2f(1,0);
			glVertex3f(1,-1,0);
			glTexCoord2f(1,1);
			glVertex3f(1,1,0);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawScene() {

	gluLookAt(eyex,eyey, eyez , 0.0, 0.0,0.0, upx, upy,upz);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	if (!pauseGame) {
		if(!start) {
			if (help) {
				drawScreen(texture[16],texture[16],texture[18]);
			} else {
				drawScreen(texture[16],texture[16],texture[8]);
			}
		} else {
			if (winner) {
				drawScreen(texture[16],texture[16],texture[17]);
				glutSwapBuffers();
				return;
			}
			if (BarreiroFlag && LikeFlag && LsdFlag && BobFlag) {
				drawScreen(texture[16],texture[16],texture[15]);
				glutSwapBuffers();
				return;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
			srand (time(NULL));
			int colorx, colory, colorz;
			colorx = rand() % 1000;
			colory = rand() % 1000;
			colorz = rand() % 1000;
			glClearColor(colorx * LsdFlag * 0.001, colory * LsdFlag * 0.001, colorz * LsdFlag * 0.001, 0.0f);
			glLoadIdentity();
		    gluLookAt( eyex, eyey, eyez, 0.0, 0.0, 0.0, upx, upy, upz );
			drawEarth();
			drawMoon();

			if (BobFlag && !LsdFlag) {
				glPushMatrix();
			  		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
			  		glTranslated(posPorcoX,posPorcoY,-26);
			  		glRotatef(-rotate,0.0f,0.0f,1.0f);
			  		posPorcoX = posPorcoX - 0.05;
			  		if (!porcoFlag)
			  			posPorcoY = posPorcoY + 0.01;
			  		else
			  			posPorcoY = posPorcoY - 0.01;
			  		if (posPorcoX < -25.0) {
			  			posPorcoX = 25;
			  		} else {
			  			if (posPorcoX > 0)
				  			_texturePorco = texture[11];
				  		else
				  			_texturePorco = texture[12];
				  	}
			  		if (posPorcoY > 6.3)
			  			porcoFlag = 1;
			  		else if (posPorcoY < 5.8)
			  			porcoFlag = 0;	  		
					glBindTexture(GL_TEXTURE_2D,_texturePorco);
					glEnable (GL_TEXTURE_2D);
					glPushMatrix();
						glBegin(GL_QUADS);						
						glTexCoord2f(1, 1);
						glVertex3f( 1.5f, 1.5f, 0.0f);
						glTexCoord2f(0, 1);
						glVertex3f(-1.5f, 1.5f, 0.0f);
						glTexCoord2f(0, 0);
						glVertex3f(-1.5f,-1.5f, 0.0f);
						glTexCoord2f(1, 0);
						glVertex3f( 1.5f,-1.5f, 0.0f);
						glEnd();
					glPopMatrix();
					glDisable(GL_TEXTURE_2D);
				glPopMatrix();
			}
			glPushMatrix();
				glLoadIdentity();
				scoredisplay(8.0f,7.8f,-17.0f,1,level);
				scoredisplay(-8,7.8f,-17.0f,1,numObjects);
				scoredisplay(1,7.8f,-17.0f,1,(2*3.14*40*score));
			glPopMatrix();

			glPushMatrix();
		        glTranslated((GLfloat) JoaoX, -4 + LikeFlag * 1, -23.5);
				glRotatef(180,0.0f,1.0f,0.0f);
				glScalef(0.09 + LikeFlag * 0.11,0.09 + LikeFlag * 0.03, 0.09);
				displayHomer();
				glutPostRedisplay();
			glPopMatrix();
			glColor3f(1,1,1);
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
				glLoadIdentity();
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
				glColor4f(0.1f, 0.1f, 0.1f, 0.0f);
				glBindTexture(GL_TEXTURE_2D, texture[9]);
		        glTranslated(-upx, 8, -19.5);
				glBegin(GL_QUADS);
					glTexCoord2f(0,1);
					glVertex3f(-10,1,0);
					glTexCoord2f(0,0);
					glVertex3f(-10,-1,0);
					glTexCoord2f(1,0);
					glVertex3f(10,-1,0);
					glTexCoord2f(1,1);
					glVertex3f(10,1,0);
				glEnd();
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();
			drawFlags();
		}
		glutSwapBuffers();
	}
}

void update(int value) {
	if ((start) && (!pauseGame) && (!help)) {
	    rotate += (1.0f + (level * playing) * 0.2);
	    score += 0.0028;
	    if ( rotate > 360.f ) {
	        rotate -= 360;
	    }
	    glutPostRedisplay();
    }
	glutTimerFunc(25,update,0);	
}

int main(int argc, char** argv) {	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("JC TAXI");
	initRendering();
 	glutTimerFunc(25,update,0);
    glutTimerFunc(5, animate, 1);
	glutTimerFunc(1000, animateV, 10);
	glutFullScreen(); // making the window full screen
	teste = (objetos *) calloc (level*10, sizeof(objetos));
    inicializarObjetos();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMainLoop();
	free(teste);
	return 0;
}