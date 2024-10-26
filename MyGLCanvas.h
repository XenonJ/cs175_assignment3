#pragma once

#ifndef MYGLCANVAS_H
#define MYGLCANVAS_H
#define GL_SILENCE_DEPRECATION

#include <FL/gl.h>
#include <FL/glut.h>
#include <FL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "objects/Cone.h"
#include "objects/Cube.h"
#include "objects/Cylinder.h"
#include "objects/Shape.h"
#include "objects/Sphere.h"

#include "Camera.h"
#include "scene/SceneParser.h"
#include "scene/SceneData.h"

class MyGLCanvas : public Fl_Gl_Window {
public:

	// Canvas
	int wireframe;
	int smooth;
	int fill;
	int normal;
	int segmentsX, segmentsY;

	// Shape
	OBJ_TYPE objType;
	Cube* cube;
	Cylinder* cylinder;
	Cone* cone;
	Sphere* sphere;
	Shape* shape;

	// Camera
	float scale;
	Camera* camera;
	SceneParser* parser;

	// Shader
	glm::vec3 rotVec;
	glm::vec3 eyePosition;
	GLubyte* pixels = NULL;
	int isectOnly;


	MyGLCanvas(int x, int y, int w, int h, const char *l = 0);
	~MyGLCanvas();
	void renderShape(OBJ_TYPE type);
	void setSegments();
	void loadSceneFile(const char* filenamePath);
	void setShape(OBJ_TYPE type);
	void renderScene();

private:
	vector<pair<ScenePrimitive *, glm::mat4>> flattenedScene;
	void setpixel(GLubyte* buf, int x, int y, int r, int g, int b);

	void draw();
	void drawScene();
  	void drawObject(OBJ_TYPE type);
  	void drawAxis();

	int handle(int);
	void resize(int x, int y, int w, int h);
	void updateCamera(int width, int height);
	void setLight(const SceneLightData &light);
  	void applyMaterial(const SceneMaterial &material);
    void precomputeSceneTree(SceneNode *root, glm::mat4 transformation);
  	glm::mat4 applyTransform(const glm::mat4 &transform,
                           vector<SceneTransformation *> transformVec);

	int pixelWidth, pixelHeight;
};

#endif // !MYGLCANVAS_H