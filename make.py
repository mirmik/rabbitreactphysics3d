#!/usr/bin/env python3

import os
import shutil
import licant
import licant.install

licant.include("rabbitreactphysics3d", "rabbitreactphysics3d.g.py")

target = "librabbitreactphysics3d.so"

install_include_path = '/usr/local/include/rabbitreactphysics3d' 
install_directory_path = '/usr/lib/'
install_library_path = os.path.join(install_directory_path, target) 
  
licant.cxx_static_and_shared("libs",
	shared_lib = "librabbitreactphysics3d.so",
	static_lib = "librabbitreactphysics3d.a",
	mdepends=[
		"rabbitreactphysics3d",
	],
	cxx_flags="-fPIC -Weffc++ -Wextra",
	cc_flags="-fPIC"
)

licant.install.install_library(
	tgt="install",
	uninstall="uninstall",
	libtgt=["librabbitreactphysics3d.so", "librabbitreactphysics3d.a"],
	hroot="rabbit",
	headers="rabbit")

licant.ex("libs")
