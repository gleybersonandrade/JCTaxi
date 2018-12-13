/* CHARACTER */
static GLuint Torso= 1;
static GLuint UppLeftArm= 2;
static GLuint LwrLeftArm= 3;
static GLuint UppRightArm= 4;
static GLuint LwrRightArm= 5;
static GLuint UppRightLeg= 6;
static GLuint LwrRightLeg= 7;
static GLuint UppLeftLeg= 6;
static GLuint LwrLeftLeg= 7;
static GLuint HomerHead= 8;

GLint toggle = 0;

/* Variables */
static GLfloat spin = 0.0;
static GLfloat ZRotate = 0.0;
static GLfloat XRotate = 0.0;
static GLfloat HeadTurn = 0.0;
static GLfloat HeadNod = 0.0;

static GLfloat BodyTurn = 0.0;

static GLfloat MoveX= 0.0;
static GLfloat MoveY= 0.0;
static GLfloat MoveZ= 0.0;

static GLfloat UpperRightLegAngleX= 0.0;
static GLfloat LowerRightLegAngleX= 0.0;
static GLfloat UpperLeftLegAngleX= 0.0;
static GLfloat LowerLeftLegAngleX= 0.0;
static GLfloat UpperLeftLegAngleZ= 0.0;
static GLfloat UpperRightLegAngleZ= 0.0;
static GLfloat UpperRightArmAngleX= 0.0;
static GLfloat LowerRightArmAngleY= 0.0;
static GLfloat LowerRightArmAngleX= 0.0;
static GLfloat UpperLeftArmAngleX= 0.0;
static GLfloat LowerLeftArmAngleX= 0.0;
static GLfloat UpperRightArmAngleZ= 0.0;
static GLfloat UpperLeftArmAngleZ= 0.0;

/* --OBJECT AND MATERIAL PROPERTIES----------------------------------*/

GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};


int leftLegFlag = 0;
int rightLegFlag = 0;
int phase = 1;
float animationPeriod = 1;

void myDrawTorso(void) {  
  GLUquadricObj *qobj;
  GLfloat diffW[] = {1.0, 0.6, 0.0, 0.0};
  
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
  glRotated(-90.0,1.0,0.0,0.0); 
  glScaled(1.2, 1.0, 1.0);
  gluSphere(qobj,2.5,30,30);
  glTranslated(0.0,0.0,-3.9);
  gluCylinder(qobj,2.5,2.5,3.9,30,30); 
  glTranslated(0.0,0.0,3.5);
  gluCylinder(qobj,2.4,0.5,3.0,30,30);
  glTranslated(0.0,0.0,-4.0);
  gluCylinder(qobj,2.6,2.5,0.6,30,30);
}

