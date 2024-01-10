#ifdef APPLE
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>      // handle the window-managing operations
#else
#include <GL/glew.h>
#include <GL/freeglut.h>    // handle the window-managing operations
#endif
#include <random>
#include <iostream>
#include <GL/freeglut.h>
GLint win_width = 1500,
win_hight = 900;
//http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
GLdouble PI = 3.14159265359;
using namespace std;

int input = 11;

// buffers
GLuint myTexture2, myTexture1;
char image1Path[] = "C:\\Users\\Jana\\source\\repos\\MyCGproject\\photo9.bmp";
char image2Path[] = "C:\\Users\\Jana\\source\\repos\\MyCGproject\\paper.bmp";

GLuint myTexture3;
char image3Path[] = "C:\\Users\\Jana\\source\\repos\\MyCGproject\\background.bmp";

GLuint myTexture9;
char image9Path[] = "C:\\Users\\Jana\\source\\repos\\MyCGproject\\sene9.bmp";

float transValueX;
float transValueY;
float transValueZ;
float nearr;
float farr;




int frame = 0;
GLdouble value01 = 1.0;
const int maxFrames = 60;
const double scalingIncrement = 0.02;
bool scalingUp = true;


GLuint LoadTexture(const char* filename, int width, int height)
{

	GLuint texture;

	unsigned char* data;

	FILE* file;


	//The following code will read in our RAW file

	//file = fopen( filename, "rb" );

	fopen_s(&file, filename, "rb");


	if (file == NULL)

	{

		cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;

		exit(0);

		return 0;

	}


	data = (unsigned char*)malloc(width * height * 3);

	fread(data, width * height * 3, 1, file);


	fclose(file);



	// reorder the image colors to RGB not BGR

	for (int i = 0; i < width * height; ++i)

	{

		int index = i * 3;

		unsigned char B, R;

		B = data[index];

		R = data[index + 2];


		data[index] = R;

		data[index + 2] = B;


	}



	/////////////////////////////////////////

	// All Exercises TODO: load another texture image

	//////

	glGenTextures(1, &texture);
	//generate the texture with the loaded data
	

	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	/////////////////////////////////////////


	free(data); //free the texture array


	if (glGetError()
		!= GL_NO_ERROR)

		printf("GLError in genTexture()\n");


	return texture; //return whether it was successfull 
}



void drawFilledCircl1(GLfloat x, GLfloat y, GLfloat radius) { // ميثود ضي

	int i;
	int triangleAmount = 50; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (0.06 * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void drawFillHalfCircle(float center_x, float center_y, float radius) {
	int num_segments = 100;  // Number of line segments to approximate the half circle

	glBegin(GL_TRIANGLE_FAN);  // Begin drawing triangles

	glVertex2f(center_x, center_y);  // Center of the half circle

	for (int i = 0; i <= num_segments / 2; ++i) {
		float theta = PI * i / num_segments;
		float x = radius * cos(theta) + center_x;
		float y = radius * sin(theta) + center_y;
		glVertex2f(x, y);  // Define a vertex
	}

	glEnd();  // End drawing
}


void drawHalfFilledCircleAngle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 100; // Increase for smoother curve

	GLfloat twicePi = PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // Center of the half circle

	for (i = 0; i <= triangleAmount / 1.12; i++) {
		GLfloat angle = -i * (twicePi / triangleAmount);
		GLfloat xPos = x + (radius * cos(angle - 200));
		GLfloat yPos = y + (radius * sin(angle - 30));
		glVertex2f(xPos, yPos);
	}

	glEnd();
}
//Function used to draw a half hollow circle  in opposite direction
void drawHalfHollowCircleMaysaa1(GLfloat x, GLfloat y, GLfloat radius, GLfloat lineWidth) {
	int i;
	int triangleAmount = 100; // Increase for smoother curve

	GLfloat twicePi = PI;

	glLineWidth(lineWidth); // Set the line width for the border

	glBegin(GL_LINE_STRIP); // Use GL_LINE_STRIP to draw the border

	for (i = 0; i <= triangleAmount; i++) {
		GLfloat angle = i * (twicePi / triangleAmount);
		GLfloat xPos = x + (radius * cos(-angle));
		GLfloat yPos = y + (radius * sin(-angle));
		glVertex2f(xPos, yPos);
	}

	glEnd();
}

void drawHalfHollowCircleMaysaa2(GLfloat x, GLfloat y, GLfloat radius, GLfloat lineWidth) {
	int i;
	int triangleAmount = 100; // Increase for smoother curve

	GLfloat twicePi = PI;

	glLineWidth(lineWidth); // Set the line width for the border

	glBegin(GL_LINE_STRIP); // Use GL_LINE_STRIP to draw the border

	for (i = 0; i <= triangleAmount; i++) {
		GLfloat angle = i * (twicePi / triangleAmount);
		GLfloat xPos = x + (radius * cos(-angle));
		GLfloat yPos = y + (radius * sin(-angle));
		glVertex2f(xPos, yPos);
	}

	glEnd();
}
void drawHalfHollowCircleAngle(GLfloat x, GLfloat y, GLfloat radius, GLfloat lineWidth) {
	int i;
	int triangleAmount = 100; // Increase for smoother curve

	GLfloat twicePi = PI;

	glLineWidth(lineWidth); // Set the line width for the border

	glBegin(GL_LINE_STRIP); // Use GL_LINE_STRIP to draw the border

	for (i = 0; i <= triangleAmount / 1.12; i++) {
		GLfloat angle = -i * (twicePi / triangleAmount);
		GLfloat xPos = x + (radius * cos(angle - 200));
		GLfloat yPos = y + (radius * sin(angle - 30));
		glVertex2f(xPos, yPos);
	}

	glEnd();
}
//https://www.youtube.com/watch?v=Oa5RWmR2OvI
void animate(int value) {

	if (frame < maxFrames) {
		if (scalingUp) {
			value01 += scalingIncrement; // Increment the scale factor
		}
		else {
			value01 -= scalingIncrement; // Decrement the scale factor
		}
		frame++;
	}
	else {
		scalingUp = !scalingUp; // Toggle direction
		frame = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(100, animate, 0);
}

// drawFilledCircle  نفس لجين
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle


	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();


}
//  drawHandDrawLine نفس ضي وبتول
void drawHandDrawLine(float startX, float startY, float endX, float endY) {
	const int numSegments = 100;
	const float maxPerturbation = 0.02f; // Maximum perturbation distance

	// Set the seed for random number generation
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	glBegin(GL_LINE_STRIP);

	// Start point of the line
	glVertex2f(startX, startY);

	// Calculate the direction and length of the line
	float dx = endX - startX;
	float dy = endY - startY;
	float length = std::sqrt(dx * dx + dy * dy);

	// Calculate the perturbation for each segment
	for (int i = 0; i < numSegments; ++i) {
		float t = static_cast<float>(i) / static_cast<float>(numSegments - 1);
		float x = startX + t * dx;
		float y = startY + t * dy;

		// Randomly perturb the position
		float perturbationX = (std::rand() / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f;
		float perturbationY = (std::rand() / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f;
		perturbationX *= maxPerturbation;
		perturbationY *= maxPerturbation;
		x += perturbationX;
		y += perturbationY;

		glVertex2f(x, y);
	}

	// End point of the line
	glVertex2f(endX, endY);

	glEnd();
}
// نفس لجين drawHalfHollowCircle  
void drawHalfHollowCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat lineWidth) {
	int i;
	int triangleAmount = 100; // Increase for smoother curve

	GLfloat twicePi = PI;

	glLineWidth(lineWidth); // Set the line width for the border

	glBegin(GL_LINE_STRIP); // Use GL_LINE_STRIP to draw the border

	for (i = 0; i <= triangleAmount; i++) {
		GLfloat angle = i * (twicePi / triangleAmount);
		GLfloat xPos = x + (radius * cos(-angle));
		GLfloat yPos = y + (radius * sin(-angle));
		glVertex2f(xPos, yPos);
	}

	glEnd();
}
// نفس لجين drawHollowCircle 
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / lineAmount)),
			y + (radius * sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}
// نفس لجين drawOval 
void drawOval(float center_x, float center_y, float radius) {
	int num_segments = 100;  // Number of line segments to approximate the oval

	glBegin(GL_LINE_LOOP);  // Begin drawing line segments

	for (int i = 0; i < num_segments; ++i) {
		float theta = 2.0 * PI * i / num_segments;
		float x = radius * cos(theta) + center_x;
		float y = 0.5 * radius * sin(theta) + center_y;
		glVertex2f(x, y);  // Define a vertex
	}

	glEnd();  // End drawing
}
void drawHalfFilledCircle1(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 100; // Increase for smoother curve

	GLfloat twicePi = PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // Center of the half circle

	for (i = 0; i <= triangleAmount; i++) { // Change the loop condition
		GLfloat angle = i * (twicePi / triangleAmount);
		GLfloat xPos = x + (radius * cos(-angle));
		GLfloat yPos = y + (radius * sin(-angle));
		glVertex2f(xPos, yPos);
	}

	glEnd();
}
//  drawFilledOval نفس لجين 
void drawFilledOval(float center_x, float center_y, float radius) {
	int num_segments = 100;  // Number of line segments to approximate the oval

	glBegin(GL_TRIANGLE_FAN);  // Begin drawing filled oval

	glVertex2f(center_x, center_y);  // Center vertex

	for (int i = 0; i <= num_segments; ++i) {
		float theta = 2.0 * PI * i / num_segments;
		float x = radius * cos(theta) + center_x;
		float y = 0.5 * radius * sin(theta) + center_y;

		glVertex2f(x, y);  // Define a vertex
	}

	glEnd();  // End drawing
}
//  drawFilleddOval نفس لجين 
void drawFilleddOval(float centerX, float centerY, float radiusX, float radiusY)
{
	const int numSegments = 100;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(centerX, centerY); // Center of the oval

	// Calculate the vertex positions for the oval
	for (int i = 0; i <= numSegments; ++i)
	{
		float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
		float x = radiusX * cos(theta);
		float y = radiusY * sin(theta);
		glVertex2f(x + centerX, y + centerY);
	}

	glEnd();
}
// نفس لجين drawLineRectangle 
void drawLineRectangle(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1); // Top-left corner
	glVertex2f(x2, y1); // Top-right corner

	glVertex2f(x2, y1); // Top-right corner
	glVertex2f(x2, y2); // Bottom-right corner

	glVertex2f(x2, y2); // Bottom-right corner
	glVertex2f(x1, y2); // Bottom-left corner

	glVertex2f(x1, y2); // Bottom-left corner
	glVertex2f(x1, y1); // Top-left corner

	glEnd();
}
//  drawLineOval نفس لجين
void drawLineOval(float centerX, float centerY, float radiusX, float radiusY)
{
	const int numSegments = 100;

	glBegin(GL_LINE_LOOP);

	// Calculate the vertex positions for the oval
	for (int i = 0; i < numSegments; ++i)
	{
		float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
		float x = radiusX * cos(theta);
		float y = radiusY * sin(theta);
		glVertex2f(x + centerX, y + centerY);
	}

	glEnd();
}
void drawHalfHollowCircle2(GLfloat x, GLfloat y, GLfloat radius, GLfloat lineWidth) {
	int i;
	int triangleAmount = 100; // Increase for smoother curve

	GLfloat twicePi = PI;

	glLineWidth(lineWidth); // Set the line width for the border

	glBegin(GL_LINE_STRIP); // Use GL_LINE_STRIP to draw the border

	for (i = 0; i <= triangleAmount; i++) {
		GLfloat angle = i * (twicePi / triangleAmount);
		GLfloat xPos = x + (radius * cos(-angle));
		GLfloat yPos = y + (radius * sin(-angle));
		glVertex2f(xPos, yPos);
	}

	glEnd();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.1 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Maroco1()
{

	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.04f, 0.04f, 40);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller


	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	   //حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle2(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();



	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);

	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();


	//eyses
	glLineWidth(1);
	//white
	glColor3f(1, 1, 1);
	drawFilledOval(.1, .3, .06);
	drawFilledOval(-.1, .3, .06);
	//black
	glColor3f(0, 0, 0);
	drawOval(.1, .3, .06);
	drawOval(-.1, .3, .06);
	//بؤبؤ
	drawFilledCircle(0.08, 0.31, .01);
	drawFilledCircle(-0.12, 0.31, .01);



	//Smile
	glColor3f(0.89f, 0.44f, 0.48f);  // Red color

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.085785970769f, 0.21f);
	glVertex2f(0.0277389634486f, 0.18f);
	glVertex2f(-0.0161221869181f, 0.16f);


	glEnd();



	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);



}



