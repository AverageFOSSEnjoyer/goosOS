# goosOS
![goos](https://c.tenor.com/HpQzsDBu5QwAAAAC/goose-honk.gif)

### What is this?
This is just a personal educational project for me to learn more about the linux kernel structure.

### Why?
I'm really interested about low level programming like the linux kernel but unfortunately UIUC's ECE 391 isn't accessible for me yet so I decided to work on this project in the meantime.

### Get started
#### dependencies
```
binutils
lib32-glibc (name may differ depending on distro)
grub-legacy
xorriso
any qemu packages that contains i386
```
#### compile and run
```
make all    # this compiles all the necessary file into an .iso image
make run    # uses qemu to run the system
```

### Goals(subject to change):
- [x] Bootable - 05/16/2022
- [x] GDT - 05/17/2022
- [x] Interrupt - 05/18/2022
- [x] I/O - 05/19/2022
- [ ] Driver
- [ ] Paging
- [ ] Scheduling
- [ ] Network
- [ ] GUI
- [ ] Conversion to C