#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <windows.h>

#define STARS_NUM 400
#define ENEMY_NUM 7
#define PI 3.14159265358979323846
using namespace std;

typedef struct Star{
    float x;
    float y;
}STAR;
STAR st[STARS_NUM];
STAR sT[STARS_NUM];
STAR St[STARS_NUM];

GLfloat IntroPositionx =-1.2;
GLfloat IntroPositiony =-0.10;

GLfloat speedYst = 0.0004;
GLfloat speedYsT = 0.0008;
GLfloat speedYSt = 0.002;

GLfloat Heropositionx = 0.0;
GLfloat Heropositiony = -0.8;
GLfloat Herospeed = 0.025;
GLfloat Herolifetime =5;


GLfloat enemies[ENEMY_NUM][2];
GLfloat Enemypositionx = 0.0;
GLfloat Enemypositiony = 0.0;
GLfloat Enemyspeed = 0.5;

GLfloat Bulletpositionx = 0.0;
GLfloat Bulletpositiony = 0.0;
GLboolean Fire = GL_FALSE;
GLfloat Bulletspeed = 10;

GLboolean Bonustime = GL_FALSE;
GLfloat Bonuspositionx=0.0;
GLfloat Bonuspositiony=0.0;

GLboolean Boost = GL_FALSE;
GLint Boosttime = 5000;

GLdouble Starttime;
GLdouble Currenttime;

GLdouble Lasttime = 0.0;
GLdouble Bonusfor = 5000.0;

GLint Score = 0;
GLint level = 1;
GLboolean displayLevelUpMessage = GL_FALSE;
GLboolean Sound = GL_TRUE;
GLboolean Paused = GL_FALSE;
GLboolean inMaindisplay = GL_TRUE;
void moveStars(){
    for (int i=0;i<STARS_NUM;i++){
        if (st[i].y<=-1){
            st[i].y=1;
        }
        if (sT[i].y<=-1){
            sT[i].y=1;
        }
        if (St[i].y<=-1){
            St[i].y=1;
        }

        st[i].y-=speedYst;
        sT[i].y-=speedYsT;
        St[i].y-=speedYSt;

    }
}

float RandomNumber(float Min, float Max){
    return((float(rand()))/(float(RAND_MAX))*(Max-Min))+Min;
}

GLboolean checkBonusCollision() {
    return fabs(Bonuspositionx - Bonuspositionx) < 0.05 && fabs(Bonuspositiony - Bonuspositiony) < 0.05;
}
void handleBonusLife() {
     if (Bonustime && checkBonusCollision()) {
        if (Herolifetime<5){
            Herolifetime += 1;
        }
        Bonustime = GL_FALSE;
    }
}
void gameoverdisplay();
void update(int value) {
    if (!Paused){
        if (IntroPositiony < -2.1)
        IntroPositiony = 0.0;
    IntroPositiony -= 0.005;

    for (GLint i = 0; i < ENEMY_NUM; ++i) {
        enemies[i][1] -= Enemyspeed * 0.005f * level;

        if (fabs(enemies[i][0] - Heropositionx) < 0.03 && fabs(enemies[i][1] - Heropositiony) < 0.1) {
            Herolifetime -= 1;
            if (Herolifetime <= 0) {
                glutDisplayFunc(gameoverdisplay);
            }
            enemies[i][0] = RandomNumber(-0.85,0.85);
            enemies[i][1] = RandomNumber(1.1,2);
        }

        if (Fire && fabs(enemies[i][0] - Bulletpositionx) < 0.05 && fabs(enemies[i][1] - Bulletpositiony) < 0.1) {
            Score += 10;
            enemies[i][0] = RandomNumber(-0.85,0.85);
            enemies[i][1] = RandomNumber(1.1,2);
            Fire = GL_FALSE;
        }

        if (enemies[i][1] < -1.0) {
            Score -= 10;
            enemies[i][0] = RandomNumber(-0.85,0.85);
            enemies[i][1] = RandomNumber(1.1,2);
        }
    }

    if (Fire) {
        Bulletpositiony += Bulletspeed * 0.01f * level;
        if (Bulletpositiony > 1.0f) {
            Fire = GL_FALSE;
        }
    }


    Currenttime = glutGet(GLUT_ELAPSED_TIME);
    if (Currenttime - Lasttime > Bonusfor) {
        Bonuspositionx = RandomNumber(-1,1);
        Bonuspositiony = 1.0;
        Bonustime = GL_TRUE;
        Lasttime = Currenttime;
        Bonustime = GL_FALSE;
    }

    Bonuspositiony -= Enemyspeed * 0.005f * level;

    // Check if the bonus is out of bounds
    if (Bonuspositiony < -1.0)
        Bonustime = GL_FALSE;


    handleBonusLife();

	Currenttime = glutGet(GLUT_ELAPSED_TIME);
    if (Currenttime - Starttime > Bonusfor) {
        Boost = GL_FALSE;
    }

    // Check if the player advances to the next level
    if (Score >= 50 * level) {
        level++;
        displayLevelUpMessage = true;
        glutTimerFunc(2000, [](int value) {
            displayLevelUpMessage = false;
            glutPostRedisplay();
        }, 0);
    }
    if (Sound){
        sndPlaySound("o.wav", SND_ASYNC);
    }

    }
    glutPostRedisplay();
	glutTimerFunc(20, update, 0);

}