void BackGroundOfMaroco1() {

	/*
	* start BackGround
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);

	glColor3f(0.6745f, 0.8039f, 0.6275f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(0.7f, 0.8f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
	/*
	end BackGround
	*/

	/* start drawLockers
	*/


	// Set color
	glColor3f(0.363137f, 0.270588f, 0.152941f);
	// Draw the Lockers
	glRectf(-1.0f, 0.4f, 1.0f, 0.3f);

	// Set color
	glColor3f(0.0f, 0.0f, 0.0f);

	// Set brown color
	glColor3f(0.631373f, 0.431373f, 0.207843f);
	glRectf(-1.0f, 1.0f, 1.0f, 0.4f);

	// Set black color
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	// Draw the frame lines
	glBegin(GL_LINE_LOOP);

	glVertex2f(-1.0f, 1.0f);  // Top left corner
	glVertex2f(1.0f, 1.0f);   // Top right corner
	glVertex2f(1.0f, 0.4f);   // Bottom right corner
	glVertex2f(-1.0f, 0.4f);  // Bottom left corner

	// Draw a line under the rectangle
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glVertex2f(-1.0f, 0.3f);   // Bottom left corner
	glVertex2f(1.0f, 0.3f);    // Bottom right corner



	// Draw the line
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glVertex2f(0.0f, 1.0f);  // Start point
	glVertex2f(0.0f, 0.4f);   // End point

	glVertex2f(0.5f, 1.0f);  // Start point
	glVertex2f(0.5f, 0.4f);   // End point

	glVertex2f(-0.5f, 1.0f);  // Start point
	glVertex2f(-0.5f, 0.4f);   // End point



	glEnd();
	/*
	* end drawLockers
	*/

	/*
	* start table
	*/
	glColor3f(0.819608f, 0.729412f, 0.431373f);
	glRectf(-0.8f, -1.0f, 0.8f, -0.5f); // 

	// Set color
	glColor3f(0.0f, 0.0f, 0.0f);

	// Draw the line
	glBegin(GL_LINES);

	glVertex2f(-0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -0.5f);   // End point

	glVertex2f(0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -1.0f);   // End point

	glVertex2f(-0.8f, -0.5f); // Start point reflected
	glVertex2f(-0.8f, -1.0f); // End point reflected

	glEnd();
	/*
	* end table
	*/

	/* start drawItemsOnTable
	*/
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-0.2f, -1.0f, 0.2f, -0.6f); // Draw Test paper

	// Call drawHandDrawLine for the first line
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHandDrawLine(-0.2f, -0.9f, 0.2f, -0.9f);
	drawHandDrawLine(-0.2f, -0.8f, 0.2f, -0.8f);

	// Draw frame
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, -1.0f);
	glVertex2f(0.2f, -1.0f);
	glVertex2f(0.2f, -0.6f);
	glVertex2f(-0.2f, -0.6f);
	glEnd();

	// draw Pencil eraser

	glColor3f(1.0f, 0.50f, 0.50f);
	glRectf(-0.4f, -0.8f, -0.39f, -0.57f);  //eraser

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);  // Bottom-left vertex
	glVertex2f(-0.4f, -0.57f); // Top-left vertex
	glVertex2f(-0.39f, -0.57f); // Top-right vertex
	glVertex2f(-0.39f, -0.8f);  // Bottom-right vertex
	glEnd();

	// Draw pencil
	glColor3f(0.2745, 0.5529, 0.7961);
	glRectf(-0.4f, -0.8f, -0.39f, -0.6f);


	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.395f, -0.83f);
	glEnd();

	// Draw black lines around the pencil
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.39f, -0.6f);
	glVertex2f(-0.395f, -0.83f);
	glVertex2f(-0.395f, -0.6f);
	glEnd();




	glEnd();

	/*
	* end drawItemsOnTable
	*/

	/*
	* start eraser
	*/


	//eraser
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.480, -0.576, 0.026);
	glColor3f(1.0f, 0.50f, 0.50f); // Set color to eraser color
	glRectf(-0.48f, -0.55f, -0.419f, -0.60f);  //eraser


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.4179783700881, -0.6040088913799);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4179783700881, -0.6040088913799);//
	glVertex2f(-0.497, -0.6);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.49, -0.5442019054577);
	glEnd();

	//eraser lines inside
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.431622879304, -0.5706971373495);
	glVertex2f(-0.4660764184768, -0.5718690264371);
	glEnd();


	//eraser
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5000, -0.5832063155461);
	glVertex2f(-0.4981625811559, -0.5748504358921);
	glVertex2f(-0.4877897650338, -0.5696640278311);
	glEnd();
	//eraser2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5, -0.59);
	glVertex2f(-0.5036371229982, -0.5774436399227);
	glVertex2f(-0.503348989217, -0.5670708238005);
	glVertex2f(-0.4975863135936, -0.5555454725537);
	glVertex2f(-0.4889423001585, -0.5494946631492);

	glEnd();

	/*
	end eraser
	*/



	/*
	* start chair
	*/
	glColor3f(0.9f, 0.5f, 0.2f); // Set the fill color to the desired value
	glRectf(-0.2f, 0.1f, 0.2f, -0.5f); // Draw the filled rectangle

	glColor3f(0.0f, 0.0f, 0.0f); // Set the line color to black
	glLineWidth(2.0f); // Set the line width to 1 pixel (adjust as needed)

	// Draw lines around the rectangle
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, 0.1f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.2f, -0.5f);
	glVertex2f(-0.2f, -0.5f);
	glEnd();
	/*
	* end chair
	*/

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.56, 0.5, 0.2);
	drawFilledCircle(-0.36, 0.3, 0.04);
	drawFilledCircle(-0.3, 0.2, 0.03);
	glEnd();

	// To write on the screen
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.7f, 0.5f);
	const char* text1 = "I have a lot of things";

	while (*text1) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);  // Increase font size here
		text1++;
	}
	// To write on the screen
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.68f, 0.4f);
	const char* text2 = "to do at home";

	while (*text2) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text2);  // Increase font size here
		text2++;
	}
}

void display1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	

	BackGroundOfMaroco1();
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	Maroco1();
	glPopMatrix();
	glDisable(GL_BLEND);
	glFlush();
	glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.2 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void BackGround() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	// background
	glColor3f(0.9f, 0.6f, 0.5f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
}
void TheBookShelf()
{
	//the background
	glBegin(GL_QUADS);
	glColor3f(0.9, 0.8, 0.8);
	glVertex2f(-3, 2);
	glVertex2f(-3, -2);
	glVertex2f(3, -2);
	glVertex2f(3, 2);
	glEnd();

	// the book shelf
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.7, 0.2);
	glVertex2f(-1, 1);
	glVertex2f(-1, .6);
	glVertex2f(-.6, .6);
	glVertex2f(-.6, 1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-1, 1);
	glVertex2f(-1, .6);
	glVertex2f(-.6, .6);
	glVertex2f(-.6, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.4, 0.7, 0.2);
	glVertex2f(-1, .6);
	glVertex2f(-1, .57);
	glVertex2f(-.62, .57);
	glVertex2f(-.62, .6);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-1, .6);
	glVertex2f(-1, .57);
	glVertex2f(-.62, .57);
	glVertex2f(-.62, .6);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.97, .97);
	glVertex2f(-.97, .63);
	glVertex2f(-.64, .63);
	glVertex2f(-.64, .97);
	glEnd();
}
void drawPencil() {

	glColor3f(1.0f, 0.50f, 0.50f);
	glRectf(-0.4f, -0.8f, -0.39f, -0.57f);  //eraser

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);  // Bottom-left vertex
	glVertex2f(-0.4f, -0.57f); // Top-left vertex
	glVertex2f(-0.39f, -0.57f); // Top-right vertex
	glVertex2f(-0.39f, -0.8f);  // Bottom-right vertex
	glEnd();

	// Draw pencil
	glColor3f(0.2745, 0.5529, 0.7961);
	glRectf(-0.4f, -0.8f, -0.39f, -0.6f);


	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.395f, -0.83f);
	glEnd();

	// Draw black lines around the pencil
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.39f, -0.6f);
	glVertex2f(-0.395f, -0.83f);
	glVertex2f(-0.395f, -0.6f);
	glEnd();



}
void TheBooks()
{
	//the Books
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.5, .7);
	glVertex2f(-.82, .92);
	glVertex2f(-.82, .63);
	glVertex2f(-.66, .63);
	glVertex2f(-.66, .92);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-.82, .92);
	glVertex2f(-.82, .63);
	glVertex2f(-.66, .63);
	glVertex2f(-.66, .92);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-.7, .92);
	glVertex2f(-.7, .63);
	glVertex2f(-.74, .92);
	glVertex2f(-.74, .63);
	glVertex2f(-.78, .92);
	glVertex2f(-.78, .63);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.82, .69);
	glVertex2f(-.82, .65);
	glVertex2f(-.66, .65);
	glVertex2f(-.66, .69);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.82, .73);
	glVertex2f(-.82, .71);
	glVertex2f(-.66, .71);
	glVertex2f(-.66, .73);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.6, 0.5, .7);
	glVertex2f(-.87, .93);
	glVertex2f(-.87, .63);
	glVertex2f(-.82, .63);
	glVertex2f(-.82, .93);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-.87, .93);
	glVertex2f(-.87, .63);
	glVertex2f(-.82, .63);
	glVertex2f(-.82, .93);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-.85, .90);
	glVertex2f(-.85, .80);
	glVertex2f(-.84, .80);
	glVertex2f(-.84, .90);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-.87, .92);
	glVertex2f(-.87, .91);
	glVertex2f(-.82, .91);
	glVertex2f(-.82, .92);
	glEnd();

	//the Blue Book
	glBegin(GL_QUADS);
	glColor3f(0.56, 0.74, .9);
	glVertex2f(-.90, .92);
	glVertex2f(-.90, .63);
	glVertex2f(-.87, .63);
	glVertex2f(-.87, .92);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-.87, .92);
	glVertex2f(-.87, .63);
	glVertex2f(-.87, .63);
	glVertex2f(-.87, .92);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.90, .69);
	glVertex2f(-.90, .65);
	glVertex2f(-.87, .65);
	glVertex2f(-.87, .69);
	glEnd();

	//the yellow Book
	glBegin(GL_QUADS);
	glColor3f(.9, .9, .8);
	glVertex2f(-.94, .91);
	glVertex2f(-.97, .64);
	glVertex2f(-.93, .63);
	glVertex2f(-.90, .90);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(.9, .9, .8);
	glVertex2f(-.94, .91);
	glVertex2f(-.97, .64);
	glVertex2f(-.93, .63);
	glVertex2f(-.90, .90);
	glEnd();
}

void blue() {
	// drawing the filled circle 
	glColor3f(0.8f, 0.9f, 1.0f);
	drawFilledCircle(-0.2368618880468, 0.7676786127801, 0.098);
	// drawing the filled circle 
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.2766911703686, 0.8186600941519, 0.028);
	// drawing the filled circle 
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.2049984621894, 0.8250327793234, 0.014);
	glBegin(GL_TRIANGLES);
	glColor3f(0.8f, 0.9f, 1.0f);
	glVertex2f(-0.1779145502106, 0.7151039601154);
	glVertex2f(-0.2750979990757, 0.6736815065008);
	glVertex2f(-0.0902901291028, 0.6529702796935);

	glEnd();

}

//pillow 
void pillow() {

	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.4f, 0.5f);
	glVertex2f(-0.9935846871062, 0.7861267306057);
	glVertex2f(-0.9988353473972, 0.626000934018);
	glVertex2f(-0.7992513544299, 0.5414482891926);
	glVertex2f(-0.7450835304723, 0.68);

	glEnd();
	//line's pillow
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.9935846871062, 0.7861267306057);
	glVertex2f(-0.7450835304723, 0.682);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.49738, 1.0f);
	glVertex2f(-0.7355245027151, 0.5924297705644);

	glEnd();


	//line's inside bed
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.9988353473972, 0.626000934018);
	glVertex2f(-0.79925135442999, 0.54);
	glEnd();

	// drawing the half-filled circle
	glColor3f(0.8f, 0.4f, 0.5f);
	drawHalfFilledCircleAngle(-0.79, 0.61034091904, 0.078f);





	// drawing a hollow half circle
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHalfHollowCircleAngle(-0.79, 0.61034091904, 0.078f, 1.0f);





}


