#!/usr/bin/env python3

import licant

licant.module("rabbitreactphysics3d",
	sources=[
		"rabbitreactphysics3d/RigidBodyDrawer.cpp",
		"rabbitreactphysics3d/RigidBodyPair.cpp",
	],
	include_paths=".", 
)