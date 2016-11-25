#include "AssimpMesh.h"

namespace Dream {
  namespace Components {
    namespace Graphics {

      AssimpMesh::AssimpMesh(
          std::vector<Vertex> vertices,
          std::vector<GLuint> indices,
          std::vector<Texture> textures) {
        mVertices = vertices;
        mIndices  = indices;
        mTextures = textures;
        init();
      }

      AssimpMesh::~AssimpMesh() { }

      void AssimpMesh::draw(ShaderInstance* shader) {
        GLuint diffuseNr = 1;
        GLuint specularNr = 1;
        for(GLuint i = 0; i < mTextures.size(); i++) {
          glActiveTexture(GL_TEXTURE0 + i); // Activate proper texture unit before binding
          // Retrieve texture number (the N in diffuse_textureN)
          std::stringstream ss;
          std::string number;
          std::string name = mTextures[i].type;
          if(name == "texture_diffuse") {
            ss << diffuseNr++; // Transfer GLuint to stream
          } else if(name == "texture_specular") {
            ss << specularNr++; // Transfer GLuint to stream
          }
          number = ss.str();
          glUniform1f(glGetUniformLocation(shader->getShaderProgram(), ("material." + name + number).c_str()), i);
          glBindTexture(GL_TEXTURE_2D, mTextures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);

        // Draw mesh
        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
      }

      void AssimpMesh::init() {
        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);
        glGenBuffers(1, &mEBO);
        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint),&mIndices[0], GL_STATIC_DRAW);
        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        // Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
        // Vertex Texture Coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
        glBindVertexArray(0);
      }

      bool AssimpMesh::checkGLError(int errorIndex) {
        GLenum errorCode = 0;
        bool wasError = false;
        do {
          errorCode = glGetError();
          if (errorCode!=0) {
            std::cerr << "Mesh: Error Check " << errorIndex << ": " << std::endl;
            switch (errorCode) {
              case GL_NO_ERROR:
                std::cerr << "\tGL_NO_ERROR" << std::endl;
                break;
              case GL_INVALID_ENUM:
                std::cerr << "\tGL_INVALID_ENUM" << std::endl;
                break;
              case GL_INVALID_VALUE:
                std::cerr << "\tGL_INVALID_VALUE" << std::endl;
                break;
              case GL_INVALID_OPERATION:
                std::cerr << "\tGL_INVALID_OPERATION" << std::endl;
                break;
              case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "\tGL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
                break;
              case GL_OUT_OF_MEMORY:
                std::cerr << "\tGL_OUT_OF_MEMORY" << std::endl;
                break;
            }
            std::cerr << "\tName: " << glewGetErrorString(errorCode) << std::endl;
            std::cerr << "\tCode: " << errorCode << std::endl;
            wasError = true;
          }
        } while(errorCode != 0);
        return wasError;
      }

    } // End of Graphics
  } // End of Components
} // End of Dream