void Maroco2()
{
	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.04f, 0.04f, 40);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller
	////black taller
	//glColor3f(0, 0, 0);
	//glLineWidth(1);
	//drawLineRectangle(-.12f, .01, 0.12f, -0.3f);

	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	   //حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle2(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();

	//////////////////////////////////////////////////////////
	//      up      //
	//////////////////////////////////////////////////////////
	////right hand
	//glColor3f(0, 0, 0);
	//glLineWidth(2);
	//drawLineOval(.13, .05, 0.03, 0.1);
	////oval lift
	//glColor3f(0.977, 0.793, 0.012);
	//glRectd(.13, .05, .11, 0.15);
	//glRectd(.16, .05, .11, 0.15);
	//glColor3f(0, 0, 0);
	//glLineWidth(1);
	//drawLineRectangle(.16, .05, .11, 0.15);
	//glColor3f(0.977, 0.793, 0.012);
	//drawFilleddOval(.13, .05, 0.03, 0.1);
	/////////////////////////////////////////////////////////


	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);


	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();




	//Smile
	glColor3f(0.89f, 0.44f, 0.48f);  // Red color
	// drawHalfFilledCircle1(0.0f, 0.2f, 0.07f);  // Center at (0, 0) with a radius of 0.5
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.04f, 0.180);
	glVertex2f(0.02f, 0.165);
	glVertex2f(0.0f, 0.160);
	glVertex2f(-0.02f, 0.165);
	glVertex2f(-0.04f, 0.180);
	glEnd();

	// drawHalfHollowCircle2(0.0f, 0.2f, 0.07f, 1.0f);

   //the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);



}

void Maroco8()
{

	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(1.0, .6, .6);
	drawHalfHollowCircle2(0.0f, 0.04f, 0.04f, 40);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller
	////black taller
	//glColor3f(0, 0, 0);
	//glLineWidth(1);
	//drawLineRectangle(-.12f, .01, 0.12f, -0.3f);

	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(1.0, .6, .6);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(1.0, .6, .6);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	   //حلق البلوزة
	glColor3f(1.0, .6, .6);
	drawHalfHollowCircle2(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle2(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();


	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(1.0, .6, .6);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(1.0, .6, .6);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);


	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();



	//face
   // Circle for face
	glColor3f(0.89f, 0.44f, 0.48f);  // Red color
	drawFilledCircle(0, 0.2, .02);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.2, .02);



	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);


}
void BackGroundOfMaroco8()
{
	BackGround();

	//bin
	glBegin(GL_QUADS);
	glColor3f(.6f, .0f, .5f);
	glVertex2f(0.9694808458089, -0.8015971642585);//
	glVertex2f(0.9778470840522, -0.4995096745197);
	glVertex2f(0.829145745826, -0.4987789450179);
	glVertex2f(0.8301149173128, -0.8030072748335);
	glEnd();
	//lines bin
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.9694808458089, -0.8015971642585);//
	glVertex2f(0.9778470840522, -0.4995096745197);
	glEnd(); glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.829145745826, -0.4987789450179);
	glVertex2f(0.8301149173128, -0.8030072748335);
	glEnd(); glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.9694808458089, -0.8015971642585);//
	glVertex2f(0.8301149173128, -0.8030072748335);
	glEnd();
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.931, -0.542, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.961, -0.523, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.971, -0.503, 0.020);



	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.901, -0.547, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.87, -0.54, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.845, -0.515, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.837, -0.49, 0.020);
	/////////////////////////////////////
	//bin balls
	glColor3f(.9f, .8f, .1f);
	drawFilledCircle(0.92, -0.60, 0.036);
	//bin balls
	glColor3f(1.0f, .4f, .1f);
	drawFilledCircle(0.87, -0.76, 0.040);
	//bin balls
	glColor3f(.1, .0f, .1f);
	drawFilledCircle(0.904, -0.47, 0.080);

	//behind wall
	glBegin(GL_QUADS);
	glColor3f(.8f, .6f, .6f);
	glVertex2f(0.7, 0.9);//
	glVertex2f(0.7, 1);
	glVertex2f(0.1, 1);
	glVertex2f(0.1, 0.9);
	glEnd();

	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.2, 1, 0.026);
	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.45, 0.98, 0.060);
	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.55, 0.98, 0.05);
	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.64, 0.98, 0.060);
	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.4, 0.98, 0.026);
	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.35, 0.98, 0.026);
	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.30, 0.98, 0.026);
	//balls
	glColor3f(.9f, .5f, .2f);
	drawFilledCircle(0.25, 0.98, 0.026);

	//table
	glBegin(GL_QUADS);
	glColor3f(1.0f, .9f, .4f);
	glVertex2f(-1, 0.8);
	glVertex2f(0.0784578330941, 1.0077154350901);//
	glVertex2f(0.7972698781947, 0.8816080587567);
	glVertex2f(-1, -1);
	glEnd();


	//paper

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.2, 0.2);
	glVertex2f(-0.6, 0.6);//
	glVertex2f(-0.9996655117425, 0.2895464203294);
	glVertex2f(-0.6, -0.2);
	glEnd();

	//eraser table
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.4125413713679, 0.5550759028981);
	glVertex2f(-0.4179783700881, 0.6040088913799);//
	glVertex2f(-0.5, 0.6);
	glVertex2f(-0.4922840192642, 0.5442019054577);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, 0.5550759028981);
	glVertex2f(-0.4179783700881, 0.6040088913799);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4179783700881, 0.6040088913799);//
	glVertex2f(-0.497, 0.6);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, 0.5550759028981);
	glVertex2f(-0.49, 0.5442019054577);
	glEnd();

	//eraser lines inside
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.431622879304, 0.5706971373495);
	glVertex2f(-0.4660764184768, 0.5718690264371);
	glEnd();

	//eraser
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.480, 0.576, 0.026);
	//eraser
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, 0.5964604694799);
	glVertex2f(-0.5000, 0.5832063155461);
	glVertex2f(-0.4981625811559, 0.5748504358921);
	glVertex2f(-0.4877897650338, 0.5696640278311);
	glEnd();
	//eraser2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, 0.5964604694799);
	glVertex2f(-0.5, 0.59);
	glVertex2f(-0.5036371229982, 0.5774436399227);
	glVertex2f(-0.503348989217, 0.5670708238005);
	glVertex2f(-0.4975863135936, 0.5555454725537);
	glVertex2f(-0.4889423001585, 0.5494946631492);
	glEnd();

	//leg table
	glBegin(GL_QUADS);
	glColor3f(0.9f, .5f, .0f);
	glVertex2f(0.7600000176618, -1.0156425057988);
	glVertex2f(0.7655959505241, 0.84);//
	glVertex2f(0.736380861007, 0.82);
	glVertex2f(0.7339836501206, -1.015543737134);
	glEnd();





	//leg table lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7600000176618, -1.0156425057988);
	glVertex2f(0.7655959505241, 0.84);//
	glEnd();



	//leg table lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.736380861007, 0.82);
	glVertex2f(0.7339836501206, -1.015543737134);
	glEnd();

	//Chair
	glBegin(GL_QUADS);
	glColor3f(0.863281250, 0.34375, 0.171875);
	glVertex2f(0.7157683680159, -1.0060008210778);
	glVertex2f(0.7157683680159, 0.10);//
	glColor3f(0.6171875, 0.23828125, 0.10546875);
	glVertex2f(0, 0.2);
	glVertex2f(0, -1);
	glEnd();

	//lines chair

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7157683680159, -1.0060008210778);
	glVertex2f(0.7157683680159, 0.10);//
	glEnd();

	//lines chair

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0, 0.2);
	glVertex2f(0, -1);
	glEnd();

	//lines chair

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7157683680159, 0.10);//
	glVertex2f(0, 0.2);
	glEnd();


	//lines chair
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.6568687524489, 0.019);//
	glVertex2f(0, 0.1);
	glEnd();


	//lines chair2
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.6568687524489, 0.019);//
	glVertex2f(0.6545709223759, -1.0);
	glEnd();



	//lines chair2
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7157683680159, 0.10);//
	glVertex2f(0.6568687524489, 0.019);
	glEnd();

	/////wall lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7, 1);
	glVertex2f(0.7, 0.9);
	glEnd();


	/////wall lines2
	glBegin(GL_LINES);
	glLineWidth(10.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7972698781947, 0.8816080587567);
	glVertex2f(1.0041912283188, 0.8667312138652);
	glEnd();



	/////wall lines22
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7669918060162, 0.8470651568574);
	glVertex2f(1.4, 0.8);
	glEnd();



	// wall edge
	glBegin(GL_QUADS);
	glColor3f(0.3f, .0f, .3f);
	glVertex2f(1.4, 0.8);
	glVertex2f(1.0041912283188, 0.8667312138652);//
	glVertex2f(0.7972698781947, 0.8816080587567);
	glVertex2f(0.7669918060162, 0.8470651568574);
	glEnd();


	//line inside table

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7475902985003, 0.89);
	glVertex2f(-0.9960926472632, -0.9051327735175);
	glEnd();



	//lines table

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7972698781947, 0.8816080587567);
	glVertex2f(-1, -1);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-1, 0.8);
	glVertex2f(0.0784578330941, 1.0077154350901);//
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.0784578330941, 1.0077154350901);//
	glVertex2f(0.7972698781947, 0.8816080587567);
	glEnd();

}


void BackGroundOfMaroco2()
{

	BackGround();

	//bed
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-1, 1);
	glVertex2f(0.7320928706902, 1.0061397258173);
	glVertex2f(1.2, -1);//
	glVertex2f(-1, -1);

	glEnd();
	glColor3f(1.0, 0.0, 0.0); // Red color



	//lines's bed
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7320928706902, 1.0061397258173);
	glVertex2f(1.2, -1);//

	glEnd();
	//bed
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-1, 1);
	glVertex2f(-0.5, 1.0f);
	glVertex2f(-0.71, 0.61);
	glVertex2f(-0.99, 0.78);

	glEnd();

	//pillow

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.51, 0.78);
	glVertex2f(0.2, 0.9);//
	glEnd();

	//pillow

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);

	glVertex2f(0.2, 0.9);//
	glVertex2f(0.260, 0.3);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.130, .2f);
	glVertex2f(0.260, 0.3);

	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.51, 0.786);
	glVertex2f(-0.65, 0.646);

	glEnd();
	//blanket 
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(1, -1.0);
	glVertex2f(1, 0.040);
	glVertex2f(-1.0, 0.040);
	glVertex2f(-1.0, -1.0);
	glEnd();
	glColor4f(.6f, 0.6f, 0.6f, 0.190);
	drawFilledCircle(-0.20, 0.34, .120);

	glColor4f(.6f, 0.6f, 0.6f, 0.190);
	drawFilledCircle(0.020, 0.36, .120);

}



void display2()
{



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer
	
	glEnable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	BackGroundOfMaroco2();



	//Maroco
	glPushMatrix();
	glTranslatef(-0.1, 0.1, 0.0);
	glScalef(1.2, 1.2, 0.0);
	Maroco8();
	glPopMatrix();

	//eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.260, 0.0);
	glRotatef(30, 0.0, 0.0, 1);
	drawHalfHollowCircleMaysaa2(-0.1f, 0.3f, 0.03f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(-0.019, 0.160, 0.0);
	glRotatef(-30, 0.0, 0.0, 1);
	drawHalfHollowCircleMaysaa2(-0.1f, 0.3f, 0.03f, 1.0f);
	glPopMatrix();


	//pillow
	glPushMatrix();

	glScalef(1., 1.8, 1.0);
	glTranslatef(-0.67, -0.82, 0.0);
	glRotatef(-59.0, .0, .0, 1.0);

	pillow();
	glPopMatrix();


	// //blue
	glPushMatrix();
	glTranslatef(0.0, -0.240, 0.0);
	glScalef(value01, 1.0, 1.0);
	blue();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, myTexture1);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);

	glVertex2f(1, -1.0);

	glTexCoord2f(1.0, 0.0);
	glVertex2f(1, 0.040);

	glTexCoord2f(1.0, 1.0);
	glVertex2f(-1.0, 0.040);

	glTexCoord2f(0.0, 1.0);
	glVertex2f(-1.0, -1.0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glFlush();
	glutSwapBuffers();




}


