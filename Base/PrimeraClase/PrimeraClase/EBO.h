#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;

	//Constuctor to generate an Elements Buffer Object and links them to the indexes.
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};
#endif // !EBO_CLASS_H


