//
// Created by nepnet on 9/25/25.
//

#include "chunk.h"

#include <string.h>

#include "cglm/cglm.h"
#include "cube.h"

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
			chunk->blocks[x][0][z] = 1;
			for (int y = 1; y < CHUNK_SIZE_Y; y++) {
				if ((x+z) % 2 == 0 && y < 2) {
					chunk->blocks[x][y][z] = 1;
				}else
				{
					chunk->blocks[x][y][z] = 0;
				}
			}
		}
	}
}

void Chunk_CreateMesh(Chunk *chunk, void **vertexData, int *vertexCount, void **indicesData, int *indicesCount) {

	int vertices = 0;
	int indices = 0;

	int vertex_size = 8 * sizeof(float);


	struct vertex {
		vec3 position,normal;
		vec2 uv;
	};

	size_t expectedVertexCount = 4 * vertex_size * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6;
	size_t expectedIndicesCount = 6 * sizeof(int) * CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6;

	*vertexData = malloc(expectedVertexCount);
	*indicesData = malloc(expectedIndicesCount);

	struct vertex *vd = *vertexData;
	unsigned int *ids = *indicesData;

	for (int z = 0; z < CHUNK_SIZE_Z; z++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			for (int x = 0; x < CHUNK_SIZE_X; x++) {

				if (chunk->blocks[x][y][z] == 0)
					continue;

				int neighbours[6] = {0};

				if (z < CHUNK_SIZE_Z - 1)
					neighbours[0] = chunk->blocks[x][y][z+1];
				if (z > 0)
					neighbours[1] = chunk->blocks[x][y][z-1];
				if (x < CHUNK_SIZE_X - 1)
					neighbours[2] = chunk->blocks[x+1][y][z];
				if (x > 0)
					neighbours[3] = chunk->blocks[x-1][y][z];
				if (y < CHUNK_SIZE_Y - 1)
					neighbours[4] = chunk->blocks[x][y+1][z];
				if (y > 0)
					neighbours[5] = chunk->blocks[x][y-1][z];

				for (int f = 0; f < 6; f++) {
					memcpy(&vd[vertices], &cube_vertices[f * 4], sizeof(struct vertex) * 4);

					if (neighbours[f] != 0)
						continue;

					vec3 offset = {x,y,z};
					for (int i = 0; i < 4; i++) {
						glm_vec3_add(vd[vertices + i].position, offset,vd[vertices + i].position);
					}

					ids[indices + 0] = cube_indices[0] + vertices;
					ids[indices + 1] = cube_indices[1] + vertices;
					ids[indices + 2] = cube_indices[2] + vertices;
					ids[indices + 3] = cube_indices[3] + vertices;
					ids[indices + 4] = cube_indices[4] + vertices;
					ids[indices + 5] = cube_indices[5] + vertices;
					vertices += 4;
					indices += 6;
				}
			}
		}
	}

	*vertexCount = vertices;
	*indicesCount = indices;
/*
	*vertexCount = 4 * 6;
	*indicesCount = 6 * 6;
	*vertexData = cube_vertices;
	*indicesData = cube_indices;
*/
}