void HeroCraft (){
    glPushMatrix();
    glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);

        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.37, 0.0);
        glVertex3f(0.02, 0.325, 0.0);
        glVertex3f(0.02, 0.2, 0.0);
        glVertex3f(0.04, 0.175, 0.0);
        glVertex3f(0.06, 0.2, 0.0);
        glVertex3f(0.06, 0.075, 0.0);
        glVertex3f(0.08, 0.025, 0.0);
        glVertex3f(0.2, -0.05, 0.0);
        glVertex3f(0.2, -0.125, 0.0);
        glVertex3f(0.08, -0.15, 0.0);
        glVertex3f(0.09, -0.175, 0.0);
        glVertex3f(0.14, -0.25, 0.0);
        glVertex3f(0.14, -0.275, 0.0);
        glVertex3f(0.03, -0.3, 0.0);
        glVertex3f(0.03, -0.25, 0.0);
        glVertex3f(0.02, -0.275, 0.0);
        glVertex3f(-0.00, -0.275, 0.0);

        glVertex3f(-0.00, -0.275, 0.0);
        glVertex3f(-0.02, -0.275, 0.0);
        glVertex3f(-0.03, -0.25, 0.0);
        glVertex3f(-0.03, -0.3, 0.0);
        glVertex3f(-0.14, -0.275, 0.0);
        glVertex3f(-0.14, -0.25, 0.0);
        glVertex3f(-0.09, -0.175, 0.0);
        glVertex3f(-0.08, -0.15, 0.0);
        glVertex3f(-0.2, -0.125, 0.0);
        glVertex3f(-0.2, -0.05, 0.0);
        glVertex3f(-0.08, 0.025, 0.0);
        glVertex3f(-0.06, 0.075, 0.0);
        glVertex3f(-0.06, 0.2, 0.0);
        glVertex3f(-0.04, 0.175, 0.0);
        glVertex3f(-0.02, 0.2, 0.0);
        glVertex3f(-0.02, 0.325, 0.0);
        glVertex3f(-0.0, 0.37, 0.0);

   glEnd();
   glPopMatrix();
}