void display8()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glPushMatrix();
	glScalef(1.0, 1.0, 0.0);
	glTranslatef(-0.1, 0.17, 0.0);
	TheBooks();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 1.0, 0.0);
	glTranslatef(0.1, 0.17, 0.0);
	TheBooks();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.0, 1.0, 0.0);
	glTranslatef(0.3, 0.17, 0.0);
	TheBooks();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, 0.17, 0.0);
	TheBooks();
	glPopMatrix();

	glPushMatrix();
	glScalef(1.4, 1.0, 0.0);
	glTranslatef(0.7, 0.17, 0.0);
	TheBooks();
	glPopMatrix();

	//Background Studying
	BackGroundOfMaroco8();



	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, myTexture2);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);  // Corresponds to (-0.2, 0.2)
	glVertex2f(-0.2, 0.2);

	glTexCoord2f(1.0, 0.0);  // Corresponds to (-0.6, 0.6)
	glVertex2f(-0.6, 0.6);

	glTexCoord2f(1.0, 1.0);  // Corresponds to (-0.9996655117425, 0.2895464203294)
	glVertex2f(-0.9996655117425, 0.2895464203294);

	glTexCoord2f(0.0, 1.0);  // Corresponds to (-0.6, -0.2)
	glVertex2f(-0.6, -0.2);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	//pencil
	glPushMatrix();
	glTranslatef(-0.9, -0.5, 0.0);
	glRotatef(180.0, 0.0, 0.0, 0.0);
	drawPencil();
	glPopMatrix();

	//Maroco
	glPushMatrix();
	glScalef(2.0, 2.0, 0.0);
	glTranslatef(0.06, -0.230, 0.0);
	//Maroco();
	Maroco2();
	glPopMatrix();

	//////eyes
	//right eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.10, 0.0, 0.0);
	glRotatef(-30, 0.0, 0.0, 1);
	drawHalfHollowCircleMaysaa2(0.1f, 0.3f, 0.03f, 1.0f);
	glPopMatrix();
	//left eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.15, 0.0, 0.0);
	glRotatef(30, 0.0, 0.0, 1);
	drawHalfHollowCircleMaysaa2(-0.1f, 0.3f, 0.03f, 1.0f);
	glPopMatrix();

	


	glDisable(GL_BLEND);
	glFlush();
	glutSwapBuffers();



}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.3 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////


void ReadingBG3()
{
	

	glBegin(GL_QUADS);
	glColor3f(0.95703125f, 0.8984375f, 0.64453125f);
	glVertex2f(1.0, 1.0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, -1.0);
	glVertex2f(-1.0, 1.0);
	glEnd();

	glLineWidth(1);

	//floor

	glBegin(GL_QUADS);
	glColor3f(0.73046875, 0.59765625, 0.31640625);
	glColor3f(0.77734375, 0.6796875, 0.39453125);
	glVertex2f(0, 0.1);
	glVertex2f(-1, 0.1);
	glVertex2f(-1, 1);
	glVertex2f(0, 1);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-1, 0.24);
	glVertex2f(-0.15, 0.24);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1, 0.34);
	glVertex2f(-0.15, 0.34);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1, 0.44);
	glVertex2f(-0.15, 0.44);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1, 0.54);
	glVertex2f(-0.15, 0.54);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1, 0.64);
	glVertex2f(-0.15, 0.64);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1, 0.74);
	glVertex2f(-0.15, 0.74);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1, 0.84);
	glVertex2f(-0.15, 0.84);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1, 0.94);
	glVertex2f(-0.15, 0.94);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0, 0.1);
	glVertex2f(-1, 0.1);
	glEnd();
	//door
	glColor3f(1, 1, 1);
	glRectd(1, 1, -0.14, 0.14);
	glColor3f(0.73046875, 0.6015625, 0.30078125);
	glBegin(GL_TRIANGLES);
	glVertex2f(1, 0.78);
	glVertex2f(-0.15, 0.895);
	glVertex2f(-0.15, 0.68);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(1, 0.44);
	glVertex2f(-0.15, 0.65);
	glVertex2f(-0.15, 0.24);
	glEnd();
	glColor3f(0.39453125, 0.34375, 0.28515625);
	glRectd(-0.21, 0.06, -0.14, 1);
	glRectd(-0.14, 0.14, 1, 0.06);




	//مخدة
	glColor3f(0.79296875, 0.88671875, 0.89453125);
	drawFilledCircle(0.278, -0.2, 0.1);
	drawFilledCircle(0.6, -0.2, 0.1);
	glColor3f(0, 0, 0);
	drawHollowCircle(0.278, -0.2, 0.1);
	drawHollowCircle(0.6, -0.2, 0.1);

	glColor3f(0.79296875, 0.88671875, 0.89453125);
	glRectd(0.7, -0.462, 0.18, -0.18);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0.7, -0.45);
	glVertex2f(0.7, -0.18);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0.18, -0.45);
	glVertex2f(0.18, -0.18);
	glEnd();



	//table
	glColor3f(0.6328125, 0.39453125, 0.2109375);
	glRectd(0.3, -0.5, 1, -1);
	glColor3f(0.80078125, 0.63671875, 0.34765625);
	glRectd(0.252, -0.465, 1, -0.5);
	glRectd(0.252, -1, 0.3, -0.50);
	glPointSize(4.0f);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(1, -0.465);
	glVertex2f(0.252, -0.465);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0.252, -0.48);
	glVertex2f(0.252, -1);
	glEnd();

	//Dish
	glColor3f(0.691406251, 0.77734375, 0.73828125);
	drawFilledCircle(0.65, -0.7, 0.1);
	glColor3f(0, 0, 0);
	drawHollowCircle(0.65, -0.7, 0.1);
	drawHollowCircle(0.65, -0.7, 0.07);


	//food


	glColor3f(0, 0, 0);

	drawLineOval(0.4, -0.67, 0.02, 0.028);
	drawLineOval(0.41, -0.671, 0.02, 0.028);
	glBegin(GL_QUADS);
	glColor3f(0.8046875, 0.734375, 0.796875);
	glVertex2f(0.4, -0.63);
	glVertex2f(0.45, -0.63);
	glColor3f(0.42578125, 0.30859375, 0.41015625);
	glVertex2f(0.45, -0.73);
	glVertex2f(0.4, -0.73);
	glEnd();
	glColor3f(0, 0, 0);
	drawLineRectangle(0.4, -0.63, 0.45, -0.73);
	glColor3f(0.8046875, 0.734375, 0.7968750);
	drawFilleddOval(0.425, -0.63, 0.025, 0.015);
	glColor3f(0.80078125, 0.63671875, 0.347656255);
	drawFilleddOval(0.425, -0.63, 0.015, 0.01);
	glColor3f(0, 0, 0);
	drawLineOval(0.425, -0.63, 0.025, 0.015);


	glBegin(GL_QUADS);
	glColor3f(0.80078125, 0.63671875, 0.347656255);
	glVertex2f(0.6, -0.63);
	glVertex2f(0.6, -0.72);
	glColor3f(0.81640625, 0.77734375, 0.71484375);
	glVertex2f(0.64, -0.76);
	glVertex2f(0.64, -0.63);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.6, -0.63);
	glVertex2f(0.6, -0.72);
	glVertex2f(0.64, -0.76);
	glVertex2f(0.64, -0.63);
	glEnd();



	glBegin(GL_QUADS);
	glColor3f(0.80078125, 0.63671875, 0.347656255);
	glVertex2f(0.64, -0.62);
	glVertex2f(0.64, -0.75);
	glColor3f(0.81640625, 0.77734375, 0.71484375);
	glVertex2f(0.68, -0.599);
	glVertex2f(0.68, -0.66);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.64, -0.62);
	glVertex2f(0.64, -0.75);
	glVertex2f(0.68, -0.66);
	glVertex2f(0.68, -0.599);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.80078125, 0.63671875, 0.347656255);
	glVertex2f(0.68, -0.6);
	glColor3f(0.81640625, 0.77734375, 0.71484375);
	glVertex2f(0.64, -0.69);
	glVertex2f(0.6, -0.63);
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.68, -0.6);
	glVertex2f(0.64, -0.69);
	glVertex2f(0.6, -0.63);
	glEnd();

	glColor3f(1, 0, 0);
	drawFilleddOval(0.62, -0.64, 0.01, 0.02);
	glColor3f(0, 0, 0);
	drawLineOval(0.62, -0.64, 0.01, 0.02);

	//book

	glBegin(GL_QUADS);
	glColor3f(0.8046875, 0.734375, 0.796875);
	glVertex2f(-0.4, -0.73);
	glVertex2f(-0.4, -0.75);
	glColor3f(0.42578125, 0.30859375, 0.41015625);
	glVertex2f(-0.5, -0.76);
	glVertex2f(-0.5, -0.81);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-0.6, -0.782);
	glVertex2f(-0.6, -0.76);
	glVertex2f(-0.5, -0.76);
	glVertex2f(-0.5, -0.81);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4, -0.73);
	glVertex2f(-0.5, -0.76);
	glVertex2f(-0.5, -0.81);
	glVertex2f(-0.4, -0.75);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.6, -0.782);
	glVertex2f(-0.6, -0.76);
	glVertex2f(-0.5, -0.76);
	glVertex2f(-0.5, -0.81);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.8046875, 0.734375, 0.796875);
	glVertex2f(-0.4, -0.73);
	glVertex2f(-0.5, -0.7);
	glColor3f(0.42578125, 0.30859375, 0.41015625);
	glVertex2f(-0.6, -0.76);
	glVertex2f(-0.5, -0.79);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4, -0.73);
	glVertex2f(-0.5, -0.7);
	glVertex2f(-0.6, -0.76);
	glVertex2f(-0.5, -0.79);
	glEnd();


	///////////////////////



}

void Maroco3()
{   
	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller
	//black taller
	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.12f, .01, 0.12f, -0.3f);

	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	//حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();

	//////////////////////////////////////////////////////////
	//      up      //
	//////////////////////////////////////////////////////////
	////right hand
	//glColor3f(0, 0, 0);
	//glLineWidth(2);
	//drawLineOval(.13, .05, 0.03, 0.1);
	////oval lift
	//glColor3f(0.977, 0.793, 0.012);
	//glRectd(.13, .05, .11, 0.15);
	//glRectd(.16, .05, .11, 0.15);
	//glColor3f(0, 0, 0);
	//glLineWidth(1);
	//drawLineRectangle(.16, .05, .11, 0.15);
	//glColor3f(0.977, 0.793, 0.012);
	//drawFilleddOval(.13, .05, 0.03, 0.1);
	/////////////////////////////////////////////////////////


	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);
	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();

	//eyses
	glLineWidth(1);
	//white
	glColor3f(1, 1, 1);
	drawFilledOval(.1, .3, .06);
	drawFilledOval(-.1, .3, .06);
	//black
	glColor3f(0, 0, 0);
	drawOval(.1, .3, .06);
	drawOval(-.1, .3, .06);
	//بؤبؤ
	drawFilledCircle(.1, .3, .01);
	drawFilledCircle(-.1, .3, .01);

	//Smile
	glColor3f(0.89f, 0.44f, 0.48f);  // Red color
	drawHalfFilledCircle1(0.0f, 0.2f, 0.07f);  // Center at (0, 0) with a radius of 0.5
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	drawHalfHollowCircle(0.0f, 0.2f, 0.07f, 1.0f);

	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);


	
	
	

}

void display3()
{
	glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer
	glEnable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ReadingBG3();
	glPushMatrix();
	glTranslatef(0.45, -0.161, 0.0);
	Maroco3();
	glPopMatrix();
	////////////////////

	glDisable(GL_BLEND);
	
	glFlush();
	glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.4 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////






void Maroco4()
{

	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller
	//black taller
	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.12f, .01, 0.12f, -0.3f);

	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	//حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();



	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);
	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();

	//eyses
	glLineWidth(1);
	//white
	glColor3f(1, 1, 1);
	drawFilledOval(.1, .3, .06);
	drawFilledOval(-.1, .3, .06);
	//black
	glColor3f(0, 0, 0);
	drawOval(.1, .3, .06);
	drawOval(-.1, .3, .06);
	//بؤبؤ
	drawFilledCircle(.1, .3, .01);
	drawFilledCircle(-.1, .3, .01);

	//Smile
	glColor3f(0.0f, 0.0f, 0.0f);  // Red color
	drawHalfHollowCircle(0.0f, 0.15f, -0.07f, 1.0f);
	glEnd();
	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);




}

