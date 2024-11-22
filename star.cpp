#include <GL/glut.h>
#include <cmath>

void displayStar(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    float degInRad;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 5; ++i) {
        degInRad = i * 72 * M_PI / 180;
        glVertex2f(0.5f * cos(degInRad), 0.5f * sin(degInRad));
        degInRad = (i * 72 + 72 / 2) * M_PI / 180;
        glVertex2f(0.25f * co(degInRad), 0.25f * sin(degInRad));
    }
    glEnd();

    glFlush();
}
