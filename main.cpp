#include <GLFW/glfw3.h>
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 500

float PX1 = 0, PX2 = 100, PX3 = 100, PY1 = 0, PY2 = 100, PY3 = 0, SLR = 0, SUD = 0;
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void DrawShape();
void rotateShape(float theta, int mode);

int main(void)
{
	GLFWwindow *window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Controling shape", NULL, NULL);
	if (!window)
		return -1;
	glfwMakeContextCurrent(window);
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment
	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		DrawShape();
		glfwSetKeyCallback(window, keyCallback);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void DrawShape() {
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(PX1 + SLR, PY1 + SUD, 0); //Left
	glVertex3f(PX2 + SLR, PY2 + SUD, 0); //Right
	glVertex3f(PX3 + SLR, PY3 + SUD, 0); //Top
	glEnd();
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	switch (key) {
		case GLFW_KEY_LEFT:
			SLR -= 3;
			break;
		case GLFW_KEY_RIGHT:
			SLR += 3;
			break;
		case GLFW_KEY_UP:
			SUD += 3;
			break;
		case GLFW_KEY_DOWN:
			SUD -= 3;
			break;
		case GLFW_KEY_L:
			rotateShape(5, 0);
			break;
		case GLFW_KEY_R:
			rotateShape(-5, 0);
			break;
		case GLFW_KEY_B:
			rotateShape(1.1, 1);
			break;
		case GLFW_KEY_S:
			rotateShape(0.9, 1);
			break;
		default:
			break;
	}
}
void rotateShape(float theta, int mode) {
	glTranslatef(PX1 + SLR, PY1 + SUD, 0);
	if (mode == 0)
		glRotatef(theta, 0, 0, 1);
	else if (mode == 1)
		glScaled(theta, theta, 0);
	glTranslatef(-(PX1 + SLR), -(PY1 + SUD), 0);
}
