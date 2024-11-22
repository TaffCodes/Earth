#include <GL/glut.h>
#include <cmath>

// Angle of rotation for each planet
float angle[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

// Speed of rotation
float speed[4] = { 0.02f, 0.01f, 0.007f, 0.005f };

// Angle of rotation for the moon
float moonAngle[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

// Speed of rotation for the moon
float moonSpeed[4] = { 0.05f, 0.07f, 0.09f, 0.11f };

const char* names[4] = { "Mercury", "Venus", "Earth", "Mars" };

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void drawFilledCircle(float x, float y, float radius) {
    int numSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Center of the circle
        for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
            float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // Current angle
            float dx = radius * cosf(theta); // X offset
            float dy = radius * sinf(theta); // Y offset
            glVertex2f(x + dx, y + dy);
        }
    glEnd();
}

void drawCircle(float x, float y, float radius) {
    int numSegments = 100;
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
            float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // Current angle
            float dx = radius * cosf(theta); // X offset
            float dy = radius * sinf(theta); // Y offset
            glVertex2f(x + dx, y + dy);
        }
    glEnd();
}

void display() {
    // Dark sky blue color for the background
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // The sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawFilledCircle(0.0f, 0.0f, 0.2f); // Sun at the center with a larger radius

    float radius[4] = { 0.4f, 0.6f, 0.8f, 1.0f }; // Larger distance of each planet from the sun
    for (int i = 0; i < 4; i++) {
        glColor3f(0.5f, 0.5f, 0.5f); // Orbit color
        drawCircle(0.0f, 0.0f, radius[i]); // Orbit size

        float x = radius[i] * cosf(angle[i]);
        float y = radius[i] * sinf(angle[i]);
        glColor3f((i+1)%2, (i+2)%2, (i+3)%2);
        drawFilledCircle(x, y, 0.04f + 0.02f * i); // Larger planet size
        glColor3f(1.0f, 1.0f, 1.0f);
        drawText(x, y, names[i]);

        // Moon for the first and third planet
        if (i == 0 || i == 2) {
            float moonX = x + (0.1f * cosf(moonAngle[i])); // Larger moon orbit
            float moonY = y + (0.1f * sinf(moonAngle[i]));
            glColor3f(1.0f, 1.0f, 1.0f); // Moon color
            drawFilledCircle(moonX, moonY, 0.02f); // Larger moon size
            moonAngle[i] += moonSpeed[i];
        }

        angle[i] += speed[i]; // Updates the angle for the next frame
    }

    glutSwapBuffers();
}

void timer(int) {
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(1000/60, timer, 0); // Redraws the scene after 1000/60 milliseconds
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // Display mode setting
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Initial window position and size
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);

    // Window title
    glutCreateWindow("Planets");

    // Display callback
    glutDisplayFunc(display);

    // Set the timer function
    glutTimerFunc(0, timer, 0);

    // Start the GLUT main loop
    glutMainLoop();

    return 0;
}
