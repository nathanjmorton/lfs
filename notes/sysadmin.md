# enter orbstack

```sh
orb shell -m lfs-host
```

# linux shell commands

```sh
gcc -dumpmachine #system-triplet eg x86_64-linux-gnu
```

# building lfs notes

## chapters 1-4

- Procedures performed as the root user after Section 2.4 must have the LFS environment variable set FOR THE ROOT USER.

## chapters 5-6

- The /mnt/lfs partition must be mounted.
- These two chapters must be done as user lfs. A su - lfs command must be issued before performing any task in these chapters. If you don't do that, you are at risk of installing packages to the host, and potentially rendering it unusable.
- The procedures in General Compilation Instructions are critical. If there is any doubt a package has been installed correctly, ensure the previously expanded tarball has been removed, then re-extract the package, and complete all the instructions in that section.

## chapters 7-10

- A few operations, from “Preparing Virtual Kernel File Systems” to “Entering the Chroot Environment,” must be done as the root user, with the LFS environment variable set for the root user.
- When entering chroot, the LFS environment variable must be set for root. The LFS variable is not used after the chroot environment has been entered.
- The virtual file systems must be mounted. This can be done before or after entering chroot by changing to a host virtual terminal and, as root, running the commands in Section 7.3.1, “Mounting and Populating /dev” and Section 7.3.2, “Mounting Virtual Kernel File Systems.”

## notes on the partitioning chapter

- instead of creating a partition in the orbstack vm, we'll just create a directory and set the LFS variable

```sh
sudo mkdir -pv /mnt/lfs
export LFS=/mnt/lfs
```

No conflicts. Here's how each requirement maps to the directory approach:

Chapters 1-4
• "LFS variable set for root" — No conflict. export LFS=/mnt/lfs works identically whether it points to a partition or directory.

Chapters 5-6
• "/mnt/lfs partition must be mounted" — No conflict. With a directory, it's always accessible. You simply skip the mount command from Section 2.4. The requirement is functionally about the path being available, which a directory always satisfies.
• The su - lfs and compilation instructions are filesystem-agnostic.

Chapters 7-10
• Virtual filesystem mounts (/proc, /sys, /dev, /run under $LFS) — No conflict. These bind mounts target paths inside $LFS, so it makes no difference whether $LFS is a partition mount point or a plain directory.
• Chroot entry — No conflict. chroot $LFS works the same either way.
• "Remount after reboot" — This is actually easier with a directory: nothing to remount. With a partition, forgetting to remount before resuming work is a common mistake. With a directory, it's always there.

One thing to watch: The underlying VM filesystem must support Linux semantics (permissions, symlinks, hard links, device files). Ubuntu's default ext4 filesystem does, so you're fine. The host-mounted Mac path (via OrbStack's macOS share) does not — make sure /mnt/lfs is on the VM's own disk, not under /Users/nathanjmorton.
