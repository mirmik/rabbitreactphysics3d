#ifndef RABBIT_REACTPHYSICS_UTIL_H
#define RABBIT_REACTPHYSICS_UTIL_H

#include <reactphysics3d/reactphysics3d.h>
#include <nos/fprint.h>

static inline ralgo::pose3<float> get_pose(reactphysics3d::RigidBody* body) 
{
    return rabbit::react_cast(body->getTransform());
}

static inline std::string get_pose_as_json(reactphysics3d::RigidBody* body) 
{
    auto pose = rabbit::react_cast(body->getTransform());
    auto lin = pose.lin;
    auto qang = pose.ang;
    return nos::format("{{'lin':[{},{},{}],'qang':[{},{},{},{}]}\n", lin.x, lin.y, lin.z, qang.x, qang.y, qang.z, qang.w);
}

static inline void set_joint_torque(reactphysics3d::HingeJoint *joint,
                                    float torque)
{
    if (torque == 0)
    {
        joint->enableMotor(false);
        joint->setMaxMotorTorque(0);
        joint->setMotorSpeed(0);
    }

    float sign = std::signbit(torque) ? -1 : 1;
    joint->enableMotor(true);
    joint->setMaxMotorTorque(std::abs(torque));
    joint->setMotorSpeed(1000000 * sign);
}

static inline double joint_angular_velocity(reactphysics3d::HingeJoint *joint)
{
    return joint->getMotorSpeed();
}

static inline reactphysics3d::HingeJoint *
create_hinge_joint(reactphysics3d::PhysicsWorld *world,
                   rabbit::vec3f point,
                   rabbit::vec3f _axis,
                   reactphysics3d::RigidBody *body1,
                   reactphysics3d::RigidBody *body2)
{
    const reactphysics3d::Vector3 anchorPoint = rabbit::react_cast(point);
    const reactphysics3d::Vector3 axis = rabbit::react_cast(_axis);
    reactphysics3d::HingeJointInfo jointInfo(body1, body2, anchorPoint, axis);
    reactphysics3d::HingeJoint *joint;
    joint = dynamic_cast<reactphysics3d::HingeJoint *>(
        world->createJoint(jointInfo));
    return joint;
}

static inline reactphysics3d::FixedJoint *
create_fixed_joint(reactphysics3d::PhysicsWorld *world,
                   rabbit::vec3f point,
                   reactphysics3d::RigidBody *body1,
                   reactphysics3d::RigidBody *body2)
{
    const reactphysics3d::Vector3 anchorPoint = rabbit::react_cast(point);
    reactphysics3d::FixedJointInfo jointInfo(body1, body2, anchorPoint);
    reactphysics3d::FixedJoint *joint;
    joint = dynamic_cast<reactphysics3d::FixedJoint *>(
        world->createJoint(jointInfo));
    return joint;
}

#endif