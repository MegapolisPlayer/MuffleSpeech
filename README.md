[![CC BY 4.0][cc-by-shield]][cc-by]

![MuffleSpeech Background](https://raw.githubusercontent.com/MegapolisPlayer/MuffleSpeech/main/background1MS.png)

# MuffleSpeech
a speech muffler

# WARNING
Some antiviruses might detect these programs as viruses. These are false positives.
This repository is not maintained anymore. Browse at your own risk.

# Welcome
Welcome to the MuffleSpeech project.
Originally developed as a prototype for a larger project, this project is basically a character changer.

# Usage
This project works as follows:

    You load a profile...

            ...input a string...
           
                     ...and you recieve a muffled output.
                    
That's basically it. For the syntax you will have to call HELP from the internal shell.

# Contents
This project includes all the source code. For the releases, check the releases tab. Development releases are usually only for Linux, but Releases not marked as dev releases are compatible with Windows.

# Releases
This is the last release. For reasoning, please check the release page for 2.0.0.

# Compiling
If you were to compile this application, both on Linux and Windows it is absolutely straight-forward, just compile like you compiling anything else.

If you are compiling for Windows on Linux - just don't forget to write the following arguments into the linker:

    -static;-static-libstdc++;-static-libgcc
    
This links the C++ standard library statically which **will** save you a lot of hassle.

I would also recommend some kind of IDE, since there are quite a few files and it is better when you don't have to link each and every one of them.

# Contributing
Feel free to contribute to this project! However, I would like to ask you to not commit directly to the main branch. Also if you were to contribute, don't forget to add your name in the `AppInfo` struct in the developer member variable.

# License
by MegapolisPlayer

This work is licensed under a
[Creative Commons Attribution 4.0 International License][cc-by].

# Notes and warnings
To say that this project is not optimized is an understatment. This was slapped together in a few days and is based off an older prototype which was written in under an hour. Obviously this is not optimized for maximum performace. This is actually one of the reasons I'm publishing this here, it's so that you - the community - can improve on this.

# Version History

**Current**   2.0.1          16.10.2022

**Past**      2.0.0,         13.10.2022

              1.1.0, (b5)    11.09.2022

              1.0.0, (b4)    25.08.2022
 
**Prototype** 0.0.0, (b1)    15.08.2022	

[![CC BY 4.0][cc-by-image]][cc-by]

[cc-by]: http://creativecommons.org/licenses/by/4.0/
[cc-by-image]: https://i.creativecommons.org/l/by/4.0/88x31.png
[cc-by-shield]: https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg
