#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int NUM_PARTICULAS = 15;
const float RADIO = 1.5f;

float px[NUM_PARTICULAS];
float py[NUM_PARTICULAS];

float vx[NUM_PARTICULAS];
float vy[NUM_PARTICULAS];

void inicializarParticulas() {
	srand(time(NULL));
	
	for (int i = 0; i < NUM_PARTICULAS; i++) {
	    px[i] = 5 + rand() % 90;
        py[i] = 5 + rand() % 90;
        
         vx[i] = (rand() % 5 + 1) * 0.2f;
        vy[i] = (rand() % 5 + 1) * 0.2f;

        if (rand() % 2 == 0) {
            vx[i] *= -1;
        }

        if (rand() % 2 == 0) {
            vy[i] *= -1;
        }
	}
}

//dibujar particula
void dibujarParticula(float x, float y) {
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);

    for (int angulo = 0; angulo <= 360; angulo += 10) {
        float radianes = angulo * 3.14159f / 180.0f;

        float dx = RADIO * cos(radianes);
        float dy = RADIO * sin(radianes);
       
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

void colorParticula(int i) {
    if (fabs(vx[i]) <= 0.2f || fabs(vy[i]) <= 0.2f) {
        glColor3f(1, 0, 0);
    }
    else if (fabs(vx[i]) <= 0.4f || fabs(vy[i]) <= 0.4f) {
        glColor3f(1, 1, 0);
    }
    else if (fabs(vx[i]) <= 0.6f || fabs(vy[i]) <= 0.6f) {
        glColor3f(1, 0, 1);
    }
    else if (fabs(vx[i]) <= 0.8f || fabs(vy[i]) <= 0.8f) {
        glColor3f(0, 1, 0);
    }
    else {
        glColor3f(0, 0, 1);
    }
}

void actualizar(int valor) {
    for (int i = 0; i < NUM_PARTICULAS; i++) {

        // Actualizar posición
        px[i] += vx[i];
        py[i] += vy[i];

        // Colisión con paredes izquierda y derecha
        if (px[i] - RADIO <= 0) {
            px[i] = RADIO;
            vx[i] *= -1;
        }
        else if (px[i] + RADIO >= 100) {
            px[i] = 100 - RADIO;
            vx[i] *= -1;
        }

        // Colisión con paredes inferior y superior
        if (py[i] - RADIO <= 0) {
            py[i] = RADIO;
            vy[i] *= -1;
        }
        else if (py[i] + RADIO >= 100) {
            py[i] = 100 - RADIO;
            vy[i] *= -1;
        }
    }

    glutPostRedisplay();

    glutTimerFunc(16, actualizar, 0);
}


// Función de dibujo
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Dibujar el contenedor
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE_LOOP);
        glVertex2f(0, 0);
        glVertex2f(100, 0);
        glVertex2f(100, 100);
        glVertex2f(0, 100);
    glEnd();

    // Dibujar las partículas

    for (int i = 0; i < NUM_PARTICULAS; i++) {
    	colorParticula(i);
        dibujarParticula(px[i], py[i]);
    }

    glutSwapBuffers();
}

// Configuración de la ventana y las coordenadas
void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, 100, 0, 100);

    glMatrixMode(GL_MODELVIEW);
}

// Función principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simulacion de particulas");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    inicializarParticulas();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutTimerFunc(16, actualizar, 0);

    glutMainLoop();

    return 0;
}
