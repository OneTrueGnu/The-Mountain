#include "Wren.h"

#include <stdlib.h>

Wren_TexturedQuad* Wren_TexturedQuad_create_onHeap(
		Wren_TextureAtlas* atlas,
		u32 atlas_entry_index,

		Wren_ShaderProgram shader_program,
		
		f32 x0,
		f32 y0,
		f32 x1, 
		f32 y1
		) {

	Wren_TexturedQuad* created_quad = malloc(sizeof *created_quad);
	*created_quad = (Wren_TexturedQuad){
		.atlas = atlas,
		.atlas_entry_index = atlas_entry_index,
		.shader_program = shader_program,
		
		.x0 = x0, .y0 = y0, .x1 = x1, .y1 = y1,
	};
	glGenVertexArrays(1, &created_quad->vao);
	glGenBuffers(1, &created_quad->vbo);
	glGenBuffers(1, &created_quad->ebo);

	glBindVertexArray(created_quad->vao);
	glBindBuffer(GL_ARRAY_BUFFER, created_quad->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, created_quad->ebo);

	f32 u0, v0, u1, v1;
	Wren_TextureAtlas_getEntryUVs_intoFloats(created_quad->atlas, created_quad->atlas_entry_index, &u0, &v0, &u1, &v1);

    f32 vertex_data[16] = {
        x0, y0, u0, v0,  
        x1, y0, u1, v0, 
        x0, y1, u0, v1,
        x1, y1, u1, v1,
    };

    u32 indices[6] = {
        0, 1, 2,
        1, 2, 3,
    };

    glBufferData(GL_ARRAY_BUFFER, (sizeof vertex_data), vertex_data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), (void*)(2 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

	return created_quad;
}  

void Wren_TexturedQuad_destroy_onHeap(Wren_TexturedQuad* quad) {
    if (quad == NULL) return;

    glDeleteVertexArrays(1, &quad->vao);
    glDeleteBuffers(1, &quad->vbo);
    glDeleteBuffers(1, &quad->ebo);

    free(quad);
}

void Wren_TexturedQuad_render(Wren_TexturedQuad* quad) {
    glUseProgram(quad->shader_program.id);
    glBindTexture(GL_TEXTURE_2D, quad->atlas->opengl_texture_id);
    glBindVertexArray(quad->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

