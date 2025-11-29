#include <glm/glm.hpp>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cassert>

// =========================
// Geometry Types
// =========================

struct Triangle {
    glm::vec3 v0, v1, v2;
    Triangle() : v0(0), v1(0), v2(0) {}
    Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
        : v0(a), v1(b), v2(c) {}
};

struct AABB {
    glm::vec3 min;
    glm::vec3 max;

    AABB()
        : min(std::numeric_limits<float>::max()),
          max(std::numeric_limits<float>::lowest()) {}

    AABB(const glm::vec3& mi, const glm::vec3& ma)
        : min(mi), max(ma) {}

    void Expand(const glm::vec3& p) {
        min = glm::min(min, p);
        max = glm::max(max, p);
    }
    void Expand(const AABB& b) {
        Expand(b.min);
        Expand(b.max);
    }

    glm::vec3 Diagonal() const { return max - min; }

    float SurfaceArea() const {
        glm::vec3 d = Diagonal();
        return 2.f * (d.x*d.y + d.x*d.z + d.y*d.z);
    }

    bool IsValid() const {
        return min.x <= max.x && min.y <= max.y && min.z <= max.z;
    }
};

AABB ComputeTriangleAABB(const Triangle& tri) {
    AABB box;
    box.Expand(tri.v0);
    box.Expand(tri.v1);
    box.Expand(tri.v2);

    // avoid zero-size AABB
    const float eps = 0.001f;
    glm::vec3 d = box.Diagonal();
    for (int i = 0; i < 3; i++) {
        if (d[i] < eps) {
            box.min[i] -= eps * 0.5f;
            box.max[i] += eps * 0.5f;
        }
    }
    return box;
}

// =========================
// BVH Primitive Info
// =========================
struct SimplePrimitiveInfo {
    int orig_index;
    glm::vec3 bbox_min;
    glm::vec3 bbox_max;
    glm::vec3 centroid;

    SimplePrimitiveInfo()
        : orig_index(-1), bbox_min(0), bbox_max(0), centroid(0) {}

    SimplePrimitiveInfo(int id, const AABB& b, const glm::vec3& c)
        : orig_index(id), bbox_min(b.min), bbox_max(b.max), centroid(c) {}
};

// =========================
// BVH Node
// =========================
struct BVHNode {
    glm::vec3 bbox_min;
    glm::vec3 bbox_max;
    int left;
    int right;
    int tri_start;
    int tri_count;

    BVHNode()
        : bbox_min(0), bbox_max(0),
          left(-1), right(-1),
          tri_start(-1), tri_count(0) {}
};

// =========================
// BVH Builder
// =========================
class BVHBuilder {
public:
    BVHBuilder(std::vector<Triangle>& tris, std::vector<BVHNode>& nodes, int leaf_size = 4)
        : triangles(tris), nodes(nodes), max_leaf_size(leaf_size)
    {}

    bool Build() {
        try {
            std::cout << "== BVH Build Start ==\n";

            primitives.clear();
            primitives.reserve(triangles.size());

            std::cout << "Generating primitive info...\n";
            for (int i = 0; i < triangles.size(); i++) {
                AABB b = ComputeTriangleAABB(triangles[i]);
                glm::vec3 c = (triangles[i].v0 + triangles[i].v1 + triangles[i].v2) * (1.f / 3.f);

                std::cout << "Tri " << i
                          << " AABB min(" << b.min.x << "," << b.min.y << "," << b.min.z << ")"
                          << " max(" << b.max.x << "," << b.max.y << "," << b.max.z << ")"
                          << " centroid(" << c.x << "," << c.y << "," << c.z << ")\n";

                primitives.emplace_back(i, b, c);
            }

            nodes.clear();
            nodes.reserve(triangles.size() * 2);

            int root_index = BuildRecursive(0, (int)primitives.size(), 0);
            std::cout << "BVH Build Finished. Root node = " << root_index
                      << "\nTotal Nodes: " << nodes.size() << "\n";

            return true;
        }
        catch (const std::exception& e) {
            std::cout << "BVH Build Exception: " << e.what() << "\n";
            return false;
        }
        catch (...) {
            std::cout << "BVH Build Unknown Exception.\n";
            return false;
        }
    }

private:
    std::vector<Triangle>& triangles;
    std::vector<SimplePrimitiveInfo> primitives;
    std::vector<BVHNode>& nodes;
    int max_leaf_size;