void myDrawHomerHead(void) {  
  GLUquadricObj *qobj;

  
  GLfloat diffB[] = {1.0, 1.0, 1.0, 1.0};  /*cor cabelo */
  GLfloat diffW[] = {0.6, 0.0, 0.0, 0.0}; /*Cor dos olhos */
  GLfloat diffBR[] = {0.5, 0.3, 0.04, 0.0}; /* cor boca */
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
  
  
  
  glRotated(-90.0,1.0,0.0,0.0);
  glPushMatrix();
  glPushMatrix();
  glTranslated(0.0,0.0,-2.5);
  glScaled(1.0, 1.15, 1.5);
  gluSphere(qobj,1.30,30,30);
  glTranslated(0.0,0.0,-3.4);
  gluCylinder(qobj,1.30,1.30,3.5,30,30);
  glPopMatrix();

  glColor3f(0.088,0.224,0.909803922);
  glPushMatrix();
    glTranslated(0.0,0.0,-1.3);
    glScaled(1.0, 1.0, 1.0);
    gluSphere(qobj,2.30,30,30);
    glTranslated(0.0,0.0,-2.5);
    gluCylinder(qobj,2.30,2.30,2.4,30,30);
  glPopMatrix();

  glColor3f(1,1,1);

  /*LEFT EYE*/ 

  glPushMatrix();

  glTranslated(0.595,-1.0,-2.3);
  gluSphere(qobj,0.6,30,30);
  glPopMatrix();
  /*RIGHT EYE*/
  glPushMatrix();
  glTranslated(-0.595,-1.0,-2.3);
  gluSphere(qobj,0.6,30,30);
  glPopMatrix();
  
  /*LEFT PUPIL*/
  glPushMatrix();
  glTranslated(0.595,-1.50,-2.2);
  gluSphere(qobj,0.175,30,30);
  glPopMatrix();
  /*RIGHT PUPIL*/
  glPushMatrix();
  glTranslated(-0.595,-1.50,-2.2);
  gluSphere(qobj,0.175,30,30);
  glPopMatrix();
  
  /*MOUTH PART*/ 
  glPushMatrix();
  glTranslated(0.0,-1.0,-3.3);
  glutSolidCone(1.2,1.2,22,22);
  glRotated(180.0,1.0,0.0,0.0);
  glutSolidCone(1.2,1.2,22,22);
  glPopMatrix();
  
  /*THE NOSE*/
  glTranslated(0.0,0.0,-2.5);
  glRotated(90.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.25,0.25,2.2,30,30);
  glTranslated(0.0,0.0,2.2);
  gluSphere(qobj,0.25,30,30);
  /*THE EARS*/
  glPushMatrix();
  glTranslated(-1.3,0.0,-2.4);
  gluSphere(qobj,0.25,30,30);
  glPopMatrix();
  glPushMatrix();
  glTranslated(1.3,0.0,-2.4);
  gluSphere(qobj,0.25,30,30);
  glPopMatrix();
  /*THE HAIR*/
  
  glPushMatrix();
  glRotated(70.0,1.0,0.0,0.0);
  glRotated(20.0,0.0,0.0,1.0);
  glTranslated(0.6,-1.8,0.0); 
  glTranslated(0.0,0.0,-1.9);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);
  gluSphere(qobj,0.06,30,30);
  glTranslated(0.0,0.0,0);
  glRotated(-321.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);
  glPopMatrix();
  glPushMatrix();
  glRotated(70.0,1.0,0.0,0.0);
  glRotated(20.0,0.0,0.0,1.0);
  glRotated(8.0,0.0,1.0,0.0);
  glTranslated(0.8,-2.3,-0.1);
  glTranslated(0.0,0.0,-1.9);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);
  gluSphere(qobj,0.06,30,30);
  glRotated(-321.0,1.0,0.0,0.0);
  glRotated(-18.0,0.0,1.0,0.0);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);  
  glPopMatrix();
  /*THE RIGHT SIDE*/
  glPushMatrix();  
  glRotated(70.0,1.0,0.0,0.0);
  glRotated(20.0,0.0,0.0,1.0);
  glTranslated(-2.0,-1.8,0.0);
  glTranslated(0.0,0.0,-1.9);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);
  gluSphere(qobj,0.06,30,30);
  glTranslated(0.0,0.0,0);
  glRotated(-321.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);
  glPopMatrix();
  glPushMatrix();
  glRotated(70.0,1.0,0.0,0.0);
  glRotated(20.0,0.0,0.0,1.0);
  glRotated(4.0,0.0,1.0,0.0);
  glTranslated(-1.7,-1.3,0.0);
  glTranslated(0.0,0.0,-1.9);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);
  gluSphere(qobj,0.06,30,30);
  glRotated(-321.0,1.0,0.0,0.0);
  glRotated(-18.0,0.0,1.0,0.0);
  gluCylinder(qobj,0.06,0.06,0.8,30,30);
  glPopMatrix();
  /*TOP OF HIS HEAD... 3 HAIRS :-P */
  glPushMatrix();
  glTranslated(-0.5,2.0,-2.0);
  glRotated(75.0,0.0,1.0,0.0);
  gluCylinder(qobj,0.04,0.04,0.8,30,30);
  gluSphere(qobj,0.04,30,30);
  glRotated(110.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.04,0.04,0.4,30,30);
  gluSphere(qobj,0.04,30,30);
  glPopMatrix();
  glPushMatrix();
  glTranslated(0.655,1.95,-1.755);
  glRotated(90.0,0.0,1.0,0.0);
  glPushMatrix();
  glRotated(45.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.04,0.04,0.2,30,30);
  gluSphere(qobj,0.04,30,30);
  glPopMatrix();
  glRotated(190.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.04,0.04,0.4,30,30);
  gluSphere(qobj,0.04,30,30);
  glPopMatrix();
  glPushMatrix();
  glTranslated(-0.5,1.905,-2.35);
  glRotated(95.0,0.0,1.0,0.0);
  gluCylinder(qobj,0.04,0.04,1.3,30,30);
  gluSphere(qobj,0.04,30,30);
  glRotated(129.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.04,0.04,0.4,30,30);
  gluSphere(qobj,0.04,30,30);
  glPopMatrix();
  glPushMatrix();
  glTranslated(-0.5,1.905,-2.05);
  glRotated(95.0,0.0,1.0,0.0);
  gluCylinder(qobj,0.04,0.04,1.3,30,30);
  gluSphere(qobj,0.04,30,30);
  glRotated(129.0,1.0,0.0,0.0);
  gluCylinder(qobj,0.04,0.04,0.4,30,30);
  gluSphere(qobj,0.04,30,30);
  glPopMatrix();
  glPopMatrix();
}

