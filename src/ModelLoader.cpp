#include "ModelLoader.h"
#include "OBJ_Loader.h"

void 
ModelLoader::init(){
}

void 
ModelLoader::update(){
}

void 
ModelLoader::render(){
}

void 
ModelLoader::destroy(){
}

LoadData
ModelLoader::load(std::string objFileName){

  //Temporal Load Data
  LoadData LD;
  objl::Loader Loader;

  bool Model = Loader.LoadFile(objFileName);

  if (Model) {

    //We have a Model .obj
    int totalVertices = Loader.LoadedVertices.size();
    int totalIndices = Loader.LoadedIndices.size();
    int loadedVertices = 0;

    LD.name = objFileName;

    WARNING("ModelLoader::Load() [Load of file: " << objFileName.c_str() << "] \n");

    LD.vertex.resize(totalVertices);

    // Convert obj_loader's vertex data to SimpleVertex struct format
    for (int i = 0; i < totalVertices; ++i) {

      LD.vertex[i].Pos.x = Loader.LoadedVertices[i].Position.X;
      LD.vertex[i].Pos.y = Loader.LoadedVertices[i].Position.Y;
      LD.vertex[i].Pos.z = Loader.LoadedVertices[i].Position.Z;

      LD.vertex[i].Tex.x = Loader.LoadedVertices[i].TextureCoordinate.X;
      LD.vertex[i].Tex.y = 1.0f - Loader.LoadedVertices[i].TextureCoordinate.Y;
    }

    LD.index.resize(totalIndices);

    for (int i = 0; i < totalIndices; ++i) {

      LD.index[i] = Loader.LoadedIndices[i];
    }

    // Store the loaded data in the LoadData structure
    LD.name = objFileName;
    LD.numVertex = totalVertices;
    LD.numIndex = totalIndices;
  }
  else {
    WARNING("ModelLoader::LoadData() [Failed to load file: " << objFileName.c_str() << "] \n");
  }

  return LD;
}
