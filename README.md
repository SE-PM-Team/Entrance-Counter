# Basic structure
Main branch is for the different versions. Only when a new version is finished, will main be updated.\
Development branch is for developing each version. This means that after you are finished with your ticketn (a task), you will push to this branch.\
For each ticket you create a new branch with the same ID as the issue. E.g. issue: Adding a new device #18; new branch: ticket-#18.\
Issues are small or large assignments and can be found in the "projects" tab (see navbar). 

# Develoment process with git commands
(only write the contents of the following two)\
"<something>" is required (type it without whitespaces)\
"[something]" is optional
## First steps
1) Open your prefered terminal
2) Move to the folder where you want to store your github repository
3) type "git clone git@github.com:SE-PM-Team/Entrance-Counter.git [your_repository_name]" in your terminal
4) Now you're done with the setup.

## Workflow
For the following processes you will always need to be in your local repository.
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
"git commit -m "briefly describe what you changed""\
Final step:\
"git push -u origin <branch name>"\


### Continue working with a ticket
Step 1:\
Update your local repository.\
"git pull origin master"\
Step 2:\
Do some coding.\
Step 3:\
"git add <file name>"\
"git commit -m "briefly describe what you changed"\
Final step:
"git push -u origin <branch name>"\


## Making a pull request
When you're done with your ticket you need to create a pull request to push it to the development branch.
Step 1:
synchronise your local repository to avoid merge conflicts.
"git pull origin master"
Step 2:
git 


# Useful github commands

# Useful terminal commands
## Linux commands
- "ls": list files, shows all the folders and files
- cd: change directory, used for moving between folders
  - "cd.." or "cd .." to go back once
  - "cd <directory_name>" to move into that folder
  - "cd~" or "cd ~" to move to your home of your disk drive
- "mkdir <directory_name>" stands for MaKe DIRectory
- rm: ReMove directoy or file
  - "rm -d <directory_name>" removes an empty directory
  - "rm -r <directory_name>" removes a directory and its contents
  - "rm <file_name>"
- "touch <file_name>" to create a file
- "cat > <file_name>" to create a file and immediately write in it, close and save file with "Ctrl+D"
- "clear": clears your terminal window
- arrow key up: select the previous command
## Windows commands
  
