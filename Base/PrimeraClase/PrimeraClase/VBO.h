#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	GLuint ID;

	//Constuctor to generate an Elements Buffer Object and links them to the indexes.
	VBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};
#endif // !VBO_CLASS_H