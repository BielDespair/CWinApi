#pragma once;

#include <vector>


#include "Vertex.hh"



struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;  
};