void BackGroundOfMaroco4() {
	/*
	* start BackGround
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);

	glColor3f(0.6745f, 0.8039f, 0.6275f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(0.7f, 0.8f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
	/*
	end BackGround
	*/

	/* start drawLockers
	*/


	// Set color
	glColor3f(0.363137f, 0.270588f, 0.152941f);
	// Draw the Lockers
	glRectf(-1.0f, 0.4f, 1.0f, 0.3f);

	// Set color
	glColor3f(0.0f, 0.0f, 0.0f);

	// Set brown color
	glColor3f(0.631373f, 0.431373f, 0.207843f);
	glRectf(-1.0f, 1.0f, 1.0f, 0.4f);

	// Set black color
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	// Draw the frame lines
	glBegin(GL_LINE_LOOP);

	glVertex2f(-1.0f, 1.0f);  // Top left corner
	glVertex2f(1.0f, 1.0f);   // Top right corner
	glVertex2f(1.0f, 0.4f);   // Bottom right corner
	glVertex2f(-1.0f, 0.4f);  // Bottom left corner

	// Draw a line under the rectangle
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glVertex2f(-1.0f, 0.3f);   // Bottom left corner
	glVertex2f(1.0f, 0.3f);    // Bottom right corner



	// Draw the line
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glVertex2f(0.0f, 1.0f);  // Start point
	glVertex2f(0.0f, 0.4f);   // End point

	glVertex2f(0.5f, 1.0f);  // Start point
	glVertex2f(0.5f, 0.4f);   // End point

	glVertex2f(-0.5f, 1.0f);  // Start point
	glVertex2f(-0.5f, 0.4f);   // End point



	glEnd();
	/*
	* end drawLockers
	*/

	/*
	* start table
	*/
	glColor3f(0.819608f, 0.729412f, 0.431373f);
	glRectf(-0.8f, -1.0f, 0.8f, -0.5f); // 

	// Set color
	glColor3f(0.0f, 0.0f, 0.0f);

	// Draw the line
	glBegin(GL_LINES);

	glVertex2f(-0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -0.5f);   // End point

	glVertex2f(0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -1.0f);   // End point

	glVertex2f(-0.8f, -0.5f); // Start point reflected
	glVertex2f(-0.8f, -1.0f); // End point reflected

	glEnd();
	/*
	* end table
	*/

	/* start drawItemsOnTable
	*/
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-0.2f, -1.0f, 0.2f, -0.6f); // Draw Test paper

	// Call drawHandDrawLine for the first line
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHandDrawLine(-0.2f, -0.9f, 0.2f, -0.9f);
	drawHandDrawLine(-0.2f, -0.8f, 0.2f, -0.8f);

	// Draw frame
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, -1.0f);
	glVertex2f(0.2f, -1.0f);
	glVertex2f(0.2f, -0.6f);
	glVertex2f(-0.2f, -0.6f);
	glEnd();

	// draw Pencil eraser

	glColor3f(1.0f, 0.50f, 0.50f);
	glRectf(-0.4f, -0.8f, -0.39f, -0.57f);  //eraser

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);  // Bottom-left vertex
	glVertex2f(-0.4f, -0.57f); // Top-left vertex
	glVertex2f(-0.39f, -0.57f); // Top-right vertex
	glVertex2f(-0.39f, -0.8f);  // Bottom-right vertex
	glEnd();

	// Draw pencil
	glColor3f(0.2745, 0.5529, 0.7961);
	glRectf(-0.4f, -0.8f, -0.39f, -0.6f);


	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.395f, -0.83f);
	glEnd();

	// Draw black lines around the pencil
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.39f, -0.6f);
	glVertex2f(-0.395f, -0.83f);
	glVertex2f(-0.395f, -0.6f);
	glEnd();




	glEnd();

	/*
	* end drawItemsOnTable
	*/

	/*
	* start eraser
	*/


	//eraser
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.480, -0.576, 0.026);
	glColor3f(1.0f, 0.50f, 0.50f); // Set color to eraser color
	glRectf(-0.48f, -0.55f, -0.419f, -0.60f);  //eraser


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.4179783700881, -0.6040088913799);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4179783700881, -0.6040088913799);//
	glVertex2f(-0.497, -0.6);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.49, -0.5442019054577);
	glEnd();

	//eraser lines inside
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.431622879304, -0.5706971373495);
	glVertex2f(-0.4660764184768, -0.5718690264371);
	glEnd();


	//eraser
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5000, -0.5832063155461);
	glVertex2f(-0.4981625811559, -0.5748504358921);
	glVertex2f(-0.4877897650338, -0.5696640278311);
	glEnd();
	//eraser2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5, -0.59);
	glVertex2f(-0.5036371229982, -0.5774436399227);
	glVertex2f(-0.503348989217, -0.5670708238005);
	glVertex2f(-0.4975863135936, -0.5555454725537);
	glVertex2f(-0.4889423001585, -0.5494946631492);

	glEnd();

	/*
	end eraser
	*/



	/*
	* start chair
	*/
	glColor3f(0.9f, 0.5f, 0.2f); // Set the fill color to the desired value
	glRectf(-0.2f, 0.1f, 0.2f, -0.5f); // Draw the filled rectangle

	glColor3f(0.0f, 0.0f, 0.0f); // Set the line color to black
	glLineWidth(2.0f); // Set the line width to 1 pixel (adjust as needed)

	// Draw lines around the rectangle
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, 0.1f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.2f, -0.5f);
	glVertex2f(-0.2f, -0.5f);
	glEnd();
	/*
	* end chair
	*/




}

void display4()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	BackGroundOfMaroco4();
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	Maroco4();
	glPopMatrix();
	glDisable(GL_BLEND);
	glFlush();
	glutSwapBuffers();
}


//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.7 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void Maroco7()
{
	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller
	//black taller
	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.12f, .01, 0.12f, -0.3f);

	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	//حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();




	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);
	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();

	//eyses
	glLineWidth(1);
	//white
	glColor3f(1, 1, 1);
	drawFilledOval(.1, .3, .06);
	drawFilledOval(-.1, .3, .06);
	//black
	glColor3f(0, 0, 0);
	drawOval(.1, .3, .06);
	drawOval(-.1, .3, .06);
	//بؤبؤ
	drawFilledCircle(.1, .3, .01);
	drawFilledCircle(-.1, .3, .01);

	//Smile

	glColor3f(0.89f, 0.44f, 0.48f);

	drawFilledOval(0.0, 0.17, .04);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(0.0f);
	drawOval(0.0, 0.17, .04);








	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);



}






void BackGroundOfMaroco7() {

	/*
	* start BackGround
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glBegin(GL_QUADS);

	glColor3f(0.6745f, 0.8039f, 0.6275f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(0.7f, 0.8f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);



	glEnd();

	/*
	* end  BackGround
	*/


	/*
	* start TheBookShelf
	*/

	//the background
	glBegin(GL_QUADS);
	glColor3f(.9, .8, .8);
	glVertex2f(-3, 2);
	glVertex2f(-3, -2);
	glVertex2f(3, -2);
	glVertex2f(3, 2);
	glEnd();

	// the book shelf
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.7, 0.2);
	glVertex2f(-1, 1);
	glVertex2f(-1, .6);
	glVertex2f(-.6, .6);
	glVertex2f(-.6, 1);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-1, 1);
	glVertex2f(-1, .6);
	glVertex2f(-.6, .6);
	glVertex2f(-.6, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.4, 0.7, 0.2);
	glVertex2f(-1, .6);
	glVertex2f(-1, .57);
	glVertex2f(-.62, .57);
	glVertex2f(-.62, .6);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-1, .6);
	glVertex2f(-1, .57);
	glVertex2f(-.62, .57);
	glVertex2f(-.62, .6);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.97, .97);
	glVertex2f(-.97, .63);
	glVertex2f(-.64, .63);
	glVertex2f(-.64, .97);
	glEnd();

	// end TheBookShelf

	/*
	start the Books
	*/

	//the Books
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.5, .7);
	glVertex2f(-.82, .92);
	glVertex2f(-.82, .63);
	glVertex2f(-.66, .63);
	glVertex2f(-.66, .92);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-.82, .92);
	glVertex2f(-.82, .63);
	glVertex2f(-.66, .63);
	glVertex2f(-.66, .92);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-.7, .92);
	glVertex2f(-.7, .63);
	glVertex2f(-.74, .92);
	glVertex2f(-.74, .63);
	glVertex2f(-.78, .92);
	glVertex2f(-.78, .63);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.82, .69);
	glVertex2f(-.82, .65);
	glVertex2f(-.66, .65);
	glVertex2f(-.66, .69);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.82, .73);
	glVertex2f(-.82, .71);
	glVertex2f(-.66, .71);
	glVertex2f(-.66, .73);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.6, 0.5, .7);
	glVertex2f(-.87, .93);
	glVertex2f(-.87, .63);
	glVertex2f(-.82, .63);
	glVertex2f(-.82, .93);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-.87, .93);
	glVertex2f(-.87, .63);
	glVertex2f(-.82, .63);
	glVertex2f(-.82, .93);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-.85, .90);
	glVertex2f(-.85, .80);
	glVertex2f(-.84, .80);
	glVertex2f(-.84, .90);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-.87, .92);
	glVertex2f(-.87, .91);
	glVertex2f(-.82, .91);
	glVertex2f(-.82, .92);
	glEnd();

	//the Blue Book
	glBegin(GL_QUADS);
	glColor3f(0.56, 0.74, .9);
	glVertex2f(-.90, .92);
	glVertex2f(-.90, .63);
	glVertex2f(-.87, .63);
	glVertex2f(-.87, .92);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex2f(-.87, .92);
	glVertex2f(-.87, .63);
	glVertex2f(-.87, .63);
	glVertex2f(-.87, .92);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-.90, .69);
	glVertex2f(-.90, .65);
	glVertex2f(-.87, .65);
	glVertex2f(-.87, .69);
	glEnd();

	//the yellow Book
	glBegin(GL_QUADS);
	glColor3f(.9, .9, .8);
	glVertex2f(-.94, .91);
	glVertex2f(-.97, .64);
	glVertex2f(-.93, .63);
	glVertex2f(-.90, .90);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(.9, .9, .8);
	glVertex2f(-.94, .91);
	glVertex2f(-.97, .64);
	glVertex2f(-.93, .63);
	glVertex2f(-.90, .90);
	glEnd();


	/*
	end the Books
	*/

	/*
	* start table
	*/

	glColor3f(0.819608f, 0.729412f, 0.431373f);
	glRectf(-0.8f, -1.0f, 0.8f, -0.5f); // Adjusted the y-coordinate for the table

	// Set color
	glColor3f(0.0f, 0.0f, 0.0f);

	// Draw the line
	glBegin(GL_LINES);

	glVertex2f(-0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -0.5f);   // End point

	glVertex2f(0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -1.0f);   // End point

	glVertex2f(-0.8f, -0.5f); // Start point reflected
	glVertex2f(-0.8f, -1.0f); // End point reflected

	glEnd();
	glColor3f(0.6196f, 0.1882f, 0.2824f);
	glRectf(-1.0f, 0.1f, 1.0f, 0.2f); //rec backgound



	/*
	* end table
	*/


	/*
	* start TableItems
	*/
	// Draw  page 
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-0.2f, -1.0f, 0.2f, -0.6f);



	// Draw edges around the paper
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, -1.0f); // Bottom-left
	glVertex2f(-0.2f, -0.6f); // Top-left
	glVertex2f(0.2f, -0.6f);  // Top-right
	glVertex2f(0.2f, -1.0f);  // Bottom-right
	glEnd();

	// Draw lines along the edges of the sheet
	glColor3f(0.0f, 0.0f, 0.0f); // Black color

	glBegin(GL_LINES);
	glVertex2f(-0.2f, -0.6f); // Bottom-left to Top-left
	glVertex2f(0.2f, -0.6f);

	glVertex2f(-0.2f, -1.0f); // Bottom-left to Bottom-right
	glVertex2f(0.2f, -1.0f);

	glVertex2f(-0.2f, -1.0f); // Bottom-right to Top-right
	glVertex2f(-0.2f, -0.6f);

	glVertex2f(0.2f, -1.0f); // Bottom-right to Top-right
	glVertex2f(0.2f, -0.6f);
	glEnd();


	drawHandDrawLine(-0.2f, -0.9f, 0.2f, -0.9f);
	drawHandDrawLine(-0.2f, -0.8f, 0.2f, -0.8f);
	drawHandDrawLine(-0.2f, -0.7f, 0.2f, -0.7f);


	// draw Pencil eraser

	glColor3f(1.0f, 0.50f, 0.50f);
	glRectf(-0.4f, -0.8f, -0.39f, -0.57f);  //eraser

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);  // Bottom-left vertex
	glVertex2f(-0.4f, -0.57f); // Top-left vertex
	glVertex2f(-0.39f, -0.57f); // Top-right vertex
	glVertex2f(-0.39f, -0.8f);  // Bottom-right vertex
	glEnd();

	// Draw pencil
	glColor3f(0.2f, 0.5f, 0.4f);
	glRectf(-0.4f, -0.8f, -0.39f, -0.6f);


	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.395f, -0.83f);
	glEnd();

	// Draw black lines around the pencil
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.39f, -0.6f);
	glVertex2f(-0.395f, -0.83f);
	glVertex2f(-0.395f, -0.6f);
	glEnd();




	glEnd();

	/*
	* end TableItems
	*/


	/*
	* start chair
	*/

	glColor3f(0.9f, 0.5f, 0.2f); // Set the fill color to the desired value
	glRectf(-0.2f, 0.1f, 0.2f, -0.5f); // Draw the filled rectangle

	glColor3f(0.0f, 0.0f, 0.0f); // Set the line color to black
	glLineWidth(2.0f); // Set the line width to 1 pixel (adjust as needed)

	// Draw lines around the rectangle
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, 0.1f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.2f, -0.5f);
	glVertex2f(-0.2f, -0.5f);
	glEnd();

	/*
	* end chair
	*/

	/*
	* start lamp
	*/
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0, 0.0f);
	glVertex2f(0.4917573843902f, 0.5945160136161f);
	glVertex2f(0.4917573843902f, 0.0954387940062f);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0.5242285082364f, 0.5903283940251f);
	glVertex2f(0.5246375324916f, 0.4021479089211f);

	glEnd();



	glBegin(GL_TRIANGLES);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw triangles
	glBegin(GL_TRIANGLES);
	glColor3f(0.392f, 0.780f, 0.761f);
	glVertex2f(0.4920509790283f, 0.6945160136161f);
	glVertex2f(0.4182684390304f, 0.5066395687206f);
	glVertex2f(0.5692665598833f, 0.5080507661117f);
	glEnd();

	// Draw black lines
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.4920509790283f, 0.6945160136161f);
	glVertex2f(0.4182684390304f, 0.5066395687206f);
	glVertex2f(0.5692665598833f, 0.5080507661117f);
	glEnd();






	glEnd();
	glColor3f(0.0f, 0.0, 0.0f);
	drawFilledCircl1(0.49f, 0.093f, .02);
	glEnd();

	/*
	* end lamp
	*/
}

