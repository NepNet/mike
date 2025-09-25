//
// Created by nepnet on 9/25/25.
//

#include "chunk.h"
#include "cglm/cglm.h"

void Chunk_Create() {
}

void Chunk_FillWave(Chunk *chunk) {
	float xStep = (CGLM_PI * 2) / (float) CHUNK_SIZE_X;
	float zStep = (CGLM_PI * 2) / (float) CHUNK_SIZE_Z;
	float height = CHUNK_SIZE_Y / 8.0f;
/*
	for (int z = 0; z < CHUNK_SIZE_Z; z++) {
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			int y = (int) (sinf((float) x * xStep) * cosf((float) z * zStep) * height + height);
			chunk->blocks[x][y][z] = 1;
		}
	}
*/
	for (int z = 0; z < CHUNK_SIZE_Z; z++) {
		for (int x = 0; x < CHUNK_SIZE_X; x++) {
			int y = (int) (sinf((float) x * xStep) * cosf((float) z * zStep) * height + height);
			chunk->blocks[x][0][z] = 1;
		}
	}
}

void Chunk_CreateMesh(Chunk *chunk, void *vertexData, int *vertexCount, void *indicesData, int *indicesCount) {

	int vertices = 0;
	int indices = 0;

	int vertex_size = 8 * sizeof(float);

	struct vertex {
		vec3 position,normal;
		vec2 uv;
	};

	struct vertex *vd = vertexData;

	for (int z = 0; z < CHUNK_SIZE_Z; z++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			for (int x = 0; x < CHUNK_SIZE_X; x++) {
				/*
				const unsigned int block_type = chunk->blocks[x][y][z];
				if (block_type == 0)
					continue;

				//left side
				if (x != 0) {
					const unsigned int left_block = chunk->blocks[x-1][y][z];
					if (left_block == 0) {

					}
				}*/

				//left
				struct vertex v = vd[vertices];
			}
		}
	}

	*vertexCount = vertices;
	*indicesCount = indices;
}
