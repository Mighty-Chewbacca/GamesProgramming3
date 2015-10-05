/*
==================================================================================
cCube.cpp
==================================================================================
*/

#include "cCube.h"


cCube::cCube()
{
	setRotAngle(5.0f);
}

void cCube::render(float rotAngle, int faceNo)
{
	glRotatef(rotAngle, 0.0f, 1.0f, 0.0f); 
	glColor3f(m_colourList[faceNo].x, m_colourList[faceNo].y, m_colourList[faceNo].z);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void cCube::initialise()
{
	m_topLeftFront = glm::vec3(-1.0f, 1.0f, 1.0f);
	m_bottomLeftFront = glm::vec3(-1.0f, -1.0f, 1.0f);
	m_topRightFront = glm::vec3(1.0f, 1.0f, 1.0f);
	m_bottomRightFront = glm::vec3(1.0f, -1.0f, 1.0f);
	m_topLeftBack = glm::vec3(-1.0f, 1.0f, -1.0f);
	m_topRightBack = glm::vec3(1.0f, 1.0f, -1.0f);
	m_bottomLeftBack = glm::vec3(-1.0f, -1.0f, -1.0f);
	m_bottomRightBack = glm::vec3(1.0f, -1.0f, -1.0f);

	//Push back 8 vertices that make up a cube 
	m_vertices.push_back(m_bottomLeftFront);
	m_vertices.push_back(m_bottomLeftBack);
	m_vertices.push_back(m_bottomRightBack);
	m_vertices.push_back(m_bottomRightFront);


	m_vertices.push_back(m_topLeftFront);
	m_vertices.push_back(m_topLeftBack);
	m_vertices.push_back(m_topRightBack);
	m_vertices.push_back(m_topRightFront);



	m_Indices[0] = 0; // red front face 
	m_Indices[1] = 2;
	m_Indices[2] = 3;
	m_Indices[3] = 0;
	m_Indices[4] = 1;
	m_Indices[5] = 2;

	m_Indices[6] = 4; // orange back face 
	m_Indices[7] = 6;
	m_Indices[8] = 7;
	m_Indices[9] = 4;
	m_Indices[10] = 5;
	m_Indices[11] = 6;

	m_Indices[12] = 0; // yellow top face 
	m_Indices[13] = 4;
	m_Indices[14] = 1;
	m_Indices[15] = 4;
	m_Indices[16] = 5;
	m_Indices[17] = 1;

	m_Indices[18] = 2; // purple bottom face 
	m_Indices[19] = 6;
	m_Indices[20] = 3;
	m_Indices[21] = 6;
	m_Indices[22] = 7;
	m_Indices[23] = 3;

	m_Indices[24] = 6; // blue left face 
	m_Indices[25] = 1;
	m_Indices[26] = 5;
	m_Indices[27] = 6;
	m_Indices[28] = 2;
	m_Indices[29] = 1;

	m_Indices[30] = 0; // green right face 
	m_Indices[31] = 7;
	m_Indices[32] = 4;
	m_Indices[33] = 0;
	m_Indices[34] = 3;
	m_Indices[35] = 7;

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

	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glGenBuffers(3, &m_VertexBufferObjects[0]);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]); //Bind the vertex buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW); //Send the data to OpenGL
  
	glTranslatef(0.0f, 0.0f, -6.0f);
	glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
}

void cCube::prepareFace(int faceNumber)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VertexBufferObjects[1]); //Bind the vertex buffer 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, &m_Indices[faceNumber * 6], GL_STATIC_DRAW); //Send the data to OpenGL

	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_colourList.size(), &m_colourList[faceNumber], GL_STATIC_DRAW); //Send the data to OpenGL 

	//Bind the colour array, and set the color pointer to point at it 
	//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[2]);
	//glColorPointer(3, GL_FLOAT, 0, 0);

	//Bind the vertex array and set the vertex pointer to point at it 
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObjects[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);
}
