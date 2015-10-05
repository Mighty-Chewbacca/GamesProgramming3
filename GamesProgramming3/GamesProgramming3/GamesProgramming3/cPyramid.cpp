/*
==================================================================================
cPyramid.cpp
==================================================================================
*/

#include "cPyramid.h"

cPyramid::cPyramid()
{
	setRotAngle(0.0f);
}

void cPyramid::render(float rotAngle)
{
	glRotatef(rotAngle, 0.0f, 1.0f, 0.0f); 
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void cPyramid::initialise()
{
	m_top = glm::vec3(0.0f, 1.0f, 0.0f);
	m_LeftFront = glm::vec3(-1.0f, 0.0f, 1.0f);
	m_RightFront = glm::vec3(1.0f, 0.0f, 1.0f);
	m_RightBack = glm::vec3(1.0f, 0.0f, -1.0f);
	m_LeftBack = glm::vec3(-1.0f, 0.0f, -1.0f);

	//Push back 8 vertices that make up a cube 
	m_vertices.push_back(m_LeftFront);
	m_vertices.push_back(m_LeftBack);
	m_vertices.push_back(m_RightBack);
	m_vertices.push_back(m_RightFront);
	m_vertices.push_back(m_top);

	m_Indices[0] = 0; // red front face 
	m_Indices[1] = 5;
	m_Indices[2] = 2;

	m_Indices[6] = 2; // orange back face 
	m_Indices[7] = 5;
	m_Indices[8] = 3;

	m_Indices[12] = 3; // yellow top face 
	m_Indices[13] = 5;
	m_Indices[14] = 4;

	m_Indices[18] = 4; // purple bottom face 
	m_Indices[19] = 5;
	m_Indices[20] = 1;

	m_Indices[24] = 1; // bottom face
	m_Indices[25] = 2;
	m_Indices[26] = 4;
	m_Indices[26] = 3;
	m_Indices[26] = 2;
	m_Indices[26] = 4;

	// Create Colour list 
	cColours theColour;

	for (int Colour = 0; Colour < 7; Colour++)
	{
		m_colourList.push_back(theColour.getColour(static_cast<cColours::colours>(Colour)));
	}

	// Assign variables that will be used to store the unique object ID’s that will be used to refer to the two buffers. 

	glGenBuffers = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(2, &m_VertexBufferObjects[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]); //Bind the vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 3 * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferObjects[1]); //Bind the vertex buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* sizeof(m_Indices), &m_Indices[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 3 * m_colourList.size(), &m_colourList[0], GL_STATIC_DRAW); //Send the data to OpenGL 

	//Bind the colour array, and set the color pointer to point at it 
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[3]);
	glColorPointer(3, GL_FLOAT, 0, 0);

	//Bind the vertex array and set the vertex pointer to point at it 
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 1.0f);
}