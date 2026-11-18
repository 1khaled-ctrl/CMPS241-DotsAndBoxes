# Alpine Linux VM setup (game starts at boot, no login)

## 1. Create the virtual machine

1. Download the **Virtual** edition of Alpine Linux, **x86_64** ISO, from
   <https://alpinelinux.org/downloads/>.
   (Mac with an Apple chip: use UTM instead of VirtualBox and the **aarch64** ISO.)
2. In VirtualBox: **New** → Type *Linux*, Version *Other Linux (64-bit)*,
   1024 MB RAM, a 4 GB virtual disk. Attach the ISO and start the VM.

## 2. Install Alpine on the virtual disk

1. Log in as `root` (no password).
2. Run `setup-alpine` and answer the questions. The defaults are fine, except:
   - set a root password you will remember,
   - when it asks which disk to use: `sda`, then `sys`, then confirm with `y`.
3. Run `poweroff`, remove the ISO from the VM settings, and start the VM again.
   Log in as `root` with your new password.

## 3. Install the tools and build the game

```sh
apk update
apk add build-base git gdb valgrind nano
cd /root
git clone https://github.com/<github-user>/<repo-name>.git DotsAndBoxes
cd DotsAndBoxes
make
./dotsandboxes        # test it once
```

For a private repo, git asks for a username and password: the password is your
GitHub personal access token (Lecture 21).

## 4. Start the game automatically at boot

When Alpine starts, its `init` program reads `/etc/inittab`. One line of that
file shows the login prompt on the first screen (`tty1`). We replace the login
prompt with our game.

```sh
cp /etc/inittab /etc/inittab.bak     # backup, to undo later
nano /etc/inittab
```

Find this line:

```
tty1::respawn:/sbin/getty 38400 tty1
```

and replace it with:

```
tty1::respawn:/root/DotsAndBoxes/dotsandboxes
```

Save (Ctrl+X, then Y, then Enter) and run `reboot`. The VM now opens straight
into the game, with no username or password.

- `tty1` = the first screen of the VM, the one you see at boot.
- `respawn` = when the program ends, start it again, so a new game starts
  after every finished game.

## 5. Working on the VM afterwards

- Press **Alt+F2** to get a normal login on the second screen (`tty2`):
  there you can `git pull` and `make`. Press **Alt+F1** to go back to the game.
- To undo the autostart: `cp /etc/inittab.bak /etc/inittab` and `reboot`.
