[how to build software](https://tldp.org/HOWTO/Software-Building-HOWTO-2.html)

# untar and gunzip

```sh
tar xzvf filename
```

# preview the untar and gunzip process

```sh
tar tzvf filename
```

The above method of unpacking "tarballs" is equivalent to either of the following:

```sh
gzip -cd filename | tar xvf -
gunzip -c filename | tar xvf -
```

(The '-' causes the tar command to take its input from stdin.)

Occasionally, you may need to update or incorporate bug fixes into the unarchived source files using a patch or diff file that lists the changes. The doc files and/or README file will inform you should this be the case. The normal syntax for invoking Larry Wall's powerful patch utility is patch < patchfile.

An Imakefile is, to quote the man page, a "template" Makefile. The imake utility constructs a Makefile appropriate for your system from the Imakefile. In almost all cases, however, you would run xmkmf, a shell script that invokes imake, a front end for it. Check the README or INSTALL file included in the software archive for specific instructions. (If, after dearchiving the source files, there is an Imake file present in the base directory, this is a dead giveaway that xmkmf should be run.) Read the Imake and xmkmf man pages for a more detailed analysis of the procedure.

Invoking xmkmf uses the Imake file to build a new Makefile appropriate for your system. You would normally invoke xmkmf with the -a argument, to automatically do a make Makefiles, make includes, and make depend. This sets the variables and defines the library locations for the compiler and linker. Sometimes, there will be no Imake file, instead there will be an INSTALL or configure script that will accomplish this purpose. Note that if you run configure, it should be invoked as ./configure to ensure that the correct configure script in the current directory is called. In most cases, the README file included with the distribution will explain the install procedure.

It is usually a good idea to visually inspect the Makefile that xmkmf or one of the install scripts builds. The Makefile will normally be correct for your system, but you may occasionally be required to "tweak" it or correct errors manually.

Installing the freshly built binaries into the appropriate system directories is usually a matter of running make install as root. The usual directories for system-wide binaries on modern Linux distributions are /usr/bin, /usr/X11R6/bin, and /usr/local/bin. The preferred directory for new packages is /usr/local/bin, as this will keep separate binaries not part of the original Linux installation.

Packages originally targeted for commercial versions of UNIX may attempt to install in the /opt or other unfamiliar directory. This will, of course, result in an installation error if the intended installation directory does not exist. The simplest way to deal with this is to create, as root, an /opt directory, let the package install there, then add that directory to the PATH environmental variable. Alternatively, you may create symbolic links to the /usr/local/bin directory.

Your general installation procedure will therefore be:

Read the README file and other applicable docs.
Run xmkmf -a, or the INSTALL or configure script.
Check the Makefile.
If necessary, run make clean, make Makefiles, make includes, and make depend.
Run make.
Check file permissions.
If necessary, run make install.

# example of failed rpms

Enough! Download the "tarball", XaoS-3.0.tar.gz, available from the ftp site, as well as from the home page. Try building it. Running ./configure, make, and finally (as root) make install, works flawlessly.

This is one of an number of examples of prepackaged binaries being more trouble than they are worth.

# example make and make install

```sh
# unpack and read documentation
tar xf filename
cd {directory created by above step}
less README
less INSTALL

# generate customised makefile
./configure {some options ...}

# compile everything in the local directory
make

# update global directories
sudo make install
```

## if there is no sudo available

```sh
su  # must then enter root password
make install
exit
```

## moving build into its own folder

```sh
# unpack into a directory {packagename}
tar xf filename

# create separate build directory
mkdir {packagename}-build

# compile everything in the separate build directory
cd {packagename}-build
../{packagename}/configure {some options}
make

# update global directories
sudo make install
```

Correct Workflow Breakdowntar xf filename extracts the source code.mkdir {packagename}-build creates the build folder.cd {packagename}-build moves you into the build folder.../{packagename}/configure reads the source but configures the build here.make builds the binaries inside the current folder.sudo make install moves the local binaries to system folders.

## cmake (configure make) instead of ./configure

```sh
cmake . -DCMAKE_BUILD_TYPE=Release {some options ...}
```

## Environment Variables

Options to configure the compilation and installation of an application are usually passed as command-line parameters to the “configure” script or the make program. However sometimes configuration options are passed via environment variables instead. These can be specified by placing the definitions on the start of the command, eg

```sh
NAME=tom ENABLE_FOO=no ./configure
```

Environment variables can also be defined before running the command:

```sh
export NAME=tom
export ENABLE_FOO=no
./configure
```

## Example Multifile Make Setup

To organize a multi-folder project, developers typically separate source code, headers, libraries, and built files into their own dedicated directories. [1, 2, 3]
Here is a standard, professional project layout and the updated Makefile required to build it.

## Recommended Directory Structure

my_project/
├── include/ # All header files (.h)
│ ├── prog.h
│ └── libmylib.h
├── src/ # Main application source code (.c)
│ └── prog.c
├── lib/ # Custom library source code and built libraries
│ ├── libmylib.c
│ └── libmylib.a # (Generated automatically)
├── obj/ # Temporary object files (.o) (Generated automatically)
└── Makefile # Build instructions at the root level

## The Multi-Folder Makefile

Save this Makefile in the root directory (my_project/). It uses variables to cleanly manage the paths.

```sh
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
# Directories
SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj
# Targets
MAIN_APP = prog
STATIC_LIB = $(LIB_DIR)/libmylib.a
# Build the main application
$(MAIN_APP): $(SRC_DIR)/prog.c $(STATIC_LIB) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/prog.c -L$(LIB_DIR) -lmylib
# Build the static library
$(STATIC_LIB): $(OBJ_DIR)/libmylib.o
	ar -rcs $@ $<
# Compile library source into object folder
$(OBJ_DIR)/libmylib.o: $(LIB_DIR)/libmylib.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
# Create the object directory if it does not exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
# Clean up built files
clean:
	rm -rf $(OBJ_DIR) $(MAIN_APP) $(LIB_DIR)/*.a
```

## Key Changes Explained

- -Iinclude: Tells the compiler to look inside the /include directory for header files. You can now use #include "prog.h" without worrying about relative paths.
- -L$(LIB_DIR): Tells the linker to look inside the /lib folder instead of the current directory (.) to find libmylib.a.
- | $(OBJ_DIR): This is an "order-only prerequisite". It ensures the obj/ folder is created before the compiler tries to write files into it.
- $@ and $<: These are automatic shorthand variables. $@ means "the target file" and $< means "the first prerequisite file". [4, 5, 6]

---

To wrap up this project setup, let me know if you would like to:

- Automate the Makefile to find all .c files automatically using wildcards
- Add a debugging target for tools like GDB
- Convert this into a shared library (.so) setup instead of static (.a) [7, 8, 9]

Which improvement should we implement?

[1] [https://www.studyplan.dev](https://www.studyplan.dev/cmake/cmake-project-structure-and-subdirectories)
[2] [https://www.ni.com](https://www.ni.com/docs/en-US/bundle/labview/page/managing-a-project-in-labview.html)
[3] [https://www.reddit.com](https://www.reddit.com/r/cpp_questions/comments/j5bkqj/place_header_files_in_separate_folder_or_not/)
[4] [https://os.phil-opp.com](https://os.phil-opp.com/multiboot-kernel/)
[5] [https://modern-fortran-in-science-and-technology.readthedocs.io](https://modern-fortran-in-science-and-technology.readthedocs.io/en/latest/chapter_fortran_projects.html)
[6] [https://shazaali.substack.com](https://shazaali.substack.com/p/makefiles)
[7] [https://dev.to](https://dev.to/medunes/build-c-projects-like-a-pro-a-guide-to-idiomatic-makefiles-53b6)
[8] [https://blog.devgenius.io](https://blog.devgenius.io/makefiles-a-practical-guide-techniques-and-templates-d7d99047bf63)
[9] [https://mangalam0015k.medium.com](https://mangalam0015k.medium.com/mastering-multi-file-c-projects-organize-guard-and-compile-f43fb9efa553)
