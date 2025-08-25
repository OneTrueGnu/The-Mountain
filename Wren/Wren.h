#ifndef Wren_h
#define Wren_h

#include <Lapidary.h>

#include <glad/glad.h>

#include <stdbool.h>

typedef struct {
	u32 id;
	bool successfully_created;
} VertexShader;

typedef struct {
	u32 id;
	bool successfully_created;
} FragmentShader;

typedef struct {
	u32 id;
	bool successfully_created;
} ShaderProgram;

/*
 * Creates and links a shader program given a vertex shader and fragment shader.
 *
 * The shaders are passed by "name", without a file extension or parent directory.
 * It is assumed that all shaders are located in `resources/shaders`, and are
 */
ShaderProgram ShaderProgram_create_nn(
		const char* vertex_shader_source_name,
		const char* fragment_shader_source_name
		);

typedef enum {
	IMAGE_FORMAT_JPEG,
	IMAGE_FORMAT_PNG,
} ImageFormat;

typedef enum {
	CHANNEL_COUNT_GRAYSCALE = 1,
	CHANNEL_COUNT_RGB = 3,
	CHANNEL_COUNT_RGBA = 4,
} ChannelCount;

ChannelCount ImageFormat_correspondingChannelCount(ImageFormat);

typedef enum {
	X0, Y0, X1, Y1
} TextureAtlasEntry_Index;

typedef u32 TextureAtlasEntry[4];

typedef struct {
	u32 width;
	u32 height;
	u32 opengl_texture_id;

	u32 number_of_entries;
	u32 current_entry_capacity;
	TextureAtlasEntry* entries;
} TextureAtlas;

TextureAtlas* TextureAtlas_create_onHeap_n(const char* image_file_name, ImageFormat);
void TextureAtlas_destroy_onHeap(TextureAtlas*);

u32 TextureAtlas_addEntry(TextureAtlas*, TextureAtlasEntry);
u32 TextureAtlas_addEntry_fromCoords(
		TextureAtlas*, 
		u32 x0, 
		u32 y0, 
		u32 x1, 
		u32 y1
		);

void TextureAtlas_getEntryUVs_intoFloats(
		TextureAtlas* atlas, 
		u32 entry_id, 
		f32* u0, 
		f32* v0, 
		f32* u1, 
		f32* v1
		);

void TextureAtlas_getEntryUVs_intoArray(
		TextureAtlas* atlas,
		u32 entry_id,
		f32* dst
		);

typedef struct {
	TextureAtlas* atlas;
	u32 atlas_entry_index;

	ShaderProgram shader_program;

	u32 vao;
	u32 vbo;
	u32 ebo;

	f32 x0;
	f32 y0;
	f32 x1;
	f32 y1;
} TexturedQuad;

TexturedQuad* TexturedQuad_create_onHeap(
		TextureAtlas*,
		u32 atlas_entry_index,

		ShaderProgram shader_program,
		
		f32 x0,
		f32 y0,
		f32 x1, 
		f32 y1
		);

void TexturedQuad_destroy_onHeap(TexturedQuad*);

void TexturedQuad_render(TexturedQuad*);


#endif /* Wren_h */