void enemyCraft(GLfloat x, GLfloat y){
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(0.25,0.25,0.0);
    glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.6, 0.0);
        glVertex3f(0.1, 0.6, 0.0);
        glVertex3f(0.22, 0.5, 0.0);
        glVertex3f(0.22, 0.40, 0.0);
        glVertex3f(0.25, 0.40, 0.0);
        glVertex3f(0.25, 0.35, 0.0);
        glVertex3f(0.28, 0.035, 0.0);
        glVertex3f(0.28, 0.3, 0.0);
        glVertex3f(0.32, 0.3, 0.0);
        glVertex3f(0.32, 0.24, 0.0);
        glVertex3f(0.35, 0.24, 0.0);
        glVertex3f(0.35, 0.16, 0.0);
        glVertex3f(0.40, 0.16, 0.0);
        glVertex3f(0.48, 0.22, 0.0);
        glVertex3f(0.48, 0.005, 0.0);
        glVertex3f(0.55, 0.1, 0.0);
        glVertex3f(0.65, 0.16, 0.0);
        glVertex3f(0.72, 0.16, 0.0);
        glVertex3f(0.72, 0.0, 0.0);
        glVertex3f(0.58, -0.12, 0.0);
        glVertex3f(0.52, -0.07, 0.0);
        glVertex3f(0.44, -0.07, 0.0);
        glVertex3f(0.35, -0.16, 0.0);
        glVertex3f(0.25, -0.07, 0.0);
        glVertex3f(0.1, -0.1, 0.0);
        glVertex3f(0.1, -0.2, 0.0);
        glVertex3f(0.07, -0.2, 0.0);
        glVertex3f(0.07, -0.15, 0.0);
        glVertex3f(0.0, -0.1, 0.0);


        glVertex3f(-0.07, -0.15, 0.0);
        glVertex3f(-0.07, -0.2, 0.0);
        glVertex3f(-0.1, -0.2, 0.0);
        glVertex3f(-0.1, -0.1, 0.0);
        glVertex3f(-0.25, -0.07, 0.0);
        glVertex3f(-0.35, -0.16, 0.0);
        glVertex3f(-0.44, -0.07, 0.0);
        glVertex3f(-0.52, -0.07, 0.0);
        glVertex3f(-0.58, -0.12, 0.0);
        glVertex3f(-0.72, 0.0, 0.0);
        glVertex3f(-0.72, 0.16, 0.0);
        glVertex3f(-0.65, 0.16, 0.0);
        glVertex3f(-0.55, 0.1, 0.0);
        glVertex3f(-0.48, 0.005, 0.0);
        glVertex3f(-0.48, 0.22, 0.0);
        glVertex3f(-0.40, 0.16, 0.0);
        glVertex3f(-0.35, 0.16, 0.0);
        glVertex3f(-0.35, 0.24, 0.0);
        glVertex3f(-0.32, 0.24, 0.0);
        glVertex3f(-0.32, 0.3, 0.0);
        glVertex3f(-0.28, 0.3, 0.0);
        glVertex3f(-0.28, 0.035, 0.0);
        glVertex3f(-0.25, 0.35, 0.0);
        glVertex3f(-0.25, 0.40, 0.0);
        glVertex3f(-0.22, 0.40, 0.0);
        glVertex3f(-0.22, 0.5, 0.0);
        glVertex3f(-0.1, 0.6, 0.0);
        glVertex3f(-0.0, 0.6, 0.0);
        glVertex3f(-0.0, 0.0, 0.0);
        glVertex3f(0.0, -0.1, 0.0);
   glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.4, 0.0, 0.0);
    glVertex3f(0.4, 0.4, 0.0);
    glVertex3f(0.45, 0.45, 0.0);
    glVertex3f(0.45, 0.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.4, 0.0, 0.0);
    glVertex3f(-0.4, 0.4, 0.0);
    glVertex3f(-0.45, 0.45, 0.0);
    glVertex3f(-0.45, 0.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.55, 0.0, 0.0);
    glVertex3f(0.55, 0.25, 0.0);
    glVertex3f(0.60, 0.25, 0.0);
    glVertex3f(0.60, 0.0, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.55, 0.0, 0.0);
    glVertex3f(-0.55, 0.25, 0.0);
    glVertex3f(-0.60, 0.25, 0.0);
    glVertex3f(-0.60, 0.0, 0.0);
    glEnd();
    glPopMatrix();
}
void Bullet(){
    glPushMatrix();
    glTranslatef(Bulletpositionx, Bulletpositiony, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    glPointSize(3);
    glBegin(GL_POINTS);glVertex2f(0.0,0.0);
    glEnd();
    glPopMatrix();
}

void Bonuss(){
    glPushMatrix();
    glTranslatef(Bulletpositionx, Bulletpositiony, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(8);
    glBegin(GL_POINTS);glVertex2f(0.0,0.0);
    glEnd();
    glPopMatrix();

}

void Stars (){
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i=0;i<STARS_NUM;i++){
        glVertex2f(st[i].x,st[i].y);
    }
    moveStars();
    glEnd();

    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i=0;i<STARS_NUM;i++){
        glVertex2f(sT[i].x,sT[i].y);
    }
    moveStars();
    glEnd();

    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(int i=0;i<STARS_NUM;i++){
        glVertex2f(St[i].x,St[i].y);
    }
    //moveStars();
    glEnd();
}