    int BuildRecursive(int start, int count, int depth) {
        if (count <= 0) return -1;

        std::cout << std::string(depth * 2, ' ')
                  << "[Depth " << depth << "] BuildRecursive start=" << start
                  << " count=" << count << "\n";

        // compute node bbox
        AABB box;
        for (int i = start; i < start + count; i++) {
            box.Expand(primitives[i].bbox_min);
            box.Expand(primitives[i].bbox_max);
        }
        if (!box.IsValid()) {
            std::cout << "Invalid AABB detected!\n";
            return -1;
        }

        // create node index
        int node_index = nodes.size();
        nodes.emplace_back();

        // leaf condition
        if (count <= max_leaf_size) {
            BVHNode& leaf = nodes[node_index];
            leaf.bbox_min = box.min;
            leaf.bbox_max = box.max;
            leaf.tri_start = start;
            leaf.tri_count = count;

            std::cout << std::string(depth * 2, ' ')
                      << "Leaf created: tri_start=" << start
                      << " tri_count=" << count << "\n";
            return node_index;
        }

        // choose split axis
        glm::vec3 extent = box.Diagonal();
        int axis = (extent.x >= extent.y && extent.x >= extent.z) ? 0 :
                   (extent.y >= extent.z) ? 1 : 2;

        std::cout << std::string(depth * 2, ' ')
                  << "Split axis = " << axis << " (extent=" << extent.x << "," << extent.y << "," << extent.z << ")\n";

        auto begin = primitives.begin() + start;
        auto end = begin + count;

        std::sort(begin, end, [&](const SimplePrimitiveInfo& a, const SimplePrimitiveInfo& b) {
            return a.centroid[axis] < b.centroid[axis];
        });

        std::cout << std::string(depth * 2, ' ')
                  << "Centroids after sorting:";
        for (int i = start; i < start + count; i++)
            std::cout << " " << primitives[i].centroid[axis];
        std::cout << "\n";

        int mid = start + count / 2;

        int left_index = BuildRecursive(start, mid - start, depth + 1);
        int right_index = BuildRecursive(mid, start + count - mid, depth + 1);

        // compute final bbox from children
        AABB fbox;
        if (left_index != -1)
            fbox.Expand(AABB(nodes[left_index].bbox_min, nodes[left_index].bbox_max));
        if (right_index != -1)
            fbox.Expand(AABB(nodes[right_index].bbox_min, nodes[right_index].bbox_max));

        BVHNode& node = nodes[node_index];
        node.bbox_min = fbox.min;
        node.bbox_max = fbox.max;
        node.left = left_index;
        node.right = right_index;

        std::cout << std::string(depth * 2, ' ')
                  << "Internal node created: left=" << left_index << " right=" << right_index << "\n";

        return node_index;
    }
};