void myDrawUppLeftArm(void) {  
  GLUquadricObj *qobj;
  /* Set the material properties. */
  
  
  
  /* Set up and draw the quadric. */
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
  /* rotate by -90 degrees about the x-axis so the quadric is aligned along the y-axis     */
  glRotated(90.0,1.0,0.0,0.0);
  /* Draw the Shoulder .. part of shirt*/
  gluSphere(qobj,0.8,30,30);
  /* Draw Sleeve of Shirt Upper Arm - should be white, as it is his shirt  */
  glRotated(30.0,0.0,1.0,0.0);
  gluCylinder(qobj,0.8,0.8,2.0,22,22);
  /*This draws part of his shirt sleeve..white */
  glTranslated(0.0,0.0,1.55);
  gluCylinder(qobj,0.8,0.8,1.4,22,22);
  
  /*This sraws part of his upper arm.. should be Yellow.. */
   glTranslated(0.0,0.0,1.4);
  gluCylinder(qobj,0.8,0.8,1.4,22,22);
  /*elbow Joint */
  glTranslated(0.0,0.0,1.3);
  gluSphere(qobj,0.7,30,30);
}

void myDrawLwrLeftArm(void) {
  GLUquadricObj *qobj;

  /* Set the material properties. */
  
  
  
  

  /* Set up and draw the quadric. */
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
 
  glColor3f(1,0.117647059,0.211764706);
  gluCylinder(qobj,0.8,0.8,1.9,22,22);
  glColor3f(1,1,1);

  glColor3f(1,1,1);

  /*Draw the hands... with 4 fingers*/
  glPushMatrix();
  glTranslated(0.0,0.0,2.2);
  glScaled(0.8, 2.0, 1.0);
  gluSphere(qobj,0.5,30,30);

  /*Finger 1*/
  glPushMatrix();
  glTranslated(0.0,0.0,0.0);
  gluCylinder(qobj,0.2,0.2,1.2,22,22);
  glTranslated(0.0,0.0,1.2);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();

   /*Finger 2*/
  glPushMatrix();
  glRotated(22.0,1.0,0.0,0.0);
  glTranslated(0.0,0.0,0.4);
  gluCylinder(qobj,0.2,0.2,0.8,22,22);
  glTranslated(0.0,0.0,0.8);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();
  
  /*Finger 3*/
  glPushMatrix();
  glRotated(35.0,1.0,0.0,0.0);
  glTranslated(0.0,-0.2,0.0);
  gluCylinder(qobj,0.2,0.2,0.8,22,22);
  glTranslated(0.0,0.0,0.8);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();

  /*Finger 4*/
  glPushMatrix();
  glRotated(-30.0,1.1,0.0,0.0);
  glTranslated(0.0,0.0,0.1);
  gluCylinder(qobj,0.2,0.2,0.8,22,22);
  glTranslated(0.0,0.0,0.8);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();
  glPopMatrix();
}

