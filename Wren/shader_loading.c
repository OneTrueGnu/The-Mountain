#include "Wren.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

Wren_ShaderProgram Wren_ShaderProgram_create_ff(
		const char* vertex_shader_source_path, 
		const char* fragment_shader_source_path
		) {

	FILE* vertex_shader_stream = fopen(vertex_shader_source_path, "r");
	if (vertex_shader_stream == NULL) {
		printf(
				"ERROR: Failed to open vertex shader source file %s for reading while creating a shader program from %s and %s: %s\n", 
				vertex_shader_source_path,
				vertex_shader_source_path,
				fragment_shader_source_path,
				strerror(errno)
			  );
		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	FILE* fragment_shader_stream = fopen(fragment_shader_source_path, "r");
	if (fragment_shader_stream == NULL) {
		printf(
				"ERROR: Failed to open fragment shader source file %s for reading while creating a shader program from %s and %s: %s\n", 
				fragment_shader_source_path,
				vertex_shader_source_path,
				fragment_shader_source_path,
				strerror(errno)
			  );
		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	fseek(vertex_shader_stream, 0, SEEK_END);
	ulong vertex_shader_source_length = ftell(vertex_shader_stream);	
	rewind(vertex_shader_stream);
	fseek(fragment_shader_stream, 0, SEEK_END);
	ulong fragment_shader_source_length = ftell(fragment_shader_stream);
	rewind(fragment_shader_stream);

	char* vertex_shader_source = calloc(sizeof(char), vertex_shader_source_length + 1);
	fread(vertex_shader_source, sizeof(char), vertex_shader_source_length, vertex_shader_stream);
	fclose(vertex_shader_stream);
	char* fragment_shader_source = calloc(sizeof(char), fragment_shader_source_length + 1);
	fread(fragment_shader_source, sizeof(char), fragment_shader_source_length, fragment_shader_stream);
	fclose(fragment_shader_stream);

	u32 vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	u32 fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex_shader, 1, (const char* const*)&vertex_shader_source, NULL);
	free(vertex_shader_source);
	glShaderSource(fragment_shader, 1, (const char* const*)&fragment_shader_source, NULL);
	free(fragment_shader_source);

	glCompileShader(vertex_shader);
	glCompileShader(fragment_shader);

	i32 vertex_shader_compilation_was_successful;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_compilation_was_successful);
	if (vertex_shader_compilation_was_successful == GL_FALSE) {
		i32 required_infolog_size;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &required_infolog_size);
		char* infolog_buffer = calloc(sizeof(char), required_infolog_size);

		glGetShaderInfoLog(vertex_shader, required_infolog_size, NULL, infolog_buffer);
		printf(
				"ERROR: Failed to compile vertex shader found in %s. Error message: %s\n",
				vertex_shader_source_path,
				infolog_buffer
			  );

		free(infolog_buffer);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	i32 fragment_shader_compilation_was_successful;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_compilation_was_successful);
	if (fragment_shader_compilation_was_successful == GL_FALSE) {
		i32 required_infolog_size;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &required_infolog_size);
		char* infolog_buffer = calloc(sizeof(char), required_infolog_size);

		glGetShaderInfoLog(fragment_shader, required_infolog_size, NULL, infolog_buffer);
		printf(
				"ERROR: Failed to compile fragment shader found in %s. Error message: %s\n",
				fragment_shader_source_path,
				infolog_buffer
			  );

		free(infolog_buffer);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	u32 shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	i32 program_linking_was_successful;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &program_linking_was_successful);
	if (program_linking_was_successful == GL_FALSE) {
		i32 required_infolog_space;
		glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &required_infolog_space);
		char* infolog_buffer = calloc(sizeof(char), required_infolog_space);

		glGetProgramInfoLog(shader_program, required_infolog_space, NULL, infolog_buffer);
		printf(
				"ERROR: Failed to link shader program built from source files %s and %s. Error message: %s\n",
				vertex_shader_source_path,
				fragment_shader_source_path,
				infolog_buffer
			  );

		free(infolog_buffer);

		glDeleteProgram(shader_program);

		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	return (Wren_ShaderProgram){ .successfully_created = true, .id = shader_program};
}

Wren_ShaderProgram Wren_ShaderProgram_create_nn(
		const char *vertex_shader_source_name, 
		const char *fragment_shader_source_name
		) {

	const char* format_string = "resources/shaders/%s.glsl";
	const u64 conversion_specifier_length = 2;

	const u64 vertex_shader_source_path_length = strlen(format_string) + strlen(vertex_shader_source_name) - conversion_specifier_length;
	char* vertex_shader_source_path = malloc((sizeof *vertex_shader_source_path) * (vertex_shader_source_path_length+1));
	if (-1 == snprintf(vertex_shader_source_path, vertex_shader_source_path_length, format_string, vertex_shader_source_name)) {
		printf("ERROR: Failed to create shader source path from vertex shader source name \"%s\": %s\n", vertex_shader_source_name, strerror(errno));
		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	const u64 fragment_shader_source_path_length = strlen(format_string) + strlen(fragment_shader_source_name) - conversion_specifier_length;
	char* fragment_shader_source_path = malloc((sizeof *fragment_shader_source_path) * (fragment_shader_source_path_length+1)); 
	if (-1 == snprintf(fragment_shader_source_path, fragment_shader_source_path_length, format_string, fragment_shader_source_name)) {
		printf("ERROR: Failed to create shader source path from fragment shader source name \"%s\": %s\n", fragment_shader_source_name, strerror(errno));
		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	Wren_ShaderProgram created_program = Wren_ShaderProgram_create_ff(vertex_shader_source_path, fragment_shader_source_path);
	if (!created_program.successfully_created) {
		printf(
				"ERROR: Failed to create shader program from source names \"%s\" (vertex) and \"%s\" (fragment). There was probably already an error message saying why.\n", 
				vertex_shader_source_name, 
				fragment_shader_source_name
			  );
		return (Wren_ShaderProgram){ .successfully_created = false };
	}

	free(vertex_shader_source_path);
	free(fragment_shader_source_path);

	return created_program;
}