// =========================
// BVH Validation
// =========================
void ValidateBVH(const std::vector<BVHNode>& nodes, int tri_count) {
    std::cout << "\n== BVH Validation ==\n";

    if (nodes.empty()) {
        std::cout << "ERROR: empty BVH\n";
        return;
    }

    std::vector<bool> covered(tri_count, false);
    int sum_leaf_tris = 0;

    for (int i = 0; i < nodes.size(); i++) {
        const BVHNode& n = nodes[i];

        std::cout << "Node " << i << ": bbox("
                  << n.bbox_min.x << "," << n.bbox_min.y << "," << n.bbox_min.z << ") - ("
                  << n.bbox_max.x << "," << n.bbox_max.y << "," << n.bbox_max.z << ")";

        if (n.tri_count > 0)
            std::cout << "  [Leaf: start=" << n.tri_start << " count=" << n.tri_count << "]";

        std::cout << "\n";

        if (n.tri_count > 0) {
            sum_leaf_tris += n.tri_count;
            for (int t = n.tri_start; t < n.tri_start + n.tri_count; t++) {
                if (t >= 0 && t < tri_count) covered[t] = true;
            }
        }
    }

    bool ok = true;
    for (int i = 0; i < tri_count; i++) {
        if (!covered[i]) {
            std::cout << "Missing tri " << i << "\n";
            ok = false;
        }
    }

    if (ok) std::cout << "All triangles covered.\n";
    std::cout << "Sum of triangles in leaves = " << sum_leaf_tris << "\n";

    // bbox hierarchy check
    for (int i = 0; i < nodes.size(); i++) {
        const BVHNode& n = nodes[i];
        if (n.left != -1) {
            for (int c : { n.left, n.right }) {
                if (c != -1) {
                    const BVHNode& ch = nodes[c];
                    for (int ax = 0; ax < 3; ax++) {
                        if (ch.bbox_min[ax] < n.bbox_min[ax] - 1e-4f ||
                            ch.bbox_max[ax] > n.bbox_max[ax] + 1e-4f) {
                            std::cout << "BBox error at node " << i << " child " << c << "\n";
                            ok = false;
                        }
                    }
                }
            }
        }
    }

    if (ok) std::cout << "Hierarchy bbox OK.\n";
    std::cout << "== End Validation ==\n";
}

// =========================
// Example main()
// =========================

void CreateTestCase1(std::vector<Triangle>& tris) {
	tris.emplace_back(glm::vec3(0,0,0), glm::vec3(1,0,0), glm::vec3(0,1,0));
	tris.emplace_back(glm::vec3(2,2,0), glm::vec3(3,2,0), glm::vec3(2,3,0));
	tris.emplace_back(glm::vec3(-1,-1,0), glm::vec3(-2,-1,0), glm::vec3(-1,-2,0));
}

void CreateTestCase2(std::vector<Triangle>& tris){
	tris.reserve(20);

    // helper lambda：生成一个随机三角形
    auto makeTri = [&](float cx, float cy, float scale) {
        float dx1 = ((rand() % 100) / 100.f - 0.5f) * scale;
        float dy1 = ((rand() % 100) / 100.f - 0.5f) * scale;
        float dx2 = ((rand() % 100) / 100.f - 0.5f) * scale;
        float dy2 = ((rand() % 100) / 100.f - 0.5f) * scale;
        float dx3 = ((rand() % 100) / 100.f - 0.5f) * scale;
        float dy3 = ((rand() % 100) / 100.f - 0.5f) * scale;

        return Triangle(
            glm::vec3(cx + dx1, cy + dy1, 0),
            glm::vec3(cx + dx2, cy + dy2, 0),
            glm::vec3(cx + dx3, cy + dy3, 0)
        );
    };

    // 放置在不同区域
    srand(1234); // 固定随机种子，便于调试

    // cluster 1：左下
    for (int i=0; i<5; i++) tris.push_back(makeTri(-5, -5, 2.0f));

    // cluster 2：右上
    for (int i=0; i<5; i++) tris.push_back(makeTri(5, 5, 2.5f));

    // cluster 3：右下
    for (int i=0; i<5; i++) tris.push_back(makeTri(5, -4, 2.0f));

    // cluster 4：中间区域
    for (int i=0; i<5; i++) tris.push_back(makeTri(0, 0, 3.0f));

    // 输出测试数据
    std::cout << "===== Test Triangles (20) =====\n";
    for (int i = 0; i < tris.size(); i++) {
        const auto& t = tris[i];
        std::cout << "Tri " << i << ": "
                  << "(" << t.v0.x << "," << t.v0.y << "), "
                  << "(" << t.v1.x << "," << t.v1.y << "), "
                  << "(" << t.v2.x << "," << t.v2.y << ")\n";
    }
}

int main() {
    // build simple test triangles
    std::vector<Triangle> tris;
	CreateTestCase1(tris);

    std::vector<BVHNode> nodes;
    BVHBuilder builder(tris, nodes, 1);

    builder.Build();
    ValidateBVH(nodes, tris.size());

    return 0;
}
