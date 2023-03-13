#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID;

	//Constuctor
	VAO();

	//Links VBO to VAO using the specified layout
	void LinkVBO(VBO& VBO, GLuint layout);

	void LinkAttributes(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();
};
#endif // !VAO_CLASS_H
