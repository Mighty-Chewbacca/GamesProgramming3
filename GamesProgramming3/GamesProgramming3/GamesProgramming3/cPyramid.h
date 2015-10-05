#ifndef _PYRAMID_H
#define _PYRAMID_H

#include "windowOGL.h"
#include "glm\glm.hpp"
#include "glx\glext.h"
#include "wglext.h"
#include <vector>
#include "cColours.h"
#include "cShapes.h"

class cPyramid : public cShapes
{
public:
	cPyramid();
	virtual void render(float rotAngle);
	virtual void initialise();

private:

	glm::vec3 m_top;
	glm::vec3 m_LeftFront;
	glm::vec3 m_RightFront;
	glm::vec3 m_RightBack;
	glm::vec3 m_LeftBack;

	glm::vec3 m_Faces[24];
	GLuint m_Indices[36];

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec3> m_colourList;
	GLuint m_VertexBufferObjects[3];
};

#endif