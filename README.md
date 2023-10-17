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
Now copy the remote repository to your own local machine.\
"git clone git@github.com:SE-PM-Team/Entrance-Counter.git [your_repository_name]" (uses ssh key)

## Workflow
For the following processes you will always need to be in your local repository with your terminal.

### First time working with a ticket
Step 1:\
Choose a ticket of the next highest priority from the project tab, move the ticket to "in progress" and imform everyone that you will work on it.\
Step 2:\
Open your local github repository with your terminal.\
Step 3:\
Create and switch to a new branch.\
"git checkout -b <branch_name>" (use ticket-#number for branch_name)\
Step 4:\
Do some coding. \
Step 5:\
"git add <file_name>"\
"git commit -m 'briefly describe what you changed'"\
Final step:\
Now commit your changes and/or files to the branch.
"git push -u origin <branch_name>"

### Continue working with a ticket
Step 1:\
Update your local repository.\
"git pull origin master"\
Step 2:\
Do some coding.\
Step 3:\
"git add <file_name>"\
"git commit -m 'briefly describe what you changed'"\
Final step:\
"git push -u origin <branch_name>"


## Making a pull request
When you're done with your ticket you need to create a pull request to push it to the development branch.\
Step 1:\
synchronise your local repository to avoid merge conflicts.\
"git pull origin master"\
Step 2:\
Now create a pull request\
"git push"\
Step 3:\
Check if a pull request has been created on github. Wait for someone to check and confirm it.\
Step 4:\
Switch to the main branch\
"git checkout master"\
Step 5:\
After the pull request has been checked and confirmed, the main branch will be updated. This means you need to update your local repository again.\
"git pull"\
Final step:\
Delete the old branch locally once you're fully finished with it. This will not delete it remotely.\
"git branch -D <branch_name>"


## Solving merge conflicts
In the case of getting a merge conflict when trying to create a pull request you can do the following steps to resolve it:\
Step 1:\
"git pull origin master"\
Step 2:\
You now should have gotten some message about a failed merge. Now you need to fix the conflict and commit the result.\
To solve this you now need to open the file(s) with the merge conflict and choose what the correct changes are.\
In VS Code to choose your changes you would click on "Accept Current Change".\
Remember to save the changed file(s).\
Step 3:\
"git add <file_name>"\
"git commit -m 'merge conflict resolved'"\
Step 4:\
"git push"\
Step 5:\
Check if the pull request has been updated on github and inform others to check and confirm your request.\
Step 6:\
Switch to the master branch\
"git checkout master"\
Step 7:\
Update your local repository\
"git pull"\
Final step:\
"git branch -D <branch_name>"

## Useful github commands
- "git fetch": using this command you can see a preview of all changes that would happen if you would use "git pull"
- "git status":
- "-A":

## Github commands you should not use before discussing it
- "-f" or "--force": this will forcefully push to the remote repository in case merge conflicts (for "git push -f")
- "git reset <stage_ID>": this will reset the remote repository to a specific commit stage

# Useful terminal commands
- cd: change directory, used for moving between folders
  - "cd.." or "cd .." to go back once
  - "cd <directory_name>" to move into that folder
  - "cd~" or "cd ~" to move to your home of your disk drive
- "clear": clears your terminal window
- arrow key up: select the previous command

## Linux specific commands
- "ls": list files, shows all the folders and files
- "mkdir <directory_name>" stands for MaKe DIRectory
- rm: ReMove directoy or file
  - "rm -d <directory_name>" removes an empty directory
  - "rm -r <directory_name>" removes a directory and its contents
  - "rm <file_name>"
- "touch <file_name>" to create a file
- "cat > <file_name>" to create a file and immediately write in it, close and save file with "Ctrl+D"

## Windows commands

# Useful sources
Introduction to Git\
https://www.youtube.com/watch?v=92sycL8ij-U \
Working in a team using Git\
https://www.youtube.com/watch?v=RzYJvSnzlMk 

Github Workflow process using terminal commands\
https://www.youtube.com/watch?v=jhtbhSpV5YA  
