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
