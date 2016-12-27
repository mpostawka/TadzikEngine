#include "VertexArray.hpp"

using namespace chaos;

VertexData::VertexData(){}

VertexData::VertexData(const std::initializer_list<GLfloat>& vV, const std::initializer_list<GLfloat>& vN,
             const std::initializer_list<GLfloat>& vU, const std::initializer_list<GLfloat>& vD)
{
    for(GLfloat x: vV)vVerts.push_back(x);
    for(GLfloat x: vN)vNormal.push_back(x);
    for(GLfloat x: vU)vUV.push_back(x);
    for(GLfloat x: vD)vData.push_back(x);
}

VertexArray::VertexArray(GLuint _vertsSize, GLuint _normalSize, GLuint _uvSize, GLuint _dataSize, std::vector<GLfloat>* vec)
:vertsSize(_vertsSize), normalSize(_normalSize), uvSize(_uvSize), dataSize(_dataSize)
{
    GLuint totalSize = vertsSize + normalSize + uvSize + dataSize;
    GLuint ctr=0;
    for(GLuint i = 0; i < vec->size()/totalSize; i++){
        VertexData vd;
        for(GLuint j = 0; j < vertsSize; j++){
            vd.vVerts.push_back(vec->at(ctr++));
        }
        for(GLuint j = 0; j < normalSize; j++){
            vd.vNormal.push_back(vec->at(ctr++));
        }
        for(GLuint j = 0; j < uvSize; j++){
            vd.vUV.push_back(vec->at(ctr++));
        }
        for(GLuint j = 0; j < dataSize; j++){
            vd.vData.push_back(vec->at(ctr++));
        }
        addVertex(vd);
    }

    std::vector<GLfloat> vData;
    buildArrayOfPlainData(&vData);
    generateVertexArray(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    unbind();
}

VertexArray::VertexArray(GLuint _vertsSize, GLuint _normalSize, GLuint _uvSize, GLuint _dataSize)
:vertsSize(_vertsSize), normalSize(_normalSize), uvSize(_uvSize), dataSize(_dataSize)
{

}

VertexArray::~VertexArray(){}

void VertexArray::addVertex(VertexData vd){
    vVertices.push_back(vd);
}
void VertexArray::setVertices(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vVerts.clear();
    for(GLfloat x: v){
        vVertices[id].vVerts.push_back(x);
    }
}
void VertexArray::setNormal(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vNormal.clear();
    for(GLfloat x: v){
        vVertices[id].vNormal.push_back(x);
    }
}
void VertexArray::setUV(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vUV.clear();
    for(GLfloat x: v){
        vVertices[id].vUV.push_back(x);
    }
}
void VertexArray::setData(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vData.clear();
    for(GLfloat x: v){
        vVertices[id].vData.push_back(x);
    }
}
void VertexArray::buildArrayOfPlainData(std::vector<GLfloat>* v){
    v->clear();
    for(GLuint i = 0; i < vVertices.size(); i++){
        for(GLuint j = 0; j < vertsSize; j++)
            v->push_back(vVertices[i].vVerts[j]);
        for(GLuint j = 0; j < normalSize; j++)
            v->push_back(vVertices[i].vNormal[j]);
        for(GLuint j = 0; j < uvSize; j++)
            v->push_back(vVertices[i].vUV[j]);
        for(GLuint j = 0; j < dataSize; j++)
            v->push_back(vVertices[i].vData[j]);
    }
}

void VertexArray::generateVertexArray(GLenum _target, GLenum _usage){
    std::vector<GLfloat> vxData;
    buildArrayOfPlainData(&vxData);
    target = _target;
    usage = _usage;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(target, VBO);
    glBufferData(target, vxData.size()*sizeof(GLfloat), vxData.data(), usage);

    GLuint stride = vertsSize+normalSize+uvSize+dataSize;

    if(vertsSize != 0){
        glVertexAttribPointer(0, vertsSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    }
    if(normalSize != 0){
        glVertexAttribPointer(1, normalSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize)));
        glEnableVertexAttribArray(1);
    }
    if(uvSize != 0){
        glVertexAttribPointer(2, uvSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize)));
        glEnableVertexAttribArray(2);
    }
    if(dataSize != 0){
        glVertexAttribPointer(3, dataSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize+uvSize)));
        glEnableVertexAttribArray(3);
    }
    glBindVertexArray(0);
}

void VertexArray::bind(){
    glBindVertexArray(VAO);
}

void VertexArray::unbind(){
    glBindVertexArray(0);
}
