#pragma once

#include "gEditor.h"
#include "Core/gObject.h"
#include "gContentBrowser.h"

class HeaderPanel : public EditorAPI 

{

public:

	void DrawHeaderPanel();


	void SaveObjectsToBinaryFile(const std::vector<SceneObject>& objects, const std::string& filename);
	std::vector<SceneObject>LoadObjectsFromBinaryFile(const std::string& filename);

	enum SelectedTab {
		NONE,
		LEVEL,
		MATERIAL,
		PARTICLE,
		ANIMATION
	};

	SelectedTab currentTab = LEVEL;


	enum FileType {
		FILE_PART,
		FILE_LVL,
		FILE_MAT,

	};

	FileType currentFileType = FILE_PART;

	SelectedTab GetCurrentTab() const {
		return currentTab;
	}


	void SetCurrentTab(SelectedTab tab) {
		currentTab = tab;
	}

private:

	bool ShowLoadFileDialog = false;
	bool ShowSaveFileDialog = false;




};