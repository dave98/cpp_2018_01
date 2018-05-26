#define GLUT_DISABLE_ATEXIT_HACK
#include <iostream>
#include <windows.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "c_point.h"
#include "c_r_tree.h"
#include "c_nodo.h"
#include <fstream>


#define KEY_ESC 27
using namespace std;


c_r_tree<float, 2, 4> arbol;

template<class T, int D, int C>
vector < c_point<T,D> > arriba_derecha;

template<class T, int D, int C>
vector< c_point<T,D> > abajo_izquierda;

vector< float > data_late;

float mar_iz_down_1 = 0.0f;
float mar_iz_down_2 = 0.0f;

float mar_rig_up_1 = 100.0f;
float mar_rig_up_2 = 100.0f;


void translate_points(float& ,float& );
//void graficar_cuadrantes(c_point, c_point);
void graficar_cuadrantes_v2();
void graficar_puntos();
void add_late_points();//Use when you have extra points coming from a document.
void OnMouseClick(int, int, int, int);
void OnMouseMotion(int, int);
void idle();
void glPaint(void);
//inicializacion de OpenGL
void init_GL(void);
//en el caso que la ventana cambie de tama�o
GLvoid window_redraw(GLsizei, GLsizei);
GLvoid window_key(unsigned char, int, int);
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1365, 700); //tama�o de la ventana
	glutInitWindowPosition(0, 0); //posicion de la ventana
	glutCreateWindow("Quadtree Simulation"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);

	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);

	glutMainLoop(); //bucle de rendering
	return 0;
}


void add_late_points(void){
	if(!data_late.empty()){
		for(unsigned int i = 0; i < data_late.size(); i+=2){
			float _x = data_late[i]; float _y = data_late[i+1];
			//translate_points(_x, _y);
			//c_point tempo(_x, _y);
			//data_point.push_back(tempo);
			//arbol.insert(_x, _y);
		}
		data_late.clear();
	}
}

//Closed window, that's a problem.
void translate_points(float& a, float& b){//Adapt incoming data to the new format needed in our map
	a = a / ( (float)glutGet(GLUT_WINDOW_WIDTH)/ mar_rig_up_1);
	b = ( (float)glutGet(GLUT_WINDOW_HEIGHT) - b ) / ( (float)glutGet(GLUT_WINDOW_HEIGHT) / mar_rig_up_2);
}

void graficar_cuadrantes(c_point l_d, c_point u_r){//Ingresamos el d_l u_r
	glBegin(GL_LINES);
	glColor3d(0, 60 , 0);
	glVertex2f(l_d.x, (l_d.y + u_r.y)/2);
	glVertex2f(u_r.x, (l_d.y + u_r.y)/2);
	glVertex2f((l_d.x + u_r.x)/2, l_d.y);
	glVertex2f((l_d.x + u_r.x)/2, u_r.y);
	//glVertex2f(0, 1000);//PRUEBA
	//glVertex2f(500, 500);//PRUEBA
	glEnd();
}

template<class T, int D, int C>
void graficar_cuadrantes_v2(){
	glBegin(GL_LINES);
	glColor3d(0, 60 , 0);
	for(unsigned int i = 0; i < arriba_derecha<T,D,C>.size(); i++){
		/*glVertex2f(data_region[i].x, (data_region[i].y + data_region[i+1].y)/2 );
		glVertex2f(data_region[i+1].x, (data_region[i].y + data_region[i+1].y)/2 );
		glVertex2f((data_region[i].x + data_region[i+1].x)/2, data_region[i].y);
		glVertex2f((data_region[i].x + data_region[i+1].x)/2, data_region[i+1].y);
		*/
    glVertex2f(0, 1000);//PRUEBA
    glVertex2f(500, 500);//PRUEBA
  }
	glEnd();
}

void graficar_puntos(){
	glPointSize(2);
	glBegin(GL_POINTS);
	for(unsigned int i = 0; i < data_point.size(); i++){
		glVertex2f(data_point[i].x, data_point[i].y);
	}
	glEnd();

}

void OnMouseClick(int button, int state, int x, int y){
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
	float x_2 = (float)x;
	float y_2 = (float)y;
	translate_points(x_2, y_2);
	c_point tempo(x_2, y_2);
	data_point.push_back(tempo);
	//convertir x,y
	//insertar un nuevo punto en el quadtree
	arbol.insert(x_2, y_2);
	/*for(unsigned int i = 0; i < data_point.size(); i++){
		cout<<data_point[i]<<" ";
	}*/
	//cout<<mar_iz_down<<"; "<<mar_der_up<<endl;
	//Graficamos el punto
	}
}

void OnMouseMotion(int x, int y){
	float x_2 = (float)x;
	float y_2 = (float)y;
	translate_points(x_2, y_2);
	c_point tempo(x_2, y_2);
	data_point.push_back(tempo);
	Sleep(0.5);
	arbol.insert(x_2, y_2);
}

void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen, se llama infinitamente por lo que constantemente se incializa
void glPaint(void) {
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	//glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);//Setting up configuration of  inner windows
	glOrtho(mar_iz_down.x,  mar_der_up.x, mar_iz_down.y, mar_der_up.y, -1.0f, 1.0f);//Setting up configuration of  inner windows
	//dibujar quadTree (qt->draw())
	//dibuja el gizmo
	//displayGizmo();//It's my own function
	//graficar_cuadrantes( c_point(0,0) , c_point(1000, 1000));
	add_late_points();
	graficar_cuadrantes_v2();
	graficar_puntos();
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);
	glOrtho(mar_iz_down.x,  mar_der_up.x, mar_iz_down.y, mar_der_up.y, -1.0f, 1.0f);//Setting up configuration of  inner windows
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
	default:
		break;
	}
}
