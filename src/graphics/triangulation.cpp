#include <graphics/triangulation.hh>
#include <math/Vector.hh>
#include <vector>

Mesh2D triangulate2D(Vec2* vertices, size_t size)
{
    Mesh2D mesh {};
    
    #ifdef _DEBUG
        if (!vertices || size < 3 || size > 1024) {
            return mesh;
        }
    #endif


    std::vector<int> indexList(size);
    for (size_t i = 0; i < size; i++)
    {
        indexList[i] = i;
    }

    int totalTriangleCount = size - 2;
    int totalTriangleIndexCount = totalTriangleCount * 3;
    std::vector<int> triangles(totalTriangleIndexCount);
    int triangleIndexCount = 0;

    
    while (indexList.size() > 3) {
        for (size_t i = 0; i < indexList.size(); i++)
        {
            int a = indexList[i];
            int b = get_circular(indexList, i - 1);
            int c = get_circular(indexList, i + 1);

            Vec2 va = vertices[a];
            Vec2 vb = vertices[b];
            Vec2 vc = vertices[c];

            Vec2 va_to_vb = vb - va;
            Vec2 va_to_vc = vc - va;


            if (va_to_vb.cross(va_to_vc) < 0.0f) {
                continue;
            }

            bool isEar = true;

            for (size_t j = 0; j < size; j++) {
                if (j == a || j == b || j == c) {
                    continue;
                }

                Vec2 p = vertices[j];
                if (is_point_in_triangle(p, vb, va, vc)) {
                    isEar = false;
                    break;
                }
            }

            if (isEar) {
                triangles[triangleIndexCount++] = b;
                triangles[triangleIndexCount++] = a;
                triangles[triangleIndexCount++] = c;

                indexList.erase(indexList.begin() + i);
                break;
            }
            
        }   
    }


    triangles[triangleIndexCount++] = indexList[0];
    triangles[triangleIndexCount++] = indexList[1];
    triangles[triangleIndexCount++] = indexList[2];

    mesh.vertices = vertices;
    mesh.vertexCount = size;
    mesh.indices = triangles;
    return mesh;
}


int get_circular(const std::vector<int>& list, int i) {
    int n = (int)list.size();
    return list[(i % n + n) % n];
}

bool is_point_in_triangle(Vec2 p, Vec2 a, Vec2 b, Vec2 c) {
    Vec2 ab = b - a;
    Vec2 bc = c - b;
    Vec2 ca = a - c;

    Vec2 ap = p - a;
    Vec2 bp = p - b;
    Vec2 cp = p - c;

    if (ab.cross(ap) > 0.0f)
        return false;
    if (bc.cross(bp) > 0.0f)
        return false;
    if (ca.cross(cp) > 0.0f)
        return false;

    return true;

}