void display7()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();



	BackGroundOfMaroco7();
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	Maroco7();
	glPopMatrix();

	glDisable(GL_BLEND);
	glFlush();
	glutSwapBuffers();

}


//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.10 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////



void Maroco10()
{
	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.04f, 0.04f, 40);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller


	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	   //حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle2(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();



	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);

	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();


	//eyses
	glColor3f(0.89f, 0.44f, 0.48f);  // Red color
	glLineWidth(2.0f);
	// drawHalfFilledCircle1(0.0f, 0.2f, 0.07f);  // Center at (0, 0) with a radius of 0.5
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.07f, 0.325f);// يسار
	glVertex2f(0.1f, 0.380f); // نص
	glVertex2f(0.13f, 0.325f);// يمين
	glEnd();
	///
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);  // Red color
	glLineWidth(2.0f);
	glVertex2f(-0.07f, 0.325f);// يسار
	glVertex2f(-0.1f, 0.380f); // نص
	glVertex2f(-0.13f, 0.325f);// يمين
	glEnd();





	//Smile
	glColor3f(0.89f, 0.44f, 0.48f);  // Red color
	// drawHalfFilledCircle1(0.0f, 0.2f, 0.07f);  // Center at (0, 0) with a radius of 0.5
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.04f, 0.180);
	glVertex2f(0.02f, 0.165);
	glVertex2f(0.0f, 0.160);
	glVertex2f(-0.02f, 0.165);
	glVertex2f(-0.04f, 0.180);
	glEnd();

	// drawHalfHollowCircle2(0.0f, 0.2f, 0.07f, 1.0f);



	glEnd();



	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);



}



void BackGroundOfMaroco10() {

	/*
	* start BackGround
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);

	glColor3f(0.6745f, 0.8039f, 0.6275f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(0.7f, 0.8f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
	/*
	end BackGround
	*/

	/* start drawLockers
	*/


	// Set color
	glColor3f(0.363137f, 0.270588f, 0.152941f);
	// Draw the Lockers
	glRectf(-1.0f, 0.4f, 1.0f, 0.3f);

	// Set color
	glColor3f(0.0f, 0.0f, 0.0f);

	// Set brown color
	glColor3f(0.631373f, 0.431373f, 0.207843f);
	glRectf(-1.0f, 1.0f, 1.0f, 0.4f);

	// Set black color
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	// Draw the frame lines
	glBegin(GL_LINE_LOOP);

	glVertex2f(-1.0f, 1.0f);  // Top left corner
	glVertex2f(1.0f, 1.0f);   // Top right corner
	glVertex2f(1.0f, 0.4f);   // Bottom right corner
	glVertex2f(-1.0f, 0.4f);  // Bottom left corner

	// Draw a line under the rectangle
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glVertex2f(-1.0f, 0.3f);   // Bottom left corner
	glVertex2f(1.0f, 0.3f);    // Bottom right corner



	// Draw the line
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glVertex2f(0.0f, 1.0f);  // Start point
	glVertex2f(0.0f, 0.4f);   // End point

	glVertex2f(0.5f, 1.0f);  // Start point
	glVertex2f(0.5f, 0.4f);   // End point

	glVertex2f(-0.5f, 1.0f);  // Start point
	glVertex2f(-0.5f, 0.4f);   // End point



	glEnd();
	/*
	* end drawLockers
	*/

	/*
	* start table
	*/
	glColor3f(0.819608f, 0.729412f, 0.431373f);
	glRectf(-0.8f, -1.0f, 0.8f, -0.5f); // 

	// Set color
	glColor3f(0.0f, 0.0f, 0.0f);

	// Draw the line
	glBegin(GL_LINES);

	glVertex2f(-0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -0.5f);   // End point

	glVertex2f(0.8f, -0.5f);  // Start point
	glVertex2f(0.8f, -1.0f);   // End point

	glVertex2f(-0.8f, -0.5f); // Start point reflected
	glVertex2f(-0.8f, -1.0f); // End point reflected

	glEnd();
	/*
	* end table
	*/

	/* start drawItemsOnTable
	*/
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-0.2f, -1.0f, 0.2f, -0.6f); // Draw Test paper



	//glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(4.0f);
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);

	glVertex2f(-0.0f, -0.9f);// يسار
	glVertex2f(0.06f, -0.7f); // نص
	//glVertex2f(-0.2f, -1.0f);// يمين
	glEnd();
	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);

	glVertex2f(-0.0f, -0.9f);// يسار
	glVertex2f(-0.06f, -0.7f); // نص
	glEnd();
	//(-0.2f, -1.0f, 0.2f, -0.6f); // Draw Test paper

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);

	glVertex2f(0.03f, -0.8f);// يسار
	glVertex2f(-0.03f, -0.8f);// يسار
	glEnd();



	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);

	glVertex2f(-0.03f, -0.94f);// يسار
	glVertex2f(-0.07f, -0.94f);// يسار
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(-0.05f, -0.90f);  // Start point
	glVertex2f(-0.05f, -0.98f);   // End point
	glEnd();


	// Draw frame
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);

	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, -1.0f);
	glVertex2f(0.2f, -1.0f);
	glVertex2f(0.2f, -0.6f);
	glVertex2f(-0.2f, -0.6f);
	glEnd();

	// draw Pencil eraser

	glColor3f(1.0f, 0.50f, 0.50f);
	glRectf(-0.4f, -0.8f, -0.39f, -0.57f);  //eraser

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);  // Bottom-left vertex
	glVertex2f(-0.4f, -0.57f); // Top-left vertex
	glVertex2f(-0.39f, -0.57f); // Top-right vertex
	glVertex2f(-0.39f, -0.8f);  // Bottom-right vertex
	glEnd();

	// Draw pencil
	glColor3f(0.2745, 0.5529, 0.7961);
	glRectf(-0.4f, -0.8f, -0.39f, -0.6f);


	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.395f, -0.83f);
	glEnd();

	// Draw black lines around the pencil
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.39f, -0.6f);
	glVertex2f(-0.395f, -0.83f);
	glVertex2f(-0.395f, -0.6f);
	glEnd();




	glEnd();

	/*
	* end drawItemsOnTable
	*/

	/*
	* start eraser
	*/


	//eraser
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.480, -0.576, 0.026);
	glColor3f(1.0f, 0.50f, 0.50f); // Set color to eraser color
	glRectf(-0.48f, -0.55f, -0.419f, -0.60f);  //eraser


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.4179783700881, -0.6040088913799);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4179783700881, -0.6040088913799);//
	glVertex2f(-0.497, -0.6);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.49, -0.5442019054577);
	glEnd();

	//eraser lines inside
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.431622879304, -0.5706971373495);
	glVertex2f(-0.4660764184768, -0.5718690264371);
	glEnd();


	//eraser
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5000, -0.5832063155461);
	glVertex2f(-0.4981625811559, -0.5748504358921);
	glVertex2f(-0.4877897650338, -0.5696640278311);
	glEnd();
	//eraser2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5, -0.59);
	glVertex2f(-0.5036371229982, -0.5774436399227);
	glVertex2f(-0.503348989217, -0.5670708238005);
	glVertex2f(-0.4975863135936, -0.5555454725537);
	glVertex2f(-0.4889423001585, -0.5494946631492);

	glEnd();

	/*
	end eraser
	*/



	/*
	* start chair
	*/
	glColor3f(0.9f, 0.5f, 0.2f); // Set the fill color to the desired value
	glRectf(-0.2f, 0.1f, 0.2f, -0.5f); // Draw the filled rectangle

	glColor3f(0.0f, 0.0f, 0.0f); // Set the line color to black
	glLineWidth(2.0f); // Set the line width to 1 pixel (adjust as needed)

	// Draw lines around the rectangle
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, 0.1f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.2f, -0.5f);
	glVertex2f(-0.2f, -0.5f);
	glEnd();
	/*
	* end chair
	*/

	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.56, 0.5, 0.2);
	drawFilledCircle(-0.36, 0.3, 0.04);
	drawFilledCircle(-0.3, 0.2, 0.03);
	glEnd();

	// To write on the screen
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.75f, 0.5f);
	const char* text1 = "YES! I get A in my exam";

	while (*text1) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);  // Increase font size here
		text1++;
	}

}

void display10()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	BackGroundOfMaroco10();
	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	Maroco10();
	glPopMatrix();
	glDisable(GL_BLEND);
	glFlush();
	glutSwapBuffers();
}



//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.5 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////







/////////////////
////////////////
// Functions //
////////////////

//http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture





void write5()
{
	// To write on the screen
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(-0.599f, 0.5f);
	const char* text1 = "No! I got a D on my exam,and I'm so sad";
	while (*text1) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);  // Increase font size here
		text1++;
	}
}

