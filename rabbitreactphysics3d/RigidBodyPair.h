#ifndef RIGID_BODY_PAIR_H
#define RIGID_BODY_PAIR_H

#include <memory>
#include <rabbit/mesh/mesh.h>
#include <rabbit/mesh/primitives.h>
#include <rabbit/opengl/qtscene.h>
#include <rabbitreactphysics3d/RigidBodyDrawer.h>
#include <rabbitreactphysics3d/react_cast.h>
#include <reactphysics3d/reactphysics3d.h>

class RigidBodyPair
{
public:
    reactphysics3d::RigidBody *body = nullptr;
    std::unique_ptr<RigidBodyDrawer> drawer = {};

public:
    RigidBodyPair() : body(nullptr) {}
    RigidBodyPair(const RigidBodyPair &other) = delete;
    RigidBodyPair &operator=(const RigidBodyPair &other) = delete;

    RigidBodyPair(reactphysics3d::RigidBody *body, bool vis)
        : body(body), drawer(new RigidBodyDrawer(body, vis))
    {
    }

    RigidBodyPair(RigidBodyPair &&oth)
        : body(oth.body), drawer(std::move(oth.drawer))
    {
        oth.body = nullptr;
    }

    RigidBodyPair &operator=(RigidBodyPair &&oth)
    {
        body = oth.body;
        drawer = std::move(oth.drawer);
        oth.body = nullptr;
        return *this;
    }

    static RigidBodyPair make(reactphysics3d::PhysicsWorld *world,
                              const ralgo::pose3<float> &pose,
                              bool vis = true)
    {
        auto body = world->createRigidBody(rabbit::react_cast(pose));
        return RigidBodyPair(body, vis);
    }

    ralgo::pose3<float> get_pose() const
    {
        return rabbit::react_cast(body->getTransform());
    }
};

#endif
