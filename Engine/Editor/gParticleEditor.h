#pragma once

#include "gEditor.h"


class ParticleUI   : public EditorAPI

{

public:


	void DrawEmitterSettings();


	float currentLifetime;
	glm::vec4 currentColor;
	float currentPointSize = 10.0f;

	glm::vec4 minColor; 
	glm::vec4 maxColor;

	GLFWwindow* m_Window;


private:


};