void Maroco5()
{
	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller
	//black taller
	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.12f, .01, 0.12f, -0.3f);

	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	//حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();




	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);
	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();

	//eyses
	glLineWidth(1);
	//white
	glColor3f(1, 1, 1);
	drawFilledOval(.1, .3, .06);
	drawFilledOval(-.1, .3, .06);
	//black
	glColor3f(0, 0, 0);
	drawOval(.1, .3, .06);
	drawOval(-.1, .3, .06);
	//بؤبؤ
	drawFilledCircle(.1, .3, .01);
	drawFilledCircle(-.1, .3, .01);

	//Smile
	glColor3f(0.0f, 0.0f, 0.0f);  // Red color
	drawHalfHollowCircle(0.0f, 0.15f, -0.07f, 1.0f);
	glEnd();



	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);



}



////////////////
// Display //
////////////////
void display5()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color buffer

	glEnable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();




	//----------------------

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, myTexture3);


	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex2f(-1.5, -1.5);

	glTexCoord2f(1.0, 0.0); glVertex2f(1.5, -1.5);

	glTexCoord2f(1.0, 1.0); glVertex2f(1.5, 1.5);

	glTexCoord2f(0.0, 1.0); glVertex2f(-1.5, 1.5);

	glEnd();

	glDisable(GL_TEXTURE_2D);


	glPushMatrix();

	glScalef(2.0, 2.0, 1.0);
	glTranslatef(0.0, -0.4, 0.0);
	Maroco5();

	glPopMatrix();
	write5();
	glDisable(GL_BLEND);

	glFlush();
	
	glutSwapBuffers();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.9 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////



GLuint LoadTexture1(const char* filename, int width, int height)
{

	GLuint texture;

	unsigned char* data;

	FILE* file;


	//The following code will read in our RAW file

	//file = fopen( filename, "rb" );

	fopen_s(&file, filename, "rb");


	if (file == NULL)

	{

		cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;

		exit(0);

		return 0;

	}


	data = (unsigned char*)malloc(width * height * 3);

	fread(data, width * height * 3, 1, file);


	fclose(file);



	// reorder the image colors to RGB not BGR

	for (int i = 0; i < width * height; ++i)

	{

		int index = i * 3;

		unsigned char B, R;

		B = data[index];

		R = data[index + 2];


		data[index] = R;

		data[index + 2] = B;


	}



	/////////////////////////////////////////

	// All Exercises TODO: load another texture image

	//////

	glGenTextures(1, &texture);
	//generate the texture with the loaded data

	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array


	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	/////////////////////////////////////////


	free(data); //free the texture array


	if (glGetError()
		!= GL_NO_ERROR)

		printf("GLError in genTexture()\n");


	return texture; //return whether it was successfull 
}

///////////////////////////////////////////////
////////////////
// Functions //
////////////////




void Maroco9()
{

	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.04f, 0.04f, 40);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller


	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	   //حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle2(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle2(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();



	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);

	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();

	//eyes
	glColor3f(0, 0, 0);
	glLineWidth(3.0f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.07f, 0.325f);// يسار
	glVertex2f(0.1f, 0.380f); // نص
	glVertex2f(0.13f, 0.325f);// يمين
	glEnd();
	///
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 0, 0);  // Red color
	glVertex2f(-0.07f, 0.325f);// يسار
	glVertex2f(-0.1f, 0.380f); // نص
	glVertex2f(-0.13f, 0.325f);// يمين
	glEnd();

	//the Mouth
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.04f, 0.180);
	glVertex2f(0.02f, 0.165);
	glVertex2f(0.0f, 0.160);
	glVertex2f(-0.02f, 0.165);
	glVertex2f(-0.04f, 0.180);
	glEnd();


}

void Text9()
{	// To write on the screen
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(-0.7f, 0.5f);
	const char* text1 = "Finally, I will sleep early today ";

	while (*text1) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);  // Increase font size here
		text1++;
	}

}

////////////////
// Display //
////////////////
void display9()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	

	//----------------------

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, myTexture9);


	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex2f(-1.5, -1.5);

	glTexCoord2f(1.0, 0.0); glVertex2f(1.5, -1.5);

	glTexCoord2f(1.0, 1.0); glVertex2f(1.5, 1.5);

	glTexCoord2f(0.0, 1.0); glVertex2f(-1.5, 1.5);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	Text9();

	glPushMatrix();
	glScalef(2.0, 2.0, 1.0);
	glTranslatef(0.0, -0.4, 0.0);
	Maroco9();
	glPopMatrix();
	glDisable(GL_BLEND);
	glFlush();

	glutSwapBuffers();
}







//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.6 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
////////////////                                                              
////////////////                                                                                                            
//////////////// 
////////////////                                                          " SCENE NO.6 "
////////////////
////////////////
////////////////
//////////////////////////////////////////////////////////////////////////////////////////






void Maroco_6() {
	
	//رقبة
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	glRectd(-.03, 0, .03, .1);

	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	//tshirt
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);

	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	glRectd(-.12f, .01, 0.12f, -0.3f);//taller
	//black taller
	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.12f, .01, 0.12f, -0.3f);

	///////////////////////////
	//lift hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(-.13, -.05, 0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(-.13, .05, -.11, -0.15);
	glRectd(-.16, -.05, -.11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(-.16, -.05, -.11, -0.15);
	drawLineRectangle(-.161, -0.141, -.11, -0.3);
	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(-.13, -.05, 0.03, 0.1);
	glRectd(-.16, -0.14, -.11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-.11, -0.3);
	glVertex2f(-.11, -0.139);
	glEnd();

	/////////////////////////

	//حلق البلوزة
	glColor3f(0.977, 0.793, 0.012);
	drawHalfHollowCircle(0.0f, 0.05f, 0.04f, 10);
	glRectd(-.031, .05, -.12, -.050);
	glRectd(.031, .05, .12, -.050);

	//حلق البلوزة اسود
	glColor3f(0, 0, 0);
	drawHalfHollowCircle(0.0f, 0.046f, 0.04f, 2);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-.031, .05);
	glVertex2f(-.135, .05);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(.031, .05);
	glVertex2f(.135, .05);
	glEnd();

	//////////////////////////////////////////////////////////
	//      up      //
	//////////////////////////////////////////////////////////
	////right hand
	//glColor3f(0, 0, 0);
	//glLineWidth(2);
	//drawLineOval(.13, .05, 0.03, 0.1);
	////oval lift
	//glColor3f(0.977, 0.793, 0.012);
	//glRectd(.13, .05, .11, 0.15);
	//glRectd(.16, .05, .11, 0.15);
	//glColor3f(0, 0, 0);
	//glLineWidth(1);
	//drawLineRectangle(.16, .05, .11, 0.15);
	//glColor3f(0.977, 0.793, 0.012);
	//drawFilleddOval(.13, .05, 0.03, 0.1);
	/////////////////////////////////////////////////////////


	////right hand
	glColor3f(0, 0, 0);
	glLineWidth(2);
	drawLineOval(.13, -.05, -0.03, 0.1);
	//oval lift
	glColor3f(0.977, 0.793, 0.012);
	glRectd(.13, .05, .11, -0.15);
	glRectd(.16, -.05, .11, -0.15);


	glColor3f(0, 0, 0);
	glLineWidth(1);
	drawLineRectangle(.16, -.05, .11, -0.15);
	drawLineRectangle(.161, -0.141, .11, -0.3);

	glColor3f(0.977, 0.793, 0.012);
	drawFilleddOval(.13, -.05, -0.03, 0.1);
	glRectd(.16, -0.14, .11, -0.3);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(.11, -0.3);
	glVertex2f(.11, -0.139);
	glEnd();


	//hair
	//CIRCIL
	glColor3f(0, 0, 0);
	drawFilledCircle(0.0, 0.36, .24);
	glRectd(-0.23, 0.2, 0.23, 0.3);//Rectd

	//ears

	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(-0.2, 0.3, .05);
	drawFilledCircle(0.2, 0.3, .05);

	//black Circle for ears
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1);
	drawHollowCircle(-0.2, 0.3, .05);
	drawHollowCircle(0.2, 0.3, .05);

	//face
	// Circle for face
	glColor3f(0.9921875f, 0.88671875f, 0.84375f);
	drawFilledCircle(0, 0.3, .2);
	// black circle for face
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHollowCircle(0.0, 0.3, .2);

	//hair
	//TRIANGLES middle القصة
	glBegin(GL_TRIANGLES);
	glVertex2f(0, .4);
	glVertex2f(-.05, .5);
	glVertex2f(.05, .5);
	glEnd();
	//TRIANGLES in right
	glBegin(GL_TRIANGLES);
	glVertex2f(.07, .4);
	glVertex2f(.15, .5);
	glVertex2f(.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(.1, .5);
	glVertex2f(.15, .38);
	glVertex2f(.19, .5);
	glEnd();
	//TRIANGLES in lift
	glBegin(GL_TRIANGLES);
	glVertex2f(-.07, .4);
	glVertex2f(-.15, .5);
	glVertex2f(-.03, .5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-.1, .5);
	glVertex2f(-.15, .38);
	glVertex2f(-.19, .5);
	glEnd();

	//eyses
	glLineWidth(1);
	//white
	glColor3f(1, 1, 1);
	drawFilledOval(.1, .3, .06);
	drawFilledOval(-.1, .3, .06);
	//black
	glColor3f(0, 0, 0);
	drawOval(.1, .3, .06);
	drawOval(-.1, .3, .06);
	//بؤبؤ
	drawFilledCircle(.1, .3, .01);
	drawFilledCircle(-.1, .3, .01);

	//Smile
	glColor3f(0.89f, 0.44f, 0.48f);  // Red color
	drawHalfFilledCircle1(0.0f, 0.2f, 0.07f);  // Center at (0, 0) with a radius of 0.5
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0.07f, 0.2);
	glVertex2f(-0.07f, 0.2);
	glEnd();

	drawHalfHollowCircle(0.0f, 0.2f, 0.07f, 1.0f);

	//the cheecks
	glColor4f(0.8, 0.3, 0.5, .4);
	drawFilledCircle(.15, .2, .02);
	drawFilledCircle(-.15, .2, .02);
}


