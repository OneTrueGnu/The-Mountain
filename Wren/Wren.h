#ifndef Wren_h
#define Wren_h

#include <Lapidary.h>

#include <glad/glad.h>

#include <stdbool.h>

typedef struct {
	u32 id;
	bool successfully_created;
} Wren_VertexShader;

typedef struct {
	u32 id;
	bool successfully_created;
} Wren_FragmentShader;

typedef struct {
	u32 id;
	bool successfully_created;
} Wren_ShaderProgram;

/*
 * Creates and links a shader program given a vertex shader and fragment shader.
 *
 * The shaders are passed by "name", without a file extension or parent directory.
 * It is assumed that all shaders are located in `resources/shaders`
 */
Wren_ShaderProgram Wren_ShaderProgram_create_nn(
		const char* vertex_shader_source_name,
		const char* fragment_shader_source_name
		);

typedef enum {
	IMAGE_FORMAT_JPEG,
	IMAGE_FORMAT_PNG,
} Wren_ImageFormat;

typedef enum {
	CHANNEL_COUNT_GRAYSCALE = 1,
	CHANNEL_COUNT_RGB = 3,
	CHANNEL_COUNT_RGBA = 4,
} Wren_ChannelCount;

Wren_ChannelCount Wren_ImageFormat_correspondingChannelCount(Wren_ImageFormat);

typedef enum {
	X0, Y0, X1, Y1
} Wren_TextureAtlasEntry_Index;

typedef u32 Wren_TextureAtlasEntry[4];

typedef struct {
	u32 width;
	u32 height;
	u32 opengl_texture_id;

	u32 number_of_entries;
	u32 current_entry_capacity;
	Wren_TextureAtlasEntry* entries;
} Wren_TextureAtlas;

Wren_TextureAtlas* Wren_TextureAtlas_create_onHeap_n(const char* image_file_name, Wren_ImageFormat);
void Wren_TextureAtlas_destroy_onHeap(Wren_TextureAtlas*);

u32 Wren_TextureAtlas_addEntry(Wren_TextureAtlas*, Wren_TextureAtlasEntry);
u32 Wren_TextureAtlas_addEntry_fromCoords(
		Wren_TextureAtlas*, 
		u32 x0, 
		u32 y0, 
		u32 x1, 
		u32 y1
		);

void Wren_TextureAtlas_getEntryUVs_intoFloats(
		Wren_TextureAtlas* atlas, 
		u32 entry_id, 
		f32* u0, 
		f32* v0, 
		f32* u1, 
		f32* v1
		);

void Wren_TextureAtlas_getEntryUVs_intoArray(
		Wren_TextureAtlas* atlas,
		u32 entry_id,
		f32* dst
		);

typedef struct {
	Wren_TextureAtlas* atlas;
	u32 atlas_entry_index;

	Wren_ShaderProgram shader_program;

	u32 vao;
	u32 vbo;
	u32 ebo;

	f32 x0;
	f32 y0;
	f32 x1;
	f32 y1;
} Wren_TexturedQuad;

Wren_TexturedQuad* Wren_TexturedQuad_create_onHeap(
		Wren_TextureAtlas*,
		u32 atlas_entry_index,

		Wren_ShaderProgram shader_program,
		
		f32 x0,
		f32 y0,
		f32 x1, 
		f32 y1
		);

void Wren_TexturedQuad_destroy_onHeap(Wren_TexturedQuad*);

void Wren_TexturedQuad_render(Wren_TexturedQuad*);


#endif /* Wren_h */
