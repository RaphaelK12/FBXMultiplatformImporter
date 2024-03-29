//
//  FBXHandler_OSX.h
//  FBXImporterBundle_OSX
//
//  Created by Doghead 1 on 4/26/18.
//  Copyright © 2018 BrandonF. All rights reserved.
//

#ifndef FBXHandler_OSX_h
#define FBXHandler_OSX_h

#import "fbxsdk.h"
//#include <vector>
#include <string>

namespace CMath
{
    struct Vector2 {
        Vector2();
        ~Vector2();
        float x;
        float y;
    };
    
    struct Vector3 {
        Vector3();
        ~Vector3();
        float x;
        float y;
        float z;
    };
    
    struct Vector4 {
        Vector4();
        ~Vector4();
        float x;
        float y;
        float z;
        float w;
    };
}

namespace ObjectInfo {
    using namespace CMath;
    struct Material {
        Material();
        ~Material();
        
        enum PropertyType {
            PROPERTYTYPE_EMISSIVE = 0,
            PROPERTYTYPE_AMBIENT,
            PROPERTYTYPE_DIFFUSE,
            PROPERTYTYPE_NORMAL,
            PROPERTYTYPE_BUMP,
            PROPERTYTYPE_TRANSPARENCY,
            PROPERTYTYPE_DISPLACEMENT,
            PROPERTYTYPE_VECTOR_DISPLACEMENT,
            PROPERTYTYPE_SPECULAR,
            PROPERTYTYPE_SHININESS,
            PROPERTYTYPE_REFLECTION,
            PROPERTYTYPE_COUNT
        };
        
        enum MaterialType {
            MATERIALTYPE_PHONG = 0,
            MATERIALTYPE_LAMBERT
        };
        
        struct PropertyData {
            PropertyData();
            ~PropertyData();
            PropertyType    m_propertyType;
            char*            m_textureRelativeFileName;
            char*            m_textureAbsoluteFilePath;
            Vector4            m_dataColorValues;
        };
        
        MaterialType    m_materialType;
        PropertyData**    m_materialProperties;
        unsigned        m_textureCount;
    };
    
    struct Mesh {
        Mesh();
        ~Mesh();
        Vector3*    m_allVerticesPositions;
        Vector3*    m_allVerticesNormals;
        Vector2*    m_allVerticesUVs;
        unsigned*    m_indices;
        unsigned    m_vertexCount;
        unsigned    m_indexCount;
    };
}

using namespace ObjectInfo;
struct Object {
    Object();
    ~Object();
    int        m_parentArrayIndexID;
    int*    m_childrenArrayIndexIDs;
    //std::vector<int>m_childrenArrayIndexIDs;
    //Object*        m_parent;
    //Object**    m_children;
    //std::vector<Object*> m_children;
    Mesh*        m_mesh;
    Material**    m_materials;
    //std::vector<Material*> m_materials;
    
    unsigned    m_childrenCount;
    unsigned    m_materialCount;
    
    char* m_name;
    unsigned    m_arrayIndexID;
};

struct Scene
{
    Scene();
    ~Scene();
    Object**    m_objects;
    //std::vector<Object*> m_objects;
    unsigned    m_numberOfObjects;
};

enum CRESULT {
    CRESULT_SUCCESS = 0,
    CRESULT_INCORRECT_FILE_PATH,
    CRESULT_NO_OBJECTS_IN_SCENE,
    CRESULT_NODE_WAS_NOT_GEOMETRY_TYPE,
    CRESULT_ROOT_NODE_NOT_FOUND
};

extern "C" {
    class FBXHandler {
        Scene*    m_scene;
        
    public:
        FBXHandler();
        ~FBXHandler();
        
        CRESULT LoadFBXFile(const char* _filePath);
        
    private:
        CRESULT LoadFBXScene(FbxScene* _fbxScene);
        CRESULT LoadSceneHelperFunction(int& _objectIndex, Scene* _scene, FbxNode* _inOutFbxNode,
                                        unsigned& _currentRootNodeIndex, unsigned& _numberOfChildrenPassed, unsigned& _previousCallsParent);
        CRESULT FillOutMesh(int& _objectIndex, Scene* _scene, FbxNode* _fbxNode);
        CRESULT FillOutMaterial(int& _objectIndex, Scene* _scene, FbxNode* _fbxNode);
        
        /* Function which runs the tasks for the fbx parser. If we want just a mesh, we only call FillOutMesh() in this function.
         * If we want to grab the meshes and materials from the fbx models inside the scene, then we call FillOutMesh() and FillOutMaterial() in this function. */
        CRESULT RunTasks(int& _objectIndex, Scene* _scene, FbxNode* _fbxNode);
    };
}


#endif /* FBXHandler_OSX_h */
