//
// Created by nepnet on 9/25/25.
//

#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE_X 2
#define CHUNK_SIZE_Y 2
#define CHUNK_SIZE_Z 2

struct {
	unsigned int blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
} typedef Chunk;

void Chunk_Create();

void Chunk_FillWave(Chunk *chunk);

void Chunk_CreateMesh(Chunk *chunk, void *vertexData, int *vertexCount, void *indicesData, int *indicesCount);

#endif //CHUNK_H
