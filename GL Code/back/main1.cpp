#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
//------ trackball----------
//#include "trackball.h" //implementacion del Trackball
//--------------------------
// variables de tme
clock_t start, end;



//------ Trackball ------------

static GLint      mouse_state;
static GLint      mouse_button;
GLdouble   pan_x = 0.0;
GLdouble   pan_y = 0.0;
GLdouble   pan_z = 0.0;
//-----------------------------

//parametros de la fuente de luz
float LightPos[] = { 0.0f, 0.0f, 1.0f, 0.0f};  
float LightAmb[] = { 0.5f, 0.5f, 0.5f, 1.0f}; 
float LightDif[] = { 1.0f, 1.0f, 1.0f, 1.0f};   
float LightSpc[] = { 1.0f, 1.0f, 1.0f, 1.0f}; 

//Azul
float mat_ambient_azul[]={0.0, 0.0, 0.25, 1.0};
float mat_diffuse_azul[]={0.0, 0.0, 1.0, 1.0};
float mat_specular_azul[]={1.0, 1.0, 1.0, 1.0};
float mat_shininess_azul=100.0;
//Blanco
float mat_ambient_blanco[]={0.25, 0.25, 0.25, 1.0};
float mat_diffuse_blanco[]={1.0, 1.0, 1.0, 1.0};
float mat_specular_blanco[]={1.0, 1.0, 1.0, 1.0};
float mat_shininess_blanco=100.0;


void init(void)
{
 glClearColor(0.0, 0.0, 0.0, 0.0);
 glShadeModel(GL_SMOOTH);
 glCullFace(GL_BACK);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_CULL_FACE);
 glLightfv(GL_LIGHT0, GL_POSITION, LightPos);     
 glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);         
 glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDif);        
 glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpc); 
 glEnable(GL_LIGHT0); 
 glEnable(GL_LIGHTING);
 //------ Trackball -----------
 //gltbInit(GLUT_LEFT_BUTTON/*GLUT_MIDDLE_BUTTON*/);
 //----------------------------
 glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void display(void)
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glPushMatrix();
 gluLookAt(0.0,0.0,10,0.0,0.0,0.0,  0.0, 1.0, 0.0);
 
 //------ Trackball -----
 //gltbMatrix();
 //----------------------
 // Esfera 1
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_azul);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_azul);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_azul);
 glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_azul);
 glPushMatrix();
 glTranslatef(-4.33,-2.5,-2.5);
 glutSolidSphere(0.3,40,20);
 glPopMatrix();


 // Esfera 2
 glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_blanco);
 glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_blanco);
 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_blanco);
 glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_blanco);
 glPushMatrix();
 glTranslatef(0,0.0,0.0);
 glutSolidSphere(0.7,40,20);
 glPopMatrix();



 glPopMatrix();
 glFlush();
 glutSwapBuffers();
}


void reshape(int w, int h)
{
 if (!h)
	return;

 //------ Trackball --------
 //gltbReshape(w, h);
 //-------------------------

 glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(130.0, (GLfloat) w/(GLfloat) h, 0.01, 100.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();

 //------ Trackball -----------
 //glTranslatef(0.0, 0.0, -18.0);
 //----------------------------
}//*/


void keyboard(unsigned char key, int x, int y)
{
 switch (key)
   {
   case 27: 
       exit(0);
       break;
   
   case 's':
   case 'S':
       start = clock();
       printf("input down or socd:2\n");
       break;

   case 'd':
   case 'D':
       end = clock();
       double dif = (end - start) * 1.0 / CLOCKS_PER_SEC;
       break;

   }
}//*/


/*
//----- Tracknall -----------
void mouse(int button, int state, int x, int y)
{
 GLdouble model[4*4];
 GLdouble proj[4*4];
 GLint view[4];
    
 // fix for two-button mice -- left mouse + shift = middle mouse 
 if (button == GLUT_LEFT_BUTTON && glutGetModifiers() & GLUT_ACTIVE_SHIFT)
	button = GLUT_MIDDLE_BUTTON;
 gltbMouse(button, state, x, y);
 mouse_state = state;
 mouse_button = button;
 if (state == GLUT_DOWN && button == GLUT_MIDDLE_BUTTON) 
	{
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);
    gluProject((GLdouble)x, (GLdouble)y, 0.0,
                model, proj, view,
                &pan_x, &pan_y, &pan_z);
    gluUnProject((GLdouble)x, (GLdouble)y, pan_z,
                 model, proj, view,
                 &pan_x, &pan_y, &pan_z);
    pan_y = -pan_y;
    }
 glutPostRedisplay();
}
//*/

//------ Trackball--------------------
/*
void motion(int x, int y)
{
 GLdouble model[4*4];
 GLdouble proj[4*4];
 GLint view[4];
    
 gltbMotion(x, y);
 if (mouse_state == GLUT_DOWN && mouse_button == GLUT_MIDDLE_BUTTON) 
	{
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, view);
    gluProject((GLdouble)x, (GLdouble)y, 0.0,
                model, proj, view,
                &pan_x, &pan_y, &pan_z);
    gluUnProject((GLdouble)x, (GLdouble)y, pan_z,
                model, proj, view,
                &pan_x, &pan_y, &pan_z);
    pan_y = -pan_y;
    }
 glutPostRedisplay();
}//*/

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitWindowSize(380, 380);
 glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
 glutCreateWindow("Trackball en OpenGL");
 init();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 //----- Trackball --------
 //glutMouseFunc(mouse);
 //glutMotionFunc(motion);
 //------------------------
 glutMainLoop();
 return 0;
}