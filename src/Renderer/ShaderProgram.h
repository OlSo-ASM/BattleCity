#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

namespace Renderer {
	class ShaderProgram {
	private:
		GLuint ProgramID;
	public:
		ShaderProgram(const std::string& vertexShaderPosition, const std::string& fragmentShaderPosition);
		~ShaderProgram();
		void use() const;
	};
}