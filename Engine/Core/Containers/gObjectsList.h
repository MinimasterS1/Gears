#pragma once


#include "Core/gCommon.h"
#include "Core/gModel.h"
#include "Core/gParticle.h"

#include "vector"

class   ObjectList {

public:

    static  ObjectList& getInstance() {
        static  ObjectList instance;  // Экземпляр синглтона создается при первом вызове функции
        return instance;
    }

    int getModelIndex() const {

        return ModelIndex;
    }

    void setModelIndex(int index) {
        if (index >= 0 && index < loadedModels.size()) {

            ModelIndex = index;
        }
    }


    std::vector<Model> loadedModels;
    std::vector<int> selectedModelIndices;
    std::vector<Model> displayedModels;
    std::string saveDirectory;
private:


    ObjectList() = default;
    ~ObjectList() = default;
    ObjectList(const  ObjectList&) = delete;
    ObjectList& operator=(const  ObjectList&) = delete;


    int ModelIndex = -1;


};