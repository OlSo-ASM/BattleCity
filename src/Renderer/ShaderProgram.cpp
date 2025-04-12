#include "ShaderProgram.h"



namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShaderPosition, const std::string& fragmentShaderPosition) {
		//vertex shader
		const char* vertexShaderSource;
		//opening, reading and saving vertex shader from file to program
		std::ifstream vertexShaderFile(vertexShaderPosition);
		std::stringstream bufferOfVertexShader;
		std::string vertexShaderSourceString;

		if (vertexShaderFile) {
			bufferOfVertexShader << vertexShaderFile.rdbuf();
			vertexShaderSourceString = bufferOfVertexShader.str();
		}
		else {
			std::cerr << "ERROR::FILE::VERTEX_SHADER::READING::FAILED\n" 
					  << "Error with file: " << vertexShaderPosition << std::endl;
		}
		vertexShaderFile.close();
		vertexShaderSource = vertexShaderSourceString.c_str();

		//fragment shader
		const char* fragmentShaderSource;
		//opening, reading and saving vertex shader from file to program
		std::ifstream fragmentShaderFile(fragmentShaderPosition);
		std::stringstream bufferOfFragmentShader;
		std::string fragmentShaderSourceString;

		if (fragmentShaderFile) {
			bufferOfFragmentShader << fragmentShaderFile.rdbuf();
			fragmentShaderSourceString = bufferOfFragmentShader.str();
		}
		else {
			std::cerr << "ERROR::FILE::FRAGMENT_SHADER::READING::FAILED\n"
				<< "Error with file: " << fragmentShaderPosition << std::endl;
		}
		fragmentShaderFile.close();
		fragmentShaderSource = fragmentShaderSourceString.c_str();
		GLint success;
		GLchar infoLog[512];

		//vertex shader assembly
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//fragment shader assembly
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//shader program assembly
		this->ProgramID = glCreateProgram();
		glAttachShader(this->ProgramID, vertexShader);
		glAttachShader(this->ProgramID, fragmentShader);
		glLinkProgram(this->ProgramID);
		glGetProgramiv(this->ProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->ProgramID, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		//shaders deleting
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	ShaderProgram::ShaderProgram::~ShaderProgram() {
		glDeleteProgram(this->ProgramID);
	}
	void ShaderProgram::use() const {
		glUseProgram(this->ProgramID);
	}
}