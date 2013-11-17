project3_cs141_fall
===================

DNA Database Search Project

Isaac Long isaacglong@gmail.com 1-408-887-1628

Zachary Sells zsell001@ucr.edu 1-626-242-3802(I did it mom!)
(Try inserting your contact info here as a test!)

Here is my ultra mini tutorial on how to use Git, with some links for 
downloading and installing Git and the Git GUI.

Getting Set Up
--------------

First, download and install the latest version of Git. This isn't the GUI,
but this will enable you to do anything and everything with Git from the
command line. I do not have experience with the Windows command line, but
the Git commands may be slightly different.

http://git-scm.com/downloads

Next, download a Git GUI. This simplifies (and visualizes) some of the more 
tedious parts of the commands you would have to do via the command line.

(Download for your OS) http://git-scm.com/downloads/guis

I already have a repository made for our projecti, and if you are reading
this you are already a contributer. The following instructions are for a 
linux terminal.

Now, make a new directory in a location of your choice that you will use
for our shared project 3 files and then navigate so that you are inside
this directory. First we set some configs for git.  

$ git config --global user.name "Your Legal Name Here"

^This can be any name you want, does not need to match anything on your 
github account 

$ git config --global user.email "youremail@youremail.com"

^This email needs to match the email you used when you signed up for a 
github account

There are some other configs you can set in this same manner, like a
default text editor, but for now just stick with these.

$ git init

^This command will initialize the current directory to a local Git 
repository (this should be the directory you made/chose).

$ git remote add origin https://github.com/username/project3_cs141_fall

^I am actually not sure if 'username' will be my username (isaaclong) or 
your Github username. This just needs to match the url you see when looking
at the repository online on Github.com. This command just connects your 
directory to the online project repository project3_cs141_fall, so all 
pushes or pulls you do will be to and from this online repository. It may
ask you for your username/password credentials when you run this command.

$ git remote -v

^This will confirm that 'origin' is set to the address you provided for
fetches and pushes.

Sync Your Directory & Learn to Push
----------------------------------- 

At this point you can switch over to the GUI if you want, it (should) 
recognize that you have a local repository that is now connected with the
online repository on Github.com. The GUI should ask for your login
information initially and then either find your activated directory 
automatically or give you the ability to specify which directory you 'git 
init'-ed.

First we need to 'pull' in order to sync anything already in the online 
repository to your directory. In the GUI it should be something relatively
simple, on mac it is command-shift-P to Pull. The Pull command basically
syncs all files in the online repository and updates your local directory
files. Below is the terminal command you would use to do it.

$ git pull origin master

^Origin is the remote address specified earlier, master is the branch name.

After doing this pull you should have this README.md file in your
directory. Now, try opening it and adding your contact information at the 
top, saving it, and closing it again. Now we can try to push the changes 
and sync back to the online repository. The 'stages' for a push are as 
follows:
 
$ git add someFilename

^This file will now be tracked by Git

$ git commit -m "Insert commit message here" 

^Takes a snapshot of your directory files to prepare for a push. A -a arg 
can be provided to commit so you don't have to 'add' every file each time.

$ git push origin master 

^Pushes any changes to the files in the directory, that you tracked, to 
the online repository). Origin is the address of the online repository,
master is the branch.

So the basic order of operations for pushes/updating our shared files
online is:

* Make some changes to the files
* git add - stages changes for commit
* git commit - commits staged changes locally
* git push - pushes committed changes to remote address we specified

This probably seems like a lot but it takes literally about 5 seconds once
you get the hang of it. The more general order of operations is:

* Call pull so that your directory files will be updated with the most
recent changes in our shared files online
* Make any changes you want
* Push the changes back to the online files

Doing all this in the GUI is even faster, as after you make changes to 
files in your directory, the sync/push can be done in one click. Pulls/
syncs can also be done just as easily. Pushes and Pulls can also specify
branches (other than master, which is the main branch). We can talk about
branches together when we meet next.
