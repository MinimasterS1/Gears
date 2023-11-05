#pragma once

#include "gEditor.h"
#include "Core/gObject.h"

class HeaderPanel : public EditorAPI

{

public:

	void DrawHeaderPanel();


	void SaveObjectsToBinaryFile(const std::vector<SceneObject>& objects, const std::string& filename);
	std::vector<SceneObject>LoadObjectsFromBinaryFile(const std::string& filename);


private:

	bool ShowLoadFileDialog = false;
	bool ShowSaveFileDialog = false;




};