void drawLevelUp() {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
    glRasterPos2f(0.0f, 0.0f);

    const char* message = "Level Up!";
    for (const char* c = message; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}



void renderBitmapString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}

void Intro(){
    glPushMatrix();
        //glTranslatef(IntroPosx,IntroPosy, 0.0f);

        glColor3f(0.247f, 0.722f, 0.773f);
        renderBitmapString(0.30f, 0.9f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "AMERICAN INTERNATION UNIVERSITY BANGLADESH");
        glColor3f(0.78f, 0.914f, 0.71f);
        renderBitmapString(0.85f, 0.83f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "MAHFUJUR RAHMAN");
        glColor3f(1.0f, 0.518f, 0.486f);
        renderBitmapString(0.80f, 0.76f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "PROJECT MOON QUEST");
        glColor3f(0.855f, 0.71f, 0.4f);
        renderBitmapString(0.70f, 0.70f, 0.0f, GLUT_BITMAP_HELVETICA_18, "ID:21-45036-2  NAME:MUSSA ALAM");
        renderBitmapString(0.60f, 0.65f, 0.0f, GLUT_BITMAP_HELVETICA_18 , "ID:21-447721-1  NAME:SHEIKH FAHIM FUAD");
        renderBitmapString(0.55f, 0.60f, 0.0f, GLUT_BITMAP_HELVETICA_18, "ID:21-44537-1  NAME:SOBNOM MOSTARY AFRIN");
        renderBitmapString(0.70f, 0.55f, 0.0f, GLUT_BITMAP_HELVETICA_18, "ID:21-44898-1  NAME:ZARIN TASNIM");
        renderBitmapString(0.60f, 0.50f, 0.0f, GLUT_BITMAP_HELVETICA_18, "ID:22-467731  NAME:TAHASIN AHMED SIAM");
    glPopMatrix();
}

void drawString(const char* label, GLint value) {
    for (const char* c = label; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    GLint digits[10];
    GLint numDigits = 0;
    do {
        digits[numDigits++] = value % 10;
        value /= 10;
    } while (value > 0);
    for (GLint i = numDigits - 1; i >= 0; --i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + digits[i]);
    }
}

void score() {
    glColor3f(0.0, 1.0, 0.0);

    glRasterPos2f(-0.9f, 0.9);
    drawString("Score: ", Score);

    glRasterPos2f(0.7, 0.9);
    drawString("Life: ", Herolifetime);

    glRasterPos2f(-0.1, 0.9);
    drawString("Level: ", level);

}







void init_Pos_Stars(){
    for (int i=0;i<STARS_NUM;i++){
        st[i].x=RandomNumber(-1,1);
        st[i].y=RandomNumber(-1,1);
        sT[i].x=RandomNumber(-1,1);
        sT[i].y=RandomNumber(-1,1);
        St[i].x=RandomNumber(-1,1);
        St[i].y=RandomNumber(-1,1);
    }
}

void init_Pos_Enemies(){
    for (GLint i = 0; i < ENEMY_NUM; ++i) {
        enemies[i][0] = RandomNumber(-0.85,0.85);
        enemies[i][1] = RandomNumber(1.1,2);
    }
}






