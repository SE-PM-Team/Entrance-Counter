# Basic structure
Main branch is for the different versions. Only when a new version is finished, will main be updated.\
Development branch is for developing each version. This means that after you are finished with your ticket (a task), you will push to this branch.\
For each ticket you create a new branch with the same ID as the issue. E.g. issue: Adding a new device #18; new branch: ticket-#18.\
Issues are small or large assignments and can be found in the "projects" tab (see navbar). 


# Develoment process with git commands
(only write the contents of the following two)\
< something > is required\
[something] is optional

## First steps
Step 1:\
Open your prefered terminal.\
Step 2:\
Move to the folder where you want to store your github repository using "cd".\
Final step:\
Now copy the remote repository to your own local machine.
```
git clone git@github.com:SE-PM-Team/Entrance-Counter.git [your_preferred_repository_name]
```
(uses ssh key)

## Workflow
For the following processes you will always need to be in your local repository with your terminal.

### First time working with a ticket
Step 1:\
Choose a ticket of the next highest priority from the project tab, move the ticket to "in progress" and inform everyone that you will work on it.\
Step 2:\
Open your local github repository with your terminal.\
Step 3:\
Create and switch to a new branch (use ticket-#number for branch_name).
```
git checkout -b <ticket_branch_name>
```
Step 4:\
Do some coding. \
Step 5:
If you created a new file or want to manually choose the files that should be added:
```
git add <file_name>
```
otherwise you can also use the following if you want to add all the files you updated (this does not add newly created files):
```
git add -u
```
optional command to check if you added the correct files:
```
git status
```
```
git commit -m 'briefly describe what you changed'
```
Final step:\
Now push your changes and/or newly created files to the branch.
```
git push -u origin <branch_name>
```

### Continue working with a ticket
Step 1:\
Update your local repository.
```
git pull origin development
```
Step 2:\
Do some coding.\
Step 3:
If you created a new file or want to manually choose the files that should be added:
```
git add <file_name>
```
otherwise you can also use the following if you want to add all the files you updated (this does not add newly created files):
```
git add -u
```
optional command to check if you added the correct files:
```
git status
```
```
git commit -m 'briefly describe what you changed'
```
Final step:
```
git push -u origin <ticket_branch_name>
```


## Making a pull request
When you're done with your ticket you need to create a pull request to push it to the development branch.\
Step 1:
Check if you're in the correct ticket branch.
```
git checkout <ticket_branch_name>
```
Step 2:\
synchronise your local repository to avoid merge conflicts.
```
git pull origin development
```
Step 3:\
Check for conflicts and resolve them if there are any.
```
git rebase development
```
Step 4:\
Now push the ticket branch to the development branch.
```
git push origin development
```
Step 5:\
Manually creating pull request
Open the github repository in the browser and manually create the pull request.

Step 6:
After the pull request has been checked and confirmed, the main branch will be updated. This means you need to update your local repository again.
```
git pull origin development
```
Final step:\
Delete the old branch locally once you're fully finished with it. This will not delete it remotely.
```
git branch -d <ticket_branch_name>
```


## Solving merge conflicts
In the case of getting a merge conflict when trying to create a pull request you can do the following steps to resolve it:\
Step 1:
```
git pull origin development
```
Step 2:\
You now should have gotten some message about a failed merge. Now you need to fix the conflict and commit the result.\
To solve this you now need to open the file(s) with the merge conflict and choose what the correct changes are.\
In VS Code to choose your changes you would click on "Accept Current Change".\
Remember to save the changed file(s).\
Step 3:
If you created a new file or want to manually choose the files that should be added:
```
git add <file_name>
```
otherwise you can also use the following if you want to add all the files you updated (this does not add newly created files):
```
git add -u
```
optional command to check if you added the correct files:
```
git status
```
```
git commit -m 'merge conflict resolved'
```
Step 4:
```
git push origin development
```
Step 5:\
Check if the pull request has been updated on github and inform others to check and confirm your pull request.\
Step 6:\
After someone confirmed your pull request switch to the development branch.
```
git checkout development
```
Step 7:\
Update your local repository
```
git pull origin development
```
Final step:\
Delete the old branch locally once you're fully finished with it. This will not delete it remotely.
```
git branch -d <ticket_branch_name>
```

## Useful github commands
- "git fetch": using this command you can see a preview of all changes that would happen if you would use "git pull"
- "git status": shows the staged files (use this command if you want to ensure that you added the correct files)
- "git log": shows the log of your commits
- "git branch": shows what branches there are, the branch with a "*" is the one you're currently in
  - "git branch -d": only deletes branch if branch is already merged with the one you're currently in (don't use "-D" since it stands for a forced deletion) 
- git "checkout": switches to another branch
  - "git checkout -b": creates a new branch
- "git add": adds files to the git tracker
  - "git add -u": adds all updated files
  - "git add <file_name>": only adds the mentioned file
- "git commit": stages all added files, so they can be pushed later
  - "git commit -m": adds a commit message
  - "git commit -a": adds all files (not recommended but can be used to skip the "git add" command) 
- "git push": pushes all staged files to the git repository

## Github commands you should not use before discussing it
- "-f" or "--force": this will forcefully push to the remote repository in case merge conflicts (for "git push -f")
- "git reset <stage_ID>": this will reset the remote repository to a specific commit stage

# Useful terminal commands
- cd: change directory, used for moving between folders
  - "cd.." or "cd .." to go back once
  - "cd <directory_name>" to move into that folder
  - "cd~" or "cd ~" to move to your home of your disk drive
- "clear": clears your terminal window (you can see the previous contents by scrolling up)
- arrow key up: select the previous command

## Linux specific commands
- "ls": list files, shows all the folders and files
- "mkdir <directory_name>": stands for MaKe DIRectory
- "rm": ReMove directoy or file
  - "rm -d <directory_name>": removes an empty directory
  - "rm -r <directory_name>": removes a directory and its contents
  - "rm <file_name>": removes a single file
- "touch <file_name>": creates a file
- "cat > <file_name>": creates a file and immediately write in it, close and save file with "Ctrl+D"

## Windows commands
- "dir": list files, shows all the folders and files
- "mkdir <directory_name>": stands for MaKe DIRectory
- "del": delete files
  - "rmdir" or "rd" – ReMove Directories
  - "rmdir /s /q <directory_name>" – Remove a directory and its content
  -"del <file_name>" – deliting file
- "type nul > <file_name>": to create a file
- "echo. > <file_name>"
-"echo Your text goes here. >> <file_name>": to create a file and immediately write in it

# Useful sources
Introduction to Git\
https://www.youtube.com/watch?v=92sycL8ij-U \
Working in a team using Git\
https://www.youtube.com/watch?v=RzYJvSnzlMk 

Github Workflow process using terminal commands\
https://www.youtube.com/watch?v=jhtbhSpV5YA  