void BackGroundOfMaroco_6()
{
	//background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.7f, 0.6f);
	glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(0.7f, 0.8f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
	///table
	glBegin(GL_QUADS);
	glColor3f(0.36317, 0.270588, 0.152941);
	glVertex2f(1.0, -0.415);
	glVertex2f(1.0, -1.0);
	glVertex2f(-0.644, -1.0);
	glVertex2f(-0.644, -0.415);
	glEnd();
	//LINE ON THE TABLE
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2.0f);
	glVertex2f(1.0, -0.415);
	glVertex2f(1.0, -1.0);
	glVertex2f(-0.644, -1.0);
	glVertex2f(-0.644, -0.415);
	glEnd();
	//TableItems
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(-0.2f, -1.0f, 0.2f, -0.6f); // Draw Test paper
	// Call drawHandDrawLine for the first line
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawHandDrawLine(-0.2f, -0.9f, 0.2f, -0.9f);
	drawHandDrawLine(-0.2f, -0.8f, 0.2f, -0.8f);
	// Draw frame
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.2f, -1.0f);
	glVertex2f(0.2f, -1.0f);
	glVertex2f(0.2f, -0.6f);
	glVertex2f(-0.2f, -0.6f);
	glEnd();
	// draw Pencil eraser

	glColor3f(1.0f, 0.50f, 0.50f);
	glRectf(-0.4f, -0.8f, -0.39f, -0.57f);  //eraser

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);  // Bottom-left vertex
	glVertex2f(-0.4f, -0.57f); // Top-left vertex
	glVertex2f(-0.39f, -0.57f); // Top-right vertex
	glVertex2f(-0.39f, -0.8f);  // Bottom-right vertex
	glEnd();

	// Draw pencil
	glColor3f(0.2745, 0.5529, 0.7961);
	glRectf(-0.4f, -0.8f, -0.39f, -0.6f);


	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.395f, -0.83f);
	glEnd();

	// Draw black lines around the pencil
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2f(-0.4f, -0.8f);
	glVertex2f(-0.4f, -0.6f);
	glVertex2f(-0.39f, -0.8f);
	glVertex2f(-0.39f, -0.6f);
	glVertex2f(-0.395f, -0.83f);
	glVertex2f(-0.395f, -0.6f);
	glEnd();


	//locker 
		// Draw the Lockers
	glColor3f(0.363137f, 0.270588f, 0.152941f);
	glRectf(-1.0f, 0.5f, 1.0f, 0.3f);
	// Set brown color
	glColor3f(0.631373f, 0.431373f, 0.207843f);
	glRectf(-1.0f, 1.0f, 1.0f, 0.4f);
	// another locker
	glColor3f(0.363137f, 0.270588f, 0.152941f);
	glRectf(-1.0f, 0.2f, 1.0f, 0.2f);
	glColor3f(0.363137f, 0.270588f, 0.152941f);
	glRectf(-1.0f, 0.2f, 1.0f, 0.2f);
	//* Set color
	glColor3f(0.0f, 0.0f, 0.0f);
	// Draw the line
	glBegin(GL_LINES);
	glLineWidth(5.0f);
	glVertex2f(0.0f, 1.0f);  // Start point
	glVertex2f(0.0f, 0.4f);   // End point
	glVertex2f(0.5f, 1.0f);  // Start point
	glVertex2f(0.5f, 0.4f);   // End point
	glVertex2f(-0.5f, 1.0f);  // Start point
	glVertex2f(-0.5f, 0.4f);   // End point
	glEnd();
	//book1
	glBegin(GL_QUADS);
	glColor3f(0.631373f, 0.431373f, 0.207843f);
	glVertex2f(0.581, -0.581);
	glVertex2f(0.664, -0.581);
	glVertex2f(0.664, -0.853);
	glVertex2f(0.581, -0.853);
	glEnd();
	//book2
	glBegin(GL_QUADS);
	glColor3f(0.631373f, 0.431373f, 0.207843f);
	glVertex2f(0.581, -0.581);
	glVertex2f(0.498, -0.581);
	glVertex2f(0.498, -0.853);
	glVertex2f(0.581, -0.853);
	glEnd();
	// locks for wardrobe
	glColor3f(0.0f, 0.0f, 0.0f);
	drawFilledCircle(-0.581, 0.79, 0.03);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawFilledCircle(-0.083, 0.79, 0.03);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawFilledCircle(0.451, 0.79, 0.03);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawFilledCircle(.94, 0.79, 0.03);
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-0.498, -0.584);
	glVertex2f(-0.583, -0.584);
	glVertex2f(-0.5, -0.584);
	glVertex2f(-0.585, -0.583);
	glEnd();
	//LINE ON BOOK 1
	glEnable(GL_LINE_LOOP);
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);//0,1,0
	glVertex2f(0.581, -0.581);
	glVertex2f(0.664, -0.581);
	glVertex2f(0.664, -0.853);
	glVertex2f(0.581, -0.853);
	glDisable(GL_LINE_LOOP);
	glEnd();
	//book 2 line
	glEnable(GL_LINE_LOOP);
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(0.581, -0.581);
	glVertex2f(0.498, -0.581);
	glVertex2f(0.498, -0.853);
	glVertex2f(0.581, -0.853);
	glEnd();
	glDisable(GL_LINE_LOOP);

	/*
	* start eraser
	*/


	//eraser
	glLineWidth(2.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(-0.480, -0.576, 0.026);
	glColor3f(1.0f, 0.50f, 0.50f); // Set color to eraser color
	glRectf(-0.48f, -0.55f, -0.419f, -0.60f);  //eraser


	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.4179783700881, -0.6040088913799);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4179783700881, -0.6040088913799);//
	glVertex2f(-0.497, -0.6);
	glEnd();

	//eraser lines
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4125413713679, -0.5550759028981);
	glVertex2f(-0.49, -0.5442019054577);
	glEnd();

	//eraser lines inside
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.431622879304, -0.5706971373495);
	glVertex2f(-0.4660764184768, -0.5718690264371);
	glEnd();


	//eraser
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5000, -0.5832063155461);
	glVertex2f(-0.4981625811559, -0.5748504358921);
	glVertex2f(-0.4877897650338, -0.5696640278311);
	glEnd();
	//eraser2
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-0.4926880393137, -0.5964604694799);
	glVertex2f(-0.5, -0.59);
	glVertex2f(-0.5036371229982, -0.5774436399227);
	glVertex2f(-0.503348989217, -0.5670708238005);
	glVertex2f(-0.4975863135936, -0.5555454725537);
	glVertex2f(-0.4889423001585, -0.5494946631492);

	glEnd();

}
//aditional method
//bin
void bins_6() {
	glBegin(GL_QUADS);
	glColor3f(.6f, .0f, .5f);
	glVertex2f(0.9694808458089, -0.8015971642585);
	glVertex2f(0.9778470840522, -0.4995096745197);
	glVertex2f(0.829145745826, -0.4987789450179);
	glVertex2f(0.8301149173128, -0.8030072748335);
	glEnd();
	//lines bin
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.9694808458089, -0.8015971642585);
	glVertex2f(0.9778470840522, -0.4995096745197);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.829145745826, -0.4987789450179);
	glVertex2f(0.8301149173128, -0.8030072748335);
	glEnd();
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.9694808458089, -0.8015971642585);
	glVertex2f(0.8301149173128, -0.8030072748335);
	glEnd();
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.931, -0.542, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.961, -0.523, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.971, -0.503, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.901, -0.547, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.87, -0.54, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.845, -0.515, 0.020);
	//bin balls
	glColor3f(1.0f, 1.0f, 1.0f);
	drawFilledCircle(0.837, -0.49, 0.020);
	/////////////////////////////////////
	//bin balls
	glColor3f(.9f, .8f, .1f);
	drawFilledCircle(0.92, -0.60, 0.036);
	//bin balls
	glColor3f(1.0f, .4f, .1f);
	drawFilledCircle(0.87, -0.76, 0.040);
	//bin balls
	glColor3f(.1, .0f, .1f);
	drawFilledCircle(0.904, -0.47, 0.080);
}

//pencil

void drawPencil_6() {

}
//earaser
void earaser_6() {
	
}
//handwritten line
void drawHandDrawLine_6(float startX, float startY, float endX, float endY)
{
	const int numSegments = 100;
	const float maxPerturbation = 0.01f; // Maximum perturbation distance (reduced value)
	// Set the seed for random number generation
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	glBegin(GL_LINE_STRIP);
	// Start point of the line
	glVertex2f(startX, startY);
	// Calculate the direction and length of the line
	float dx = endX - startX;
	float dy = endY - startY;
	float length = std::sqrt(dx * dx + dy * dy);
	// Calculate the perturbation for each segment
	for (int i = 0; i < numSegments; ++i)
	{
		float t = static_cast<float>(i) / static_cast<float>(numSegments - 1);
		float x = startX + t * dx;
		float y = startY + t * dy;
		// Randomly perturb the position
		float perturbationX = (std::rand() / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f;
		float perturbationY = (std::rand() / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f;
		perturbationX *= maxPerturbation;
		perturbationY *= maxPerturbation;
		x += perturbationX;
		y += perturbationY;
		glVertex2f(x, y);
	}
}
// Display_6
void display6() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	BackGroundOfMaroco_6();

	glPushMatrix();
	glTranslatef(-1.7, -0.2, 0.0);
	bins_6();
	glPopMatrix();

	
	glPushMatrix();
	glTranslatef(0.0, -0.115, 0.0);
	Maroco_6();
	glPopMatrix();
	
	
	

	glDisable(GL_BLEND);

	glFlush();
	glutSwapBuffers();
}




//////////////////////////////////////////////////////////
////
///
///
/// 
/// 
///                          MAIN
/// 
/// 
/// 
/// 
/// 
/// 
/////////////////////////////////////////////////////////






void reshapeFun(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	win_width = newWidth;
	win_hight = newHeight;
}

void init()
{




		transValueX = 0.0;

		transValueY = 0.0;

		transValueZ = 2.0;

		nearr = 0.01;

		farr = 50;


		----------------------



			//------- Texture ---------


		myTexture1 = LoadTexture(image1Path, 720, 1280);
		myTexture2 = LoadTexture(image2Path, 736, 731);
		myTexture3 = LoadTexture1(image3Path, 500, 281);
		myTexture9 = LoadTexture1(image9Path, 736, 454);

		

		if (myTexture1 == -1)
		{
			cout << "Error in loading the texture" << endl;
		}
		else {
			cout << "The texture value is: " << myTexture1 << endl;
		}
		myTexture1 = LoadTexture(image1Path, 720, 1280);



		if (myTexture2 == -1)
		{
			cout << "Error in loading the texture" << endl;
		}
		else {
			cout << "The texture value is: " << myTexture2 << endl;
		}


		if (myTexture3 == -1)

		{

			cout << "Error in loading the texture" << endl;

		}

		else {

			cout << "The texture value is: " << myTexture3 << endl;
		}


		if (myTexture9 == -1)

		{

			cout << "Error in loading the texture" << endl;

		}

		else {

			cout << "The texture value is: " << myTexture9 << endl;
		}

		/////////////////////////////////////////



		glClearColor(0.70f, 0.70f, 0.70f, 1.0f); // Set background color to black and opaque


		//glMatrixMode(GL_PROJECTION);

		//gluPerspective(65, (win_width / win_hight), 0.01, 50);


		/*glMatrixMode(GL_MODELVIEW);

		gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);*/
	
	
	
}

//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);                          // Initialize GLUT
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   // Specify the display Mode – RGB, RGBA or color // Index, single or double Buffer
//	glutInitWindowSize(win_width, win_hight);       // Set the window's initial width & height
//	glutInitWindowPosition(50, 50);                 // Position the window's initial top-left corner
//	glutTimerFunc(100, animate, 0);
//	glutCreateWindow("CG");                          // Create a window with the given title
//	init2();
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glutDisplayFunc(display2);                        // Register display callback handler for window re-paint
//	glutReshapeFunc(reshapeFun);
//	glutMainLoop();                                  // Enter the infinitely event-processing loop
//	return 0;
//}







void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case '1': // lowercase 's'
		input = 1;

		std::cout << "First BG" << std::endl;
		break;

	case '2': // uppercase 'S'
		input = 2;

		std::cout << "Second BG" << std::endl;
		break;

	case '3': // lowercase 't'
		input = 3;
		std::cout << "Third BG" << std::endl;
		// do something here too
		break;
	case '4': // uppercase 'T'
		input = 4;
		std::cout << "Forth BG" << std::endl;
		// do something here too
		break;
	case '5': // lowercase 't'
		input = 5;
		std::cout << "Fifth BG" << std::endl;
		// do something here too
		break;
	case '6': // uppercase 'T'
		input = 6;
		std::cout << "Sixth BG" << std::endl;
		// do something here too
		break;
	case '7': // lowercase 't'
		input = 7;
		std::cout << "Seventh BG" << std::endl;
		// do something here too
		break;
	case '8': // uppercase 'T'
		input = 8;
		std::cout << "Eighth BG" << std::endl;
		// do something here too
		break;
	case '9': // lowercase 't'
		input = 9;
		std::cout << "Ninth BG" << std::endl;
		// do something here too
		break;
	case '0': // uppercase 'T'
		input = 0;
		std::cout << "Tenth BG" << std::endl;
		// do something here too
		break;
	

	}//end swich


}


void display()
{
	
	if (input == 1) {
		glClear(GL_COLOR_BUFFER_BIT);
		display1();

	}
	else if (input == 2) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display2();
	}
	else if (input == 3) {
		glClear(GL_COLOR_BUFFER_BIT);
		display3();
	}
	else if (input == 4) {
		
		glClear(GL_COLOR_BUFFER_BIT);
		display4();
	}
	else if (input == 5) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display5();
	}
	else if (input == 6) {
		glClear(GL_COLOR_BUFFER_BIT);
		display6();
	}
	else if (input == 7) {
		glClear(GL_COLOR_BUFFER_BIT);
		display7();
	}
	else if (input == 8) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display8();
	}
	else if (input == 9) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display9();
	}
	else if (input == 0) {
		glClear(GL_COLOR_BUFFER_BIT);
		display10();
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);                          // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   //  Specify the display Mode – RGB, RGBA or color //  Index, single or double Buffer
	glutInitWindowSize(1500, 900);       // Set the window's initial width & height
	glutInitWindowPosition(50, 50);                 // Position the window's initial top-left corner
	glutCreateWindow("CG Project.");    // Create a window with the given title
	init();
	glutTimerFunc(100, animate, 0);
	glutKeyboardFunc(keyboard);                     // Register the keyboard callback function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutDisplayFunc(display);                        // Register display callback handler for window re-paint
	glutReshapeFunc(reshapeFun);
	glutMainLoop();                                  // Enter the infinitely event-processing loop
	return 0;
}