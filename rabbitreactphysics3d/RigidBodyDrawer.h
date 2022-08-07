#include <rabbit/mesh/mesh.h>
#include <rabbit/mesh/primitives.h>
#include <rabbit/opengl/qtscene.h>
#include <rabbitreactphysics3d/react_cast.h>
#include <reactphysics3d/reactphysics3d.h>

class RigidBodyDrawer : public rabbit::drawable_object
{
    reactphysics3d::RigidBody *m_body = nullptr;
    rabbit::mesh<float> m_mesh = {};

public:
    RigidBodyDrawer(const RigidBodyDrawer &other) = default;
    RigidBodyDrawer &operator=(const RigidBodyDrawer &other) = default;
    RigidBodyDrawer(RigidBodyDrawer &&other) = default;
    RigidBodyDrawer &operator=(RigidBodyDrawer &&other) = default;

    ~RigidBodyDrawer() override = default;

    RigidBodyDrawer(reactphysics3d::RigidBody *body, bool vis) : m_body(body)
    {
        if (vis)
            m_mesh = rabbit::cylinder_mesh(0.1, 1, 10, 10);
    }

    RigidBodyDrawer(reactphysics3d::RigidBody *body, rabbit::mesh<float> mesh)
        : m_body(body), m_mesh(mesh)
    {
    }

    void draw_on(rabbit::view &v) override
    {
        v.draw_mesh(m_mesh,
                    rabbit::react_cast(m_body->getTransform()).to_mat4());
    }
};