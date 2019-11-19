#include "Shader.h"

Shader::Shader() {
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

Shader::~Shader() {
	clearShader();
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode) {
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation) {
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Failed to read " << fileLocation << "! File doesn't exist!";
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + '\n');
	}

	fileStream.close();

	return content;
}

void Shader::useShader() {
	glUseProgram(shaderID);
}

void Shader::clearShader() {
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode) {
	shaderID = glCreateProgram();

	if (shaderID != GL_TRUE) {
		std::cout << "Shader program error!\n";
	}

	//Adding shaders
	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	//Getting error information for linking
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	//Linking shader
	glLinkProgram(shaderID);

	//Shader linking status
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program! " << eLog << '\n';
	}


	//Gets shader ID and then binds it with the variable inside shader
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);


	//Getting error information for linking
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the " << shaderType << ' ' << eLog << '\n';
	}


	glAttachShader(theProgram, theShader);
}
