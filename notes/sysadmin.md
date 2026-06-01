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