void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Stars();

    if (Fire){
        Bullet();
    }

    for (GLint i = 0; i < ENEMY_NUM; ++i) {
        enemyCraft(enemies[i][0], enemies[i][1]);
    }

    score();

    if (Bonustime) {Bonuss();

    }
    if (displayLevelUpMessage) {
        drawLevelUp();
    }


    glScalef(0.5,0.5,0.0);
    glTranslatef(Heropositionx*2, Heropositiony*2, 0.0);
    HeroCraft();

    //glutSwapBuffers();
    glFlush();
}



void Maindisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    Stars();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
        glBegin(GL_POLYGON);
        glVertex3f(-0.4,0.6,0.0);
        glVertex3f(0.4,0.6,0.0);
        glVertex3f(0.4,0.8,0.0);
        glVertex3f(-0.4,0.8,0.0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex3f(-0.4,0.5,0.0);
        glVertex3f(0.4,0.5,0.0);
        glVertex3f(0.4,0.3,0.0);
        glVertex3f(-0.4,0.3,0.0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex3f(-0.4,0.2,0.0);
        glVertex3f(0.4,0.2,0.0);
        glVertex3f(0.4,0.0,0.0);
        glVertex3f(-0.4,0.0,0.0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex3f(-0.4,-0.1,0.0);
        glVertex3f(0.4,-0.1,0.0);
        glVertex3f(0.4,-0.3,0.0);
        glVertex3f(-0.4,-0.3,0.0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex3f(-0.4,-0.4,0.0);
        glVertex3f(0.4,-0.4,0.0);
        glVertex3f(0.4,-0.6,0.0);
        glVertex3f(-0.4,-0.6,0.0);
        glEnd();

        glColor3f(0,0,0);
        renderBitmapString(-0.1, 0.68, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "START");
        renderBitmapString(-0.2, 0.38, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "INSTRUCTION");
        renderBitmapString(-0.13, 0.08, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "OPTION");
        renderBitmapString(-0.13, -0.23, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "CREDIT");
        renderBitmapString(-0.1, -0.5, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "EXIT");



    glPopMatrix();

    glFlush();
}

void instructiondisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Stars();
    glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
        glVertex3f(-0.8,-0.8,0.0);
        glVertex3f(0.8,-0.8,0.0);
        glVertex3f(0.8,0.8,0.0);
        glVertex3f(-0.8,0.8,0.0);
    glEnd();
    glColor3f(1,1,1);
        renderBitmapString(-0.4, 0.6, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Click Start to begin the game");
        renderBitmapString(-0.55, 0.4, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Click W or Upper Arrow to move upwards");
        renderBitmapString(-0.5, 0.2, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Click S or Down arrow to move down");
        renderBitmapString(-0.52, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Click D or Right arrow to proceed right");
        renderBitmapString(-0.48, -0.2, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Click A or left arrow to move back");
        renderBitmapString(-0.5, -0.4, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Press Space button for launching bullet");
        renderBitmapString(-0.45, -0.6, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Click Option for controlling sound");

    glPopMatrix();
    glFlush();
}
void optiondisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    renderBitmapString(-0.5, 0.7, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'm' to mute the game");
    glPopMatrix();
    glFlush();
}
void creditdisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Stars();
    glTranslatef(IntroPositionx, IntroPositiony, 0.0);
    Intro();
    glFlush();
}

void gameoverdisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();glScalef(2,2,0);
    glPushMatrix();
    glColor3f(1.0,1.0,0.0);

    renderBitmapString(-0.1, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, "Game Over");
    glPopMatrix();
    glFlush();
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            if(Heropositiony > 1.6/2)
                Heropositiony = 1.65/2;
            else
                Heropositiony += Herospeed;
            break;
        case 's':
            if(Heropositiony < -1.65/2)
                Heropositiony = -1.7/2;
        else
                Heropositiony += -Herospeed;
            break;
        case 'a':
            if(Heropositionx < -1.75/2)
                Heropositionx = -1.8/2;
            else
                Heropositionx += -Herospeed;
            break;
        case 'd':
            if(Heropositionx > 1.75/2)
                Heropositionx = 1.8/2;
            else
                Heropositionx += Herospeed;
            break;
        case 'b':
            if (!Boost) {
                Boost = GL_TRUE;
                Starttime = glutGet(GLUT_ELAPSED_TIME);
            }
            break;
        case 'm':
            if (!Sound) {
                Sound = GL_TRUE;
            }
            else{
                Sound = GL_FALSE;
            }
        case 'x':
            inMaindisplay = GL_TRUE;
            glutDisplayFunc(Maindisplay);

        /*case 'o':
            if (!Paused){
                Paused = GL_TRUE;
            }
            else{
                Paused = GL_FALSE;
            }

            break;*/

        case ' ':
            if (!Fire) {
                Fire = GL_TRUE;
                Bulletpositionx = Heropositionx;
                Bulletpositiony = Heropositiony;
            }
            break;

    }
    glutPostRedisplay();
}

void SpecialInput(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP:
            if(Heropositiony > 1.6/2)
                Heropositiony = 1.65/2;
            else
                Heropositiony += Herospeed;
            break;
        case GLUT_KEY_DOWN:
            if(Heropositiony < -1.65/2)
                Heropositiony = -1.7/2;
        else
                Heropositiony += -Herospeed;
            break;
        case GLUT_KEY_LEFT:
            if(Heropositionx < -1.75/2)
                Heropositionx = -1.8/2;
            else
                Heropositionx += -Herospeed;
            break;
        case GLUT_KEY_RIGHT:
            if(Heropositionx > 1.75/2)
                Heropositionx = 1.8/2;
            else
                Heropositionx += Herospeed;
            break;
    }
    glutPostRedisplay();
}

void handleMouse(int button, int state, int x, int y) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (inMaindisplay){
        if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
        float xs=(x-350)/350.0;
        float ys =(350-y)/350.0;
        if (xs <= 0.4 && xs >=-0.4 && ys >=0.6 && ys <=0.8){
            inMaindisplay = GL_FALSE;
            glutDisplayFunc(display);
        }
        if (xs <= 0.4 && xs >=-0.4 && ys >=0.3 && ys <=0.5){
            glutDisplayFunc(instructiondisplay);
        }
        if (xs <= 0.4 && xs >=-0.4 && ys >=0.0 && ys <=0.2){
            glutDisplayFunc(optiondisplay);
        }
        if (xs <= 0.4 && xs >=-0.4 && ys <=-0.1 && ys >=-0.3){
            glutDisplayFunc(creditdisplay);
        }
        if (xs <= 0.4 && xs >=-0.4 && ys <=-0.4 && ys >=-0.6){
            exit(0);
        }
        //cout<<xs<<" "<<ys<<endl;
    }
    }

	if (button == GLUT_LEFT_BUTTON){
		if (!Fire) {
            Fire = GL_TRUE;
            Bulletpositionx = Heropositionx;
            Bulletpositiony = Heropositiony;
        }
	}
	if (button == GLUT_RIGHT_BUTTON){

        /*if (!Boost) {
                Boost = GL_TRUE;
                Starttime = glutGet(GLUT_ELAPSED_TIME);
        }*/
	}


	glutPostRedisplay();
}


void reshape(int w,int h){
    glViewport(0.0,0.0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void init(){
    glClearColor(1.0,0.0,0.0,1.0);
    glColor3f(1.0,1.0,1.0);
}
void initGL(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main (int argc,char**argv){
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(600,100);
    glutInitWindowSize(700,700);
    glutCreateWindow("JoJo");

    init_Pos_Stars();
    init_Pos_Enemies();
    glutDisplayFunc(Maindisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(SpecialInput);
    glutMouseFunc(handleMouse);

    glutTimerFunc(20,update,0);
    init();
    initGL();
    Starttime = glutGet(GLUT_ELAPSED_TIME);
    if (Sound){
        sndPlaySound("o.wav", SND_ASYNC);
    }
    glutMainLoop();
    return 0;
}
