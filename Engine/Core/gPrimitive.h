#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Primitives

{

public:

	void Init();

	void DrawCube(float lineWidth);

	void DrawQuad();

	void DrawSphere();

private:

	

};

#endif // PRIMITIVES_H