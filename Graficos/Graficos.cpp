// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <math.h>

#include <iostream>
using namespace std;

//Declaracion de la ventana
GLFWwindow *window;

GLfloat red = 0.0f, green = 0.0f, blue = 0.0f;
GLfloat ty, tx = 0.0f;
GLfloat angulo = 0.0f;

double tiempoAnterior = 0.0;
double velocidad = 0.1;

//Aqui esta bien para cambiar los valores de las variables de mi programa
void actualizar() {
	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = tiempoActual - tiempoAnterior;

	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		if (ty < 0.95) {
			ty += velocidad*tiempoTranscurrido;
		}
	}
	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		if (ty > -0.95) {
			ty -= velocidad*tiempoTranscurrido;
		}
	}
	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		if (angulo > -90) {
			angulo-=0.1;
		}
	}
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		if (angulo < 90) {
			angulo += 0.1;
		}
	}
	tiempoAnterior = tiempoActual;
}

void dibujar() {
	glPushMatrix();
	glTranslatef(tx, ty, 0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0, 1.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
	glPopMatrix();
}

/*void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (ty < 0.95 && key == GLFW_KEY_UP && (action == GLFW_PRESS|| action == GLFW_REPEAT)) {
		ty += 0.05f;
	}
	if (ty > -1 && key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		ty -= 0.05f;
	}
	if (tx < 1 && key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		tx += 0.05f;
	}
	if (tx > -1 && key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		tx -= 0.05f;
	}
}*/

int main()
{
	//Declaracion de la ventana
	//GLFWwindow *window;

	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 720;

	//Inicializacion de GLFW
	if (!glfwInit()) {
		//Si no se inicio bien, terminar la ejecucion
		exit(EXIT_FAILURE);
	}

	//Iniciar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verificar si se creo bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecucion
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como conexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;

	//glfwSetKeyCallback(window, key_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {		
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

