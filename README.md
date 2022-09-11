[![CC BY 4.0][cc-by-shield]][cc-by]

![MuffleSpeech Background](https://raw.githubusercontent.com/MegapolisPlayer/MuffleSpeech/main/background1MS.png)

# MuffleSpeech
a speech muffler

# Welcome
Welcome to the MuffleSpeech project.
Originally developed as a prototype for a larger project, this project is basically a character changer.

**Note:** Some antiviruses (most notably Windows Defender) flag this software as a trojan. For information: This program does not contact any IPs.

# Usage
This project works as follows:

    You load a profile...

            ...input a string...
           
                     ...and you recieve a muffled output.
                    
That's basically it. For the syntax you will have to call _HELP from the internal shell.

    (_E, _Q) _EXIT or _QUIT - Exit application
	(_H) _HELP - display this menu
    (_R) _RELOAD - reload character map
	(_A) _ABOUT - about the application
	Any other string not beginning with _ will be muffled according to the current loaded profile.
	The commands in brackets is the shortened form.

# Contents
This project includes all the source code. For the releases, check the releases tab. Development releases are usually only for Linux, but Releases not marked as dev releases are compatible with Windows.

# GUI
This project will, at some point, have a GUI. It, however, will be closed-source. It will still be free and published in this repository, but the code itself will be running on my custom closed-source framework.

# Releases
This project does not have any release schedule - if I find a bug I usually try to fix as soon as possible.

# Compiling
If you were to compile this application, on Linux it is absolutely straight-forward, just compile like you compiling anything else.

If you are compiling for Windows on Linux - just don't forget to write the following arguments into the linker:

    -static;-static-libstdc++;-static-libgcc
    
This links the C++ standard library statically which **will** save you a lot of hassle.

# License
by MegapolisPlayer


This work is licensed under a
[Creative Commons Attribution 4.0 International License][cc-by].

# Notes and warnings
To say that this project is not optimized is an understatment. This was slapped together in a few days and is based off an older prototype which was written in under an hour. Obviously this is not optimized for maximum performace. This is actually one of the reasons i'm publishing this here, it's so that you - the community - can improve on this.

[![CC BY 4.0][cc-by-image]][cc-by]

[cc-by]: http://creativecommons.org/licenses/by/4.0/
[cc-by-image]: https://i.creativecommons.org/l/by/4.0/88x31.png
[cc-by-shield]: https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg
