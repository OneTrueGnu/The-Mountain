#include "Wren.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <glad/glad.h>
#include <stb_image.h>

Wren_ChannelCount Wren_ImageFormat_correspondingWren_ChannelCount(Wren_ImageFormat image_format) {
	switch(image_format) {
		case IMAGE_FORMAT_JPEG:
			return CHANNEL_COUNT_RGB;
		case IMAGE_FORMAT_PNG:
			return CHANNEL_COUNT_RGBA;
	}
}

Wren_TextureAtlas* Wren_TextureAtlas_create_onHeap_n(const char* image_file_name, Wren_ImageFormat image_file_format) {
	Wren_TextureAtlas* created_atlas = malloc(sizeof(Wren_TextureAtlas));
	
	char* image_file_extension;
	switch (image_file_format) {
		case IMAGE_FORMAT_JPEG:
			image_file_extension = ".jpeg";
			break;
		case IMAGE_FORMAT_PNG:
			image_file_extension = ".png";
			break;
	}

	char* image_file_path;
	asprintf(&image_file_path, "resources/images/%s%s", image_file_name, image_file_extension);

	int loaded_image_width, loaded_image_height, loaded_image_channel_count;
	u8* loaded_image_data = stbi_load(
			image_file_path, 
			&loaded_image_width,
			&loaded_image_height,
			&loaded_image_channel_count,
			Wren_ImageFormat_correspondingWren_ChannelCount(image_file_format)
			);

	glActiveTexture(GL_TEXTURE0);
	u32 loaded_texture_id;
	glGenTextures(1, &loaded_texture_id);
	glBindTexture(GL_TEXTURE_2D, loaded_texture_id); {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float out_of_bounds_access_color[4] = { 1.0, 0.0, 0.0, 1.0 };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, out_of_bounds_access_color);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		u32 mipmap_level_of_a_base_image = 0;
		glTexImage2D(
				GL_TEXTURE_2D, 
				mipmap_level_of_a_base_image, 
				GL_RGBA, 
				loaded_image_width, 
				loaded_image_height,
				0, 
				GL_RGBA, 
				GL_UNSIGNED_BYTE, 
				loaded_image_data
				);
		stbi_image_free(loaded_image_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} glBindTexture(GL_TEXTURE_2D, 0);

	*created_atlas = (Wren_TextureAtlas){
		.height = (u32)loaded_image_height,
		.width = (u32)loaded_image_width,
		.opengl_texture_id = loaded_texture_id,
		
		.number_of_entries = 0,
		.current_entry_capacity = 1,
		.entries = malloc(sizeof *created_atlas->entries),
	};

	free(image_file_path);

	return created_atlas;
}

void Wren_TextureAtlas_destroy_onHeap(Wren_TextureAtlas* atlas_to_destroy) {
	free(atlas_to_destroy->entries);
	free(atlas_to_destroy);
}

u32 Wren_TextureAtlas_addEntry(Wren_TextureAtlas* atlas, Wren_TextureAtlasEntry new_entry) {
	u32 new_entry_id = atlas->number_of_entries;

	++atlas->number_of_entries;
	if (atlas->number_of_entries > atlas->current_entry_capacity) {
		atlas->entries = realloc(atlas->entries, atlas->number_of_entries * (sizeof *atlas->entries));
	}

	memcpy(atlas->entries[new_entry_id], new_entry, sizeof(Wren_TextureAtlasEntry));

	return new_entry_id;
}

u32 Wren_TextureAtlas_addEntry_fromCoords(
		Wren_TextureAtlas* atlas, 
		u32 x0, 
		u32 y0, 
		u32 x1, 
		u32 y1
		) {
	Wren_TextureAtlasEntry new_entry = { x0, y0, x1, y1 };

	return Wren_TextureAtlas_addEntry(atlas, new_entry);
}

void Wren_TextureAtlas_getEntryUVs_intoFloats(
		Wren_TextureAtlas* atlas, 
		u32 entry_id, 
		f32* u0, 
		f32* v0, 
		f32* u1, 
		f32* v1
		) {
	*u0 = (f32)atlas->entries[entry_id][X0] / (f32)atlas->width;
	*v0 = (f32)atlas->entries[entry_id][Y0] / (f32)atlas->height;
	*u1 = (f32)atlas->entries[entry_id][X1] / (f32)atlas->width;
	*v1 = (f32)atlas->entries[entry_id][Y1] / (f32)atlas->height;
}

void Wren_TextureAtlas_getEntryUVs_intoArray(
		Wren_TextureAtlas* atlas,
		u32 entry_id,
		f32* dst
		) {
	Wren_TextureAtlas_getEntryUVs_intoFloats(atlas, entry_id, &(dst[0]), &(dst[1]), &(dst[2]), &(dst[3]));
}


