//
//  Cwheel.cpp
//  Color_Wheel
//
//  Created by Ohub on 11/29/21.
//  Copyright © 2021 Revilo. All rights reserved.
//
// COMPILE: g++ -Wall -Wno-deprecated-declarations -O3 -o brick main.cpp -DMAC -framework OPENGL -framework GLUT
//---------------------------------------



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables
int step = 0;
bool loop = false;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

//---------------------------------------
// Function to get RGB color based on angle
//---------------------------------------
void get_color(int angle, float *R, float *G, float *B)
{
    // Interpolate between R and G
    float r=0, g=0, b=0;
    if ((angle >= 0) && (angle < 120))
    {
        float fraction = angle / 120.0;
        r = 1.0 - fraction;
        g = fraction;
        b = 0.0;
    }
    
    // Interpolate between G and B
    else if ((angle >= 120) && (angle < 240))
    {
        float fraction = (angle - 120) / 120.0;
        r = 0.0;
        g = 1.0 - fraction;
        b = fraction;
    }
    
    // Interpolate between B and R
    else if ((angle >= 240) && (angle < 360))
    {
        float fraction = (angle - 240) / 120.0;
        r = fraction;
        g = 0.0;
        b = 1.0 - fraction;
    }
    
    // Normalize length
    float length = sqrt(r * r + g * g + b * b);
    if (length > 0) r /= length;
    if (length > 0) g /= length;
    if (length > 0) b /= length;
    *R = r;
    *G = g;
    *B = b;
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    
    int angle = 0;
    
    //booleans for causing repetition
    if(loop == false)
        step++;
    
    if(loop == true)
        step--;
    
    if(step > 362)
        loop = true;
    
    if(step < 2 )
        loop = false;
    
    
    
    //set1A
    for (angle = 360; angle > 0; angle -= step)
    {
        // Specify color
        float R, G, B;
        get_color(angle, &R, &G, &B);
        glColor3f(G , B, R);
        
        // Specify vertex
        float radians2 = M_PI * (angle + 15) / 180.0;
        float C = 0.99 * cos(radians2);
        float D = 0.99 * sin(radians2);
        glVertex2f(C, D);
        
        // Specify vertex
        float radians3 = M_PI * (angle - 10) / 180.0;
        float E = 0.80 * cos(radians3);
        float F = 0.80 * sin(radians3);
        glVertex2f(E, F);
        
        float I = 0.65 * cos(radians3);
        float J = 0.65 * sin(radians3);
        glVertex2f(I, J);
        
        
        // Specify vertex
        float radians = M_PI * angle / 180.0;
        float X = 0.5 * cos(radians);
        float Y = 0.5 * sin(radians);
        glVertex2f(X, Y);
        
        
    }
    
    
    //set2A
    for (angle = 0; angle < 360; angle += step)
    {
        
        // Specify color
        float R, G, B;
        get_color(angle, &R, &G, &B);
        glColor3f(R, G, B);
        
        // Specify vertex
        float radians2 = M_PI * (angle + 15) / 180.0;
        float C = 0.99 * cos(radians2);
        float D = 0.99 * sin(radians2);
        glVertex2f(C, D);
        
        // Specify vertex
        float radians3 = M_PI * (angle - 10) / 180.0;
        float E = 0.80 * cos(radians3);
        float F = 0.80 * sin(radians3);
        glVertex2f(E, F);
        
        float I = 0.65 * cos(radians3);
        float J = 0.65 * sin(radians3);
        glVertex2f(I, J);
        
        
        // Specify vertex
        float radians = M_PI * angle / 180.0;
        float X = 0.5 * cos(radians);
        float Y = 0.5 * sin(radians);
        glVertex2f(X, Y);
        
        
    }
    
    glEnd();
    glFlush();
}

//---------------------------------------
// Idle callback for OpenGL
//---------------------------------------
void idle()
{
    
    glutPostRedisplay();
    
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(250, 250);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Color Wheel");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
