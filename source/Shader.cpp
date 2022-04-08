//
// Created by beerd on 12/18/2021.
//

#include "Shader.h"

#include <fstream>
#include <glad/glad.h>
#include <sstream>

#include "Logger.h"

bool Shader::load(std::string_view strVertexPath, std::string_view strFragmentPath)
{
    int isOk = 0;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    if (compileShader(strVertexPath, GL_VERTEX_SHADER, vertexShader) &&
        compileShader(strFragmentPath, GL_FRAGMENT_SHADER, fragmentShader))
    {
        m_id = glCreateProgram();
        glAttachShader(m_id, vertexShader);
        glAttachShader(m_id, fragmentShader);
        glLinkProgram(m_id);

        // print linking errors if any
        glGetProgramiv(m_id, GL_LINK_STATUS, &isOk);
        if (isOk == 0)
        {
            char szInfoLog[512];
            glGetProgramInfoLog(m_id, sizeof(szInfoLog), nullptr, szInfoLog);
            LOG_ERROR("Failed to link shader {} and {}:\n{}", strVertexPath, strFragmentPath, szInfoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    return isOk == 1;
}

bool Shader::compileShader(std::string_view strShaderPath, uint16_t shaderType, unsigned int &rShaderId)
{
    std::string strFullShaderPath = std::string{SHADERS_LOCATION} + strShaderPath.data();
    LOG_INFO("Loading shader {}", strFullShaderPath);

    bool isOk = false;

    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string strShaderCode;

    try
    {
        shaderFile.open(strFullShaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        strShaderCode = shaderStream.str();
    } catch (std::ifstream::failure &rError)
    {
        LOG_ERROR("Failed to read shader file: {}", rError.what());
    }

    if (!strShaderCode.empty())
    {
        // vertex Shader
        rShaderId = glCreateShader(shaderType);

        if (rShaderId != 0)
        {
            const char *szShaderCode = strShaderCode.data();

            glShaderSource(rShaderId, 1, &szShaderCode, nullptr);
            glCompileShader(rShaderId);

            int success = false;
            glGetShaderiv(rShaderId, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                // print compile errors if any
                char infoLog[512];
                glGetShaderInfoLog(rShaderId, sizeof(infoLog), nullptr, infoLog);
                LOG_ERROR("Shader compilation of {} failed:\n{}", strShaderPath, infoLog);
            }
            else
            {
                isOk = true;
            }
        }
        else
        {
            LOG_ERROR("Failed to create new shader id for {}", strShaderPath);
        }
    }

    return isOk;
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::setBool(std::string_view strName, bool value)
{
    glUniform1i(glGetUniformLocation(m_id, strName.data()), static_cast<int>(value));
}

void Shader::setFloat(std::string_view strName, float value)
{
    glUniform1f(glGetUniformLocation(m_id, strName.data()), value);
}

void Shader::setInt(std::string_view strName, int value)
{
    glUniform1i(glGetUniformLocation(m_id, strName.data()), value);
}

void Shader::setVec2(std::string_view strName, glm::vec2 value)
{
    glUniform2fv(glGetUniformLocation(m_id, strName.data()), 1, &value[0]);
}

void Shader::setVec3(std::string_view strName, glm::vec3 value)
{
    glUniform3fv(glGetUniformLocation(m_id, strName.data()), 1, &value[0]);
}

void Shader::setVec4(std::string_view strName, glm::vec4 value)
{
    glUniform4fv(glGetUniformLocation(m_id, strName.data()), 1, &value[0]);
}

void Shader::setMat2(std::string_view strName, glm::mat2 value)
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, strName.data()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat3(std::string_view strName, glm::mat2 value)
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, strName.data()), 1, GL_FALSE, &value[0][0]);
}

void Shader::setMat4(std::string_view strName, glm::mat2 value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, strName.data()), 1, GL_FALSE, &value[0][0]);
}
