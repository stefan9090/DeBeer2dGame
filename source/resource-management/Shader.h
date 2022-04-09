//
// Created by beerd on 12/18/2021.
//

#ifndef DEBEER2D_SHADER_H
#define DEBEER2D_SHADER_H

#include <string>
#include "glm/glm.hpp"

class Shader
{
private:
    unsigned int m_id;
public:
    bool load(std::string_view strVertexPath, std::string_view strFragmentPath);
    void use();

    void setBool(std::string_view strName, bool value);
    void setFloat(std::string_view strName, float value);
    void setInt(std::string_view strName, int value);

    void setVec2(std::string_view strName, glm::vec2 value);
    void setVec3(std::string_view strName, glm::vec3 value);
    void setVec4(std::string_view strName, glm::vec4 value);

    void setMat2(std::string_view strName, glm::mat2 value);
    void setMat3(std::string_view strName, glm::mat2 value);
    void setMat4(std::string_view strName, glm::mat2 value);

private:
    static bool compileShader(std::string_view strShaderPath, uint16_t shaderType, unsigned int &rShaderId);
};


#endif //DEBEER2D_SHADER_H
