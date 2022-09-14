[![CC BY 4.0][cc-by-shield]][cc-by]

![MuffleSpeech Background](https://raw.githubusercontent.com/MegapolisPlayer/MuffleSpeech/main/background1MS.png)

# MuffleSpeech
a speech muffler

# Welcome
Welcome to the MuffleSpeech project.
Originally developed as a prototype for a larger project, this project is basically a character changer.

# Usage
This project works as follows:

    You load a profile...

            ...input a string...
           
                     ...and you recieve a muffled output.
                    
That's basically it. For the syntax you will have to call _HELP from the internal shell.

    (_H) _HELP - display this menu
    (_R) _RELOAD - reload character map
    (_A) _ABOUT - about the application
    (_E, _Q) _EXIT or _QUIT - Exit application
	Any other string not beginning with _ will be muffled according to the current loaded profile.
	The commands in brackets are the shortened variation.

# Contents
This project includes all the source code. For the releases, check the releases tab. Development releases are usually only for Linux, but Releases not marked as dev releases are compatible with Windows.

# GUI
This project will, at some point, have a GUI. It, however, will be closed-source. It will still be free and published in this repository, but the code itself will be running on my custom closed-source framework.

# Releases
This project has (with some exceptions) a monthly release schedule. This rule doesn't apply to patches and bug-fix releases.

This project will NOT have a release in the following months:

	January (New Year, school ramping up again)
	
	June, July (Holidays)
	
	August (might sometimes, Holidays)

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
To say that this project is not optimized is an understatment. This was slapped together in a few days and is based off an older prototype which was written in under an hour. Obviously this is not optimized for maximum performace. This is actually one of the reasons i'm publishing this here, it's so that you - the community - can improve on this.

# Version History

**Upcoming**  1.2.0, approx. 10.10.2022

**Current**   1.1.0, (b5)    11.09.2022

**Past**      1.0.0, (b4)    25.08.2022

**Prototype** 0.0.0, (b0)    15.08.2022	

[![CC BY 4.0][cc-by-image]][cc-by]

[cc-by]: http://creativecommons.org/licenses/by/4.0/
[cc-by-image]: https://i.creativecommons.org/l/by/4.0/88x31.png
[cc-by-shield]: https://img.shields.io/badge/License-CC%20BY%204.0-lightgrey.svg