void myDrawUppRightArm(void) {  

  GLUquadricObj *qobj;


  /* Set the material properties. */
  
  GLfloat diffW[] = {1.0, 1.0, 1.0, 1.0}; /*cor da manga camisa */

  
  
  
  
  /* Set up and draw the quadric. */
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
  /* rotate by -90 degrees about the x-axis so the quadric is aligned along the y-axis   */
  glRotated(90.0,1.0,0.0,0.0); 
    
  /* Draw the Shoulder .. part of shirt*/
  gluSphere(qobj,0.8,30,30);
  /* Draw Sleeve of Shirt Upper Arm - should be white, as it is his shirt*/


  glRotated(-30.0,0.0,1.0,0.0); 
  /* Draw Sleeve of Shirt Upper Arm - should be white, as it is his shirt*/

 
  gluCylinder(qobj,0.8,0.8,2.0,22,22);

  
  /*This draws part of his shirt sleeve..white */
  glTranslated(0.0,0.0,1.55);
  gluCylinder(qobj,0.8,0.8,1.4,22,22);
  
  
  /*This sraws part of his upper arm.. should be Yellow.. */
   glTranslated(0.0,0.0,1.4);
  gluCylinder(qobj,0.8,0.8,1.4,22,22);
   
  /*elbow Joint */
  glTranslated(0.0,0.0,1.3);
  gluSphere(qobj,0.7,30,30);
}

void myDrawLwrRightArm(void) {
  GLUquadricObj *qobj;
  /* Set the material properties. */
  glColor3f(1,0.117647059,0.211764706);
  qobj = gluNewQuadric();
  /* Set up and draw the quadric. */
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
  gluCylinder(qobj,0.8,0.8,1.9,22,22);
  /*Draw the hands... with 4 fingers*/
  glColor3f(1,1,1);
  glPushMatrix();
  glTranslated(0.0,0.0,2.2);
  glScaled(1.0, 2.0, 1.0);
  gluSphere(qobj,0.5,30,30);

  /*Finger 1*/
  glPushMatrix();
  glTranslated(0.0,0.0,0.0);
  gluCylinder(qobj,0.2,0.2,1.2,22,22);
  glTranslated(0.0,0.0,1.2);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();

  /*Finger 2*/
  glPushMatrix();
  glRotated(22.0,1.0,0.0,0.0);
  glTranslated(0.0,0.0,0.4);
  gluCylinder(qobj,0.2,0.2,0.8,22,22);
  glTranslated(0.0,0.0,0.8);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();

  /*Finger 3*/
  glPushMatrix();
  glRotated(35.0,1.0,0.0,0.0);
  glTranslated(0.0,-0.2,0.0);
  gluCylinder(qobj,0.2,0.2,0.8,22,22);
  glTranslated(0.0,0.0,0.8);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();
  
  /*Finger 4*/
  glPushMatrix();
  glRotated(-30.0,1.1,0.0,0.0);
  glTranslated(0.0,0.0,0.1);
  gluCylinder(qobj,0.2,0.2,0.8,22,22);
  glTranslated(0.0,0.0,0.8);
  gluSphere(qobj,0.2,30,30);
  glPopMatrix();
  glPopMatrix();
}

void myDrawUppRightLeg(void) {
  GLUquadricObj *qobj;
  
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);

  gluSphere(qobj,1.45,30,30);
  glRotated(-90.0,1.0,0.0,0.0);
  glTranslated(0.0,0.0,-3.3);
  gluCylinder(qobj,1.30,1.45,3.5,30,30);
}

void myDrawLwrRightLeg(void) {
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();

  gluSphere(qobj,1.30,30,30);
  glTranslated(0.0,0.0,-3.2);
  gluCylinder(qobj,1.00,1.30,3.2,30,30);

  
  gluSphere(qobj,1.0,30,30);
  glTranslated(0.0,-0.5,-0.5);
  glRotated(90.0,1.0,0.0,0.0);
  glScaled(2.6, 1, 4.5);
  gluSphere(qobj,0.45,30,30);
}

void myDrawUppLeftLeg(void) {  
  GLUquadricObj *qobj;
  glColor3f(0,0,0.090196078);
  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
  gluSphere(qobj,1.45,30,30);
  glRotated(-90.0,1.0,0.0,0.0);
  glTranslated(0.0,0.0,-3.3);
  gluCylinder(qobj,1.30,1.45,3.5,30,30); 
  glColor3f(1,1,1);
}

void myDrawLwrLeftLeg(void) {  

  GLUquadricObj *qobj;
  glColor3f(0,0,0.090196078);

  qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj,GLU_SMOOTH);
  gluSphere(qobj,1.30,30,30);
  glTranslated(0.0,0.0,-3.2);
  gluCylinder(qobj,1.00,1.30,3.2,30,30);
    glColor3f(1,1,1);

  gluSphere(qobj,1.0,30,30);
  glTranslated(0.0,-0.5,-0.5);
  glRotated(90.0,1.0,0.0,0.0);
  glScaled(2.6, 1, 4.5);  
  
  gluSphere(qobj,0.45,30,30);
}

void setLighting(void) {
  GLfloat ambient[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat diffuse0[] = {1.0, 1.0, 1.0, 1.0}; 
  GLfloat position0[] = {0.0, 50.0, 60.0, 0.0}; /* Behind and up. */
  GLfloat lmodel_ambient[] = {0.0, 0.0, 0.0, 1.0}; /* Set the background ambient lighting. */
  GLfloat lmodel_twoside[] = {GL_TRUE}; /* Compute lighting for both inside and outside faces. */
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

  /* Set the light properties */
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}

void initHomer(void) {
  glClearColor(0.0,0.0,0.0,0.0); 
  glFrontFace(GL_CCW); /* Front faces defined using a clockwise rotation. */
  glDepthFunc(GL_LEQUAL); /* Plot pixel */
  glEnable(GL_DEPTH_TEST); /* Use a depth (z) buffer to draw only visible objects. */
  glEnable(GL_CULL_FACE); /* Use back face culling to improve speed. */
  glCullFace(GL_BACK); /* Cull only back faces. */
  /* Which shade model to use: GL_FLAT / GL_SMOOTH. */
  glShadeModel(GL_SMOOTH);

  glPushMatrix();
  //setLighting();

  /* Generate the display lists to store the robot: */
  glNewList(Torso,GL_COMPILE);
    glColor3f(1,0.117647059,0.211764706);
    myDrawTorso();
    glColor3f(1,1,1);

  glEndList();

  glNewList(UppLeftArm,GL_COMPILE);
    glColor3f(1,0.117647059,0.211764706);
    myDrawUppLeftArm();
    glColor3f(1,1,1);

  glEndList();
  
  glNewList(LwrLeftArm,GL_COMPILE);
   myDrawLwrLeftArm();
  glEndList();

  glNewList(UppRightArm,GL_COMPILE);
    glColor3f(1,0.117647059,0.211764706);

   myDrawUppRightArm();
    glColor3f(1,1,0.211764706);

  glEndList();

  glNewList(LwrRightArm,GL_COMPILE);
   myDrawLwrRightArm();
  glEndList();
  
  glNewList(UppRightLeg,GL_COMPILE);
   myDrawUppRightLeg();
  glEndList();

  glNewList(LwrRightLeg,GL_COMPILE);
   myDrawLwrRightLeg();
  glEndList();

  glNewList(UppLeftLeg,GL_COMPILE);
   myDrawUppLeftLeg();
  glEndList();

  glNewList(LwrLeftLeg,GL_COMPILE);
   myDrawLwrLeftLeg();
  glEndList();

  glNewList(HomerHead,GL_COMPILE);
   myDrawHomerHead();
  glEndList();

  glPopMatrix();
}

void displayHomer(void) {

  glPushMatrix();
  glTranslated(0.0,0.0,0.0); 
  glRotated(spin, 0,1,0);
  /* The Following is Scenery Object hierachy
   -- Will contain the walls, Lamps, TV etc
  */
  glPushMatrix();
  glTranslated (MoveX,MoveY,MoveZ); 
  glRotated(XRotate,1,0,0);
  glRotated(ZRotate,0,0,1);
  glRotated(BodyTurn,0,1,0);
  glPushMatrix();
  /*Torso*/
  glTranslated(0.0,0.0,0.0);
  glCallList(Torso);  
  glPopMatrix();
  /*HOMER HEAD*/
  glPushMatrix();
  glTranslated(0.0,6.5,0.0);
  glRotatef(HeadNod, 1, 0, 0);
  glRotatef(HeadTurn, 0, 1, 0);
  glCallList(HomerHead); 
  glPopMatrix();
  /*RIGHT ARM*/
  glPushMatrix(); 
  glTranslated(-2.0,1.5,0.0);  
  glRotatef(UpperRightArmAngleX, 1, 0, 0);
  glRotatef(UpperRightArmAngleZ, 0, 0, 1);
  glCallList(UppRightArm);    
  glPushMatrix();
  glRotatef(LowerRightArmAngleX, 1, 0, 0);
  glRotatef(LowerRightArmAngleY, 0, 1, 0);
  glCallList(LwrRightArm);  
  glPopMatrix();
  glPopMatrix();
  /*LEFT ARM*/
  glPushMatrix();
  glTranslated(2.0,1.5,0.0);
  glRotatef(UpperLeftArmAngleX, 1, 0, 0);
  glRotatef(UpperLeftArmAngleZ, 0, 0, 1);
  glCallList(UppLeftArm);
  glPushMatrix();     
  glRotatef(LowerLeftArmAngleX, 1, 0, 0);
  glCallList(LwrLeftArm);
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  glPopMatrix();
  /*RIGHT LEG*/
  glPushMatrix();   
  glTranslated(-1.3,-3.85,0.0); 
  glRotatef(UpperRightLegAngleX, 1, 0, 0);
  glRotatef(UpperRightLegAngleZ, 0, 0, 1);
  glCallList(UppRightLeg);
  glPushMatrix();  
  glRotatef(LowerRightLegAngleX, 1, 0, 0);
  glCallList(LwrRightLeg);   
  glPopMatrix();
  glPopMatrix();
  /*LEFT LEG*/
  glPushMatrix();   
  glTranslated(1.3,-3.85,0.0);
  glRotatef(UpperLeftLegAngleX , 1, 0, 0);
  glRotatef(UpperLeftLegAngleZ, 0, 0, 1);
  glCallList(UppLeftLeg);  
  glPushMatrix();
  glRotatef(LowerLeftLegAngleX , 1, 0, 0);
  glCallList(LwrLeftLeg); 
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
}

void animateLeftLeg(void) {
  if (LowerLeftLegAngleX > 85.0) {
    leftLegFlag = 1;
  } else if (LowerLeftLegAngleX < 0) {
    leftLegFlag = 0;
    phase = 2;
  }
  if (leftLegFlag == 0) {
    HeadTurn+=2.0;
    LowerLeftLegAngleX += 10;
    LowerRightArmAngleX -= 20;
  } else {
    HeadTurn-=2.0;
    LowerLeftLegAngleX -= 10;
    LowerRightArmAngleX += 20;
  }
  glutPostRedisplay();
}

void animateRightLeg(void) { 
  if (LowerRightLegAngleX > 85.0) {
    rightLegFlag = 1;
  } else if (LowerRightLegAngleX < 0) {
    rightLegFlag = 0;    
    phase = 1;
  }
  if (rightLegFlag == 0) {
    HeadTurn+=2.0;
    LowerRightLegAngleX += 10;
    LowerLeftArmAngleX -= 20;
  } else {
    HeadTurn-=2.0;
    LowerRightLegAngleX -= 10;
    LowerLeftArmAngleX += 20;
  }
  glutPostRedisplay();
}

void animate(int value) {
  if (phase == 1) {
    animateLeftLeg();
  } else {
    animateRightLeg();  
  }  
  glutTimerFunc(animationPeriod, animate, 1);
  glutPostRedisplay();
}

void myReshape(int width, int height) {
  glViewport(0, 0, (GLsizei) width, (GLsizei) height); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum (-1.0, 1.0, -1.0, 1.0, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*int main(int argc, char** argv) {
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
  glutInitWindowSize(800,800); 
  glutInitWindowPosition(100,150); 
  glutCreateWindow("Homer Simpson in 3D");
  glutDisplayFunc(displayHomer); 
  glutReshapeFunc(myReshape); 
  glutTimerFunc(5, animate, 1);
  myInit();
  glutMainLoop();
  return 0;
}*/